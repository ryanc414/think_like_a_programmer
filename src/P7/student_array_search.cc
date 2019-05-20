/*
 * 7-3. Consider a collection of studentRecord objects. We want to be able to quickly
 * find a particular record based on student number. Store the student records
 * in an array, sort the array by student number, and investigate and implement
 * the interpolation search algorithm.
 *
 * 7-5. For the problem in 7-3, implement a solution using a class from the C++ library.
 */

#include <cassert>
#include <iostream>
#include <array>
#include <algorithm>
#include <map>

#include "student.hh"

constexpr int kNumStudents = 10;
const StudentRecord *
InterpolationSearch(std::array<StudentRecord, kNumStudents> students,
                    int student_id);
void TestInterpolationSearch(
    const std::array<StudentRecord, kNumStudents> &students);
void TestStdMap(
    const std::array<StudentRecord, kNumStudents> &students);

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


    TestInterpolationSearch(students);
    TestStdMap(students);

    return 0;
}

// Test the interpolation search function on a sorted array of students.
void TestInterpolationSearch(
    const std::array<StudentRecord, kNumStudents> &students) {

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
}

// Insert students from the sorted array into a std::map and check that they
// can be retrieved.
void TestStdMap(
    const std::array<StudentRecord, kNumStudents> &students) {

    std::map<int, StudentRecord> students_map;

    for (const StudentRecord &student : students) {
        students_map[student.number] = student;
    }

    assert(students_map.at(32).name == "Emily");

    try {
        auto student = students_map.at(99);
        throw std::runtime_error("No exception raised.");
    } catch (std::out_of_range &err) {
        std::cout << "Caught out_of_range: " << err.what() << std::endl;
    }

    std::cout << "std::map assertions passed." << std::endl;
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

