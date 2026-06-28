#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
using namespace std;
/*
=========================================
Student Management System
=========================================

Features:
- Add Student
- View Students
- Search Student
- Update Student
- Delete Student
- File Handling
- Input Validation

Concepts Used:
- OOP
- Encapsulation
- Inheritance
- File Handling

Developed By: Your Name
=========================================
*/

//================ PERSON CLASS ================

class Person
{
protected:
    string name;
    int age;

public:
    void setPersonData(string n, int a)
    {
        name = n;
        age = a;
    }

    string getName()
    {
        return name;
    }

    int getAge()
    {
        return age;
    }
};

//================ VALIDATION CLASS ================

class Validation
{
public:
    static bool validAge(int age)
    {
        return (age >= 16 && age <= 40);
    }

    static bool validCGPA(float cgpa)
    {
        return (cgpa >= 0.0 && cgpa <= 4.0);
    }
};

//================ STUDENT CLASS ================

class Student : public Person
{
private:
    string studentID;
    string department;
    float cgpa;

public:
    void saveToFile()
{
    ofstream file("students.txt", ios::app);

    if(file.is_open())
    {
        file << studentID << ","
             << name << ","
             << age << ","
             << department << ","
             << cgpa << endl;

        file.close();

        cout << "\nStudent record saved successfully!\n";
    }
    else
    {
        cout << "\nError opening file.\n";
    }
}

    void inputStudent()
    {
     do
{
    cout << "Enter Student ID: ";
    cin >> studentID;

    if(idExists(studentID))
    {
        cout << "Student ID already exists. Enter a different ID.\n";
    }

} while(idExists(studentID));   

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        do
        {
            cout << "Enter Age (16-40): ";
            cin >> age;

            if (!Validation::validAge(age))
                cout << "Invalid Age! Try Again.\n";

        } while (!Validation::validAge(age));

        cin.ignore();

        cout << "Enter Department: ";
        getline(cin, department);

        do
        {
            cout << "Enter CGPA (0.0 - 4.0): ";
            cin >> cgpa;

            if (!Validation::validCGPA(cgpa))
                cout << "Invalid CGPA! Try Again.\n";

        } while (!Validation::validCGPA(cgpa));
    }

    void displayStudent()
    {
        cout << "\n===== STUDENT RECORD =====\n";
        cout << "Student ID : " << studentID << endl;
        cout << "Name       : " << name << endl;
        cout << "Age        : " << age << endl;
        cout << "Department : " << department << endl;
        cout << "CGPA       : " << cgpa << endl;
    }

