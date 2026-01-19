/**
 * @file main.c
 * @author Ladipo Ipadeola
 * @brief Entry point for the MedQueue application.
 *
 * This file contains the main function which initializes the ncurses interface,
 * manages the main menu loop, and handles user input to drive the application logic.
 * @version 1.0
 * @date 19-01-2026
 * @copyright Copyright (c) 2026
 */

#include "util.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  Patient_Queue Q = {0};

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
  int height = 20, width = 55;
  int start_y = (LINES - height) / 2, start_x = (COLS - width) / 2;

  WINDOW *menu_win = newwin(height, width, start_y, start_x);
  keypad(menu_win, TRUE);

  while (1)
  {
    werase(menu_win);
    box(menu_win, 0, 0);
    mvwprintw(menu_win, 2, (width - 35) / 2, "====== MedQueue Clinic System ======");
    mvwhline(menu_win, 3, 2, ACS_HLINE, width - 4);
    for (int i = 0; i < n_choices; i++)
    {
      if (i == highlight)
        wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, 5 + (i * 2), (width - strlen(choices[i])) / 2, "%s",
                choices[i]);
      wattroff(menu_win, A_REVERSE);
    }
    wrefresh(menu_win);

    int c = wgetch(menu_win);
    if (c == 10)
    {
      if (highlight == 0)
      {
        register_patient(menu_win, width, &Q, false);
      }
      else if (highlight == 1)
      {
        serving_patient(menu_win, width, &Q);
      }
      else if (highlight == 2)
      {
        // TODO Emergency Admit
        register_patient(menu_win, width, &Q, true);
      }
      else if (highlight == 3)
      {
        // TODO imp view queue
        view_line(menu_win, width, &Q);
      }
      else if (highlight == 4)
      {
        break; // Exit
      }
    }
    else if (c == KEY_UP)
    {
      highlight = (highlight == 0) ? n_choices - 1 : highlight - 1;
    }
    else if (c == KEY_DOWN)
    {
      highlight = (highlight == n_choices - 1) ? 0 : highlight + 1;
    }
  }

  endwin();
  return 0;
}
