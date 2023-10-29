//
// Created by joao on 09-10-2023.
//

#ifndef SCHEDULE_SCHEDULE_H
#define SCHEDULE_SCHEDULE_H

#include <vector>
#include "Lesson.h"
#include <algorithm>
using namespace std;

class Schedule {
public:
    Schedule();
    void set_lessons(vector<Lesson> lessons);
    void add_lesson(Lesson lesson);
    void remove_lesson(Lesson lesson);
    vector<Lesson> get_lessons() const;
private:
    vector<Lesson> lessons_;
};


#endif //SCHEDULE_SCHEDULE_H
