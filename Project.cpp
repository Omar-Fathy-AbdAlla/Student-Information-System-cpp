#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

const int max_students = 100;
const int max_courses = 10;

struct Course {
    char course_name[50];
    float grade;
    int credit_hours;
};

struct Student {
    int id;
    char name[50];
    char nationalID[20];
    char gender[10];
    char major[50];
    int course_num;
    Course courses[max_courses];  //nested struct
    float GPA;
};

Student students[max_students];
int student_count = 0;

// Used in sorting and searching by name
void to_lowercase(char str[]) {
    int len = strlen(str);  
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
}

// Swaps two student objects using a temporary variable, it's used in sorting
void swapStudents(Student &a, Student &b) {
    Student temp = a;
    a = b;
    b = temp; 
}

void calcGPA(Student &st) {
    float total_grades = 0;
    int total_hours = 0;
    for (int i = 0; i < st.course_num; i++) {
        total_grades += st.courses[i].grade * st.courses[i].credit_hours;
        total_hours += st.courses[i].credit_hours;
    }
    if (total_hours != 0)
        st.GPA = total_grades / total_hours;
    else
        st.GPA = 0;
}

// Handle input of no. of courses, their credit hours, and their GPAs
void coursesInput(Student &st) {
    // Validate course count
    do {
        cout << "Enter number of courses (1 - " << max_courses << "): ";
        cin >> st.course_num;
        if (st.course_num < 1 || st.course_num > max_courses) {
            cout << "Invalid number of courses! Please enter a number between 1 and " << max_courses << ".\n";
        }
    } while (st.course_num < 1 || st.course_num > max_courses);

    //Input each course data
    for (int i = 0; i < st.course_num; i++) {
        cout << "Enter course " << i + 1 << " name: ";
        cin.ignore();
        cin.getline(st.courses[i].course_name, 50);

        // GPA input (between 0 and 4)
        do {
            cout << "Enter course " << i + 1 << " GPA (0 - 4): ";
            cin >> st.courses[i].grade;
            if (st.courses[i].grade < 0 || st.courses[i].grade > 4) {
                cout << "Invalid GPA! GPA must be between 0 and 4. Please re-enter.\n";
            }
        } while (st.courses[i].grade < 0 || st.courses[i].grade > 4);

        // credit hours input (between 0 and 5)
        do {
            cout << "Enter course " << i + 1 << " credit hours (0 - 5): ";
            cin >> st.courses[i].credit_hours;
            if (st.courses[i].credit_hours < 0 || st.courses[i].credit_hours > 5) {
                cout << "Invalid input! Credit hours must be between 0 and 5. Please re-enter.\n";
            }
        } while (st.courses[i].credit_hours < 0 || st.courses[i].credit_hours > 5);
    }
}

//Function to pause the program after any menu fuction is done, and wait for the user to press Enter to go back to the menu
void waitForEnter() {
    cout << "Press Enter to return to the menu...";
    cin.ignore();
    cin.get();
}

//Saves student records to file
void saveStudentsToFile() {
    ofstream outFile("students.txt", ios::trunc);
    if (!outFile) {
        cout << "Error: Unable to open students.txt for writing.\n";
        return; }
    for (int i = 0; i < student_count; i++) {
        outFile << students[i].id << "\t"
                << students[i].name << "\t"
                << students[i].nationalID << "\t"
                << students[i].gender << "\t"
                << students[i].major << "\t"
                << students[i].course_num << "\t";
        for (int j = 0; j < students[i].course_num; j++) {
            outFile << students[i].courses[j].course_name << "\t"
                    << students[i].courses[j].grade << "\t"
                    << students[i].courses[j].credit_hours << "\t";
        }
        outFile << students[i].GPA << endl;
    }
    outFile.close();
}

