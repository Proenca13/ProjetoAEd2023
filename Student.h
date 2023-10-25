//
// Created by joao on 09-10-2023.
//

#ifndef SCHEDULE_STUDENT_H
#define SCHEDULE_STUDENT_H
#include "Schedule.h"
#include <string>
using namespace std;

class Student {
public:
    Student(string name, string studentCode, Schedule schedule);
    string get_name() const;
    Schedule get_schedule() const;
    string get_studentCode() const;
    void set_schedule(Schedule schedule);
    void set_name(string name);
    void set_studentCode(string studentCode);
    bool operator<(Student student) const;

private:
    string name_;
    string studentCode_;
    Schedule schedule_;

};


#endif //SCHEDULE_STUDENT_H