    void viewStudents()
{
    ifstream file("students.txt");

    if(!file)
    {
        cout << "\nNo student records found.\n";
        return;
    }

    string id, name, age, department, cgpa;
    bool found = false;

    cout << "\n==============================================================\n";
    cout << "ID\tName\t\tAge\tDepartment\tCGPA\n";
    cout << "==============================================================\n";

    while(getline(file, id, ',') &&
          getline(file, name, ',') &&
          getline(file, age, ',') &&
          getline(file, department, ',') &&
          getline(file, cgpa))
    {
        found = true;

        cout << id << "\t"
             << name << "\t\t"
             << age << "\t"
             << department << "\t\t"
             << cgpa << endl;
    }

    if(!found)
    {
        cout << "\nNo student records found.\n";
    }

    file.close();
}

void searchStudent()
{
    string searchID;

    cout << "\nEnter Student ID to Search: ";
    cin >> searchID;

    ifstream file("students.txt");

    string id, name, age, department, cgpa;
    bool found = false;

    while(getline(file, id, ',') &&
          getline(file, name, ',') &&
          getline(file, age, ',') &&
          getline(file, department, ',') &&
          getline(file, cgpa))
    {
        if(id == searchID)
        {
            cout << "\n===== STUDENT FOUND =====\n";

            cout << "ID         : " << id << endl;
            cout << "Name       : " << name << endl;
            cout << "Age        : " << age << endl;
            cout << "Department : " << department << endl;
            cout << "CGPA       : " << cgpa << endl;

            found = true;
            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nStudent Not Found!\n";
    }
}
void updateStudent()
{
    string updateID;

    cout << "\nEnter Student ID to Update: ";
    cin >> updateID;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    string id, name, age, department, cgpa;
    bool found = false;

    while(getline(file, id, ',') &&
          getline(file, name, ',') &&
          getline(file, age, ',') &&
          getline(file, department, ',') &&
          getline(file, cgpa))
    {
        if(id == updateID)
        {
            found = true;

            string newName;
            int newAge;
            string newDepartment;
            float newCGPA;

            cin.ignore();

            cout << "Enter New Name: ";
            getline(cin, newName);

            do
{
    cout << "Enter New Age (16-40): ";
    cin >> newAge;

    if(!Validation::validAge(newAge))
    {
        cout << "Invalid Age!\n";
    }

} while(!Validation::validAge(newAge));

            cin.ignore();

            cout << "Enter New Department: ";
            getline(cin, newDepartment);

            do
{
    cout << "Enter New CGPA (0.0 - 4.0): ";
    cin >> newCGPA;

    if(!Validation::validCGPA(newCGPA))
    {
        cout << "Invalid CGPA!\n";
    }

} while(!Validation::validCGPA(newCGPA));

            temp << id << ","
                 << newName << ","
                 << newAge << ","
                 << newDepartment << ","
                 << newCGPA << endl;

            cout << "\nStudent Updated Successfully!\n";
        }
        else
        {
            temp << id << ","
                 << name << ","
                 << age << ","
                 << department << ","
                 << cgpa << endl;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(!found)
    {
        cout << "\nStudent Not Found!\n";
    }
}
void deleteStudent()
{
    string deleteID;

    cout << "\nEnter Student ID to Delete: ";
    cin >> deleteID;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    string id, name, age, department, cgpa;
    bool found = false;

    while(getline(file, id, ',') &&
          getline(file, name, ',') &&
          getline(file, age, ',') &&
          getline(file, department, ',') &&
          getline(file, cgpa))
    {
        if(id == deleteID)
        {
            found = true;
            continue; // Skip this record
        }

        temp << id << ","
             << name << ","
             << age << ","
             << department << ","
             << cgpa << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(found)
    {
        cout << "\nStudent Deleted Successfully!\n";
    }
    else
    {
        cout << "\nStudent Not Found!\n";
    }
}
bool idExists(string searchID)
{
    ifstream file("students.txt");

    string id, name, age, department, cgpa;

    while(getline(file, id, ',') &&
          getline(file, name, ',') &&
          getline(file, age, ',') &&
          getline(file, department, ',') &&
          getline(file, cgpa))
    {
        if(id == searchID)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

};
class StudentManager
{
private:
    Student student;

public:

    void addStudent()
    {
        student.inputStudent();
        student.saveToFile();
    }

    void viewStudents()
    {
        student.viewStudents();
    }

    void searchStudent()
    {
        student.searchStudent();
    }

    void updateStudent()
    {
        student.updateStudent();
    }

    void deleteStudent()
    {
        student.deleteStudent();
    }
};

class Menu
{
public:
    void showMenu()
    {
        cout << "\n====================================";
        cout << "\n   STUDENT MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Add Student";
        cout << "\n2. View Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";
        cout << "\n====================================";
        cout << "\nEnter Choice: ";
    }
};

//================ MAIN FUNCTION ================

int main()
{
    StudentManager manager;
    Menu menu;

    int choice;

    do
    {
        menu.showMenu();
        cin >> choice;

        switch(choice)
        {
        case 1:
               manager.addStudent();
            break;

        case 2:
           manager.viewStudents();
            break;

        case 3:
            manager.searchStudent();
            break;

        case 4:
            manager.updateStudent();
            break;

        case 5:
            manager.deleteStudent();
            break;

        case 6:
            cout << "\n====================================";
            cout << "\n Thank You For Using The System!";
            cout << "\n====================================\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while(choice != 6);

    return 0;
}