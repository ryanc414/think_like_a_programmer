/*
 * 7-2. Rewrite our studentCollection functions from Chapter 4 (addRecord and
 * averageRecord) so that instead of directly implementing a linked list, you
 * use a class from the C++ library.
 */

#include <iostream>
#include <string>
#include <cassert>
#include <list>

#include "student.hh"

enum class FirstStudentPolicy {
    kHigherGrade,
    kLowerStudentNum,
    kNameComesFirst
};

class StudentCollection {
  public:
    // Modifiers.
    void AddRecord(int student_num, int grade, std::string name);
    bool RemoveRecord(int student_num);

    // Return information from the collection.
    int CountRecords() const;
    double AverageRecords() const;
    StudentCollection RecordsWithinRange(int lower, int upper) const;
    const StudentRecord *FirstStudent(FirstStudentPolicy policy) const;

  private:
    // Student records are stored in a std::list.
    std::list<StudentRecord> students_;

    // Helper functions for choosing the first student according to each
    // policy.
    const StudentRecord *HighestGradeStudent_() const;
    const StudentRecord *LowestNumStudent_() const;
    const StudentRecord *FirstNameStudent_() const;
};

std::ostream &
operator<<(std::ostream &stream, const StudentRecord &student);
void TestFirstStudent(StudentCollection &sc);


int main() {
    StudentCollection sc;

    // Add four records to the collection.
    sc.AddRecord(44, 87, "Andy");
    sc.AddRecord(55, 54, "Bill");
    sc.AddRecord(21, 92, "Charlie");
    sc.AddRecord(11, 25, "David");

    // Should have 4 records.
    std::cout << "Have " << sc.CountRecords() << " records in collection."
              << std::endl;
    assert(sc.CountRecords() == 4);

    // Remove one record - should now have 3.
    assert(sc.RemoveRecord(21));
    std::cout << "Now have " << sc.CountRecords() << " records in collection."
              << std::endl;
    assert(sc.CountRecords() == 3);

    // Try and remove a record that doesn't exist - should still have 3 in
    // the collection.
    assert(!sc.RemoveRecord(-7));
    assert(sc.CountRecords() == 3);

    // Find the average grade.
    std::cout << "Average grade = " << sc.AverageRecords() << std::endl;

    // Add some more records.
    sc.AddRecord(84, 81, "Emily");
    sc.AddRecord(38, 43, "Frances");
    sc.AddRecord(75, 77, "Geraldine");

    // Filter the records into a new collection for grades between 70-90.
    StudentCollection filtered_sc = sc.RecordsWithinRange(70, 90);
    std::cout << "Have " << filtered_sc.CountRecords()
              << " records within the range 70-90." << std::endl;
    assert(filtered_sc.CountRecords() == 3);

    TestFirstStudent(sc);

    return 0;
}

// Test the FirstStudent method on all three policies.
void TestFirstStudent(StudentCollection &sc) {
    const StudentRecord *student = sc.FirstStudent(
        FirstStudentPolicy::kHigherGrade);
    assert(student != nullptr);
    std::cout << "Highest grade student = " << *student << std::endl;
    assert(student->number == 44);

    student = sc.FirstStudent(FirstStudentPolicy::kLowerStudentNum);
    assert(student != nullptr);
    std::cout << "Lowest number student = " << *student << std::endl;
    assert(student->number == 11);

    student = sc.FirstStudent(FirstStudentPolicy::kNameComesFirst);
    assert(student != nullptr);
    std::cout << "Alphabetically first student = " << *student << std::endl;
    assert(student->number == 44);

    std::cout << "FirstStudent assertions passed." << std::endl;
}

// Adds a new record to the head of the list.
void
StudentCollection::AddRecord(int student_num, int grade, std::string name) {
    students_.emplace_front(student_num, grade, name);
}

// Remove a record that matches the given student num. Returns true if the
// record was found and deleted, false otherwise.
bool StudentCollection::RemoveRecord(int student_num) {
    // Loop through the list of students looking for a matching
    // student_num.
    for (auto it = students_.begin(); it != students_.end(); ++it) {
        if (it->number == student_num) {
            // Remove the matching record from the list and delete it.
            students_.erase(it);
            return true;
        }
    }

    return false;
}

// Count the number of records in the collection.
int StudentCollection::CountRecords() const {
    return students_.size();
}

// Return the average of all grades in the collection.
double StudentCollection::AverageRecords() const {
    double grade_sum = 0;
    int count = 0;

    for (const StudentRecord &student : students_) {
        grade_sum += static_cast<double>(student.grade);
        ++count;
    }

    return grade_sum / static_cast<double>(count);
}

// Return a new StudentCollection containing records from this collection
// with grades within the given range (inclusive).
StudentCollection
StudentCollection::RecordsWithinRange(int lower, int upper) const {
    StudentCollection new_collection;

    for (const StudentRecord student : students_) {
        if ((student.grade >= lower) &&
            (student.grade <= upper)) {
            new_collection.AddRecord(student.number,
                                     student.grade,
                                     student.name);
        }
    }

    return new_collection;
}

// Returns the "first" student in the collection according to the chosen
// policy.
const StudentRecord *
StudentCollection::FirstStudent(FirstStudentPolicy policy) const {
    switch (policy) {
        case FirstStudentPolicy::kHigherGrade:
            return HighestGradeStudent_();

        case FirstStudentPolicy::kLowerStudentNum:
            return LowestNumStudent_();

        case FirstStudentPolicy::kNameComesFirst:
            return FirstNameStudent_();

        // Even though we covered all possible enums, a default case is
        // still required to silence "control reaches end of non-void function"
        // compile error.
        default:
            throw std::runtime_error("Invalid first student policy");
    }
}

const StudentRecord *StudentCollection::HighestGradeStudent_() const {
    const StudentRecord *highest_grade_student = nullptr;

    for (const StudentRecord &student : students_) {
        if ((highest_grade_student == nullptr) ||
            (student.grade > highest_grade_student->grade)) {
            highest_grade_student = &student;
        }
    }

    return highest_grade_student;
}

const StudentRecord *StudentCollection::LowestNumStudent_() const {
    const StudentRecord *lowest_num_student = nullptr;

    for (const StudentRecord &student : students_) {
        if ((lowest_num_student == nullptr) ||
            (student.number < lowest_num_student->number)) {
            lowest_num_student = &student;
        }
    }

    return lowest_num_student;
}

const StudentRecord *StudentCollection::FirstNameStudent_() const {
    const StudentRecord *first_name_student = nullptr;

    for (const StudentRecord &student : students_) {
        if ((first_name_student == nullptr) ||
            (student.name < first_name_student->name)) {
            first_name_student = &student;
        }
    }

    return first_name_student;
}

// Enable a StudentRecord to be printed to stdout.
std::ostream &
operator<<(std::ostream &stream, const StudentRecord &student) {
    stream << "Student[number = " << student.number
           << ", grade = " << student.grade
           << ", name = " << student.name;
    return stream;
}

