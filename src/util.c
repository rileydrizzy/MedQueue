#include "util.h"
#include <ctype.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Patient_Node *create_patient_node(Patient_Queue *queue, bool er_mode) {
  Patient_Node *patient = calloc(1, sizeof(Patient_Node));
  if (patient == NULL) {
    // TODO Implement a error val
    puts("Allocation failed");
    return NULL;
  }
  patient->next_patient = NULL;
  if (queue->head == NULL) {
    queue->head = patient;
    queue->tail = patient;
    return patient;
  } else {
    if (er_mode) {
      patient->next_patient = queue->head;
      queue->head = patient;
      return patient;
    } else {
      queue->tail->next_patient = patient;
      queue->tail = patient;
      return patient;
    }
  }
}

void register_patient(WINDOW *win, int width, Patient_Queue *queue,
                      bool er_mode) {
  Patient_Node *new_patient = create_patient_node(queue, er_mode);

  // Clear the inside of the existing box
  werase(win);
  box(win, 0, 0);
  wattron(win, A_BOLD);
  mvwprintw(win, 2, (width - 16) / 2, "REGISTER PATIENT");
  wattroff(win, A_BOLD);
  mvwhline(win, 3, 2, ACS_HLINE, width - 4);

  // Enable typing visibility
  echo();
  curs_set(1); // Show cursor for typing
  // Safe input for strings
  mvwprintw(win, 5, 4, "Enter Patient First Name: ");
  wgetnstr(win, new_patient->first_name, 49);

  mvwprintw(win, 7, 4, "Enter Patient Last Name: ");
  wgetnstr(win, new_patient->last_name, 49);
  // char p_initial;
  // p_initial = new_patient->last_name[0]; // TODO add p.inital to be show on
  // display
  mvwprintw(win, 9, 4, "Enter Patient Age: ");
  wrefresh(win);

  // Using scanw style for age
  char age_str[4];
  wgetnstr(win, age_str, 9);
  new_patient->age = atoi(age_str);

  // Success Message
  noecho();
  curs_set(0);
  wattron(win, COLOR_PAIR(1) | A_BOLD); // Assuming color 1 is green
  mvwprintw(win, 12, 20, "==[Success]==");
  mvwprintw(win, 13, (width - (18 + strlen(new_patient->last_name))) / 2,
            "%s added to the queue.", new_patient->last_name);
  wattroff(win, COLOR_PAIR(1) | A_BOLD);

  mvwprintw(win, 16, (width - 25) / 2, "Press any key to return...");
  wrefresh(win);
  wgetch(win); // Wait for user to read success message
  return;
}

void serving_patient(WINDOW *win, int width, Patient_Queue *queue) {
  werase(win);
  box(win, 0, 0);
  wattron(win, A_BOLD);
  mvwprintw(win, 2, (width - 16) / 2, "NOW SERVING");
  wattroff(win, A_BOLD);
  mvwhline(win, 3, 2, ACS_HLINE, width - 4);
  if (queue->head != NULL) {
    Patient_Node *current_patient = queue->head;
    mvwprintw(win, 5, 4, "Patient: %s", current_patient->first_name);
    mvwprintw(win, 7, 4, "Room: Examination Room B");
    wrefresh(win);

    queue->head = current_patient->next_patient;
    free(current_patient);
  } else {
    mvwprintw(win, 7, 4, "There is no Patient on the queue");
    wrefresh(win);
  }
  mvwprintw(win, 12, (width - 25) / 2, "Press any key to return...");
  wrefresh(win);
  wgetch(win);
  return;
}

// BUG Segfault when running
void view_line(WINDOW *win, int width, Patient_Queue *queue) {
  werase(win);
  box(win, 0, 0);
  wattron(win, A_BOLD);
  mvwprintw(win, 2, (width - 16) / 2, "LINE");
  wattroff(win, A_BOLD);
  mvwhline(win, 3, 2, ACS_HLINE, width - 4);
  wrefresh(win);
  if (queue->head == NULL) {
    mvwprintw(win, 5, (width - 20) / 2, "There No Queue");
  } else {

    Patient_Node *current = queue->head;
    int i = 0;
    int display_y = 5; // Starting Y position for displaying patients
    do {
      while (current != NULL && i < 5) // Display up to 10 patients
      {
        mvwprintw(win, display_y + (i * 2), 4, "%d. %s %s (Patient ID: %d)",
                  i + 1, current->first_name, current->last_name, current->id);
        current = current->next_patient;
        i++;
      }
      if (current != NULL) {
        while (true) {
          mvwprintw(
              win, display_y + (i * 2), 4,
              "Press N to see the or Q to Quit"); // Indicate more patients
          char c = wgetch(win);
          if (tolower(c) == 'q') {
            return;
          } else if {
            i = 0;
          } else {
            mvwprintw(win, display_y + (i * 2), 4,
                      "Invalid option select try again");
            nodelay() continue;
          }
        }
        mvwprintw(win, 16, (width - 25) / 2, "Press any key to return...");
        wrefresh(win);
        wgetch(win); // Wait for user to read success message
        return;
      }
    }
  // void clean_up();
