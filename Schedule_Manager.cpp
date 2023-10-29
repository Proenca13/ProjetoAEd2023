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
    cout << "|                1-Consult                 |"<<'\n';
    cout << "|                2-Request                 |"<< '\n';
    cout << "|                3-Historic                |"<< '\n';
    cout << "|                4-Quit                    |" << '\n';
    cout << "--------------------------------------------"<< '\n';
    cout << "Choose the option you want to do: ";
}
void Schedule_Manager::consult() {
    cout << "----------------------------Consult Menu----------------------------"<< '\n';
    cout << "| 1-Consult the schedule of a given student or class              |"<<'\n';
    cout << "| 2-Consult the students within a given class, course or year     |"<< '\n';
    cout << "| 3-Consult the number of students registered in at least n UCs   |" << '\n';
    cout << "| 4-Consult the class/year/UC occupation                          |" << '\n';
    cout << "| 5-Consult the UCs with the greatest number of students          |" << '\n';
    cout << "| 6-Menu                                                          |" << '\n';
    cout << "--------------------------------------------------------------------"<< '\n';
    cout << "Choose the option you want to do: ";
}
void Schedule_Manager::consult_schedule() {
    cout << "----------------Choose one----------------"<<'\n';
    cout << "|              1-Student                 |"<<'\n';
    cout << "|              2-Class                   |"<<'\n';
    cout << "|              3-Back                    |"<<'\n';
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
                    cout << aula.get_class_code() << " " << aula.get_uc_code() <<" "<< aula.get_type()<< " "<< aula.get_weekday() <<" "
                    << aula.get_start_time()<< " " << aula.get_duration() << '\n';
                }
                break;
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
                break;
            }
        }
    }
    else if(i == '3');
    else
        cout <<"Invalid input!"<<'\n';
}
void Schedule_Manager::consult_students() {
    cout << "----------------Choose one----------------"<<'\n';
    cout << "|              1-Class                   |"<<'\n';
    cout << "|              2-Course                  |"<<'\n';
    cout << "|              3-Year                    |"<<'\n';
    cout << "|              4-Back                    |"<<'\n';
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
        sort(student_class[ClassCode].begin(), student_class[ClassCode].end());
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
        sort(student_ucs[UcCode].begin(), student_ucs[UcCode].end());
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
        sort(student_year[year].begin(), student_year[year].end());
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
            if (ucs.size() >= i-'0')res++;
        }
        cout << "The number of students registered in at least " << i << " ucs is " << res << '\n';
    }
    else cout << "Invalid input!" << '\n';
    }
void Schedule_Manager::consult_occuption() {
    cout << "----------------Choose one----------------"<<'\n';
    cout << "|              1-Class                   |"<<'\n';
    cout << "|              2-UC                      |"<<'\n';
    cout << "|              3-Year                    |"<<'\n';
    cout << "|              4-Back                    |"<<'\n';
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
        cout << "The class "<< ClassCode << " has "<< student_class[ClassCode].size()<< " students!"<<'\n';
    }
    else if(i == '2'){
        cout << "Code of the Uc: ";
        string UcCode;
        cin >> UcCode;
        unordered_map<string,vector<string>> student_ucs;
        for(auto student: students){
            for(auto course:student.get_belong_ucs())student_ucs[course].push_back(student.get_name());
        }
        cout << "The UC "<< UcCode << " has "<< student_ucs[UcCode].size()<< " students!"<<'\n';
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
        cout << "The year "<< year << " has "<< student_year[year].size()<< " students!"<<'\n';
    }
    else if(i=='4');
    else
        cout <<"Invalid input!"<< '\n';

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
void Schedule_Manager::request() {
    cout << "------------------------Request------------------------"<< '\n';
    cout << "|                      1-Add                          |"<<'\n';
    cout << "|                      2-Remove                       |"<< '\n';
    cout << "|                      3-Switch                       |" << '\n';
    cout << "|                      4-Menu                         |" << '\n';
    cout << "-------------------------------------------------------"<< '\n';
    cout << "Choose the option you want to do: ";
}

