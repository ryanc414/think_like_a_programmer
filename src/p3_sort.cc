/* Are you disappointed we didn’t do more with sorting? I’m here to help. To
 * make sure you are comfortable with qsort, write code that uses the function
 * to sort an array of our student struct. First have it sort by grade, and
 * then try it again using the student ID.
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

using std::string;
using std::cout;
using std::endl;

struct student {
    int grade;
    int studentID;
    string name;
};

void sort_by_grade();
void sort_by_id();
int comp_grades(const void *a, const void *b);
int comp_id(const void *a, const void *b);
void print_student(student *self);

const int ARRAY_SIZE = 10;
student studentArray[ARRAY_SIZE] = {
    {87, 10001, "Fred"},
    {28, 10002, "Tom"},
    {100, 10003, "Alistair"},
    {78, 10004, "Sasha"},
    {84, 10005, "Erin"},
    {98, 10006, "Belinda"},
    {75, 10007, "Leslie"},
    {70, 10008, "Candy"},
    {81, 10009, "Aretha"},
    {68, 10010, "Veronica"}
};

int main()
{
    sort_by_grade();
    sort_by_id();

    return 0;
}

// Sort the array of students by grade and print it.
void sort_by_grade()
{
    qsort(studentArray, ARRAY_SIZE, sizeof(student), comp_grades);

    cout << "Students sorted by grade:" << endl;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        print_student(&studentArray[i]);
    }
    cout << endl;
}

// Sort the array of students by their ID and print it.
void sort_by_id()
{
    qsort(studentArray, ARRAY_SIZE, sizeof(student), comp_id);

    cout << "Students sorted by ID:" << endl;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        print_student(&studentArray[i]);
    }
    cout << endl;
}

// Comparison function for student grades.
int comp_grades(const void *a, const void *b)
{
    student *student_a = (student *)a;
    student *student_b = (student *)b;

    return student_b->grade - student_a->grade;
}

// Comparison function for student IDs.
int comp_id(const void *a, const void *b)
{
    student *student_a = (student *)a;
    student *student_b = (student *)b;

    return student_b->studentID - student_a->studentID;
}

// Print a string representation of a student.
void print_student(student *self)
{
    cout << self->name << " ID = " << self->studentID <<
            ", grade = " << self->grade << endl;
}

