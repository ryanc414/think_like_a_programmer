/*
 * 7-6. Suppose you are working on a project in which a particular studentRecord
 * may need to be augmented with one of the following pieces of data: term
 * paper title, year of enrollment, or a bool indicating whether the student is
 * auditing the class. You don't want to include all of these data fields in the
 * base studentRecord class, knowing that in most cases they won't be used. Your
 * first thought is to create three subclasses, each having one of the data fields,
 * with names such as studentRecordTitle, studentRecordYear and studentRecordAudit.
 * Then you are informed that some student records will contain two of these
 * additional data fields or perhaps all three. Creating subclasses for each
 * possible variation is impractical. Find a design pattern that addresses this
 * conundrum, and implement a solution.
 *
 * 7-7. Develop a solution to the problem described in 7-6 that does not make use
 * of the pattern you discovered but instead solves the problem using C++
 * library classes. Rather than focusing on the three particular data fields
 * described in the previous question, try to make a general solution: a version
 * of the studentRecord class that allows arbitrary extra fields of data to be added
 * to particular objects. So, for example, if sr1 is a studentRecord, you might want
 * client code to make the call sr1.addExtraField("Title", "Problems of Unconditional
 * Branching"), and then later sr1.retrieveField("Title") would return Problems
 * of Unconditional Branching.
 */

#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <any>

#include "student.hh"

class AugmentedStudentRecord : public StudentRecord {
  public:
    AugmentedStudentRecord(int number, int grade, std::string name) :
        StudentRecord(number, grade, name) {};
    void AddExtraField(std::string name, std::any value);
    std::any RetrieveField(std::string name);

  private:
    std::map<std::string, std::any> fields_;
};

int main() {
    AugmentedStudentRecord student(45, 85, "Ryan");

    student.AddExtraField("Title",
                          std::string("Problems of Unconditional Branching"));
    student.AddExtraField("Enrollment Year", 2012);
    student.AddExtraField("Auditing", true);

    assert(std::any_cast<std::string>(student.RetrieveField("Title")) ==
        "Problems of Unconditional Branching");
    assert(std::any_cast<int>(student.RetrieveField("Enrollment Year")) ==
        2012);
    assert(std::any_cast<bool>(student.RetrieveField("Auditing")));

    std::cout << "All assertions passed." << std::endl;

    return 0;
}

// Adds an extra field into the object. If the field is already added, its
// value will be overwritten.
void AugmentedStudentRecord::AddExtraField(std::string name, std::any value) {
    fields_[name] = value;
}

std::any AugmentedStudentRecord::RetrieveField(std::string name) {
    return fields_[name];
}

