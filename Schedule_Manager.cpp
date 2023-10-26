//
// Created by joao on 23-10-2023.
//

#include "Schedule_Manager.h"

using namespace std;
Schedule_Manager::Schedule_Manager(){
    classes = parsing_classes();
    classes = parsing_schedules(classes);
    students = parsing_students(classes);
}
void Schedule_Manager::print_menu() {
    cout << "--------------------Menu--------------------"<< '\n';
    cout << "|               1- Consult                 |"<<'\n';
    cout << "|               2- Request                 |"<< '\n';
    cout << "|               3- Quit                    |" << '\n';
    cout << "--------------------------------------------"<< '\n';
    cout << "Choose the option you want to do: ";
}
void Schedule_Manager::consult() {
    cout << "----------------------------Consult Menu----------------------------"<< '\n';
    cout << "| 1- Consult the schedule of a given student or class              |"<<'\n';
    cout << "| 2- Consult the students within a given class, course or year     |"<< '\n';
    cout << "| 3- Consult the number of students registered in at least n UCs   |" << '\n';
    cout << "| 4- Consult the class/year/UC occupation                          |" << '\n';
    cout << "| 5- Consult the UCs with the greatest number of students          |" << '\n';
    cout << "| 6- Menu                                                          |" << '\n';
    cout << "--------------------------------------------------------------------"<< '\n';
    cout << "Choose the option you want to do: ";
}
void Schedule_Manager::consult_schedule() {
    cout << "----------------Choose one----------------"<<'\n';
    cout << "|              1-student                 |"<<'\n';
    cout << "|              2-class                   |"<<'\n';
    cout << "|              3-back                    |"<<'\n';
    cout << "------------------------------------------"<<'\n';
    cout << "Choose the option you want to do: ";
    int i;
    cin >> i;
    if(i== 1){
        cout << "Code of the student: ";
        string StudentCode;
        cin >> StudentCode;
        for(auto student:students){
            if (student.get_studentCode() == StudentCode){
                for(auto aula : student.get_schedule().get_lessons()){
                    cout << aula.get_uc_code() <<" "<< aula.get_type()<< " "<< aula.get_weekday() <<" "
                    << aula.get_start_time()<< " " << aula.get_duration() << '\n';
                }
            }
        }
    }
    else if(i==2){
        cout << "Code of the class: ";
        string ClassCode;
        cin >> ClassCode;
        for(auto turma : classes){
            if(turma.get_classCode() == ClassCode){
                for(auto aula: turma.get_schedule().get_lessons()){
                    cout << aula.get_uc_code() <<" "<< aula.get_type()<< " "<< aula.get_weekday() <<" "
                         << aula.get_start_time()<< " " << aula.get_duration() << '\n';
                }
            }
        }
    }
    else if(i == 3);
    else
        cout << "Invalid input!"<<'\n';
}
void Schedule_Manager::consult_students() {
    cout << "----------------Choose one----------------"<<'\n';
    cout << "|              1-class                   |"<<'\n';
    cout << "|              2-course                  |"<<'\n';
    cout << "|              3-year                    |"<<'\n';
    cout << "|              4-back                    |"<<'\n';
    cout << "------------------------------------------"<<'\n';
    cout << "Choose the option you want to do: ";
    int i;
    cin >> i;
    if(i== 1);
    else if(i == 2);
    else if(i==3);
    else if(i==4);
    else
        cout << "Invalid input!"<< '\n';

}
