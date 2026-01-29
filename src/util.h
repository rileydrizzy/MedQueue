/**
 * @file util.h
 * @brief Header file containing definitions and function prototypes for the MedQueue application.
 *
 * This file defines the patient structure, the queue structure, and declares functions
 * for creating nodes, registering patients, serving patients, viewing the queue,
 * and cleaning up resources.
 */

#ifndef UTIL_H
#define UTIL_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define NAME_LENGTH 30

/**
 * @brief Represents a node in the linked list of patients.
 *
 * Contains the patient's personal information and a pointer to the next patient in the queue.
 */
typedef struct Patient_Node
{
  int id;                            /**< Unique identifier for the patient, four digits. */
  int age;                           /**< Age of the patient. */
  char first_name[NAME_LENGTH];      /**< Patient's first name. */
  char last_name[NAME_LENGTH];       /**< Patient's last name. */
  struct Patient_Node *next_patient; /**< Pointer to the next patient in the queue. */
} Patient_Node;

/**
 * @brief Represents the queue of patients.
 *
 * Maintains pointers to the head (front) and tail (end) of the linked list
 * to allow for efficient enqueueing and dequeueing operations.
 */
typedef struct
{
  Patient_Node *head; /**< Pointer to the first patient in the queue (next to be served). */
  Patient_Node *tail; /**< Pointer to the last patient in the queue (most recently added). */
} Patient_Queue;

/**
 * @brief Allocates a new patient node and adds it to the queue.
 *
 * Depending on the mode, the patient is added either to the end (standard)
 * or the front (emergency) of the queue.
 *
 * @param queue Pointer to the Patient_Queue to add the node to.
 * @param er_mode If true, adds to the front (Emergency). Otherwise, adds to the end.
 * @return Pointer to the created Patient_Node, or NULL on allocation failure.
 */
Patient_Node *create_patient_node(Patient_Queue *queue, bool ER_mode);

/**
 * @brief Displays a form to register a new patient and adds them to the queue.
 *
 * @param win Pointer to the ncurses window for display.
 * @param width Width of the window.
 * @param queue Pointer to the Patient_Queue to add the patient to.
 * @param er_mode If true, registers as an emergency patient.
 */
void register_patient(WINDOW *win, int width, Patient_Queue *queue, bool ER_mode);

/**
 * @brief Serves the next patient in the queue.
 * Displays the patient's name and assigned room.
 *
 * @param win Pointer to the ncurses window for display.
 * @param width Width of the window.
 * @param queue Pointer to the Patient_Queue to serve from.
 */
void serving_patient(WINDOW *win, int width, Patient_Queue *queue);

/**
 * @brief Displays the current list of patients waiting in the queue.
 *
 * @param win Pointer to the ncurses window for display.
 * @param width Width of the window.
 * @param queue Pointer to the Patient_Queue to view.
 */
void view_line(WINDOW *win, int width, Patient_Queue *queue);

/**
 * @brief Frees all memory associated with the patient queue.
 *
 * Iterates through the linked list and frees each patient node.
 * Should be called before the program exits to prevent memory leaks.
 *
 * @param queue Pointer to the Patient_Queue to clean up.
 */
void clean_up(Patient_Queue *queue);

#endif
