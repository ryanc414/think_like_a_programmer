/* Are you disappointed we didn't do more with sorting? I'm here to help. To
 * make sure you are comfortable with qsort, write code that uses the function
 * to sort an array of our Student struct. First have it sort by grade, and
 * then try it again using the Student ID.
 *
 * Write a program that processes an array of student objects and determines
 * the grade quartiles - that is, the grade one would need to score as well as or
 * better than 25% of the students, 50% of the students, and 75% of the students.
 */
#include <iostream>
#include <string>
#include <array>
#include <algorithm>

struct Student {
    int grade;
    int student_id;
    std::string name;
};
constexpr int kArraySize = 10;

void SortByGrade(std::array<const Student *, kArraySize> &students);
void SortById(std::array<const Student *, kArraySize> &students);
std::ostream& operator<<(std::ostream &strm, Student const &stud);
void PrintPercentiles(std::array<const Student *, kArraySize> &students);
double MedianGrade(const Student **students, const int num_students);

// Set up an array of Students, to be std::sorted.
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
    std::array<const Student *, kArraySize> student_pointers;

    // Set up an array of pointers to the Students defined in the Student
    // array. We will sort this pointer array for efficiency.
    for (int i = 0; i < kArraySize; ++i) {
        student_pointers[i] = &kStudents[i];
    }

    SortByGrade(student_pointers);
    SortById(student_pointers);

    return 0;
}

// Sort the array of Students by grade and print it.
void SortByGrade(std::array<const Student *, kArraySize> &students) {
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

    // In addition, print out information on the percentiles of grades
    // using the sorted array.
    PrintPercentiles(students);
}

// Sort the array of Students by their ID and print it.
void SortById(std::array<const Student *, kArraySize> &students) {
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

// Print out the 25, 50 and 75 percentile grades from the array of students
// that has already been sorted ing grade order.
void PrintPercentiles(std::array<const Student *, kArraySize> &students) {
    // To calculate the lower and upper quartiles, calculate the medians of
    // the respective lower and upper sub-arrays. Round the size up so that
    // the middle value is included in both sub-arrays in case of an odd
    // array size.
    const int rounded_half_size = (students.size() + 1) / 2;
    const double Percentile25 = MedianGrade(
        students.data(), rounded_half_size);
    const double Percentile50 = MedianGrade(students.data(), students.size());
    const double Percentile75 = MedianGrade(
        students.data() + students.size() / 2, rounded_half_size);

    std::cout << "25 percentile: " << Percentile25 << std::endl
              << "50 percentile: " << Percentile50 << std::endl
              << "75 percentile: " << Percentile75 << std::endl
              << std::endl;
}


double MedianGrade(const Student **students, const int num_students) {
    int middle = num_students / 2;

    if (num_students % 2 == 0) {
        return static_cast<double>(
            students[middle - 1]->grade + students[middle]->grade) / 2.0;
    } else {
        return static_cast<double>(students[middle]->grade);
    }
}

