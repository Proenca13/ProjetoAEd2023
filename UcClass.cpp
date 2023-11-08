//
// Created by joao on 09-10-2023.
//

#include "UcClass.h"
using namespace std;
UcClass::UcClass(string classCode, Schedule schedule): classCode_(classCode), schedule_ (schedule){}
Schedule UcClass::get_schedule() const {return schedule_;}
string UcClass::get_classCode() const {return classCode_;}
void UcClass::set_classCode(string classCode) { classCode_ = classCode;}
void UcClass::set_schedule(Schedule schedule) { schedule_ = schedule;}
/**
 * Utiliza o operador para comparar duas turmas com base no seu classCode
 * @param uclass a turma para comparar
 * @return Retorna verdadeiro se a turma tiver classCode menor que a uclass, caso contrário retorna falso.
 */
bool UcClass::operator<(UcClass uclass) const{
    return classCode_ < uclass.get_classCode();
}