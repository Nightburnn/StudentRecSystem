#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct Student - Structure to store student information
 * @name: Student's name
 * @rollNumber: Student's roll number
 * @marks: Student's marks
 */


typedef struct {
    char name[50];
    int rollNumber;
    int marks;
} Student;

/* Function prototypes */
void welcomeUser();
void addStudents(Student **students, int *count);
void displayStudents(Student *students, int count);
void saveStudents(Student *students, int count, const char *filename);
void loadStudents(Student **students, int *count, const char *filename);
void searchStudent(Student *students, int count);
void calculateAverageMarks(Student *students, int count);
void sortStudents(Student *students, int count, int ascending);
void modifyStudent(Student *students, int count);
void removeStudent(Student **students, int *count);
void checkPassFail(Student student);
int getIntegerInput(const char *prompt);
void getStringInput(const char *prompt, char *input, int size);

/**
 * main - Entry point of the program
 * Return: 0 on success
 */
int main() {
    welcomeUser();

    Student *students = NULL;
    int studentCount = 0;
    int option;

    loadStudents(&students, &studentCount, "studentSaved.txt");

    do {
        printf("\nMenu:\n");
        printf("1. Add Students\n");
        printf("2. Display Students\n");
        printf("3. Modify Student\n");
        printf("4. Remove Student\n");
        printf("5. Search Student by Roll Number\n");
        printf("6. Calculate Average Marks\n");
        printf("7. Sort Students by Marks (Ascending)\n");
        printf("8. Sort Students by Marks (Descending)\n");
        printf("9. Save and Exit\n");
        printf("Enter a Number: ");
        option = getIntegerInput("");

        switch (option) {
            case 1:
                addStudents(&students, &studentCount);
                break;
            case 2:
                if (studentCount > 0) {
                    displayStudents(students, studentCount);
                } else {
                    printf("No student records to display.\n");
                }
                break;
            case 3:
                if (studentCount > 0) {
                    modifyStudent(students, studentCount);
                } else {
                    printf("No student records to modify.\n");
                }
                break;
            case 4:
                if (studentCount > 0) {
                    removeStudent(&students, &studentCount);
                } else {
                    printf("No student records to remove.\n");
                }
                break;
            case 5:
                if (studentCount > 0) {
                    searchStudent(students, studentCount);
                } else {
                    printf("No student records to search.\n");
                }
                break;
            case 6:
                if (studentCount > 0) {
                    calculateAverageMarks(students, studentCount);
                } else {
                    printf("No student records to calculate average marks.\n");
                }
                break;
            case 7:
                if (studentCount > 0) {
                    sortStudents(students, studentCount, 1);
                    displayStudents(students, studentCount);
                } else {
                    printf("No student records to sort.\n");
                }
                break;
            case 8:
                if (studentCount > 0) {
                    sortStudents(students, studentCount, 0);
                    displayStudents(students, studentCount);
                } else {
                    printf("No student records to sort.\n");
                }
                break;
            case 9:
                saveStudents(students, studentCount, "studentSaved.txt");
                printf("Student records saved successfully. Exiting...\n");
                break;
            default:
                printf("Invalid option! Please try again.\n");
        }
    } while (option != 9);

    free(students);

    return 0;
}

/**
 * welcomeUser - Greets the user by their name
 */
void welcomeUser() {
    char userName[50];
    printf("Please Enter Your First Name: ");
    getStringInput("", userName, sizeof(userName));
    printf("Welcome, %s!, To Our Student Record System\n", userName);
}

/**
 * addStudents - Adds multiple new students to the student list
 * @students: Pointer to the array of students
 * @count: Pointer to the count of students
 */
void addStudents(Student **students, int *count) {
    char choice[10];
    do {
        (*count)++;
        *students = realloc(*students, (*count) * sizeof(Student));
        if (*students == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }

        getStringInput("Enter student name: ", (*students)[*count - 1].name, sizeof((*students)[*count - 1].name));
        (*students)[*count - 1].rollNumber = getIntegerInput("Enter roll number: ");
        (*students)[*count - 1].marks = getIntegerInput("Enter marks: ");
        checkPassFail((*students)[*count - 1]);

        printf("Do you want to add another student? (yes/no): ");
        getStringInput("", choice, sizeof(choice));
    } while (strcmp(choice, "yes") == 0);
}

/**
 * getStringInput - Prompts the user for a string input and validates it
 * @prompt: The prompt message
 * @input: The buffer to store the input
 * @size: The size of the input buffer
 */
