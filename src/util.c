#include "util.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Patient_Node *alloc_patient(Patient_Queue *queue)
{
  Patient_Node *Patient = malloc(sizeof(Patient_Node));
  if (Patient == NULL)
  {
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
  Patient_Node *new_Patient = alloc_patient(queue);

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

  // 3. Success Message
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
    Patient_Node *var = *queue->head;
    mvwprintw(win, 5, 4, "Patient: %s, %s", var->first_name);
    mvwprintw(win, 7, 4, "Room: Examination Room B");
    wrefresh(win);
    // Patient_Node *temp = HEAD;
    queue->head = var->next_patient;
    free(var);
  }
  else
  {
    mvwprintw(win, 7, 4, "No Patient on the line");
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
