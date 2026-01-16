#include <form.h>
#include <menu.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void register_patient(WINDOW *win, int width, int height) {
  char name[50];
  int age;

  // 1. Clear the inside of the existing box
  werase(win);
  box(win, 0, 0);
  wattron(win, A_BOLD);
  mvwprintw(win, 2, (width - 16) / 2, "REGISTER PATIENT");
  wattroff(win, A_BOLD);
  mvwhline(win, 3, 2, ACS_HLINE, width - 4);

  // 2. Enable typing visibility
  echo();
  curs_set(1); // Show cursor for typing

  mvwprintw(win, 5, 4, "Enter Patient Name: ");
  wgetnstr(win, name, 49); // Safe input for strings

  mvwprintw(win, 7, 4, "Enter Patient Age: ");
  wrefresh(win);

  // Using scanw style for age
  char age_str[10];
  wgetnstr(win, age_str, 9);
  age = atoi(age_str);

  // 3. Success Message
  noecho();
  curs_set(0);                          // Hide cursor again
  wattron(win, COLOR_PAIR(1) | A_BOLD); // Assuming color 1 is green
  mvwprintw(win, 10, (width - (18 + strlen(name))) / 2,
            "[Success] %s added to the line.", name);
  wattroff(win, COLOR_PAIR(1) | A_BOLD);

  mvwprintw(win, 12, (width - 25) / 2, "Press any key to return...");
  wrefresh(win);
  wgetch(win); // Wait for user to read success message
}

int main() {
  initscr();
  start_color();
  noecho();
  cbreak();
  curs_set(0);

  // Initialize a green color pair for success messages
  init_pair(1, COLOR_GREEN, COLOR_BLACK);

  const char *choices[] = {"1. Register Patient", "2. Serve Patient",
                           "3. Emergency Admit", "4. View Line", "5. Exit"};
  int n_choices = 5, highlight = 0;
  int height = 15, width = 50;
  int start_y = (LINES - height) / 2, start_x = (COLS - width) / 2;

  WINDOW *menu_win = newwin(height, width, start_y, start_x);
  keypad(menu_win, TRUE);

  while (1) {
    // (Render Main Menu Logic - same as before)
    werase(menu_win);
    box(menu_win, 0, 0);
    mvwprintw(menu_win, 2, (width - 26) / 2, "=== MedQueue Clinic System ===");
    for (int i = 0; i < n_choices; i++) {
      if (i == highlight)
        wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, 5 + (i * 2), (width - strlen(choices[i])) / 2, "%s",
                choices[i]);
      wattroff(menu_win, A_REVERSE);
    }
    wrefresh(menu_win);

    int c = wgetch(menu_win);
    if (c == 10) { // Enter Key
      if (highlight == 0) {
        register_patient(menu_win, width, height);
      } else if (highlight == 4) {
        break; // Exit
      }
    } else if (c == KEY_UP) {
      highlight = (highlight == 0) ? n_choices - 1 : highlight - 1;
    } else if (c == KEY_DOWN) {
      highlight = (highlight == n_choices - 1) ? 0 : highlight + 1;
    }
  }

  endwin();
  return 0;
}