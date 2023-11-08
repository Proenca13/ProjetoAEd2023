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
/**
 * Lê do ficheiro "classes_per_uc.csv" todas as turmas existentes e inicializa um objeto UcClass para cada turma
 *
 * @return Retorna um set com um objeto UcClass para cada turma;
 * Complexidade : O(n * log(n)), sendo n o número de "classes".
 */
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
/**
 * Lê do ficheiro "classes.csv" todas as lessons e inicializa o horário de cada turma
 *
 * @return Retorna um set com um objeto UcClass para cada turma com o horário respetivo;
 * Complexidade : O(l * n * log(n)), sendo l o número de "lessons" e n o número de "classes".
 */
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
/**
 * Lê do ficheiro "students_classes.csv" todos os students e inicializa um objeto Student para cada student com o respetivo horário
 *
 * @return Retorna um set com um objeto Student para cada estudante com o horário respetivo;
 * Complexidade : O(n^2), sendo n o número de estudantes.
 */
set<Student> parsing_students(set<UcClass> classes){
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
            Schedule schedule;
            Student student(StudentName,StudentCode,schedule);
            temp_students.push_back(student);
            auto itr = find(temp_students.begin(),temp_students.end(),student);
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
    for(auto i :temp_students)students.insert(i);
    in.close();
    return students;
}
/**
 * Dá print ás lesson pertencentes ao horario e dá sort ás lesson pelo dia de semana e hora a que começam antes de printar.
 *
 * @param schedule O horário a ser printado.
 * Complexidade : O(1).
 */
void print_schedule (Schedule schedule){
    set<Lesson> ordered_lessons;
    for(auto& lesson : schedule.get_lessons()){
        ordered_lessons.insert(lesson);
    }
    cout << "Weekday: UcCode/ClassCode start_time:end_time, Type" << '\n';
    for(auto& printed : ordered_lessons){
        float end_time = printed.get_start_time() + printed.get_duration();
        int start_hours = static_cast<int>(printed.get_start_time());
        int start_minutes = static_cast<int>((printed.get_start_time() - start_hours) * 60);
        int end_hours = static_cast<int>(end_time);
        int end_minutes = static_cast<int>((end_time - end_hours) * 60);
            cout << printed.get_weekday() << ": " << printed.get_uc_code() << '/' << printed.get_class_code() << ' '<< setfill('0') << setw(2) << start_hours << ":"<< setfill('0') << setw(2)
            << start_minutes << '-'<< setfill('0') << setw(2) <<end_hours << ":"<< setfill('0') << setw(2) << end_minutes << ", (" << printed.get_type() << ")\n";
    }
}

