//
// Created by joao on 09-10-2023.
//

#include "Schedule.h"
using namespace std;
Schedule::Schedule(): lessons_(){}
vector<Lesson> Schedule::get_lessons() const{return lessons_;}
void Schedule::add_lesson(Lesson lesson) {lessons_.push_back(lesson);}
void Schedule::remove_lesson(Lesson lesson) {
    auto it = find(lessons_.begin(), lessons_.end(), lesson);
    if (it != lessons_.end()) {
        lessons_.erase(it);
    }
}
void Schedule::set_lessons(vector<Lesson> lessons) {lessons_ = lessons;}
