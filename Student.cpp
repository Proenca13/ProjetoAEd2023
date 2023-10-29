//
// Created by joao on 09-10-2023.
//

#include "Student.h"

using namespace std;
Student::Student() : name_(""), studentCode_(""), schedule_(){};
Student::Student(string name,string studentCode,Schedule schedule): name_(name),studentCode_(studentCode),
                                                                    schedule_(schedule){}
string Student::get_name() const {return name_;}
Schedule Student::get_schedule() const{return schedule_;}
string Student::get_studentCode() const {return studentCode_;}
set<string> Student::get_belong_class() const {
    set<string> s;
    for(auto const& lesson : this->schedule_.get_lessons()){
        s.insert(lesson.get_class_code());
    }
    return s;
}
set<string> Student::get_belong_ucs() {
    set<string> s;
    for(auto const& lesson : this->schedule_.get_lessons()){
        s.insert(lesson.get_uc_code());
    }
    return s;
}
void Student::set_name(std::string name) {name_ = name;}
void Student::set_schedule(Schedule schedule) {schedule_ = schedule;}
void Student::set_studentCode(std::string studentCode) {studentCode_ = studentCode;}
bool Student::operator<(Student student) const{
    return studentCode_ < student.get_studentCode();
}