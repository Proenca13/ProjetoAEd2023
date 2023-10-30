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
bool Schedule_Manager::check_student(string StudentCode ) {
    for (const auto& student : students) {
        if (student.get_studentCode() == StudentCode) {
            return true;
        }
    }
    return false;
}
bool Schedule_Manager::check_class(string ClassCode) {
    for (auto& turma: classes){
        if(turma.get_classCode() == ClassCode){
            return true;
        }
    }
    return false;
}
bool Schedule_Manager::check_uc(string UcCode) {
    for(auto& turma: classes ){
        for (auto& aula: turma.get_schedule().get_lessons()){
            if (aula.get_uc_code() == UcCode)return true;
        }
    }
    return false;
}
map<pair<string,string>,vector<string>> Schedule_Manager::get_uc_class() {
    map <pair<string,string >,vector<string>> uc_class;
    for(auto& student:students){
        for(auto& uc : student.get_schedule().get_lessons()){
            pair <string,string> p = {uc.get_uc_code(),uc.get_class_code()};
            auto found = find(uc_class[p].begin(),uc_class[p].end(),student.get_name());
            if(found == uc_class[p].end())uc_class[p].push_back(student.get_name());
        }
    }
    return uc_class;
}
int Schedule_Manager::get_min_attendance(string UcCode){
    int min ;
    bool first_try = true;
    map <pair<string,string >,vector<string>> uc_class = get_uc_class();
    for(auto pair : uc_class){
        if(pair.first.first == UcCode){
            if (first_try){
                first_try = false;
                min = pair.second.size();
            }
            else if(min > pair.second.size())min = pair.second.size();
        }
    }
    return min;
}

