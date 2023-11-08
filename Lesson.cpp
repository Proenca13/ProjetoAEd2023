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
/**
 * Verifica se duas lessons são equivalentes através dos seus atributos
 * * @param other uma lesson para comparar.
 * @return retorna verdadeiro se duas lessons forem iguais, caso contrário retorna falso
 */
bool Lesson::operator==(const Lesson &other) const {
    return this->duration == other.get_duration() && this->start_time == other.get_start_time() && this->type == other.get_type() && this->uc_code == other.get_uc_code() && this->weekday == other.get_weekday();
}
/**
 * Compara dois objetos lesson com base no dia da semana e em que horas começam
 * É considerado menor se tiver num dia da semana mais cedo,
 * se forem no mesmo dia é comparado pelas horas em que começam
 *
 * @param other uma lesson para comparar.
 * @return retorna verdadeiro se a lesson for antes que a other lesson, caso contrário falso.
 */
bool Lesson::operator<(const Lesson &other) const {
    map<std::string, int> weekday_to_int = {{"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3}, {"Thursday", 4},
                                                 {"Friday", 5}, {"Saturday", 6}, {"Sunday", 7}};
    int this_weekday = weekday_to_int[this->weekday];
    int other_weekday = weekday_to_int[other.get_weekday()];

    // Compare by weekday first
    if (this_weekday < other_weekday) {
        return true;
    } else if (this_weekday > other_weekday) {
        return false;
    }

    // If weekdays are equal, compare by start_time
    return this->start_time < other.get_start_time();
}
