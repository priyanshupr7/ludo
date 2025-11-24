#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PLAYERS 4
#define TOKENS 4
#define TRACK 52
#define HOME_START 52
#define HOME_END 57
#define FINISHED 100

// Player colors
const char *names[] = { "RED", "GREEN", "YELLOW", "BLUE" };

// Token structure
typedef struct {
    int position;   // -1 = in base, 0–51 = board, 52–57 = home path, 100 = finished
} Token;

// Player structure
typedef struct {
    Token token[TOKENS];
    int finishedTokens;
} Player;

Player players[PLAYERS];

// Dice roll
int rollDice() {
    return (rand() % 6) + 1;
}

// Get absolute board position accounting for player start offset
int globalPos(int player, int pos) {
    if (pos < 0 || pos >= TRACK) return pos;
    return (pos + (player * 13)) % TRACK;
}

// Cut opponent tokens (only on main track, not home path)
void checkCut(int player, int tkn) {
    int pos = players[player].token[tkn].position;
    if (pos < 0 || pos >= TRACK) return;  // Only cut on main track

    int gpos = globalPos(player, pos);

    for (int p = 0; p < PLAYERS; p++) {
        if (p == player) continue;

        for (int t = 0; t < TOKENS; t++) {
            int opos = players[p].token[t].position;
            if (opos < 0 || opos >= TRACK) continue;

            int ogpos = globalPos(p, opos);

            if (ogpos == gpos) {
                printf("  🗡 %s cuts %s's token!\n", names[player], names[p]);
                players[p].token[t].position = -1; // Send back to base
            }
        }
    }
}

// Move token
int moveToken(int player, int tkn, int dice) {
    Token *tok = &players[player].token[tkn];

    if (tok->position == -1) {
        if (dice == 6) {
            tok->position = 0;
            printf("  %s token leaves base!\n", names[player]);
            return 1;
        } else {
            printf("  Need 6 to leave base.\n");
            return 0;
        }
    } else if (tok->position >= 0 && tok->position < TRACK) {
        // On main track
        int newpos = tok->position + dice;
        if (newpos > TRACK) {
            printf("  Move exceeds track, cannot move.\n");
            return 0;
        }
        tok->position = newpos;
        if (newpos == TRACK) {
            tok->position = HOME_START;  // Enter home path
            printf("  %s token enters home path!\n", names[player]);
        }
        return 1;
    } else if (tok->position >= HOME_START && tok->position <= HOME_END) {
        // On home path
        int newpos = tok->position + dice;
        if (newpos > HOME_END + 1) {  // HOME_END +1 to allow finishing
            printf("  Move exceeds home path, cannot move.\n");
            return 0;
        }
        tok->position = newpos;
        if (newpos == HOME_END + 1) {
            tok->position = FINISHED;
            players[player].finishedTokens++;
            printf("  🎉 Token reached HOME for %s!\n", names[player]);
        }
        return 1;
    } else if (tok->position == FINISHED) {
        printf("  Token already finished.\n");
        return 0;
    }
    return 0;
}

// Display board info
void displayState() {
    printf("\n----------------------------\n");
    for (int p = 0; p < PLAYERS; p++) {
        printf("%s: ", names[p]);
        for (int t = 0; t < TOKENS; t++) {
            int pos = players[p].token[t].position;
            if (pos == -1) printf("B ");
            else if (pos == FINISHED) printf("H ");
            else if (pos >= HOME_START && pos <= HOME_END) printf("h%d ", pos - HOME_START + 1);
            else printf("%d ", globalPos(p, pos));
        }
        printf("\n");
    }
    printf("----------------------------\n");
}

// Game entry point
int main() {
    srand(time(NULL));

    // Initialize all tokens to base
    for (int p = 0; p < PLAYERS; p++) {
        for (int t = 0; t < TOKENS; t++) {
            players[p].token[t].position = -1;
        }
        players[p].finishedTokens = 0;
    }

    int turn = 0;

    printf("\n=== LUDO GAME (Console C Version) ===\n");

    while (1) {
        displayState();

        printf("\n%s's turn. Press ENTER to roll dice...", names[turn]);
        getchar();

        int dice = rollDice();
        printf("Dice rolled: %d\n", dice);

        // Check win
        if (players[turn].finishedTokens == TOKENS) {
            printf("\n🏆 %s WINS THE GAME!\n", names[turn]);
            break;
        }

        printf("Select token to move (0-3): ");
        int tkn;
        scanf("%d", &tkn);
        getchar();

        if (tkn < 0 || tkn >= TOKENS) {
            printf("Invalid token.\n");
            continue;
        }

        if (moveToken(turn, tkn, dice)) {
            checkCut(turn, tkn);
        }

        if (dice != 6)
            turn = (turn + 1) % PLAYERS;
    }

    return 0;
}
