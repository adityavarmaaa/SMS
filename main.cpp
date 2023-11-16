#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <iomanip>

using namespace std;

// Student structure to hold student information
struct Student {
    char firstName[50];
    char lastName[50];
    int age;
    double grade;
};

// Function prototypes
void displayMenu();
void addStudent();
void viewStudents();
void searchStudent();
void modifyStudent();
void deleteStudent();
void writeToFile(Student);
void readFromFile();

int main() {
    readFromFile(); // Load existing data from the file

    int choice;

    do {
        displayMenu();
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                modifyStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }

    } while (choice != 6);

    return 0;
}

// Function to display the menu
void displayMenu() {
    cout << "\n====== Student Management System ======\n";
    cout << "1. Add Student\n";
    cout << "2. View Students\n";
    cout << "3. Search Student\n";
    cout << "4. Modify Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Exit\n";
    cout << "=======================================\n";
}

// Function to add a new student
void addStudent() {
    Student newStudent;

    cout << "Enter First Name: ";
    cin >> newStudent.firstName;
    cout << "Enter Last Name: ";
    cin >> newStudent.lastName;
    cout << "Enter Age: ";
    cin >> newStudent.age;
    cout << "Enter Grade: ";
    cin >> newStudent.grade;

    writeToFile(newStudent);
    cout << "Student added successfully!\n";
}

// Function to view all students
void viewStudents() {
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading.\n";
        exit(EXIT_FAILURE);
    }

    Student currentStudent;
    cout << "\n====== List of Students ======\n";
    cout << left << setw(20) << "Name" << setw(5) << "Age" << setw(10) << "Grade" << "\n";
    cout << "-----------------------------------\n";

    while (inFile.read(reinterpret_cast<char*>(&currentStudent), sizeof(Student))) {
        cout << left << setw(20) << strcat(strcat(currentStudent.firstName, " "), currentStudent.lastName);
        cout << setw(5) << currentStudent.age << setw(10) << fixed << setprecision(2) << currentStudent.grade << "\n";
    }

    cout << "-----------------------------------\n";
    inFile.close();
}

// Function to search for a student by name
void searchStudent() {
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading.\n";
        exit(EXIT_FAILURE);
    }

    char searchName[50];
    cout << "Enter the name of the student to search: ";
    cin.ignore(); // Clear the newline character from the buffer
    cin.getline(searchName, 50);

    Student currentStudent;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&currentStudent), sizeof(Student))) {
        if (strstr(currentStudent.firstName, searchName) || strstr(currentStudent.lastName, searchName)) {
            cout << "Student Found!\n";
            cout << "Name: " << currentStudent.firstName << " " << currentStudent.lastName << "\n";
            cout << "Age: " << currentStudent.age << "\n";
            cout << "Grade: " << fixed << setprecision(2) << currentStudent.grade << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student not found.\n";
    }

    inFile.close();
}

// Function to modify student information
void modifyStudent() {
    ifstream inFile("students.dat", ios::binary);
    ofstream tempFile("temp.dat", ios::binary);

    if (!inFile || !tempFile) {
        cerr << "Error opening files for modification.\n";
        exit(EXIT_FAILURE);
    }

    char modifyName[50];
    cout << "Enter the name of the student to modify: ";
    cin.ignore(); // Clear the newline character from the buffer
    cin.getline(modifyName, 50);

    Student currentStudent;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&currentStudent), sizeof(Student))) {
        if (strstr(currentStudent.firstName, modifyName) || strstr(currentStudent.lastName, modifyName)) {
            cout << "Student Found!\n";
            cout << "Current Information:\n";
            cout << "Name: " << currentStudent.firstName << " " << currentStudent.lastName << "\n";
            cout << "Age: " << currentStudent.age << "\n";
            cout << "Grade: " << fixed << setprecision(2) << currentStudent.grade << "\n";

            // Modify information
            cout << "Enter new information:\n";
            cout << "Enter First Name: ";
            cin >> currentStudent.firstName;
            cout << "Enter Last Name: ";
            cin >> currentStudent.lastName;
            cout << "Enter Age: ";
            cin >> currentStudent.age;
            cout << "Enter Grade: ";
            cin >> currentStudent.grade;

            found = true;
        }

        tempFile.write(reinterpret_cast<char*>(&currentStudent), sizeof(Student));
    }

    if (!found) {
        cout << "Student not found.\n";
    }

    inFile.close();
    tempFile.close();

    // Replace the original file with the modified data
    remove("students.dat");
    rename("temp.dat", "students.dat");

    cout << "Modification complete.\n";
}

// Function to delete a student
void deleteStudent() {
    ifstream inFile("students.dat", ios::binary);
    ofstream tempFile("temp.dat", ios::binary);

    if (!inFile || !tempFile) {
        cerr << "Error opening files for deletion.\n";
        exit(EXIT_FAILURE);
    }

    char deleteName[50];
    cout << "Enter the name of the student to delete: ";
    cin.ignore(); // Clear the newline character from the buffer
    cin.getline(deleteName, 50);

    Student currentStudent;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&currentStudent), sizeof(Student))) {
        if (strstr(currentStudent.firstName, deleteName) || strstr(currentStudent.lastName, deleteName)) {
            cout << "Student Found!\n";
            cout << "Deleted Information:\n";
            cout << "Name: " << currentStudent.firstName << " " << currentStudent.lastName << "\n";
            cout << "Age: " << currentStudent.age << "\n";
            cout << "Grade: " << fixed << setprecision(2) << currentStudent.grade << "\n";
            found = true;
        } else {
            tempFile.write(reinterpret_cast<char*>(&currentStudent), sizeof(Student));
        }
    }

    if (!found) {
        cout << "Student not found.\n";
    }

    inFile.close();
    tempFile.close();

    // Replace the original file with the modified data
    remove("students.dat");
    rename("temp.dat", "students.dat");

    cout << "Deletion complete.\n";
}

// Function to write a student to the file
void writeToFile(Student newStudent) {
    ofstream outFile("students.dat", ios::binary | ios::app);
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        exit(EXIT_FAILURE);
    }

    outFile.write(reinterpret_cast<char*>(&newStudent), sizeof(Student));
    outFile.close();
}

// Function to read data from the file and display it
void readFromFile() {
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        // If the file doesn't exist, it will be created when adding the first student
        return;
    }

    Student currentStudent;

    cout << "\n====== Students Loaded from File ======\n";
    while (inFile.read(reinterpret_cast<char*>(&currentStudent), sizeof(Student))) {
        cout << "Name: " << currentStudent.firstName << " " << currentStudent.lastName << "\n";
        cout << "Age: " << currentStudent.age << "\n";
        cout << "Grade: " << fixed << setprecision(2) << currentStudent.grade << "\n";
        cout << "----------------------------\n";
    }

    cout << "=======================================\n";
    inFile.close();
}
