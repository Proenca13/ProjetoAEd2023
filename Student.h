//
// Created by joao on 09-10-2023.
//

#ifndef SCHEDULE_STUDENT_H
#define SCHEDULE_STUDENT_H
#include "Schedule.h"
#include <string>
#include <set>
using namespace std;

class Student {
public:
    Student(string name, string studentCode, Schedule schedule);
    string get_name() const;
    Schedule get_schedule() const;
    string get_studentCode() const;
    set<string> get_belong_class() const;
    void add_belong_class(string turma);
    void set_belong_class(set <string> belong_class);
    void set_schedule(Schedule schedule);
    void set_name(string name);
    void set_studentCode(string studentCode);
    bool operator<(Student student) const;

private:
    string name_;
    string studentCode_;
    Schedule schedule_;
    set <string> belong_class_;
};


#endif //SCHEDULE_STUDENT_H
