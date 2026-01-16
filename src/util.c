#include "util.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void get_patient_detatil(void)

typedef struct {
  char *First_Name;
  char *Last_Name;
  int Age;
  struct Patient_Node *next_patient;
} Patient_Node;

extern Patient_Node *HEAD;
extern Patient_Node *TAIL;

Patient_Node *alloc_patient(void) {

  if (HEAD == NULL) {
    HEAD = &Patient;
    TAIL = &Patient;
    return Patient;

  } else {
    TAIL->next_patient = &Patient;
    TAIL = &Patient;
  }
  return Patient;
}

void register_patient(WINDOW *win, int width, int height) {
          alloc_patient();

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
  curs_set(0);
  wattron(win, COLOR_PAIR(1) | A_BOLD); // Assuming color 1 is green
  mvwprintw(win, 10, (width - (18 + strlen(name))) / 2,
            "[Success] %s added to the line.", name);
  wattroff(win, COLOR_PAIR(1) | A_BOLD);

  mvwprintw(win, 12, (width - 25) / 2, "Press any key to return...");
  wrefresh(win);
  wgetch(win); // Wait for user to read success message
}

void serving_patient(WINDOW *win, int width, int height) {
  werase(win);
  box(win, 0, 0);
  wattron(win, A_BOLD);
  mvwprintw(win, 2, (width - 16) / 2, "NOW SERVING");
  wattroff(win, A_BOLD);
  mvwhline(win, 3, 2, ACS_HLINE, width - 4);
  mvwprintw(win, 7, 4, "Patient: ");
  mvwprintw(win, 9, 4, "Room: Examination Room B");
  wrefresh(win);
  mvwprintw(win, 12, (width - 25) / 2, "Press any key to return...");
  wrefresh(win);
  wgetch(win); // Wait for user
  return;
}