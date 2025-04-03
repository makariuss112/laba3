#include "functions.h"
/*
    Task:

    1. Find and print the 2 most significant bits of an unsigned integer.
    2. A structure contains information about company employees:
       - department code (integer)
       - surname (pointer)
       - nested structure (date of employment) – a fixed-length string
       - salary (an integer)

       Requirements:
         - Find employees with a given surname.
         - Remove (delete) employees whose salary is below a given threshold.

    Additional requirements:
    1) For Task #1, use bit fields; the data is entered from the keyboard.
    2) For Task #2, declare a dynamic array of structures in main, check the memory allocation and free it at the end of the program.
    3) For Task #2, write functions to input and output the first two fields of the structure.
    4) For Task #2, write a function to search in the array of structures by a given parameter (surname).
    5) For Task #2, write a function to remove structures from the array by a given parameter (salary).
    6) Implement a menu to manage the array of structures and perform all necessary data checks.

    Student surname: Masukov
    Date of writing the code: 30/03/2025
*/

/* ------------------------------------------------------------------
 *                           TASK #1
 * Find and print the 2 most significant bits of an unsigned integer
 * using bit fields (input from the keyboard).
 * ------------------------------------------------------------------ */

/* ------------------------------------------------------------------
 *                           TASK #2
 * Company employee structure:
 *   - department_code (int)
 *   - surname (char *surname)
 *   - nested structure (date of employment) - fixed-length string
 *   - salary (double)
 *
 * Required:
 *   1) Implement input and output of the first two fields (department_code, surname).
 *   2) Find employees with a given surname.
 *   3) Remove employees whose salary is below a given threshold.
 *   4) Implement a menu to manage a dynamic array of structures.
 * ------------------------------------------------------------------ */

 int main(void)
{
    int mainChoice;
    Employee *employees = NULL;
    int employeeCount = 0;

    do {
        printf("\nMAIN MENU:\n");
        printf("1. Task #1 (bit fields, 2 most significant bits)\n");
        printf("2. Task #2 (employee management)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &mainChoice) != 1) {
            printf("Input error!\n");
            while (getchar() != '\n'); 
            continue;
        }
        while (getchar() != '\n');

        switch (mainChoice) {
        case 1:
            findMSB();
            break;
        case 2:
            menuEmployeeManager(&employees, &employeeCount);
            break;
        case 0:
            printf("Program finished.\n");
            break;
        default:
            printf("Unknown menu option, please try again.\n");
            break;
        }
    } while (mainChoice != 0);
    if (employees) {
        for (int i = 0; i < employeeCount; i++) {
            free(employees[i].surname);
            employees[i].surname = NULL;
        }
        free(employees);
        employees = NULL;
    }
    return 0;
}
