/*
 * 7-3. Consider a collection of studentRecord objects. We want to be able to quickly
 * find a particular record based on student number. Store the student records
 * in an array, sort the array by student number, and investigate and implement
 * the interpolation search algorithm.
 */

#include <cassert>
#include <iostream>
#include <array>
#include <algorithm>

#include "student.hh"

constexpr int kNumStudents = 10;
const StudentRecord *
InterpolationSearch(std::array<StudentRecord, kNumStudents> students,
                    int student_id);

int main() {
    std::array<StudentRecord, kNumStudents> students{
        StudentRecord(10, 72, "Alan"),
        StudentRecord(23, 62, "Bill"),
        StudentRecord(8, 87, "Charlie"),
        StudentRecord(83, 62, "Dean"),
        StudentRecord(32, 63, "Emily"),
        StudentRecord(62, 88, "Frances"),
        StudentRecord(22, 44, "Graham"),
        StudentRecord(37, 67, "Harrie"),
        StudentRecord(83, 73, "Isaac"),
        StudentRecord(63, 91, "Jessica")
    };

    std::sort(students.begin(), students.end());

    // Check that the expected student record can be found.
    const StudentRecord *student = InterpolationSearch(students, 32);
    assert(student != nullptr);
    assert(student->number == 32);
    assert(student->grade == 63);
    assert(student->name == "Emily");
    std::cout << "Correct record was found." << std::endl;

    // Try searching for a record that doesn't exist - nullptr should be
    // returned.
    assert(InterpolationSearch(students, 50) == nullptr);
    std::cout << "Searching for non-existent ID returned nullptr."
              << std::endl;

    return 0;
}

// Implement operator< for StudentRecord objects so that we can sort them.
// Sort by their ID.
bool StudentRecord::operator<(const StudentRecord &other) const {
    return number < other.number;
}

// Search for a particular student record in an array using interpolation
// search algorithm.
const StudentRecord *
InterpolationSearch(std::array<StudentRecord, kNumStudents> students,
                    int student_id) {
    int lo = 0;
    int hi = kNumStudents - 1;

    while ((lo <= hi) &&
            (student_id >= students[lo].number) &&
            (student_id <= students[hi].number)) {
        if (lo == hi) {
            if (students[lo].number == student_id) {
                return &students[lo];
            } else {
                return nullptr;
            }
        }

        int pos = lo + (
            ((student_id - students[lo].number) * (hi - lo))
            / (students[hi].number - students[lo].number));

        if (students[pos].number == student_id) {
            return &students[pos];
        }

        if (students[pos].number < student_id) {
            lo = pos + 1;
        } else {
            hi = pos - 1;
        }
    }

    return nullptr;
}