// Loads student data from file into the students array
void loadStudentsFromFile() {
    ifstream inFile("students.txt");
    if (!inFile)
        return;
    
    student_count = 0;  // resets the counter to ensure that program starts with an empty list before filling it with student data from the file.

    while (inFile >> students[student_count].id) {
        inFile.ignore(); // Skip the tab after ID

        inFile.getline(students[student_count].name, 50, '\t');
        inFile.getline(students[student_count].nationalID, 20, '\t');
        inFile.getline(students[student_count].gender, 10, '\t');
        inFile.getline(students[student_count].major, 50, '\t');

        inFile >> students[student_count].course_num;
        inFile.ignore();

        // Read each course data for the current student
        for (int j = 0; j < students[student_count].course_num; j++) {
            inFile.getline(students[student_count].courses[j].course_name, 50, '\t');
            inFile >> students[student_count].courses[j].grade;
            inFile.ignore(); 
            inFile >> students[student_count].courses[j].credit_hours;
            inFile.ignore(); 
        }

        inFile >> students[student_count].GPA;
        inFile.ignore(); 
        student_count++;
    }

    inFile.close();
}

// Adding a new student
void add_student() {
    if (student_count >= max_students) {
        cout << "Maximum student limit reached!\n";
        waitForEnter();
        return;
    }
        
    Student st;
    do {
        cout << "Enter student ID (non-negative & no characters!!): ";
        cin >> st.id;
        if (st.id < 0) {
            cout << "Invalid ID! Please enter a non-negative number.\n";
        }
    } while (st.id < 0);
    // Check for duplicate ID
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == st.id) {
            cout << "Error: A student with this ID already exists!\n";
            waitForEnter();
            return;
        }
    }
    cin.ignore();    
    cout << "Enter student full name: ";
    cin.getline(st.name, 50);

    cout << "Enter student National ID: ";
    cin.getline(st.nationalID, 20); 

    cout << "Enter student gender: ";
    cin.getline(st.gender, 10); 
    
    cout << "Enter student major: ";
    cin.getline(st.major, 50); 
    
    // Call the function to input courses data
    coursesInput(st);
    // Calculate GPA
    calcGPA(st);

    // Add the new student to the array and save to file
    students[student_count++] = st;
    saveStudentsToFile();
    cout << "Student added successfully!\n";
    waitForEnter();
 
}

// Delete student by ID
void delete_student() {
    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            // Shift students left to overwrite deleted entry
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            saveStudentsToFile();
            cout << "Student deleted successfully!\n";
            waitForEnter();
            return;
        }
    }
    cout << "Student not found!\n";
    waitForEnter();
}

// Modify student data
void modify_student() {
    int id;
    cout << "Enter student ID to modify: ";
    cin >> id;
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            cin.ignore(); 
            cout << "Enter new full name: ";
            cin.getline(students[i].name, 50);

            cout << "Enter new National ID: ";
            cin.getline(students[i].nationalID, 20);

            cout << "Enter new gender: ";
            cin.getline(students[i].gender, 10);

            cout << "Enter new major: ";
            cin.getline(students[i].major, 50);

            coursesInput(students[i]);
            calcGPA(students[i]);
            //Save new student data to the file
            saveStudentsToFile();
            cout << "Student data modified!\n";
            waitForEnter(); 
            return;
        }
    }
    cout << "Student not found!\n";
    waitForEnter(); 
}

void search_byName() {
    char name[50];
    char studentName[50];
    cout << "Enter student's full name to search: ";
    cin.ignore();  
    cin.getline(name, 50); 
    
    to_lowercase(name);

    for (int i = 0; i < student_count; i++) {
        strcpy(studentName, students[i].name);  // Copy the student name to a temporary variable (first, second, etc.., until name is found, or the students array end)
        
        to_lowercase(studentName);

        if (strcmp(studentName, name) == 0) {
            cout << "Student Found: " << students[i].name << ", GPA: " << fixed << setprecision(2) << students[i].GPA << endl;
            cout << "Courses:\n";
            for (int j = 0; j < students[i].course_num; j++) {
                cout << j+1 << "- " << students[i].courses[j].course_name << endl;
            }
            cout << "Press Enter to return to the menu...";
            cin.get();
            return;
        }
    }
    
    cout << "Student not found!\n";
    cout << "Press Enter to return to the menu...";
    cin.get();
}

