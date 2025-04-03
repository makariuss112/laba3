#include "functions.h"

typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lower_bits : 30;
        unsigned int second_bit : 1; // bit 30
        unsigned int first_bit  : 1; // bit 31
    } fields;
} BitFieldUnion;

/* Function to find most significant bits */
void findMSB()
{
    BitFieldUnion number;
    printf("Task #1: Find the two most significant bits of an unsigned integer.\n");
    printf("Enter an unsigned integer: ");

    if (scanf("%u", &number.value) != 1)
    {
        printf("Error reading the number!\n");
        return;
    }

    printf("The first most significant bit (bit 31):  %u\n", number.fields.first_bit);
    printf("The second most significant bit (bit 30): %u\n\n", number.fields.second_bit);
}

void inputEmployee(Employee *employee)
{
    if (employee == NULL)
    {
        fprintf(stderr, "Employee pointer is NULL.\n");
        return;
    }

    // Department code
    printf("Enter department code (integer): ");
    if (scanf("%d", &employee->department_code) != 1)
    {
        fprintf(stderr, "Error reading department code!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    // Date of employment
    printf("Enter date of employment (format DD.MM.YYYY): ");
    if (scanf("%10s", employee->hire_date.date) != 1)
    {
        fprintf(stderr, "Error reading date!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    // Salary
    printf("Enter employee's salary (integer): ");
    if (scanf("%d", &employee->salary) != 1)
    {
        fprintf(stderr, "Error reading salary!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    // Surname
    printf("Enter employee's surname: ");
    char temp[256];
    if (fgets(temp, sizeof(temp), stdin) == NULL)
    {
        fprintf(stderr, "Error reading surname!\n");
        return;
    }
    size_t length = strlen(temp);
    if (length > 0 && temp[length - 1] == '\n') {
        temp[length - 1] = '\0';
        --length;
    }

    employee->surname = (char *)malloc((length + 1) * sizeof(char));
    if (employee->surname == NULL)
    {
        fprintf(stderr, "Memory allocation error for surname!\n");
        return;
    }
    strcpy(employee->surname, temp);
}

/* 
   Print all fields of an Employee, 
   including the newly added department code and hire date.
*/
void printEmployee(const Employee *employee)
{
    if (employee == NULL) 
        return;

    printf(
        "Department code: %d | Date of employment: %s | Surname: %s | Salary: %d\n",
        employee->department_code,
        employee->hire_date.date,
        employee->surname,
        employee->salary
    );
}

/* Find employees by surname */
void findEmployeesBySurname(const Employee *employees, int empCount, const char *targetSurname)
{
    if (!employees || !targetSurname) 
    return;

    int found = 0;
    for (int i = 0; i < empCount; i++)
    {
        if (employees[i].surname && strcmp(employees[i].surname, targetSurname) == 0)
        {
            printEmployee(&employees[i]);
            found = 1;
        }
    }

    if (found == 0)
    {
        printf("No employees found with the surname \"%s\".\n", targetSurname);
    }
}

/* Remove employees whose salary is below a given threshold */
int removeEmployeesBelowSalary(Employee *employees, int empCount, int minSalary)
{
    if (!employees || empCount <= 0) 
    return empCount;

    int newSize = 0;
    for (int i = 0; i < empCount; i++)
    {
        if (employees[i].salary >= minSalary)
        {
            if (newSize != i) {
                employees[newSize] = employees[i];
            }
            newSize++;
        }
        else
        {
            free(employees[i].surname);
            employees[i].surname = NULL;
        }
    }
    return newSize;
}

/* Menu for managing the employee array */
void menuEmployeeManager(Employee **employees, int *empCount)
{
    int choice;
    do
    {
        printf("\nEmployee Management Menu:\n");
        printf("1. Add an employee\n");
        printf("2. Find employees by surname\n");
        printf("3. Remove employees with salary below threshold\n");
        printf("4. Print all employees\n");
        printf("0. Return to main menu\n");
        printf("Enter menu option: ");

        if (scanf("%d", &choice) != 1)
        {
            fprintf(stderr, "Input error!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice)
        {
        case 1:
        {
            Employee newEmployee;
            inputEmployee(&newEmployee);

            Employee *temp = (Employee *)realloc(*employees, (*empCount + 1) * sizeof(Employee));
            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation error!\n");
                free(newEmployee.surname);
                newEmployee.surname = NULL;
                break;
            }
            *employees = temp;
            (*employees)[*empCount] = newEmployee;
            (*empCount)++;
            break;
        }
        case 2:
        {
            if (*empCount == 0) {
                printf("Employee list is empty.\n");
                break;
            }
            char temp[256];
            printf("Enter the surname to search for: ");
            if (fgets(temp, sizeof(temp), stdin) == NULL)
            {
                fprintf(stderr, "Error reading surname.\n");
                break;
            }
            size_t len = strlen(temp);
            if (len > 0 && temp[len - 1] == '\n') {
                temp[len - 1] = '\0';
            }
            findEmployeesBySurname(*employees, *empCount, temp);
            break;
        }
        case 3:
        {
            if (*empCount == 0) {
                printf("Employee list is empty.\n");
                break;
            }
            int minSalary;
            printf("Enter the minimum salary: ");
            if (scanf("%d", &minSalary) != 1) {
                fprintf(stderr, "Error reading salary.\n");
                while (getchar() != '\n'); 
                break;
            }
            while (getchar() != '\n');
            int oldCount = *empCount;
            *empCount = removeEmployeesBelowSalary(*employees, *empCount, minSalary);
            if (*empCount < oldCount) {
                printf("Removed %d employee(s).\n", oldCount - *empCount);
            } else {
                printf("No employees were removed.\n");
            }
            break;
        }
        case 4:
        {
            if (*empCount == 0) {
                printf("Employee list is empty.\n");
                break;
            }
            for (int i = 0; i < *empCount; i++) {
                printEmployee(&((*employees)[i]));
            }
            break;
        }
        default:
            break;
        }
    } while (choice != 0);
}