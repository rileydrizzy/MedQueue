#include "def.h"
#include <stdio.h>
#include <stdlib.h>

// void get_patient_detatil(void) {}
// void append_patient(Patient, h_tail)

Patient *make_patient(char *name, int age) {
  Patient *p = malloc(sizeof(Patient));
  if (!p) {
    puts("Patient Allocaltion failed");
    return NULL;
  }
  p->age = age;
  p->next_patient = NULL;
  return p;
}
