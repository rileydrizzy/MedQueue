#include "util.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Patient_Node *create_patient_node(Patient_Queue *queue)
{
  Patient_Node *Patient = calloc(1, sizeof(Patient_Node));
  if (Patient == NULL)
  {
    // TODO Implement a error val
    puts("Allocation failed");
    return NULL;
  }
  Patient->next_patient = NULL;
  if (queue->head == NULL)
  {
    queue->head = Patient;
    queue->tail = Patient;
    return Patient;
  }
  else
  {
    queue->tail->next_patient = Patient;
    queue->tail = Patient;
  }
  return Patient;
}

void register_patient(WINDOW *win, int width, int height, Patient_Queue *queue)
{
  Patient_Node *new_Patient = create_patient_node(queue);

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
  wgetnstr(win, new_Patient->first_name, 49);

  mvwprintw(win, 7, 4, "Enter Patient Last Name: ");
  wgetnstr(win, new_Patient->last_name, 49);

  mvwprintw(win, 9, 4, "Enter Patient Age: ");
  wrefresh(win);

  // Using scanw style for age
  char age_str[4];
  wgetnstr(win, age_str, 9);
  new_Patient->age = atoi(age_str);

  // Success Message
  noecho();
  curs_set(0);
  wattron(win, COLOR_PAIR(1) | A_BOLD); // Assuming color 1 is green
  mvwprintw(win, 12, (width - (18 + strlen(new_Patient->first_name))) / 2,
            "[Success] %s, %s added to the line.", new_Patient->first_name,
            new_Patient->last_name);
  wattroff(win, COLOR_PAIR(1) | A_BOLD);

  mvwprintw(win, 14, (width - 25) / 2, "Press any key to return...");
  wrefresh(win);
  wgetch(win); // Wait for user to read success message
}

void serving_patient(WINDOW *win, int width, int height, Patient_Queue *queue)
{
  werase(win);
  box(win, 0, 0);
  wattron(win, A_BOLD);
  mvwprintw(win, 2, (width - 16) / 2, "NOW SERVING");
  wattroff(win, A_BOLD);
  mvwhline(win, 3, 2, ACS_HLINE, width - 4);
  if (queue->head != NULL)
  {
    Patient_Node *current_patient = queue->head;
    mvwprintw(win, 5, 4, "Patient: %s", current_patient->first_name);
    mvwprintw(win, 7, 4, "Room: Examination Room B");
    wrefresh(win);

    queue->head = current_patient->next_patient;
    free(current_patient);
  }
  else
  {
    mvwprintw(win, 7, 4, "There is no Patient on the queue");
    wrefresh(win);
  }
  mvwprintw(win, 12, (width - 25) / 2, "Press any key to return...");
  wrefresh(win);
  wgetch(win);
  return;
}


void view_line(WINDOW *win, int width, Patient_Queue *queue)
{
  Patient_Node *Current = queue->head;
  werase(win);
  box(win, 0, 0);
  wattron(win, A_BOLD);
  mvwprintw(win, 2, (width - 16) / 2, "LINE");
  wattroff(win, A_BOLD);
  mvwhline(win, 3, 2, ACS_HLINE, width - 4);
  while (queue->head)
  {
    // mvwprintw(win, 5, 4, "Patient: %s, %s", HEAD->First_Name, HEAD->Last_Name);
  }
}
