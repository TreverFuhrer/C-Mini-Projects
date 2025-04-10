# 💻 UW-Milwaukee CS Projects – C Programming Assignments

Welcome to my **C Programming Homework Projects** repository!  
These mini-projects were completed as part of my coursework for **Computer Science at UW-Milwaukee** during the Spring 2025 semester. Each assignment focuses on a different foundational concept in C, helping build core programming skills through hands-on implementation.

---

## 🐳 Dockerized Development Environment

To ensure consistency and compatibility across different machines and instructor environments, I used **Docker** throughout the development of all assignments. This approach allowed me to:
- Run code in a clean, isolated Linux-based container 🐧
- Standardize compiler versions, tools, and dependencies
- Ensure reproducible results regardless of the host system
- Simplify testing and grading for instructors ✅

Every assignment was developed and tested within a containerized environment using a custom `Dockerfile` that mimics the course's expected runtime. This guarantees the code behaves the same way for everyone — no "works on my machine" issues here!

---

## 🧭 HW1: Path Finder

**Topics Covered:**
- 1D & 2D Arrays  
- Function Definitions  
- Linking Multiple C Files  

**What It Does:**
Frodo embarks on a journey through a dangerous jungle grid filled with obstacles like spiders, werewolves, and swamps 🕷️🐺. This program:
- Reads and stores a jungle grid from user input.
- Counts and prints stats for each obstacle.
- Determines a path from the top-left corner to the bottom-right corner, using only **safe zones (0s)**.
- Prints directions (right, bottom) or "die" if no path exists.

**What I Learned:**
- Mastery of multi-dimensional arrays and nested loops
- Efficient data processing without `if/else` or `switch` statements
- Pathfinding logic based on directional rules

---

## 📦 HW2: Static and Dynamic Stack

**Topics Covered:**
- Static vs. Dynamic Memory  
- Stack Operations (Push/Pop)  
- Pointers & `malloc` / `realloc` / `free`  

**What It Does:**
Implements both a **fixed-size stack** and a **dynamic stack** that resizes itself when needed:
- Validates stack capacity before operations
- Uses dynamic memory to expand stack size on the fly
- Ensures no memory leaks or dangling pointers

**What I Learned:**
- Manual memory management in C
- Error handling for allocation failure
- Using pointer arithmetic and addressing stack-based data structures efficiently

---

## 🔐 HW3: Simple Text Encryptor

**Topics Covered:**
- Manual String Manipulation  
- Character Arithmetic  
- Dynamic Memory Allocation  

**What It Does:**
A custom Caesar cipher that encrypts/decrypts messages based on the **length of the message**.  
- Each letter is shifted by the total number of characters (including spaces).
- Handles lowercase and uppercase letters separately.
- Leaves non-letter characters unchanged.

**What I Learned:**
- Implementing algorithms without relying on string.h or ctype.h
- ASCII manipulation for custom logic
- How encryption works at a basic level

---

## 🔍 HW4: Grep Lite

**Topics Covered:**
- File I/O in C  
- String Searching  
- Command-Line Arguments & Flags  

**What It Does:**
A simplified version of the `grep` command:
- Takes a pattern and filename as input
- Optionally accepts `-i` (case-insensitive) and/or `-n` (line numbers) flags
- Outputs all matching lines from the file
- Handles input validation and command-line errors gracefully

**What I Learned:**
- Parsing command-line arguments
- Reading files line-by-line and matching substrings
- Emulating real-world Unix utilities in C

---

## 📚 Summary of Skills Gained

✅ Array manipulation  
✅ File and string handling  
✅ Memory allocation and pointers  
✅ Command-line interface design  
✅ Modular coding with `.h`, `.c`, and Makefiles  
✅ Strong C syntax and logic development  
✅ Docker-based development & testing environments

---

## ⚙️ How to Run

Each homework contains a `Makefile`. To compile and run locally:

```bash
make        # Compiles the code
./out       # or ./mystack / ./mygrep depending on the project