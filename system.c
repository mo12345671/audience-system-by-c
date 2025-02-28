#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store employee details
struct Employee {
    int id;
    char name[50];
    char department[50];
    char role[50];
    int password;
};

/* Function prototypes*/
void addEmployee(struct Employee employees[], int *count);
void viewEmployees(struct Employee employees[], int count);
void updateEmployee(struct Employee employees[], int count);
void saveEmployeesToFile(struct Employee employees[], int count);
void loadEmployeesFromFile(struct Employee employees[], int *count);

int main(void) {
    struct Employee employees[100];
    int employeeCount = 0;

    // Load employee data from file
    loadEmployeesFromFile(employees, &employeeCount);

    int choice;
    do {
        // Main menu
        printf("\n--- Employee Management System ---\n");
        printf("1. Employee Login\n");
        printf("2. Admin Menu\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: { // Employee Login
                int id, password;
                printf("Enter your ID: ");
                scanf("%d", &id);
                printf("Enter your password: ");
                scanf("%d", &password);

                int found = 0;
                for (int i = 0; i < employeeCount; i++) {
                    if (employees[i].id == id && employees[i].password == password) {
                        printf("\nHello, %s!\n", employees[i].name);
                        printf("Department: %s\n", employees[i].department);
                        printf("Role: %s\n", employees[i].role);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Invalid ID or password.\n");
                }
                break;
            }

            case 2: { // Admin Menu
                int adminChoice;
                do {
                    printf("\n--- Admin Menu ---\n");
                    printf("1. Add Employee\n");
                    printf("2. View Employees\n");
                    printf("3. Update Employee\n");
                    printf("4. Back to Main Menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &adminChoice);

                    switch (adminChoice) {
                        case 1:
                            addEmployee(employees, &employeeCount);
                            saveEmployeesToFile(employees, employeeCount);
                            break;
                        case 2:
                            viewEmployees(employees, employeeCount);
                            break;
                        case 3:
                            updateEmployee(employees, employeeCount);
                            saveEmployeesToFile(employees, employeeCount);
                            break;
                        case 4:
                            printf("Returning to main menu...\n");
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                } while (adminChoice != 4);
                break;
            }

            case 3:
                printf("Exiting the program...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);


    saveEmployeesToFile(employees, employeeCount);

    return 0;
}

// Function to add a new employee
void addEmployee(struct Employee employees[], int *count) {
    if (*count >= 100) {
        printf("Employee limit reached. Cannot add more employees.\n");
        return;
    }

    struct Employee newEmployee;
    newEmployee.id = *count + 1; 

    printf("Enter employee name: ");
    scanf(" %[^\n]", newEmployee.name);
    printf("Enter department: ");
    scanf(" %[^\n]", newEmployee.department);
    printf("Enter role: ");
    scanf(" %[^\n]", newEmployee.role);
    printf("Set password: ");
    scanf("%d", &newEmployee.password);

    employees[*count] = newEmployee;
    (*count)++;
    printf("Employee added successfully!\n");
}

// Function to view all employees
void viewEmployees(struct Employee employees[], int count) {
    if (count == 0) {
        printf("No employees found.\n");
        return;
    }

    printf("\n--- Employee List ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d\n", employees[i].id);
        printf("Name: %s\n", employees[i].name);
        printf("Department: %s\n", employees[i].department);
        printf("Role: %s\n", employees[i].role);
        printf("Password: %d\n", employees[i].password);
        printf("-------------------\n");
    }
}


void updateEmployee(struct Employee employees[], int count) {
    int id;
    printf("Enter the ID of the employee to update: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            printf("Enter new name: ");
            scanf(" %[^\n]", employees[i].name);
            printf("Enter new department: ");
            scanf(" %[^\n]", employees[i].department);
            printf("Enter new role: ");
            scanf(" %[^\n]", employees[i].role);
            printf("Enter new password: ");
            scanf("%d", &employees[i].password);
            found = 1;
            printf("Employee details updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }
}


void saveEmployeesToFile(struct Employee employees[], int count) {
    FILE *file = fopen("employees.dat", "wb");
    if (file == NULL) {
        printf("Error saving employee data.\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file); // Save the number of employees
    fwrite(employees, sizeof(struct Employee), count, file); // Save employee data
    fclose(file);
    printf("Employee data saved to file.\n");
}


void loadEmployeesFromFile(struct Employee employees[], int *count) {
    FILE *file = fopen("employees.dat", "rb");
    if (file == NULL) {
        printf("No existing employee data found. Starting with an empty list.\n");
        return;
    }

    fread(count, sizeof(int), 1, file); 
    fread(employees, sizeof(struct Employee), *count, file); 
    fclose(file);
    printf("Employee data loaded from file.\n");
}