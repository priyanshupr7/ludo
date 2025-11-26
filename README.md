# 🎲 Ludo Game – C Console Edition

A simple yet engaging console-based implementation of the classic **Ludo board game**, written entirely in C. This version supports **4 players**, each with **4 tokens**, and includes all core mechanics such as dice rolling, token movement, cutting, and reaching home.

---

## 🚀 Features

- **4-player gameplay** (RED, GREEN, YELLOW, BLUE)
- **Random dice system** using C’s `rand()`
- **Token cutting** – land on an opponent to send them back to base
- **Home path and finishing logic**
- **Turn-based flow** with extra turns on rolling a 6
- Lightweight, portable, and beginner-friendly C code

---

## 📁 Project Structure

ludo.c # Main game source code
└── README.md # Documentation file
---

## 🧠 How the Game Works

### 🎮 Turn Sequence
1. Player presses **ENTER** to roll the dice.  
2. Dice result appears.  
3. Player selects a token (0–3).  
4. If dice = **6**, the same player gets another turn.

---

### 🧱 Token Position States

| State | Meaning |
|-------|----------|
| -1 | Token in base |
| 0–51 | On the main board |
| 52–57 | On the player’s home path |
| 100 | Token has reached home |

---

## ⚔ Cutting Rules

If a player lands on a tile currently occupied by another player’s token:
- Opponent token is **sent back to base**.
- A cut message is displayed in the console.

---

## 🏆 Winning Condition

A player wins after **all 4 tokens** reach home.

---
![Ludo Screenshot](https://github.com/priyanshupr7/ludo/blob/274639ef0647c113bc085a2784e9af2033e3e676/Screenshot%202025-11-26%20151143.png?raw=true)


## 🛠 Compilation & Running

### Compile:
```bash
gcc ludo.c -o ludo
