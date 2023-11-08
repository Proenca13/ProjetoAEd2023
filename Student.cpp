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
/**
 * Percorre o horário do aluno , vê a turma em que está a cada aula e mete o código da turma num set
 * @return retorna um set com as turmas a que o objeto student pertence
 */
set<string> Student::get_belong_class() const {
    set<string> s;
    for(auto const& lesson : this->schedule_.get_lessons()){
        s.insert(lesson.get_class_code());
    }
    return s;
}
/**
 * Percorre o horário do aluno , vê as ucs em que está e mete o código de cada uc num set
 * @return retorna um set com as ucs a que o objeto student pertence
 */
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
/**
 * Utiliza o operador para comparar dois estudantes com base no seu student_code
 * @param student o estudante para comparar.
 * @return Retorna verdadeiro se o estudante tiver studentcode menor que o other student, caso contrário retorna falso.
 */
bool Student::operator<(Student student) const{
    return studentCode_ < student.get_studentCode();
}
/**
 * Utiliza o operador para comparar dois estudantes com base no seu student_code
 * @param student o estudante para comparar.
 * @return Retorna verdadeiro se o estudante tiver studentcode igual ao other student, caso contrário retorna falso.
 */
bool Student::operator==(Student student) const {
    return studentCode_ == student.get_studentCode();
}


