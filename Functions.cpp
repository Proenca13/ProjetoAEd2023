//
// Created by joao on 23-10-2023.
//
#include "Functions.h"
#include "Lesson.h"
#include "Schedule.h"
#include "Student.h"
#include <list>
#include <algorithm>
using namespace std;
set<UcClass> parsing_classes(){
    ifstream in;
    in.open("../Read_Info/classes_per_uc.csv");
    if (!in.is_open()){
        cout << "File not found!"<<'\n';
    }
    set<UcClass> classes;
    string skip;
    getline(in, skip);
    while(in){
        string line;
        while(getline(in,line)){
            stringstream read(line);
            string UcCode,ClassCode;
            getline(read,UcCode,',');
            getline(read,ClassCode,'\r');
            Schedule schedule;
            UcClass uclass(ClassCode, schedule);
            classes.insert(uclass);
        }
    }
    in.close();
    return classes;
}

set<UcClass> parsing_schedules(set<UcClass> classes) {
    ifstream in;
    in.open("../Read_Info/classes.csv");
    if (!in.is_open()){
        cout << "File not found!"<<'\n';
    }
    string skip;
    getline(in, skip);
    while (in) {
        string line;
        while(getline(in,line)) {
            stringstream read(line);
            string ClassCode,UcCode,Weekday,Type;
            float StartHour,Duration;
            getline(read,ClassCode,',');
            getline(read,UcCode,',');
            getline(read,Weekday,',');
            read >> StartHour;
            read.ignore(1);
            read >> Duration;
            read.ignore(1);
            getline(read,Type,'\r');
            Lesson lesson(UcCode,Weekday,StartHour,Duration,Type, ClassCode);
            for (auto turma : classes){
                if (turma.get_classCode() == ClassCode){
                    Schedule schedule;
                    schedule = turma.get_schedule();
                    classes.erase(UcClass(ClassCode,schedule));
                    schedule.add_lesson(lesson);
                    classes.insert(UcClass(ClassCode,schedule));
                }
            }
        }
    }
    in.close();
    return classes;
}

set<Student> parsing_students(set<UcClass> classes) {
    ifstream in;
    in.open("../Read_Info/students_classes.csv");
    if (!in.is_open()){
        cout << "File not found!"<<'\n';
    }
    set<Student> students;
    list<Student> temp_students;
    string skip;
    getline(in, skip);
    while (in) {
        string line;
        while (getline(in, line)) {
            stringstream read(line);
            string StudentCode, StudentName, UcCode, ClassCode;
            getline(read,StudentCode,',');
            getline(read,StudentName,',');
            getline(read,UcCode,',');
            getline(read,ClassCode,'\r');
            auto itr = temp_students.begin();
            while(itr!=temp_students.end()){
                if(itr->get_studentCode()== StudentCode){
                    break;
                }
                itr++;
            }
            if (itr == temp_students.end()) {
                for (auto turma: classes) {
                    if (turma.get_classCode() == ClassCode) {
                        for (auto aula: turma.get_schedule().get_lessons()){
                            if (UcCode == aula.get_uc_code()) {
                                Schedule schedule;
                                schedule.add_lesson(aula);
                                Student student(StudentName,StudentCode,schedule);
                                temp_students.push_back(student);
                                break;
                            }
                        }
                        break;
                    }
                }
            } else {
                for (auto turma: classes) {
                    if (turma.get_classCode() == ClassCode) {
                        for (auto aula: turma.get_schedule().get_lessons()){
                            if (UcCode == aula.get_uc_code()){
                                Schedule schedule = itr->get_schedule();
                                schedule.add_lesson(aula);
                                itr->set_schedule(schedule);
                            }
                        }
                    }
                }
            }
        }
    }
    for(auto i :temp_students){
        students.insert(i);
    }
    in.close();
    return students;
}
