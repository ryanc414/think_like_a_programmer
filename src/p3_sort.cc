/* Are you disappointed we didn't do more with sorting? I'm here to help. To
 * make sure you are comfortable with qsort, write code that uses the function
 * to sort an array of our student struct. First have it sort by grade, and
 * then try it again using the student ID.
 */
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::array;
using std::vector;
using std::sort;
using std::ostream;

struct student {
    int grade;
    int studentID;
    string name;
};

void sort_by_grade(vector<const student *> &students);
void sort_by_id(vector<const student *> &students);
ostream & operator<<(ostream &strm, student const &stud);

// Set up an array of students, to be sorted.
const int ARRAY_SIZE = 10;
const array<const student, ARRAY_SIZE> STUDENTS = {{
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
}};

// Sort the student array by both grade and ID.
int main()
{
    vector<const student *> student_pointers;

    // Set up a vector of pointers to the students defined in studentArray.
    // We will sort this pointer array for efficiency.
    student_pointers.reserve(ARRAY_SIZE);
    for (const student &std : STUDENTS) {
        student_pointers.push_back(&std);
    }

    sort_by_grade(student_pointers);
    sort_by_id(student_pointers);

    return 0;
}

// Sort the array of students by grade and print it.
void sort_by_grade(vector<const student *> &students)
{
    sort(students.begin(),
         students.end(),
         [](const student *a, const student *b) {
             return a->grade < b->grade;
    });

    cout << "Students sorted by grade:" << endl;
    for (const student *std : students) {
        cout << *std << endl;
    }
    cout << endl;
}

// Sort the array of students by their ID and print it.
void sort_by_id(vector<const student *> &students)
{
    sort(students.begin(),
         students.end(),
         [](const student *a, const student *b) {
             return a->studentID < b->studentID;
    });

    cout << "Students sorted by ID:" << endl;
    for (const student *std : students) {
        cout << *std << endl;
    }
}

// Enable printing of student via cout.
ostream & operator<<(ostream &strm, student const &stud)
{
    return strm << stud.name << ": ID = " << stud.studentID << ", grade = "
                << stud.grade;
}

