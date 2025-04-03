#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

void findMSB();


typedef struct {
    char date[11];  // e.g. "DD.MM.YYYY"
} HireDate;

typedef struct
{
    char *surname;
    int department_code;
    HireDate hire_date;
    int salary;
} Employee;

void menuEmployeeManager(Employee **empArr, int *empCount);


#endif