void Schedule_Manager::add_uc() {
    string StudentCode;
    cout << "What is your Student code?";
    cin >> StudentCode;
    Student user;
    bool exist = false;
    for (const auto& student : students) {
        if (student.get_studentCode() == StudentCode) {
            user = student;
            exist = true;
            break;
        }
    }
    if (!exist) {
        cout << "Student not found! \n";
        return;
    }
    string UcCode, Weekday, Type, ClassCode;
    float Start_Time, Duration;
    if(user.get_schedule().get_lessons().size() > 6){
        cout << "You can't add any more Lessons to your schedule. \n";
        return;
    }
    cout << "UcCode: ";
    cin >> UcCode;
    cout << "Class Code: ";
    cin >> ClassCode;
    cout << "Weekday: ";
    cin >> Weekday;
    cout << "Type:";
    cin >> Type;
    cout << "Start Time: ";
    cin >> Start_Time;
    cout << "Duration: ";
    cin >> Duration;
    for(auto lesson_ : user.get_schedule().get_lessons()){
        if(lesson_.get_weekday() == Weekday){
            if((Start_Time + Duration > lesson_.get_start_time()) && (Start_Time < lesson_.get_start_time() + lesson_.get_duration())){
                cout << "Lesson Overlap, you can't add this lesson to your schedule. \n";
                return;
            }
        }
        if(lesson_.get_uc_code() == UcCode){
            cout << "You're already in a Class in that Uc. \n";
            return;
        }
    }
    Schedule schedule = user.get_schedule();
    schedule.add_lesson(Lesson(UcCode, Weekday, Start_Time,Duration, Type, ClassCode));
    students.erase(user);
    user.set_schedule(schedule);
    students.insert(user);
}

void Schedule_Manager::remove_uc(){
    string StudentCode, UcCode;
    cout << "What is your Student code?";
    cin >> StudentCode;
    cout << "What is the Uc code of the Uc you want to remove?";
    cin >> UcCode;
    Student user;
    bool exist = false;
    for(const auto& student : students){
        if(student.get_studentCode() == StudentCode){
            user = student;
            exist = true;
            break;
        }
    }
    if(!exist){
        cout << "Student not found! \n";
        return;
    }
    exist = false;
    Schedule new_schedule = user.get_schedule();
    for(auto lesson_ : user.get_schedule().get_lessons()){
        if(lesson_.get_uc_code() == UcCode){
            new_schedule.remove_lesson(lesson_);
            exist = true;
            break;
        }
    }
    if(!exist){
        cout << "Could not find Uc! \n";
        return;
    }
    students.erase(user);
    user.set_schedule(new_schedule);
    students.insert(user);
}
void Schedule_Manager::switch_uc() {
    string StudentCode, UcCode;
    cout << "What is your Student code?";
    cin >> StudentCode;
    cout << "What is the Uc code of the Uc you want to remove?";
    cin >> UcCode;
    Student user;
    bool exist = false;
    for(const auto& student : students){
        if(student.get_studentCode() == StudentCode){
            user = student;
            exist = true;
            break;
        }
    }
    if(!exist){
        cout << "Student not found! \n";
        return;
    }
    exist = false;
    Schedule new_schedule = user.get_schedule();
    for(auto lesson_ : user.get_schedule().get_lessons()){
        if(lesson_.get_uc_code() == UcCode){
            new_schedule.remove_lesson(lesson_);
            exist = true;
            break;
        }
    }
    if(!exist){
        cout << "Could not find Uc! \n";
        return;
    }
    string Weekday, Type, ClassCode;
    float Start_Time, Duration;
    cout << "UcCode:";
    cin >> UcCode;
    cout << "Weekday:";
    cin >> Weekday;
    cout << "Type:";
    cin >> Type;
    cout << "Start Time:";
    cin >> Start_Time;
    cout << "Duration";
    cin >> Duration;
    cout << "Class Code:";
    cin >> ClassCode;
    for(auto lesson_ : user.get_schedule().get_lessons()){
        if(lesson_.get_weekday() == Weekday){
            if((Start_Time + Duration > lesson_.get_start_time()) && (Start_Time < lesson_.get_start_time() + lesson_.get_duration())){
                cout << "Lesson Overlap, you can't add this lesson to your schedule. \n";
                return;
            }
        }
        if(lesson_.get_uc_code() == UcCode){
            cout << "You're already in a Class in that Uc. \n";
            return;
        }
    }
    user.get_schedule().add_lesson(Lesson(UcCode, Weekday, Start_Time,Duration, Type, ClassCode));
    user.set_schedule(new_schedule);
    students.erase(user);
    students.insert(user);
}
void Schedule_Manager::print_history() {
    cout << "Changes" <<'\n';
}

