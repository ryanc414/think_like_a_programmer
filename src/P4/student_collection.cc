/*
 * 4-5. Write a function removeRecord that takes a pointer to a studentCollection and a
 * student number and that removes the record with that student number from
 * the collection.
 *
 * 5-7. Take the student record functions from Chapter 4 (addRecord and averageRecord)
 * and use them to create a class representing a collection of student records, as
 * before, making sure to implement all necessary constructors, a destructor,
 * and an overloaded assignment operator.
 *
 * 5-8. For the student record collection class of the previous exercise, add a method
 * RecordsWithinRange that takes a low grade and a high grade as parameters and
 * returns a new collection consisting of the records in that range (the original
 * collection is unaffected). For example, myCollection.RecordsWithinRange(75, 80)
 * would return a collection of all records with grades in the range 75-80 inclusive.
 *
 * 7-1. A complaint offered against the policy/strategy pattern is that it requires exposing
 * some internals of the class, such as types. Modify the first student program
 * from earlier in this chapter so that the policy functions are all stored within
 * the class and are chosen by passing a code value (of a new, enumerated type,
 * for example), instead of passing the policy function itself.
 */

#include <iostream>
#include <string>
#include <cassert>

struct StudentRecord {
    int number;
    int grade;
    std::string name;
};

enum class FirstStudentPolicy {
    kHigherGrade,
    kLowerStudentNum,
    kNameComesFirst
};

class StudentCollection {
  public:
    // Constructors and destructor.
    StudentCollection() : head_(nullptr) {};
    StudentCollection(const StudentCollection &other);
    StudentCollection(StudentCollection &&other);
    ~StudentCollection();

    // Overloaded operators.
    StudentCollection & operator=(const StudentCollection &other);
    StudentCollection & operator=(StudentCollection &&other);
    bool operator!=(const StudentCollection &other);

    // Other public member functions.
    void AddRecord(int student_num, int grade, std::string name);
    bool RemoveRecord(int student_num);
    int CountRecords() const;
    double AverageRecords() const;
    StudentCollection RecordsWithinRange(int lower, int upper);
    StudentRecord *FirstStudent(FirstStudentPolicy policy) const;

  private:
    struct ListNode {
        StudentRecord student;
        ListNode *next;
    } *head_;

    void DeleteList();
    void CopyList(const ListNode *from);
    StudentRecord *HighestGradeStudent_() const;
    StudentRecord *LowestNumStudent_() const;
    StudentRecord *FirstNameStudent_() const;
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
    StudentRecord *student = sc.FirstStudent(FirstStudentPolicy::kHigherGrade);
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

// Copy constructor.
StudentCollection::StudentCollection(const StudentCollection &other) {
    CopyList(other.head_);
}

// Move constructor.
StudentCollection::StudentCollection(StudentCollection &&other) {
    head_ = other.head_;
    other.head_ = nullptr;
}

// Destructor.
StudentCollection::~StudentCollection() {
    DeleteList();
}

// Copy assignment.
StudentCollection &
StudentCollection::operator=(const StudentCollection &other) {
    if (*this != other) {
        DeleteList();
        CopyList(other.head_);
    }

    return *this;

}

// Move assignment.
StudentCollection & StudentCollection::operator=(StudentCollection &&other) {
    if (*this != other) {
        DeleteList();
        head_ = other.head_;
        other.head_ = nullptr;
    }

    return *this;
}

// Inequality comparison.
bool StudentCollection::operator!=(const StudentCollection &other) {
    return head_ != other.head_;
}

// Adds a new record to the head of the list.
void
StudentCollection::AddRecord(int student_num, int grade, std::string name) {
    ListNode *new_record = new ListNode{{student_num, grade, name}, head_};
    head_ = new_record;
}

// Remove a record that matches the given student num. Returns true if the
// record was found and deleted, false otherwise.
bool StudentCollection::RemoveRecord(int student_num) {
    ListNode *record = head_;
    ListNode *prev_record = nullptr;

    // Loop through the list of students looking for a matching
    // student_num.
    while (record != nullptr) {
        if (record->student.number == student_num) {
            // Remove the matching record from the list and delete it.
            if (prev_record == nullptr) {
                head_ = record->next;
            } else {
                prev_record->next = record->next;
            }

            delete record;
            return true;
        }

        prev_record = record;
        record = record->next;
    }

    return false;
}

// Count the number of records in the collection.
int StudentCollection::CountRecords() const {
    int count = 0;

    for (ListNode *record = head_; record != nullptr; record = record->next) {
        ++count;
    }

    return count;
}

// Return the average of all grades in the collection.
double StudentCollection::AverageRecords() const {
    double grade_sum = 0;
    int count = 0;

    for (ListNode *record = head_; record != nullptr; record = record->next) {
        grade_sum += static_cast<double>(record->student.grade);
        ++count;
    }

    return grade_sum / static_cast<double>(count);
}

// Return a new StudentCollection containing records from this collection
// with grades within the given range (inclusive).
StudentCollection StudentCollection::RecordsWithinRange(int lower, int upper) {
    StudentCollection new_collection;

    for (ListNode *record = head_; record != nullptr; record = record->next) {
        if ((record->student.grade >= lower) &&
            (record->student.grade <= upper)) {
            new_collection.AddRecord(record->student.number,
                                     record->student.grade,
                                     record->student.name);
        }
    }

    return new_collection;
}

// Delete all nodes from the StudentCollection list.
void StudentCollection::DeleteList() {
    ListNode *record = head_;
    ListNode *next_record;

    while (record != nullptr) {
        next_record = record->next;
        delete record;
        record = next_record;
    }

    head_ = nullptr;
}

// Copy another list into this one, appending to any existing list entries.
void StudentCollection::CopyList(const ListNode *from) {
    for (const ListNode *record = from;
         record != nullptr;
         record = record->next) {
        AddRecord(record->student.number,
                  record->student.grade,
                  record->student.name);
    }
}

// Returns the "first" student in the collection according to the chosen
// policy.
StudentRecord *
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

StudentRecord *StudentCollection::HighestGradeStudent_() const {
    ListNode *record = head_;
    StudentRecord *highest_grade_student = nullptr;

    while (record != nullptr) {
        if ((highest_grade_student == nullptr) ||
            (record->student.grade > highest_grade_student->grade)) {
            highest_grade_student = &record->student;
        }
        record = record->next;
    }

    return highest_grade_student;
}

StudentRecord *StudentCollection::LowestNumStudent_() const {
    ListNode *record = head_;
    StudentRecord *lowest_num_student = nullptr;

    while (record != nullptr) {
        if ((lowest_num_student == nullptr) ||
            (record->student.number < lowest_num_student->number)) {
            lowest_num_student = &record->student;
        }
        record = record->next;
    }

    return lowest_num_student;
}

StudentRecord *StudentCollection::FirstNameStudent_() const {
    ListNode *record = head_;
    StudentRecord *first_name_student = nullptr;

    while (record != nullptr) {
        if ((first_name_student == nullptr) ||
            (record->student.name < first_name_student->name)) {
            first_name_student = &record->student;
        }
        record = record->next;
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