void Schedule_Manager::print_menu() {
    cout << "--------------------Menu--------------------"<< '\n';
    cout << "|1-Consult                                 |"<<'\n';
    cout << "|2-Request                                 |"<< '\n';
    cout << "|3-Historic                                |"<< '\n';
    cout << "|4-Quit                                    |" << '\n';
    cout << "--------------------------------------------"<< '\n';
    cout << "Choose the option you want to do: ";
}
void Schedule_Manager::consult() {
    cout << "----------------------------Consult Menu----------------------------"<< '\n';
    cout << "| 1-Consult the schedule of a given student or class               |"<<'\n';
    cout << "| 2-Consult the students within a given class, course or year      |"<< '\n';
    cout << "| 3-Consult the number of students registered in at least n UCs    |" << '\n';
    cout << "| 4-Consult the class/year/UC occupation                           |" << '\n';
    cout << "| 5-Consult the UCs with the greatest number of students           |" << '\n';
    cout << "| 6-Menu                                                           |" << '\n';
    cout << "--------------------------------------------------------------------"<< '\n';
    cout << "Choose the option you want to do: ";
}
void Schedule_Manager::consult_schedule() {
    while (true){
        cout << "----------------Choose one----------------"<<'\n';
        cout << "|              1-Student                 |"<<'\n';
        cout << "|              2-Class                   |"<<'\n';
        cout << "|              3-Back                    |"<<'\n';
        cout << "------------------------------------------"<<'\n';
        cout << "Choose the option you want to do: ";
        char i;
        cin >> i;
        bool cloose = false;
        if(i== '1'){
            cout << "Code of the student: ";
            string StudentCode;
            cin >> StudentCode;
            bool exist = check_student(StudentCode);
            if (!exist) {
                cout << "Student not found! \n";
                return;
            }
            for(auto& student:students){
                if (student.get_studentCode() == StudentCode){
                    for(auto& aula : student.get_schedule().get_lessons()){
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
            bool exist = check_class(ClassCode);
            if (!exist) {
                cout << "Class not found! \n";
                return;
            }
            for(auto& turma : classes){
                if(turma.get_classCode() == ClassCode){
                    for(auto& aula: turma.get_schedule().get_lessons()){
                        cout << aula.get_uc_code() <<" "<< aula.get_type()<< " "<< aula.get_weekday() <<" "
                             << aula.get_start_time()<< " " << aula.get_duration() << '\n';
                    }
                    break;
                }
            }
        }
        else if(i == '3')cloose = true;
        else
            cout <<"Invalid input!"<<'\n';
        if(cloose)break;
    }
    }

void Schedule_Manager::consult_students() {
    while (true){
        cout << "----------------Choose one----------------"<<'\n';
        cout << "|              1-Class                   |"<<'\n';
        cout << "|              2-Course                  |"<<'\n';
        cout << "|              3-Year                    |"<<'\n';
        cout << "|              4-Uc/Class                |"<<'\n';
        cout << "|              5-Back                    |"<<'\n';
        cout << "------------------------------------------"<<'\n';
        cout << "Choose the option you want to do: ";
        char i;
        cin >> i;
        bool cloose = false;
        if(i== '1'){
            cout << "Code of the class: ";
            string ClassCode;
            cin >> ClassCode;
            bool exist = check_class(ClassCode);
            if (!exist) {
                cout << "Class not found! \n";
                return;
            }
            unordered_map<string,vector<string>> student_class;
            for(auto& student:students){
                for(auto& turma: student.get_belong_class())student_class[turma].push_back(student.get_name());
            }
            sort(student_class[ClassCode].begin(), student_class[ClassCode].end());
            for(auto& student:student_class[ClassCode]){
                cout << student << '\n';
            }
        }
        else if(i == '2'){
            cout << "Code of the Uc: ";
            string UcCode;
            cin >> UcCode;
            bool exist = check_uc(UcCode);
            if (!exist) {
                cout << "Uc not found! \n";
                return;
            }
            unordered_map<string,vector<string>> student_ucs;
            for(auto student: students){
                for(auto course:student.get_belong_ucs())student_ucs[course].push_back(student.get_name());
            }
            sort(student_ucs[UcCode].begin(), student_ucs[UcCode].end());
            for (auto& student :student_ucs[UcCode]){
                cout << student << '\n';
            }
        }
        else if(i=='3'){
            cout << "Year: ";
            string year;
            cin >> year;
            unordered_map<string,vector<string>> student_year;
            for(auto& student:students){
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
            for(auto& student:student_year[year]){
                cout << student << '\n';
            }
        }
        else if(i == '4'){
            cout << "Code of the Uc: ";
            string UcCode;
            cin >> UcCode;
            bool exist = check_uc(UcCode);
            if (!exist) {
                cout << "Uc not found! \n";
                return;
            }
            cout << "Code of the class: ";
            string ClassCode;
            cin >> ClassCode;
            exist = check_class(ClassCode);
            if (!exist) {
                cout << "Class not found! \n";
                return;
            }
            map <pair<string,string >,vector<string>> uc_class = get_uc_class();
            sort(uc_class[{UcCode, ClassCode}].begin(), uc_class[{UcCode, ClassCode}].end());
            for (auto& student: uc_class[{UcCode,ClassCode}]){
                cout << student << '\n';
            }
        }
        else if(i=='5')cloose = true;
        else
            cout <<"Invalid input!"<< '\n';
        if(cloose)break;
    }
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
    while (true){
        cout << "----------------Choose one----------------"<<'\n';
        cout << "|              1-Class                   |"<<'\n';
        cout << "|              2-UC                      |"<<'\n';
        cout << "|              3-Year                    |"<<'\n';
        cout << "|              4-Uc/Class                |"<<'\n';
        cout << "|              5-Back                    |"<<'\n';
        cout << "------------------------------------------"<<'\n';
        cout << "Choose the option you want to do: ";
        char i;
        cin >> i;
        bool cloose = false;
        if(i== '1'){
            cout << "Code of the class: ";
            string ClassCode;
            cin >> ClassCode;
            bool exist = check_class(ClassCode);
            if (!exist) {
                cout << "Class not found! \n";
                return;
            }
            unordered_map<string,vector<string>> student_class;
            for(auto& student:students){
                for(auto& turma: student.get_belong_class())student_class[turma].push_back(student.get_name());
            }
            double occupation = (static_cast<double>(student_class[ClassCode].size())/students.size())*100;
            cout << "The class "<< ClassCode <<" with " << student_class[ClassCode].size() << " students has an occuption of "<< fixed << setprecision(2)<< occupation<< "% !"<<'\n';
        }
        else if(i == '2'){
            cout << "Code of the Uc: ";
            string UcCode;
            cin >> UcCode;
            bool exist = check_uc(UcCode);
            if (!exist) {
                cout << "Uc not found! \n";
                return;
            }
            unordered_map<string,vector<string>> student_ucs;
            for(auto student: students){
                for(auto course:student.get_belong_ucs())student_ucs[course].push_back(student.get_name());
            }
            double occupation = (static_cast<double>(student_ucs[UcCode].size())/students.size())*100;
            cout << "The UC "<< UcCode<< " with " << student_ucs[UcCode].size() << " students has an occuption of "<< fixed << setprecision(2)<< occupation<< "% !"<<'\n';
        }
        else if(i=='3'){
            cout << "Year: ";
            string year;
            cin >> year;
            unordered_map<string,vector<string>> student_year;
            for(auto& student:students){
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
            double occupation = (static_cast<double>(student_year[year].size()) / students.size()) * 100.0;
            cout << "The year "<< year << " with "<<  student_year[year].size() <<" students has an occuption of "<< fixed << setprecision(2)<<occupation<< "% !"<<'\n';
        }
        else if(i == '4'){
            cout << "Code of the Uc: ";
            string UcCode;
            cin >> UcCode;
            bool exist = check_uc(UcCode);
            if (!exist) {
                cout << "Uc not found! \n";
                return;
            }
            cout << "Code of the class: ";
            string ClassCode;
            cin >> ClassCode;
            exist = check_class(ClassCode);
            if (!exist) {
                cout << "Class not found! \n";
                return;
            }
            map <pair<string,string >,vector<string>> uc_class = get_uc_class();
            double occupation = (static_cast<double>(uc_class[{UcCode,ClassCode}].size())/students.size())*100;
            cout << "The uc " << UcCode << " in class "<< ClassCode<< " with " <<uc_class[{UcCode,ClassCode}].size()<<
                 " students has an occuption of "<< fixed<<setprecision(2)<<occupation<< "% !" << '\n';
        }
        else if(i=='5')cloose = true;
        else
            cout <<"Invalid input!"<< '\n';
        if(cloose)break;
    }
}

void Schedule_Manager::uc_most_students(){
    stack<string> ucs;
    unordered_map<string, vector<string>> student_ucs;
    int max = 0;
    for (auto student: students) {
        for (auto course: student.get_belong_ucs())student_ucs[course].push_back(student.get_name());
    }
    for (auto& pair: student_ucs) {
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
    cout << "Student code? ";
    cin >> StudentCode;
    Student user;
    bool exist = check_student(StudentCode);
    if (!exist) {
        cout << "Student not found! \n";
        return;
    }
    for (const auto& student : students) {
        if (student.get_studentCode() == StudentCode) {
            user = student;
            break;
        }
    }
    string UcCode,ClassCode;
    if(user.get_schedule().get_lessons().size() > 6){
        cout << "You can't add any more Lessons to your schedule. \n";
        return;
    }
    cout << "UcCode: ";
    cin >> UcCode;
    cout << "Class Code: ";
    cin >> ClassCode;
    int min = get_min_attendance(UcCode);
    map <pair<string,string >,vector<string>> uc_class = get_uc_class();
    int class_size = uc_class[{UcCode,ClassCode}].size();
    if(class_size > min + 3){
        cout << "Class full!"<< '\n';
        return;
    }
    Lesson lesson;
    bool enconter_lesson = false;
    for(auto turma : classes){
        if(ClassCode == turma.get_classCode()){
            for(auto aula: turma.get_schedule().get_lessons())
                if(UcCode == aula.get_uc_code()){
                    lesson = aula;
                    enconter_lesson = true;
                    break;
                }
        }
    }
    if (!enconter_lesson){
        cout << "Uc not found!"<<'\n';
        return;
    }
    for(auto lesson_ : user.get_schedule().get_lessons()){
        if(lesson_.get_uc_code() == UcCode){
            cout << "You're already in a Class in that Uc. \n";
            return;
        }
        if(lesson_.get_weekday() == lesson.get_weekday()){
            if((lesson.get_start_time() + lesson.get_duration() > lesson_.get_start_time()) && (lesson.get_start_time() < lesson_.get_start_time() + lesson_.get_duration())){
                cout << "Lesson Overlap, you can't add this lesson to your schedule. \n";
                return;
            }
        }
    }
    Schedule schedule = user.get_schedule();
    schedule.add_lesson(Lesson(UcCode, lesson.get_weekday(), lesson.get_start_time(),lesson.get_duration(), lesson.get_type(), ClassCode));
    students.erase(user);
    user.set_schedule(schedule);
    students.insert(user);
    string change = "Added student " + StudentCode + " to class " + ClassCode + " in Uc " + UcCode + "!    ";
    cout << change << '\n';
    changes.push(change);
}

void Schedule_Manager::remove_uc(){
    string StudentCode, UcCode;
    cout << "Student code? ";
    cin >> StudentCode;
    bool exist = check_student(StudentCode);
    if(!exist){
        cout << "Student not found! \n";
        return;
    }
    cout << "What is the Uc code of the Uc you want to remove? ";
    cin >> UcCode;
    Student user;
    Lesson lesson_remove;
    for(const auto& student : students){
        if(student.get_studentCode() == StudentCode){
            user = student;
            break;
        }
    }
    exist = false;
    string ClassCode;
    Schedule new_schedule = user.get_schedule();
    for(auto& lesson_ : user.get_schedule().get_lessons()){
        if(lesson_.get_uc_code() == UcCode){
            lesson_remove = lesson_;
            ClassCode = lesson_.get_class_code();
            exist = true;
            break;
        }
    }
    if(!exist){
        cout << "Could not find Uc! \n";
        return;
    }
    int min = get_min_attendance(UcCode);
    map <pair<string,string >,vector<string>> uc_class = get_uc_class();
    int class_size = uc_class[{UcCode,ClassCode}].size();
    if(class_size == min){
        cout << "Can´t remove from class!" << '\n';
        return;
    }
    new_schedule.remove_lesson(lesson_remove);
    students.erase(user);
    user.set_schedule(new_schedule);
    students.insert(user);
    string change = "Removed student " + StudentCode + " from class " + ClassCode  + " in Uc " + UcCode + "!";
    cout << change << '\n';
    changes.push(change);

}
void Schedule_Manager::switch_students() {
    Student user;
    Lesson lesson_add, lesson_remove;
    string StudentCode, UcCode1, UcCode2, ClassCode;
    cout << "What is your Student code? ";
    cin >> StudentCode;
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
    cout << "What is the UcCode of the lesson you want to remove? ";
    cin >> UcCode1;
    cout << "What is the UcCode and the class of the lesson you want to add? ";
    cin >> UcCode2;
    cin >> ClassCode;
    exist = false;
    string removed_class;
    Schedule new_schedule = user.get_schedule();
    for(auto lesson_ : user.get_schedule().get_lessons()){
        if(lesson_.get_uc_code() == UcCode1){
            exist = true;
            lesson_remove = lesson_;
            removed_class = lesson_.get_class_code();
            break;
        }
    }
    int min = get_min_attendance(UcCode1);
    map <pair<string,string >,vector<string>> uc_class = get_uc_class();
    int class_size = uc_class[{UcCode1,ClassCode}].size();
    if(class_size == min ){
        cout << "Can´t remove from class!";
        return;
    }
    new_schedule.remove_lesson(lesson_remove);
    if(!exist){
        cout << "Could not find Uc! \n";
        return;
    }
    bool done = false;
    for(auto& turma : classes){
        if(turma.get_classCode() == ClassCode && !done){
            for(auto& lesson_ : turma.get_schedule().get_lessons()){
                if(lesson_.get_uc_code() == UcCode2){
                    lesson_add = lesson_;
                    done = true;
                    break;
                }
            }
        }
        else{
            break;
        }
    }
    for(auto& lesson_ : user.get_schedule().get_lessons()){
        if(lesson_.get_weekday() == lesson_add.get_weekday()){
            if((lesson_add.get_start_time() + lesson_add.get_duration() > lesson_.get_start_time()) && (lesson_add.get_start_time() < lesson_.get_start_time() + lesson_.get_duration())){
                cout << "Lesson Overlap, you can't add this lesson to your schedule. \n";
                return;
            }
        }
        if(lesson_.get_uc_code() == UcCode2){
            cout << "You're already in a Class in that Uc. \n";
            return;
        }
    }
    min = get_min_attendance(UcCode2);
    class_size = uc_class[{UcCode2,ClassCode}].size();
    if(class_size > min + 3){
        cout << "Class full!";
        return;
    }
    new_schedule.add_lesson(lesson_add);
    students.erase(user);
    user.set_schedule(new_schedule);
    students.insert(user);
    string change = "Switched student " + StudentCode + " from class " + removed_class  + " in Uc " + UcCode1 + "!";
    cout << change << '\n';
    changes.push(change);

}
void Schedule_Manager::undo_add(std::string StudentCode, std::string UcCode, std::string ClassCode) {
    Student user;
    Lesson lesson_remove;
    for(const auto& student : students){
        if(student.get_studentCode() == StudentCode){
            user = student;
            break;
        }
    }
    Schedule new_schedule = user.get_schedule();
    for(auto& lesson_ : user.get_schedule().get_lessons()){
        if(lesson_.get_uc_code() == UcCode){
            lesson_remove = lesson_;
            break;
        }
    }
    int min = get_min_attendance(UcCode);
    map <pair<string,string >,vector<string>> uc_class = get_uc_class();
    int class_size = uc_class[{UcCode,ClassCode}].size();
    if(class_size == min){
        cout << "Can´t remove from class!" << '\n';
        return;
    }
    new_schedule.remove_lesson(lesson_remove);
    students.erase(user);
    user.set_schedule(new_schedule);
    students.insert(user);
}
void Schedule_Manager::undo_remove(std::string StudentCode, std::string UcCode, std::string ClassCode) {
    Student user;
    for (const auto& student : students) {
        if (student.get_studentCode() == StudentCode) {
            user = student;
            break;
        }
    }
    if(user.get_schedule().get_lessons().size() > 6){
        cout << "You can't add any more Lessons to your schedule. \n";
        return;
    }
    int min = get_min_attendance(UcCode);
    map <pair<string,string >,vector<string>> uc_class = get_uc_class();
    int class_size = uc_class[{UcCode,ClassCode}].size();
    if(class_size > min + 3){
        cout << "Class full!"<< '\n';
        return;
    }
    Lesson lesson;
    bool enconter_lesson = false;
    for(auto turma : classes){
        if(ClassCode == turma.get_classCode()){
            for(auto aula: turma.get_schedule().get_lessons())
                if(UcCode == aula.get_uc_code()){
                    lesson = aula;
                    enconter_lesson = true;
                    break;
                }
        }
    }
    if (!enconter_lesson){
        cout << "Uc not found!"<<'\n';
        return;
    }
    for(auto lesson_ : user.get_schedule().get_lessons()){
        if(lesson_.get_uc_code() == UcCode){
            cout << "You're already in a Class in that Uc. \n";
            return;
        }
        if(lesson_.get_weekday() == lesson.get_weekday()){
            if((lesson.get_start_time() + lesson.get_duration() > lesson_.get_start_time()) && (lesson.get_start_time() < lesson_.get_start_time() + lesson_.get_duration())){
                cout << "Lesson Overlap, you can't add this lesson to your schedule. \n";
                return;
            }
        }
    }
    Schedule schedule = user.get_schedule();
    schedule.add_lesson(Lesson(UcCode, lesson.get_weekday(), lesson.get_start_time(),lesson.get_duration(), lesson.get_type(), ClassCode));
    students.erase(user);
    user.set_schedule(schedule);
    students.insert(user);
}
void Schedule_Manager::print_history() {
    vector<string> historic;
    while(!(changes.empty())){
        string change = changes.front();
        historic.push_back(change);
        changes.pop();
    }
    bool cloose = false;
    while (true){
        cout << "-----------------------------Changes----------------------------" <<'\n';
        int i = 1;
        for(auto change:historic){
            cout << "|"<<i<<"-"<<change<<'|'<<'\n';
            i++;
        }
        cout << "----------------------------------------------------------------"<<'\n';
        cout << "Do you want to undo the last change?(Y/N) ";
        char k;
        cin >> k;
        if(_toupper(k) == 'Y'){
            if(historic.size() > 0){
                stringstream in(historic[historic.size()-1]);
                vector<string> Code;
                string word;
                while(in >> word){
                    Code.push_back(word);
                }
                if(Code[0]=="Added")undo_add(Code[2],Code[8].substr(0,Code[8].size()-1),Code[5]);
                else if(Code[0]=="Removed")undo_remove(Code[2],Code[8].substr(0,Code[8].size()-1),Code[5]);
                historic.erase(historic.end()-1);
            }
            else {
                cout << "There is no changes yet!"<< '\n';
                cout << "Going back to the menu!" << '\n';
                cloose = true;
            }
        }
        else if (_toupper(k) == 'N'){
            cout << "Going back to the menu!" << '\n';
            cloose = true;
        }
        else cout << "Invalid input!" << '\n';
        if(cloose)break;
    }
    for (auto& change : historic)changes.push(change);
}


