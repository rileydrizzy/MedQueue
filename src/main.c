#include "util.h"
#include "def.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

// Global variable
Patient* Head;
Patient* Tail;

/** === MedQueue Clinic System ===
1. Register Patient
2. Serve Patient
3. Emergency Admit
4. View Line
5. Exit

Enter choice: 1

Enter Patient Name: Sarah
Enter Patient Age: 25
[Success] Sarah added to the line.

Enter choice: 2
NOW Serving Patient Sarah

Enter choice: 3
Emergeny Admit
Enter Patient Name: Ladi
Enter Patient Age: 15
[Success] Ladi added to the line.

Enter choice: 4

Enter choice: 5
Close program

**/

void menu_display(void) {
  initscr();
  mvprintw();
  endwin();
  return;
}

int main(void) {
  menu_display();
  return EXIT_SUCCESS;
}