void getStringInput(const char *prompt, char *input, int size) {
    printf("%s", prompt);
    while (fgets(input, size, stdin)) {
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
            break;
        } else {
            printf("Invalid input! Please enter a valid string: ");
            while (getchar() != '\n');
        }
    }
}

/**
 * getIntegerInput - Prompts the user for an integer input and validates it
 * @prompt: The prompt message
 * Return: The validated integer input
 */
int getIntegerInput(const char *prompt) {
    int input;
    char term;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d%c", &input, &term) != 2 || term != '\n') {
            while (getchar() != '\n');
            printf("Invalid input! Please enter a valid number.\n");
        } else {
            break;
        }
    }
    return input;
}

/**
 * displayStudents - Displays the list of students
 * @students: Array of students
 * @count: Count of students
 */
 
void displayStudents(Student *students, int count) {
    for (int i = 0; i < count; i++) {
        printf("Name: %s, Roll Number: %d, Marks: %d, Status: %s\n",
               students[i].name, students[i].rollNumber, students[i].marks,
               students[i].marks > 40 ? "Passed" : "Failed");
    }
}

/**
 * searchStudent - Searches for a student by roll number
 * @students: Array of students
 * @count: Count of students
 */
void searchStudent(Student *students, int count) {
    int rollNo = getIntegerInput("Enter roll number to search: ");

    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNo) {
            printf("Student found: Name: %s, Roll Number: %d, Marks: %d, Status: %s\n",
                   students[i].name, students[i].rollNumber, students[i].marks,
                   students[i].marks > 40 ? "Passed" : "Failed");
            return;
        }
    }
    printf("Student with roll number %d not found.\n", rollNo);
}

/**
 * calculateAverageMarks - Calculates and displays the average marks
 * @students: Array of students
 * @count: Count of students
 */
void calculateAverageMarks(Student *students, int count) {
    int totalMarks = 0;
    for (int i = 0; i < count; i++) {
        totalMarks += students[i].marks;
    }
    printf("Average Marks: %.2f\n", (float)totalMarks / count);
}

/**
 * sortStudents - Sorts the student records by marks
 * @students: Array of students
 * @count: Count of students
 * @ascending: Sort order (1 for ascending, 0 for descending)
 */
void sortStudents(Student *students, int count, int ascending) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if ((ascending && students[i].marks > students[j].marks) ||
                (!ascending && students[i].marks < students[j].marks)) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

/**
 * modifyStudent - Modifies a student's record
 * @students: Array of students
 * @count: Count of students
 */
void modifyStudent(Student *students, int count) {
    int rollNo = getIntegerInput("Enter roll number of student to modify: ");
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNo) {
            printf("Modifying student with roll number %d\n", rollNo);
            getStringInput("Enter new name: ", students[i].name, sizeof(students[i].name));
            students[i].marks = getIntegerInput("Enter new marks: ");
            printf("Student record updated.\n");
            return;
        }
    }
    printf("Student with roll number %d not found.\n", rollNo);
}

/**
 * removeStudent - Removes a student's record
 * @students: Pointer to the array of students
 * @count: Pointer to the count of students
 */
void removeStudent(Student **students, int *count) {
    int rollNo = getIntegerInput("Enter roll number of student to remove: ");
    for (int i = 0; i < *count; i++) {
        if ((*students)[i].rollNumber == rollNo) {
            for (int j = i; j < *count - 1; j++) {
                (*students)[j] = (*students)[j + 1];
            }
            (*count)--;
            *students = realloc(*students, (*count) * sizeof(Student));
            printf("Student with roll number %d removed.\n", rollNo);
            return;
        }
    }
    printf("Student with roll number %d not found.\n", rollNo);
}

/**
 * checkPassFail - Checks if a student passed or failed
 * @student: The student record
 */
void checkPassFail(Student student) {
    if (student.marks > 40) {
        printf("%s has passed.\n", student.name);
    } else {
        printf("%s has failed.\n", student.name);
    }
}

/**
 * saveStudents - Saves student records to a file
 * @students: Array of students
 * @count: Count of students
 * @filename: The filename to save to
 */
void saveStudents(Student *students, int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for saving!\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), count, file);
    fclose(file);
}

/**
 * loadStudents - Loads student records from a file
 * @students: Pointer to the array of students
 * @count: Pointer to the count of students
 * @filename: The filename to load from
 */
void loadStudents(Student **students, int *count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        *students = NULL;
        *count = 0;
        return;
    }
    fread(count, sizeof(int), 1, file);
    *students = malloc(*count * sizeof(Student));
    if (*students == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    fread(*students, sizeof(Student), *count, file);
    fclose(file);
}
