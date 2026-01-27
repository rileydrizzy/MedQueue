# MedQueue Clinic System

## Overview
MedQueue is a robust, terminal-based patient management system developed in C. It utilizes the `ncurses` library to provide an interactive Text User Interface (TUI) for clinic staff to manage patient queues efficiently. The system handles standard patient registration, emergency admissions, and patient service flow using a dynamic linked-list data structure.

## Features
*   **Register Patient:** Standard enqueue operation to add new patients to the end of the waiting line. Captures Name, Age, and assigns a unique ID.
*   **Serve Patient:** Dequeues the next patient in line, assigning them to a randomized examination room (A-E).
*   **Emergency Admit:** Priority insertion that places critical patients at the very front of the queue, bypassing the standard waitlist.
*   **View Line:** Displays the current queue of waiting patients with pagination support for long lists.
*   **Interactive Interface:** User-friendly menu navigation using arrow keys.

## Prerequisites
To build and run this project, you need a C compiler (GCC recommended) and the ncurses library installed on your system.

### Linux (Debian/Ubuntu)
```bash
sudo apt update
sudo apt install build-essential libncurses-dev
```

### macOS
```bash
brew install ncurses
```

## Compilation
You can compile the project using `gcc` from the project root directory:

```bash
gcc src/main.c src/util.c -o medqueue -lncurses
```
or making use of the Makefile, and running the make program
```bash
make
```

## Usage
1.  **Run the application:**
    ```bash
    ./medqueue
    ```

2.  **Navigation:**
    *   Use the **UP** and **DOWN** arrow keys to navigate the main menu.
    *   Press **ENTER** to select an option.

3.  **Operations:**
    *   Follow the on-screen prompts to enter patient details.
    *   In the "View Line" screen, use **'N'** to view the next page of patients or **'Q'** to return to the main menu.

## Project Structure
*   `src/main.c`: Entry point of the application. Handles the main menu loop and initialization.
*   `src/util.c`: Implementation of core logic, including linked list operations and UI rendering functions.
*   `src/util.h`: Header file defining data structures (`Patient_Node`, `Patient_Queue`) and function prototypes.

