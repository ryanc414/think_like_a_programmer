/* Define the common StudentRecord type. */

#include <string>

struct StudentRecord {
    // Constructors.
    StudentRecord() : number(0), grade(0), name("") {};
    StudentRecord(int number, int grade, std::string name) :
        number(number), grade(grade), name(name) {};

    int number;
    int grade;
    std::string name;

    bool operator<(const StudentRecord &other) const;
    bool operator>(const StudentRecord &other) const;
};

