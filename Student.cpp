//
// Created by joao on 09-10-2023.
//

#include "Student.h"

using namespace std;
Student::Student(string name,string studentCode,Schedule schedule): name_(name),studentCode_(studentCode),
                                                                    schedule_(schedule){}
string Student::get_name() const {return name_;}
Schedule Student::get_schedule() const{return schedule_;}
string Student::get_studentCode() const {return studentCode_;}
void Student::set_name(std::string name) {name_ = name;}
void Student::set_schedule(Schedule schedule) {schedule_ = schedule;}
void Student::set_studentCode(std::string studentCode) {studentCode_ = studentCode;}
bool Student::operator<(Student student) const{
    return studentCode_ < student.get_studentCode();
}