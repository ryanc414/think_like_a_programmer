/* Are you disappointed we didn't do more with sorting? I'm here to help. To
 * make sure you are comfortable with qsort, write code that uses the function
 * to sort an array of our Student struct. First have it sort by grade, and
 * then try it again using the Student ID.
 */
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <vector>

struct Student {
    int grade;
    int student_id;
    std::string name;
};

void SortByGrade(std::vector<const Student *> &students);
void SortById(std::vector<const Student *> &students);
std::ostream& operator<<(std::ostream &strm, Student const &stud);

// Set up an array of Students, to be std::sorted.
constexpr int kArraySize = 10;
const std::array<const Student, kArraySize> kStudents = {{
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

// Sort the Student array by both grade and ID.
int main() {
    std::vector<const Student *> student_pointers;

    // Set up a std::vector of pointers to the Students defined in the Student
    // array. We will sort this pointer array for efficiency.
    student_pointers.reserve(kArraySize);
    for (const Student &std : kStudents) {
        student_pointers.push_back(&std);
    }

    SortByGrade(student_pointers);
    SortById(student_pointers);

    return 0;
}

// Sort the array of Students by grade and print it.
void SortByGrade(std::vector<const Student *> &students) {
    std::sort(students.begin(),
         students.end(),
         [](const Student *a, const Student *b) {
             return a->grade < b->grade;
    });

    std::cout << "Students sorted by grade:" << std::endl;
    for (const Student *std : students) {
        std::cout << *std << std::endl;
    }
    std::cout << std::endl;
}

// sort the array of Students by their ID and print it.
void SortById(std::vector<const Student *> &students) {
    std::sort(students.begin(),
         students.end(),
         [](const Student *a, const Student *b) {
             return a->student_id < b->student_id;
    });

    std::cout << "Students sorted by ID:" << std::endl;
    for (const Student *std : students) {
        std::cout << *std << std::endl;
    }
}

// Enable printing of Student via std::cout.
std::ostream& operator<<(std::ostream &strm, Student const &stud) {
    return strm << stud.name << ": ID = " << stud.student_id << ", grade = "
                << stud.grade;
}

