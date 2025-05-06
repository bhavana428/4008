#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants

#define MAX_NAME_LENGTH 100
#define MAX_STUDENTS 1000

// Structure to hold student information

struct Student 
{
    int id;
    char name[MAX_NAME_LENGTH];
    float grade;
};

// Global array of students

struct Student students[MAX_STUDENTS];
int student_count = 0;

// Function declarations

void menu();
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void saveToFile();
void loadFromFile();
void clearScreen();

// Main function

int main()
 {
    int choice;
    loadFromFile(); // Load student data from file on startup
    
    while (1)
     {
        menu(); // Display the menu
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To catch the newline character after scanf

        switch (choice) 
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                saveToFile();
                break;

            case 6:
                loadFromFile();
                break;

            case 7:
                printf("Exiting program.\n");
                saveToFile(); // Save data before exit
                return 0;

            default:

                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Menu function to display options

void menu()
 {
    clearScreen();
    printf("=== Student Management System ===\n");
    printf("1. Add Student\n");
    printf("2. Display Students\n");
    printf("3. Search Student\n");
    printf("4. Delete Student\n");
    printf("5. Save to File\n");
    printf("6. Load from File\n");
    printf("7. Exit\n");
    printf("===============================\n");
}

// Function to add a student record

void addStudent() 
{
    if (student_count >= MAX_STUDENTS)
     {
        printf("Cannot add more students. Max limit reached.\n");
        return;
    }
    
    struct Student newStudent;
    newStudent.id = student_count + 1;
     // Assign ID automatically

    printf("Enter student's name: ");
    fgets(newStudent.name, MAX_NAME_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0; 
    // Remove newline from name

    printf("Enter student's grade: ");
    scanf("%f", &newStudent.grade);
    getchar(); 
    // To clear the newline

    students[student_count++] = newStudent;
    printf("Student added successfully!\n");
}

// Function to display all student records

void displayStudents() 
{
    clearScreen();
    printf("=== All Students ===\n");

    if (student_count == 0) 
    {
        printf("No students to display.\n");
        return;
    }

    for (int i = 0; i < student_count; i++)
     {
        printf("ID: %d, Name: %s, Grade: %.2f\n", students[i].id, students[i].name, students[i].grade);
    }

    printf("=====================\n");
}

// Function to search for a student by name or ID

void searchStudent() 
{
    clearScreen();
    int choice;
    printf("Search by: 1. ID 2. Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); 

    // To clear the newline

    if (choice == 1)
     {
        int search_id;
        printf("Enter student ID: ");
        scanf("%d", &search_id);
        getchar();

        int found = 0;
        for (int i = 0; i < student_count; i++)
         {
            if (students[i].id == search_id)
             {
                printf("ID: %d, Name: %s, Grade: %.2f\n", students[i].id, students[i].name, students[i].grade);
                found = 1;
                break;
            }
        }
        if (!found)
         {
            printf("Student with ID %d not found.\n", search_id);
        }
    } 
    else if (choice == 2)
     {
        char search_name[MAX_NAME_LENGTH];
        printf("Enter student name: ");
        fgets(search_name, MAX_NAME_LENGTH, stdin);
        search_name[strcspn(search_name, "\n")] = 0;

        int found = 0;
        for (int i = 0; i < student_count; i++) 
        {
            if (strcmp(students[i].name, search_name) == 0) 
            {
                printf("ID: %d, Name: %s, Grade: %.2f\n", students[i].id, students[i].name, students[i].grade);
                found = 1;
                break;
            }
        }
        if (!found)
         {
            printf("Student with name %s not found.\n", search_name);
        }
    }
     else 
     {
        printf("Invalid choice.\n");
    }
}

// Function to delete a student record by ID

void deleteStudent() 
{
    int delete_id;
    printf("Enter student ID to delete: ");
    scanf("%d", &delete_id);
    getchar();

    int found = 0;
    for (int i = 0; i < student_count; i++) 
    {
        if (students[i].id == delete_id) {
            for (int j = i; j < student_count - 1; j++) 
            {
                students[j] = students[j + 1]; 
                // Shift students to the left
            }
            student_count--;
            found = 1;
            printf("Student with ID %d deleted successfully.\n", delete_id);
            break;
        }
    }

    if (!found) 
    {
        printf("Student with ID %d not found.\n", delete_id);
    }
}

// Function to save student data to a file

void saveToFile()
 {
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL)
     {
        printf("Error opening file for saving.\n");
        return;
    }

    fwrite(&student_count, sizeof(int), 1, file); 
    // Write the student count
    fwrite(students, sizeof(struct Student), student_count, file);
     // Write student data

    fclose(file);
    printf("Student data saved successfully!\n");
}

// Function to load student data from a file

void loadFromFile()
 {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL)
     {
        printf("No saved data found. Starting with an empty list.\n");
        return;
    }

    fread(&student_count, sizeof(int), 1, file); 
    // Read the student count
    fread(students, sizeof(struct Student), student_count, file); 
    // Read student data

    fclose(file);
    printf("Student data loaded successfully!\n");
}

// Function to clear the console screen (platform-dependent)

void clearScreen() 
{

    // For Unix-based systems like Linux/macOS
    #ifdef __unix__
    system("clear");
    #endif

    // For Windows
    
    #ifdef _WIN32
    system("cls");
    #endif
}

