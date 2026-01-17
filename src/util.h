#ifndef UTIL_H
#define UTIL_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Patient_Node
{
  int id;
  char first_name[20];
  char last_name[20];
  int age;
  struct Patient_Node *next_patient;
} Patient_Node;

typedef struct
{
  Patient_Node *head;
  Patient_Node *tail;
} Patient_Queue;

Patient_Node *alloc_patient(Patient_Queue *queue);

void serving_patient(WINDOW *win, int width, int height, Patient_Queue *queue);

void register_patient(WINDOW *win, int width, int height, Patient_Queue *queue);

void view_line(WINDOW *win, int width, Patient_Queue *queue);

#endif
