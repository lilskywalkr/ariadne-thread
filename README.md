# Ariadne Thread 🧵
Ariadne's Thread is a simple C program that loads a maze from a text file, searches for a path from the start ('a') to the end ('b') point, and prints the solution if a path exists.  
It uses a recursive depth-first search (DFS) strategy to navigate through the maze.

---

## 📂 Project Structure

- **`main()`** — Loads the maze, locates start ('a') and end ('b') points, solves the maze, and displays the result.
- **`load_maze()`** — Reads the maze from a file and validates its structure.
- **`path_finding()`** — Recursively searches for a path through the maze.
- **`maze_size()`** — Calculates the width and height of the maze.
- **`solve_maze()`** — Prepares and starts the pathfinding process.
- **`free_maze()`** — Frees dynamically allocated memory for the maze.

---

## 📜 Requirements
- GCC Compiler
- Standard C libraries (`stdio.h`, `stdlib.h`, `string.h`)

---

## 🛠️ Compilation and Usage

```bash
gcc -o main main.c
./main
```

The program will prompt:

```
Enter filename:
```

Provide the **name of the file** containing your maze (must be in the same directory or give the full path).

---

## 🧩 Maze Format

- Must be a **rectangular grid** (all rows same length).
- Must contain exactly **one** `'a'` (start point) and **one** `'b'` (end point).
- Walls are marked with `'#'`.
- Free spaces are marked with `' '` (space character).

Example:

```
Enter filename: maze.txt⏎
###################
#       #  *******#
# ### ### #*#####*#
#   #     #***#***#
### #########*#*###
#     #*******#*# #
#######*#######*# #
#b******#*******# #
#########*####### #
#   #*****#a****  #
# # #*#########*###
# # #*#*******#***#
### #*#*#####*###*#
#   #***#   #***#*#
# ####### #####*#*#
#              ***#
###################
```

---

## ⚡ Program Behavior

- If the file is missing, corrupted, or has an invalid format, the program will output an error.
- If a path is found, the maze will be printed with the path marked by `'*'`.
- If no path is found, it will notify you.

---

## 🧹 Memory Management

All allocated memory for the maze is properly freed before program termination to prevent memory leaks.

---

## 🐛 Error Codes
| Code | Meaning |
|-----|--------|
| 4   | Couldn't open the file |
| 6   | File corrupted (invalid maze) |
| 8   | Failed to allocate memory |
