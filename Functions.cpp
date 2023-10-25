//
// Created by joao on 23-10-2023.
//
#include "Functions.h"
#include "Lesson.h"
#include "Schedule.h"
#include "Student.h"
set<UcClass> parsing_classes(){
    ifstream in("classes_per_uc.csv");
    set<UcClass> classes;
    while(in){
        string line;
        while(getline(in,line)){
            stringstream read(line);
            string word;
            vector<string> info;
            while (getline(read, word, ',')) {
                info.push_back(word);
            }
            Schedule schedule;
            UcClass uclass(info[1], schedule);
            classes.insert(uclass);
        }
    }
    return classes;
}
void parsing_schedules(set<UcClass> classes) {
    ifstream in("classes.csv");
    while (in) {
        string line;
        while(getline(in,line)) {
            stringstream read(line);
            string word;
            vector<string> info;
            while (getline(read, word, ',')) {
                info.push_back(word);
            }
            string ClassCode,UcCode,Weekday,Type;
            float StartHour,Duration;
            ClassCode = info[0];
            UcCode = info[1];
            Weekday = info[2];
            StartHour = stof(info[3]);
            Duration = stof(info[4]);
            Type = info[5];
            Lesson lesson(UcCode,Weekday,StartHour,Duration,Type);
            for (auto turma : classes){
                if (turma.get_classCode() == ClassCode)turma.get_schedule().add_lesson(lesson);
            }

        }
    }
}
void parsing_students(set<UcClass> classes) {
    ifstream in("students_classes.csv");
    set<Student> students;
    while (in) {
        string line;
        while (getline(in, line)) {
            stringstream read(line);
            string word;
            vector<string> info;
            while (getline(read, word, ',')) {
                info.push_back(word);
            }
            string StudentCode, StudentName, UcCode, ClassCode;
            info[0] = StudentCode;
            info[1] = StudentName;
            info[2] = UcCode;
            info[3] = ClassCode;
            auto itr = students.begin();
            while (itr != students.end()) {
                if (itr->get_name() == StudentName) {
                    break;
                }
            }
            if (itr == students.end()) {
                for (auto turma: classes) {
                    if (turma.get_classCode() == ClassCode) {
                        for (auto aula: turma.get_schedule().get_lessons())
                            if (UcCode == aula.get_uc_code()) {
                                Schedule schedule;
                                schedule.add_lesson(aula);
                                students.insert(Student(StudentName, StudentCode, schedule));
                            }
                    }
                }
            } else {
                for (auto turma: classes) {
                    if (turma.get_classCode() == ClassCode) {
                        for (auto aula: turma.get_schedule().get_lessons())itr->get_schedule().add_lesson(aula);
                    }

                }
            }
        }
    }
}