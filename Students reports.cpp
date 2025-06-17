#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class Student {
    int rollNo;
    string name;
    int marks[5];
    float percentage;
    char grade;

public:
    void inputData() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter marks for 5 subjects:\n";
        int total = 0;
        for (int i = 0; i < 5; i++) {
            cout << "Subject " << (i + 1) << ": ";
            cin >> marks[i];
            total += marks[i];
        }
        percentage = total / 5.0;

        if (percentage >= 90)
            grade = 'A';
        else if (percentage >= 80)
            grade = 'B';
        else if (percentage >= 70)
            grade = 'C';
        else if (percentage >= 60)
            grade = 'D';
        else
            grade = 'F';
    }

    void displayData() const {
        cout << "\n--- Student Report ---\n";
        cout << "Roll No     : " << rollNo << endl;
        cout << "Name        : " << name << endl;
        cout << "Percentage  : " << fixed << setprecision(2) << percentage << "%" << endl;
        cout << "Grade       : " << grade << endl;
        cout << "----------------------\n";
    }

    void saveToFile(ofstream &outFile) {
        outFile << rollNo << endl;
        outFile << name << endl;
        for (int i = 0; i < 5; i++)
            outFile << marks[i] << " ";
        outFile << endl << percentage << endl << grade << endl;
    }

    bool readFromFile(ifstream &inFile) {
        if (!(inFile >> rollNo))
            return false;
        inFile.ignore();
        getline(inFile, name);
        for (int i = 0; i < 5; i++)
            inFile >> marks[i];
        inFile >> percentage >> grade;
        return true;
    }
};

void addStudent() {
    ofstream outFile("student.txt", ios::app);
    Student s;
    s.inputData();
    s.saveToFile(outFile);
    outFile.close();
    cout << "\nStudent record added successfully!\n";
}

void showAllStudents() {
    ifstream inFile("student.txt");
    Student s;
    bool found = false;
    while (s.readFromFile(inFile)) {
        s.displayData();
        found = true;
    }
    if (!found)
        cout << "\nNo student records found.\n";
    inFile.close();
}

int main() {
    int choice;
    do {
        cout << "\n===== Student Report Card Menu =====\n";
        cout << "1. Add Student Record\n";
        cout << "2. Show All Records\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: showAllStudents(); break;
            case 3: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
