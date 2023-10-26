//
// Created by joao on 23-10-2023.
//

#ifndef SCHEDULE_SCHEDULE_MANAGER_H
#define SCHEDULE_SCHEDULE_MANAGER_H
#include <iostream>
#include "Student.h"
#include "Lesson.h"
#include "UcClass.h"
#include "Schedule.h"
#include <set>
#include "Functions.h"
class Schedule_Manager {
public:
    Schedule_Manager();
    void print_menu();
    void consult();
    void consult_schedule();
    void consult_students();
private:
    set<UcClass> classes;
    set<Student> students;
};


#endif //SCHEDULE_SCHEDULE_MANAGER_H
