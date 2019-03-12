/*
 * 4-5. Write a function removeRecord that takes a pointer to a studentCollection and a
 * student number and that removes the record with that student number from
 * the collection.
 */

#include <iostream>
#include <cassert>

struct ListNode {
    int student_num;
    int grade;
    ListNode *next;
};

struct StudentCollection {
    ListNode *head;

    StudentCollection() {
        head = nullptr;
    }

    // Adds a new record to the head of the list.
    void AddRecord(int student_num, int grade) {
        ListNode *new_record = new ListNode{student_num, grade, head};
        head = new_record;
    }

    // Remove a record that matches the given student num. Returns true if the
    // record was found and deleted, false otherwise.
    bool RemoveRecord(int student_num) {
        ListNode *record = head;
        ListNode *prev_record = nullptr;

        // Loop through the list of students looking for a matching
        // student_num.
        while (record != nullptr) {
            if (record->student_num == student_num) {
                // Remove the matching record from the list and delete it.
                if (prev_record == nullptr) {
                    head = record->next;
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
    int CountRecords() const {
        ListNode *record = head;
        int count = 0;

        while (record != nullptr) {
            ++count;
            record = record->next;
        }

        return count;
    }

};

int main() {
    StudentCollection sc;

    // Add four records to the collection.
    sc.AddRecord(44, 87);
    sc.AddRecord(55, 54);
    sc.AddRecord(21, 92);
    sc.AddRecord(11, 25);

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

    return 0;
}

