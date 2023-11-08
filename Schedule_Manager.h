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
#include <unordered_map>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <utility>
#include <iomanip>
class Schedule_Manager {
public:
    Schedule_Manager();
    void print_menu();
    void consult();
    void consult_schedule();
    void consult_students();
    void number_students();
    void consult_occuption();
    void uc_most_students();
    void add_uc();
    void remove_uc();
    void switch_students();
    void request();
    void print_history();
    void save_requests();
    void load_request();
private:
    set<UcClass> classes;
    set<Student> students;
    queue <string> changes;
    map<pair<string,string>,vector<string>> get_uc_class();
    void upper(string& word);
    int get_min_attendance(string UcCode);
    bool check_student(string StudentCode);
    bool check_class(string ClassCode);
    bool check_uc(string UcCode);
    void automatic_remove(string StudentCode ,string UcCode,string ClassCode);
    void automatic_add(string StudentCode ,string UcCode,string ClassCode);
    void automatic_switch(string StudentCode ,string from_ClassCode,string from_UcCode,string to_ClassCode,string to_UcCode);
};


#endif //SCHEDULE_SCHEDULE_MANAGER_H
