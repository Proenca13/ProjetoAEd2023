//
// Created by joao on 18-10-2023.
//


#ifndef LESSON_H
#define LESSON_H

#include <string>
#include <iostream>
using namespace std;
//class that represents each individual lesson.
class Lesson {
private:
    string uc_code;
    string weekday;
    float start_time;
    float duration;
    string type;
    string class_code;
public:
    Lesson() {};
    Lesson(string uccode, string weekday_, float starttime, float duration, string type, string class_code) ;
    string get_uc_code() const;
    string get_weekday() const;
    float get_start_time() const;
    float get_duration() const;
    string get_type() const;
    string get_class_code() const;
    //declare getters.
    void set_uc_code(string uccode);
    void setweekday(string weekday);
    void set_start_time(float starttime);
    void setduration(float duration);
    void settype(string type);
    void set_class_code(string class_code);
    //declare setters.
    bool operator==(const Lesson& other) const;
};

#endif
