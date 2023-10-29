//
// Created by joao on 18-10-2023.
//

#include "Lesson.h"
Lesson::Lesson(string uccode, string weekday_, float starttime, float duration, string type, string class_code):uc_code(uccode), weekday(weekday_),start_time(starttime),duration(duration),type(type), class_code(class_code) {}
string Lesson::get_uc_code() const{
    return this->uc_code;
}
string Lesson::get_weekday() const{
    return this->weekday;
}
float Lesson::get_start_time() const{
    return this->start_time;
}
float Lesson::get_duration() const{
    return this->duration;
}
string Lesson::get_type() const{
    return this->type;
}
string Lesson::get_class_code() const {
    return this->class_code;
}
//getter implementation for all Lesson attributes.

void Lesson::set_uc_code(string uccode){
    this->uc_code = uccode;
}
void Lesson::setweekday(string weekday){
    this->weekday = weekday;
}
void Lesson::set_start_time(float starttime){
    this->start_time = starttime;
}
void Lesson::setduration(float duration){
    this->duration = duration;
}
void Lesson::settype(string type){
    this->type = type;
}
void Lesson::set_class_code(std::string class_code) {
    this->class_code = class_code;
}

//setter implementation for all Lesson attributes.

bool Lesson::operator==(const Lesson &other) const {
    return this->duration == other.get_duration() && this->start_time == other.get_start_time() && this->type == other.get_type() && this->uc_code == other.get_uc_code() && this->weekday == other.get_weekday();
}