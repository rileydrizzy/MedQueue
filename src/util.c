#include "util.h"
#include <ctype.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Patient_Node *create_patient_node(Patient_Queue *queue, bool ER_mode)
{
  Patient_Node *patient = calloc(1, sizeof(Patient_Node));
  if (patient == NULL)
  {
    // TODO Implement a error val
    puts("Allocation failed");
    return NULL;
  }
  patient->next_patient = NULL;
  if (queue->head == NULL)
  {
    queue->head = patient;
    queue->tail = patient;
    return patient;
  }
  else
  {
    if (ER_mode)
    {
      patient->next_patient = queue->head;
      queue->head = patient;
      return patient;
    }
    else
    {
      queue->tail->next_patient = patient;
      queue->tail = patient;
      return patient;
    }
  }
}

void register_patient(WINDOW *win, int width, Patient_Queue *queue,
                      bool ER_mode)
{
  Patient_Node *new_patient = create_patient_node(queue, ER_mode);

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
  wgetnstr(win, new_patient->first_name, 29);

  mvwprintw(win, 7, 4, "Enter Patient Last Name: ");
  wgetnstr(win, new_patient->last_name, 29);

  mvwprintw(win, 9, 4, "Enter Patient Age: ");
  wrefresh(win);

  // Using scanw style for age
  char input_buffer[5];
  wgetnstr(win, input_buffer, 3);
  new_patient->age = atoi(input_buffer);
  strtod()
  // Set Patient ID
  mvwprintw(win, 11, 4, "Enter Patient ID: ");
  wrefresh(win);
  memset(input_buffer, '\0', sizeof(input_buffer));
  wgetnstr(win, input_buffer, 4);
  new_patient->id = atoi(input_buffer);

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

void serving_patient(WINDOW *win, int width, Patient_Queue *queue)
{
  werase(win);
  box(win, 0, 0);
  wattron(win, A_BOLD);
  mvwprintw(win, 2, (width - 16) / 2, "NOW SERVING");
  wattroff(win, A_BOLD);
  mvwhline(win, 3, 2, ACS_HLINE, width - 4);
  if (queue->head != NULL)
  {
    int i = rand() % 5;
    char room[5] = {'A', 'B', 'C', 'D', 'E'};
    Patient_Node *current_patient = queue->head;
    mvwprintw(win, 5, 4, "Patient: %s", current_patient->first_name);
    mvwprintw(win, 6, 4, "Patient ID: %d", current_patient->id);
    mvwprintw(win, 7, 4, "Room: Examination Room %c", room[i]);
    wrefresh(win);
    if (current_patient->next_patient == NULL)
      queue->tail = NULL;
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

  werase(win);
  box(win, 0, 0);
  wattron(win, A_BOLD);
  mvwprintw(win, 2, (width - 16) / 2, "LINE");
  wattroff(win, A_BOLD);
  mvwhline(win, 3, 2, ACS_HLINE, width - 4);
  wrefresh(win);
  if (queue->head == NULL)
  {
    mvwprintw(win, 5, (width - 32) / 2, "There is no Patient on the queue");
    mvwprintw(win, 16, (width - 25) / 2, "Press any key to return...");
    wrefresh(win);
    wgetch(win); // Wait for user to read success message
    return;
  }
  else
  {

    Patient_Node *current = queue->head;
    int i = 0;
    int total_count = 0, index = 0;
    int display_y = 5; // Starting Y position for displaying patients

    while (current != NULL)
    {
      // Clear and redraw for pagination
      werase(win);
      box(win, 0, 0);
      wattron(win, A_BOLD);
      mvwprintw(win, 2, (width - 16) / 2, "LINE");
      wattroff(win, A_BOLD);
      mvwhline(win, 3, 2, ACS_HLINE, width - 4);

      i = 0;
      while (current != NULL && i < 5) // Display up to 5 patients
      {
        mvwprintw(win, display_y + (i * 2), 4, "%d. %s %s (Patient ID: %d)",
                  index + 1, current->first_name, current->last_name, current->id);
        current = current->next_patient;
        i++;
        index++;
        total_count++;
      }

      if (current != NULL)
      {
        mvwprintw(win, display_y + (i * 2), 4, "Press N for next page or Q to Quit");
        wrefresh(win);

        bool next_page = false;
        while (true)
        {
          int c = wgetch(win);
          if (tolower(c) == 'q')
            return;
          if (tolower(c) == 'n')
          {
            next_page = true;
            break;
          }
        }
        if (next_page)
          continue;
      }
      else
      {
        mvwprintw(win, 14, (width - 37) / 2, "Total count of patients waiting: %d \n", total_count);
        mvwprintw(win, 16, (width - 25) / 2, "Press any key to return...");
        wrefresh(win);
        wgetch(win);
        return;
      }
    }
  }
}

void clean_up(Patient_Queue *queue)
{
  Patient_Node *current = queue->head;
  while (current)
  {
    Patient_Node *temp_node = current;
    current = current->next_patient;
    free(temp_node);
  }
  queue->head = NULL;
  queue->tail = NULL;
}