void search_byID() {
    int id;
    cout << "Enter student's ID to search: ";
    cin >> id;
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            cout << "Student Found: " << students[i].name << ", GPA: " << fixed << setprecision(2) << students[i].GPA << endl;
            cout << "Courses:\n";
        for (int j = 0; j < students[i].course_num; j++) {
            cout << j+1 <<"-  " << students[i].courses[j].course_name << endl;
        }
            waitForEnter();
            return;
        }
    }
    cout << "Student with ID " << id << " was not found.\n";
    waitForEnter();
}

void search_byNationalID() {
    char National_ID[20];
    cout << "Enter student's National ID to search: ";
    cin >> National_ID;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].nationalID, National_ID) == 0) {
            cout << "Student Found: " << students[i].name << ", GPA: " << fixed << setprecision(2) << students[i].GPA << endl;
            cout << "Courses:\n";
        for (int j = 0; j < students[i].course_num; j++) {
            cout << j+1 <<"-  " << students[i].courses[j].course_name << endl;
        }
            waitForEnter();
            return;
        }
    }
    cout << "Student not found!\n";
    waitForEnter();
}

// Sort by ID in ascending order
void sort_byID() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (students[i].id > students[j].id) {
                swapStudents(students[i], students[j]);
            }
        }
    }
    cout << "Students sorted by ID.\n";
    waitForEnter();
}

// Sort by name in alphabetical order
void sort_byName() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = i + 1; j < student_count; j++) {
            char name1[50], name2[50];
            
            strcpy(name1, students[i].name);
            strcpy(name2, students[j].name);
            to_lowercase(name1);
            to_lowercase(name2);
            if (strcmp(name1, name2) == 1) {
                swapStudents(students[i], students[j]);
            }
        }
    }
    cout << "Students sorted by Name.\n";
    waitForEnter();
}

// Sort by GPA in descending order
void sort_byGPA() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (students[i].GPA < students[j].GPA) {
                swapStudents(students[i], students[j]);
            }
        }
    }
    cout << "Students sorted by Total GPA Score.\n";
    waitForEnter();
}

// Displays all students and their information, including their study plan
void display_students() {
    if (student_count == 0) {
        cout << "No student data found.\n";
        waitForEnter();
        return;
    }
    for (int i = 0; i < student_count; i++) {
        cout << "------------------------\n";
        cout << "ID: " << students[i].id << endl;
        cout << "Name: " << students[i].name << endl;
        cout << "National ID: " << students[i].nationalID << endl;
        cout << "Gender: " << students[i].gender << endl;
        cout << "Major: " << students[i].major << endl;
        cout << "GPA: " << fixed << setprecision(2) << students[i].GPA << endl;
        cout << "Courses:\n";
        for (int j = 0; j < students[i].course_num; j++) {
            cout << j+1 <<"-  " << students[i].courses[j].course_name << endl;
        }
    }
    waitForEnter();
}

void display_MainMenu() {
    cout << "\n===== Student Information System =====\n";
    cout << "1. Display all students info\n";
    cout << "2. Add a new student\n";
    cout << "3. Remove a student\n";
    cout << "4. Search for a student by Name\n";
    cout << "5. Search for a student by ID\n";
    cout << "6. Search for a student by National ID\n";
    cout << "7. Sort students by Name\n";
    cout << "8. Sort students by Total GPA\n";
    cout << "9. Sort students by ID\n";
    cout << "10. Modify data of a student\n";
    cout << "11. Exit\n";
}

int main() {
    loadStudentsFromFile();
    int choice;
    do {
        display_MainMenu();
        cout << "\n Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: display_students(); break;
            case 2: add_student(); break;
            case 3: delete_student(); break;
            case 4: search_byName(); break;
            case 5: search_byID(); break;
            case 6: search_byNationalID(); break;
            case 7: sort_byName(); break;
            case 8: sort_byGPA(); break;
            case 9: sort_byID(); break;
            case 10: modify_student(); break;
            case 11: cout << "Exiting program...\n"; break;
            default: {
                cout << "Invalid choice! Try again.\n";
                waitForEnter();
            }
        }
    } while (choice != 11);
    return 0;
}