# Chess Game in OpenGL

A fully functional chess game implementation using OpenGL and C++ with Object-Oriented Programming principles. The game features a 2D rendered chessboard with interactive gameplay, move validation, and check detection.

**Prepared by:** Azmal Karim

## Game Description

This is a classic chess game where two players take turns moving pieces on an 8x8 board. The objective is to checkmate the opponent's king by putting it in a position where it cannot escape capture.

### Visual Indicators

The game provides clear visual feedback for player actions:

- **Selected Piece**: Greenish border around the square containing the selected piece
- **Available Moves**: Green circles indicating valid move positions
- **Attack Moves**: Orange border highlighting squares where opponent pieces can be captured
- **Check Warning**: Red border around the king when it's in check

### Game Rules & Validation

- Players cannot make moves that would put their own king in check
- If a player's king is in check, they must make a move that removes the check
- All standard chess piece movements are implemented (pawn, rook, knight, bishop, queen, king)
- Automatic pawn promotion to queen when reaching the last rank

### Features Not Implemented

- Stalemate detection
- Castling (kingside and queenside)
- Pawn promotion choice (automatically promotes to Queen)

## How to Run

### Clone the Repository
```bash
git clone https://github.com/AzmalSirat/2D-Chess-OpenGL
cd chess-project
```

### Windows (with OpenGL installed)
```bash
./run.sh
```

### Linux (with OpenGL installed)
```bash
g++ chess.cpp -o chess -lglut -lGLU -lGL && ./chess
```


## Gameplay

1. Click on a piece to select it (greenish border will appear)
2. Available moves will be shown as green circles
3. Squares with opponent pieces that can be captured will show orange borders
4. Click on a highlighted square to move the selected piece
5. The game alternates between white and black players
6. When a king is in check, a red border appears around it
7. The game ends when checkmate is achieved

## Demo

Youtube Link: [Demo Video](https://github.com/AzmalSirat)

## Requirements

- OpenGL libraries (GL, GLU, GLUT)
- C++ compiler (g++)
- X11 server (for GUI display)

## Technologies Used

- **C++** for core game logic with **Object-Oriented Programming** design
  - Classes for different chess pieces (Pawn, Rook, Knight, Bishop, Queen, King)
  - Inheritance and polymorphism for piece behavior
  - Encapsulation of game state and move validation
- **OpenGL** for 3D graphics rendering
- **GLUT** for window management and input handling
- **Docker** for containerized deployment

---

## Author

<div align="center">

**Developed by [Azmal Karim](https://github.com/AzmalSirat)**

*CSE, BUET*


</div>

---
