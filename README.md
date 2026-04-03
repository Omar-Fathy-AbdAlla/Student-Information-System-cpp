# Student Information System (SIS)

A comprehensive, terminal-based Student Information System built purely in C++. This academic project was designed to efficiently manage student records and academic data, utilizing custom data structures, file handling for persistent storage, and basic sorting/searching algorithms.

## 🚀 Key Features

* **Complete CRUD Operations:** Add, modify, remove, and display student records via an intuitive 11-option terminal menu.
* **Persistent File Data:** Automatically loads from and saves to `students.txt` using C++ file streams (`<fstream>`), ensuring data is never lost between sessions.
* **Automated GPA Calculation:** Dynamically calculates total GPA based on individual course grades (0-4 scale) and credit hours.
* **Advanced Multi-Criteria Search:** Implements linear search algorithms to find students by their unique ID, National ID, or Full Name (utilizing custom case-insensitive string matching).
* **Multi-Criteria Sorting:** Includes custom-built Bubble Sort algorithms to organize the database alphabetically by Name, ascending by ID, or descending by Total GPA.
* **Data Validation:** Prevents duplicate student IDs, restricts GPA inputs to valid ranges (0-4), limits credit hours (0-5), and caps capacities at 100 students and 10 courses per student to manage memory safely.

## 🛠️ Technical Implementation

* **Language:** C++
* **Core Libraries:** `<iostream>`, `<fstream>`, `<cstring>`, `<iomanip>`
* **Data Structures:** Fixed-size Arrays and Nested Structs (A `Student` struct containing an array of `Course` structs).
* **Algorithms:** Bubble Sort (custom implementation for struct arrays), Linear Search.

## 📋 Menu Navigation

Upon running the program, users interact with the following menu:
1. Display all students info
2. Add a new student
3. Remove a student
4. Search for a student by Name
5. Search for a student by ID
6. Search for a student by National ID
7. Sort students by Name
8. Sort students by Total GPA
9. Sort students by ID
10. Modify data of a student
11. Exit

## 💻 How to Run

1. Clone this repository or download the source code.
2. Open your terminal or command prompt.
3. Compile the code using a standard C++ compiler (like g++):
   ```bash
   g++ Project.cpp -o sis
