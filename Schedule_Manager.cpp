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
    char i;
    cin >> i;
    if(i== '1'){
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
    else if(i=='2'){
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
    else if(i == '3');
    else
        cout <<"Invalid input!"<<'\n';
}
void Schedule_Manager::consult_students() {
    cout << "----------------Choose one----------------"<<'\n';
    cout << "|              1-class                   |"<<'\n';
    cout << "|              2-course                  |"<<'\n';
    cout << "|              3-year                    |"<<'\n';
    cout << "|              4-back                    |"<<'\n';
    cout << "------------------------------------------"<<'\n';
    cout << "Choose the option you want to do: ";
    char i;
    cin >> i;
    if(i== '1'){
        cout << "Code of the class: ";
        string ClassCode;
        cin >> ClassCode;
        unordered_map<string,vector<string>> student_class;
        for(auto student:students){
            for(auto turma: student.get_belong_class())student_class[turma].push_back(student.get_name());
        }
        for(auto student:student_class[ClassCode]){
            cout << student << '\n';
        }
    }
    else if(i == '2'){
        cout << "Code of the Uc: ";
        string UcCode;
        cin >> UcCode;
        unordered_map<string,vector<string>> student_ucs;
        for(auto student: students){
            for(auto course:student.get_belong_ucs())student_ucs[course].push_back(student.get_name());
        }
        for (auto student:student_ucs[UcCode]){
            cout << student << '\n';
        }
    }
    else if(i=='3'){
        cout << "Year: ";
        string year;
        cin >> year;
        unordered_map<string,vector<string>> student_year;
        for(auto student:students){
            set<string> turmas = student.get_belong_class();
            auto maxElement = max_element(turmas.begin(),turmas.end());
            if((*maxElement)[0] == '1'){
                student_year["1"].push_back(student.get_name());
            }
            else if((*maxElement)[0] == '2'){
                student_year["2"].push_back(student.get_name());
            }
            else if((*maxElement)[0] == '3'){
                student_year["3"].push_back(student.get_name());
            }
        }
        for(auto student:student_year[year]){
            cout << student << '\n';
        }
    }
    else if(i=='4');
    else
        cout <<"Invalid input!"<< '\n';

}
void Schedule_Manager::number_students() {
    cout << "Number of ucs: ";
    char i;
    cin >> i;
    if (i>='0' and i<='7') {
        int res = 0;
        for (auto aluno: students) {
            set<string> ucs = aluno.get_belong_ucs();
            if (ucs.size() == i-'0')res++;
        }
        cout << "The number of students registered in " << i << " ucs is " << res << '\n';
    }
    else cout << "Invalid input!" << '\n';
    }

void Schedule_Manager::uc_most_students(){
    stack<string> ucs;
    unordered_map<string, vector<string>> student_ucs;
    int max = 0;
    for (auto student: students) {
        for (auto course: student.get_belong_ucs())student_ucs[course].push_back(student.get_name());
    }
    for (auto pair: student_ucs) {
        string uc = pair.first;
        vector<string> alunos = pair.second;
        if (ucs.empty()) {
            ucs.push(uc);
            max = alunos.size();
        } else if (alunos.size() > max) {
            max = alunos.size();
            while (!ucs.empty())ucs.pop();
            ucs.push(uc);
        } else if (alunos.size() == max) {
            ucs.push(uc);
        }

    }
    while (!ucs.empty()) {
        cout << ucs.top() << '\n';
        ucs.pop();
    }
   }
