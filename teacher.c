#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 10

#define COLOR_RESET "\033[0m"
#define COLOR_BLUE "\033[34m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"

typedef struct {
    char firstName[50];
    char surname[50];
    char lastName[50];
    int grade;
    char egn[11];
    int scores[MAX_SUBJECTS];
    int overallScore;
    char uniqueKey[10];
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

// Функция за генериране на уникален 9-цифрен ключ
void generateUniqueKey(char *key) {
    int isUnique;
    do {
        isUnique = 1;
        for (int i = 0; i < 9; i++) {
            key[i] = '0' + rand() % 10;
        }
        key[9] = '\0';

        // Проверка за уникалност
        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].uniqueKey, key) == 0) {
                isUnique = 0;
                break;
            }
        }
    } while (!isUnique);
}

// Функция за добавяне на студент
void addStudent() {
    if (student_count < MAX_STUDENTS) {
        char firstName[50], surname[50], lastName[50], egn[11];
        int grade, overallScore;

        printf("Enter first name: ");
        scanf("%49s", firstName);
        printf("Enter surname: ");
        scanf("%49s", surname);
        printf("Enter last name: ");
        scanf("%49s", lastName);
        printf("Enter grade: ");
        scanf("%d", &grade);
        printf("Enter EGN: ");
        scanf("%10s", egn);
        printf("Enter overall score: ");
        scanf("%d", &overallScore);

        strncpy(students[student_count].firstName, firstName, 49);
        strncpy(students[student_count].surname, surname, 49);
        strncpy(students[student_count].lastName, lastName, 49);
        students[student_count].grade = grade;
        strncpy(students[student_count].egn, egn, 10);
        students[student_count].egn[11] = '\0';
        students[student_count].overallScore = overallScore;

        generateUniqueKey(students[student_count].uniqueKey);

        student_count++;
        printf("Student added successfully!\n");
    } else {
        printf("Student's list is full!\n");
    }
}

// Функция за изтриване на студент
void deleteStudent(char *egn) {
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].egn, egn) == 0) {
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            printf("Student with EGN %s was deleted.\n", egn);
            return;
        }
    }
    printf("Student with EGN %s wasn't deleted.\n", egn);
}

// Функция за редактиране на студент
void editStudent(char *egn) {
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].egn, egn) == 0) {
            printf("Edit student with EGN %s:\n", egn);
            printf("Enter new info (name, surname, last name, grade, score): ");
            scanf("%49s %49s %49s %d %d",
                  students[i].firstName, students[i].surname, students[i].lastName,
                  &students[i].grade, &students[i].overallScore);
            return;
        }
    }
    printf("Student with EGN %s wasn't found.\n", egn);
}

// Функция за показване на всички студенти
// Функция за показване на всички студенти
void showAllStudents() {
    if (student_count == 0) {
        printf("No students in the list.\n");
        return;
    }

    printf("\nList of all students:\n");
    for (int i = 0; i < student_count; i++) {
        printf("%d. %s%s%s %s%s%s %s%s%s, Grade: %d, %sEGN: %s%s, Score: %d, %sKey: %s%s\n",
            i + 1,
            COLOR_BLUE, students[i].firstName, COLOR_RESET,  // Първо име
            COLOR_BLUE, students[i].surname, COLOR_RESET,    // Бащино име
            COLOR_BLUE, students[i].lastName, COLOR_RESET,   // Фамилия
            students[i].grade,                               // Клас
            COLOR_GREEN, students[i].egn, COLOR_RESET,       // ЕГН
            students[i].overallScore,                        // Оценка
            COLOR_RED, students[i].uniqueKey, COLOR_RESET    // Уникален ключ
        );
    }
}

// Helper function to print student information
void printStudentInfo(int i) {
    printf("%d. %s%s%s %s%s%s %s%s%s, Grade: %d, %sEGN: %s%s, Score: %d, %sKey: %s%s\n",
        i + 1,
        COLOR_BLUE, students[i].firstName, COLOR_RESET,  // Първо име
        COLOR_BLUE, students[i].surname, COLOR_RESET,    // Бащино име
        COLOR_BLUE, students[i].lastName, COLOR_RESET,   // Фамилия
        students[i].grade,                               // Клас
        COLOR_GREEN, students[i].egn, COLOR_RESET,       // ЕГН
        students[i].overallScore,                        // Оценка
        COLOR_RED, students[i].uniqueKey, COLOR_RESET    // Уникален ключ
    );
}

// Rewritten searchStudents() function
void searchStudents() {
    char criteria[50];
    int choice;
    int found = 0;

    printf("Search by:\n");
    printf("1. Name\n");
    printf("2. Surname\n");
    printf("3. Last name\n");
    printf("4. Grade\n");
    printf("5. EGN\n");
    printf("6. Score\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Go on: ");
    scanf("%s", criteria);

    printf("\nFound student(s):\n");
    for (int i = 0; i < student_count; i++) {
        switch (choice) {
            case 1:
                if (strstr(students[i].firstName, criteria)) {
                    printStudentInfo(i);
                    found++;
                }
                break;
            case 2:
                if (strstr(students[i].surname, criteria)) {
                    printStudentInfo(i);
                    found++;
                }
                break;
            case 3:
                if (strstr(students[i].lastName, criteria)) {
                    printStudentInfo(i);
                    found++;
                }
                break;
            case 4:
                if (students[i].grade == atoi(criteria)) {
                    printStudentInfo(i);
                    found++;
                }
                break;
            case 5:
                if (strcmp(students[i].egn, criteria) == 0) {
                    printStudentInfo(i);
                    found++;
                }
                break;
            case 6:
                if (students[i].overallScore == atoi(criteria)) {
                    printStudentInfo(i);
                    found++;
                }
                break;
            default:
                printf("Invalid choice!\n");
                return;
        }
    }

    if (found == 0) {
        printf("No students found.\n");
    }
}


// Основно меню
void menu() {
    int choice;

    do {
        printf("\n1. Add student\n2. Search student\n3. Show all students\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                searchStudents();
                break;
            case 3:
                showAllStudents();
                break;
            case 4:
                printf("Exit...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);
}

int main() {
    srand(time(NULL));
    menu();
    return 0;
}
