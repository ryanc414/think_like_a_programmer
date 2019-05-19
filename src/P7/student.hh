/* Define the common StudentRecord type. */

#include <string>

struct StudentRecord {
    StudentRecord(int number, int grade, std::string name) :
        number(number), grade(grade), name(name) {};

    int number;
    int grade;
    std::string name;

    bool operator<(const StudentRecord &other) const;
};

