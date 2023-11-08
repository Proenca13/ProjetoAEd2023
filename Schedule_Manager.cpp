//
// Created by joao on 23-10-2023.
//

#include "Schedule_Manager.h"

using namespace std;
/**
 * este constructor inicializa o objeto Schedule_Manager ao fazer parsing das turmas,horários estudantes.
 */
Schedule_Manager::Schedule_Manager(){
    classes = parsing_classes();
    classes = parsing_schedules(classes);
    students = parsing_students(classes);
}
/**
 * Percorre o set que contem todos os estudantes e verifica se há algum estudante com código de estudante igual ao fornecido
 * @param StudentCode o StudentCode para comparar
 * @return retorna verdeiro se existir um estudante com este StudentCode, falso caso contrário.
 * Complexidade : O(n), sendo n o número de estudantes.
 */
bool Schedule_Manager::check_student(string StudentCode ) {
    for (const auto& student : students) {
        if (student.get_studentCode() == StudentCode) {
            return true;
        }
    }
    return false;
}
/**
 * Percorre o set que contem todas as turmas e verifica se há alguma turma com código igual ao fornecido
 * @param ClassCode o ClassCode para comparar
 * @return retorna verdeiro se existir uma turma com este ClassCode, falso caso contrário.
 * Complexidade : O(n), sendo n o número de turmas.
 */
bool Schedule_Manager::check_class(string ClassCode) {
    for (auto& turma: classes){
        if(turma.get_classCode() == ClassCode){
            return true;
        }
    }
    return false;
}
/**
 * Percorre o set que contem todas as turmas,percorre o horário de cada turma e verifica se há alguma uc com código igual ao fornecido
 * @param UcCode o UcCode para comparar
 * @return retorna verdeiro se existir uma turma com uma uc com este UcCode, falso caso contrário.
 * Complexidade : O(n * m), sendo n o número de Ucs e m o número de "lessons".
 */
bool Schedule_Manager::check_uc(string UcCode) {
    for(auto& turma: classes ){
        for (auto& aula: turma.get_schedule().get_lessons()){
            if (aula.get_uc_code() == UcCode)return true;
        }
    }
    return false;
}
/**
 * Percorre o set que contem todas os estudantes , percorre o horário do estudante e cria um par com o UcCode e o ClassCode
 * de cada aula e usando o valor do par como chave adiciona o nome do aluno a um vetor que corresponde ao valor da chave
 * @return retorna um map cuja chaves são pares de strings sendo uma delas a uc e outra a turma e
 * os valores um vetor com os nomes dos os estudantes que pertencem aquela turma naquela uc.
 * Complexidade : O(s * n), sendo s o número de estudantes e n o tamanho médio do vetor no mapa.
 */
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
/**
 * Percorre o map que contem os alunos a cada uc/turma e vê se o tamanho dessa turma é o minimo
 * @param UcCode uc á qual se quer ver o tamanho das turmas
 * @return retorna um inteiro que representa o minimo de alunos numa turma a determinada uc.
 */
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
/**
 * Percorre uma string e coloca todos os seus characters em upper_case
 * @param string que vai ser colocada em upper_case
 */
void Schedule_Manager::upper(std::string &word) {
    for (auto& i :word)i= _toupper(i);
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
/**
 * Permite ao utilizador escolher se quer visualizar um hoŕario de um estudante ou de uma turma podendo escolher
 * o respetivo estudante e a respetiva turma.
 */
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
                    print_schedule(student.get_schedule());
                    break;
                }
            }
        }
        else if(i=='2'){
            cout << "Code of the class: ";
            string ClassCode;
            cin >> ClassCode;
            upper(ClassCode);
            bool exist = check_class(ClassCode);
            if (!exist) {
                cout << "Class not found! \n";
                return;
            }
            for(auto& turma : classes){
                if(turma.get_classCode() == ClassCode) {
                    print_schedule(turma.get_schedule());
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
/**
 * Permite ao utilizador consultar todos os estudantes a uma determinada/o turma,uc,ano ou numa uc a uma determinada turma.
 */
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
            upper(ClassCode);
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
            upper(UcCode);
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
            upper(UcCode);
            bool exist = check_uc(UcCode);
            if (!exist) {
                cout << "Uc not found! \n";
                return;
            }
            cout << "Code of the class: ";
            string ClassCode;
            cin >> ClassCode;
            upper(ClassCode);
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
/**
 * Permite ao utilizador consultar o número de estudantes inscritos em pelo menos n(um número definido pelo utilizador) ucs.
 */
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
/**
 * Permite ao utilizador consultar o número de estudantes e a ocupação a uma determinada/o
 * turma,uc,ano ou numa uc a uma determinada turma.
 */
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
            upper(ClassCode);
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
            upper(UcCode);
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
            upper(UcCode);
            bool exist = check_uc(UcCode);
            if (!exist) {
                cout << "Uc not found! \n";
                return;
            }
            cout << "Code of the class: ";
            string ClassCode;
            cin >> ClassCode;
            upper(ClassCode);
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
/**
 * Permite ao utilizador consultar a uc com mais alunos.
 */
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
/**
 * Permite ao utilizador adicionar uma nova unidade curricular ao estudante ,desde que cumpra com as normas.
 */
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
    if(user.get_belong_ucs().size()> 6){
        cout << "You can't add any more Lessons to your schedule. \n";
        return;
    }
    cout << "UcCode: ";
    cin >> UcCode;
    upper(UcCode);
    cout << "Class Code: ";
    cin >> ClassCode;
    upper(ClassCode);
    int min = get_min_attendance(UcCode);
    map <pair<string,string >,vector<string>> uc_class = get_uc_class();
    int class_size = uc_class[{UcCode,ClassCode}].size();
    if(class_size >= min + 4){
        cout << "Class full!"<< '\n';
        return;
    }
    Lesson lesson_tp;
    vector<Lesson> lesson_t;
    bool enconter_lesson = false;
    for(auto turma : classes){
        if(ClassCode == turma.get_classCode()){
            for(auto aula: turma.get_schedule().get_lessons())
                if(UcCode == aula.get_uc_code()){
                    if(aula.get_type() == "T")lesson_t.push_back(aula);
                    else lesson_tp = aula;
                    enconter_lesson = true;
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
        if(lesson_.get_weekday() == lesson_tp.get_weekday()){
            if((lesson_tp.get_start_time() + lesson_tp.get_duration() > lesson_.get_start_time()) && (lesson_tp.get_start_time() < lesson_.get_start_time() + lesson_.get_duration())){
                cout << "Lesson Overlap, you can't add this lesson to your schedule. \n";
                return;
            }
        }
    }
    Schedule schedule = user.get_schedule();
    schedule.add_lesson(lesson_tp);
    for(auto le : lesson_t)schedule.add_lesson(le);
    students.erase(user);
    user.set_schedule(schedule);
    students.insert(user);
    string change = "Added student " + StudentCode + " to class " + ClassCode + " in Uc " + UcCode + "!                                     ";
    cout << change << '\n';
    changes.push(change);
}
/**
 * Permite ao utilizador remover uma  unidade curricular ao estudante ,desde que cumpra com as normas.
 */
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
    upper(UcCode);
    Student user;
    for(const auto& student : students){
        if(student.get_studentCode() == StudentCode){
            user = student;
            break;
        }
    }
    exist = false;
    string ClassCode;
    Schedule new_schedule = user.get_schedule();
    Lesson lesson_remove;
    vector<Lesson> lesson_t;
    for(auto& lesson_ : user.get_schedule().get_lessons()){
        if(lesson_.get_uc_code() == UcCode){
            if(lesson_.get_type() == "T")lesson_t.push_back(lesson_);
            else lesson_remove = lesson_;
            ClassCode = lesson_.get_class_code();
            exist = true;
        }
    }
    if(!exist){
        cout << "Could not find Uc! \n";
        return;
    }
    int min = get_min_attendance(UcCode);
    map <pair<string,string >,vector<string>> uc_class = get_uc_class();
    int class_size = uc_class[{UcCode,ClassCode}].size();
    if(class_size <= min){
        cout << "Can´t remove from class!" << '\n';
        return;
    }
    new_schedule.remove_lesson(lesson_remove);
    for ( auto le:lesson_t)new_schedule.remove_lesson(le);
    students.erase(user);
    user.set_schedule(new_schedule);
    students.insert(user);
    string change = "Removed student " + StudentCode + " from class " + ClassCode  + " in Uc " + UcCode + "!                                 ";
    cout << change << '\n';
    changes.push(change);
}
/**
 * Permite ao utilizador trocar uma uc ou trocar de turma a uma uc , desde de que cumpra as normas.
 */
void Schedule_Manager::switch_students() {
            Student user;
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
            upper(UcCode1);
            cout << "What is the UcCode of the lesson you want to add? ";
            cin >> UcCode2;
            upper(UcCode2);
            cout << "What is the ClassCode of the class you want to be in? ";
            cin >> ClassCode;
            upper(ClassCode);
            exist = false;
            string removed_class;
            Schedule new_schedule = user.get_schedule();
            Lesson lesson_remove;
            vector<Lesson> lesson_t;
            for(auto& lesson_ : user.get_schedule().get_lessons()){
                if(lesson_.get_uc_code() == UcCode1){
                    if(lesson_.get_type() == "T")lesson_t.push_back(lesson_);
                    else lesson_remove = lesson_;
                    removed_class = lesson_.get_class_code();
                    exist = true;
                    }
            }
            if(!exist){
                cout << "Could not find Uc! \n";
                return;
            }
            int min = get_min_attendance(UcCode1);
            map <pair<string,string >,vector<string>> uc_class = get_uc_class();
            int class_size = uc_class[{UcCode1,removed_class}].size();
            if(class_size <= min){
                cout << "Can´t remove from class!" << '\n';
                return;
            }
            new_schedule.remove_lesson(lesson_remove);
            for (auto le:lesson_t)new_schedule.remove_lesson(le);
            bool encontered_lesson = false;
            bool done = false;
            Lesson lesson_add;
            vector<Lesson> lesson_t_add;
            for(auto turma: classes){
                if(ClassCode == turma.get_classCode()){
                    for(auto aula : turma.get_schedule().get_lessons()){
                        if(UcCode2 == aula.get_uc_code()){
                            if(aula.get_type() == "T")lesson_t_add.push_back(aula);
                            else lesson_add = aula;
                            encontered_lesson = true;
                            done = true;
                        }
                    }
                }
            }
            if(!encontered_lesson){
                cout << "Could not find Uc to add! \n";
            }
            for(auto& lesson_ : new_schedule.get_lessons()){
                if(lesson_.get_weekday() == lesson_add.get_weekday()){
                    if(lesson_.get_uc_code() == UcCode2){
                        cout << "You're already in a Class in that Uc. \n";
                        done = false;
                    }
                    if((lesson_add.get_start_time() + lesson_add.get_duration() > lesson_.get_start_time()) && (lesson_add.get_start_time() < lesson_.get_start_time() + lesson_.get_duration())){
                        cout << "Lesson Overlap, you can't add this lesson to your schedule. \n";
                        done = false;
                    }
                }
            }
            min = get_min_attendance(UcCode2);
            class_size = uc_class[{UcCode2,ClassCode}].size();
            if(class_size >= min + 4){
                cout << "Class full!"<<'\n';
                done = false;
            }
            if (done) {
                new_schedule.add_lesson(lesson_add);
                for(auto le :lesson_t_add)new_schedule.add_lesson(le);
                students.erase(user);
                user.set_schedule(new_schedule);
                students.insert(user);
                string change = "Switched student " + StudentCode + " from class " + removed_class + " in Uc " + UcCode1 +" to class " + ClassCode + " in Uc " + UcCode2 +"!";
                cout << change << '\n';
                changes.push(change);
            }
}
/**
 * Remove um estudante de uma uc a uma determinada turma,desde que cumpra as normas.
 * @param StudentCode estudante que vai ser removido
 * @param UcCode uc a que vai ser retirado
 * @param ClassCode class a que vai ser retirado.
 */
void Schedule_Manager::automatic_remove(string StudentCode, string UcCode, string ClassCode) {
    bool exist = check_student(StudentCode);
    if(!exist){
        cout << "Student not found! \n";
        return;
    }
    Student user;
    for(const auto& student : students){
        if(student.get_studentCode() == StudentCode){
            user = student;
            break;
        }
    }
    exist = false;
    Schedule new_schedule = user.get_schedule();
    Lesson lesson_remove;
    vector<Lesson> lesson_t;
    for(auto& lesson_ : user.get_schedule().get_lessons()){
        if(lesson_.get_uc_code() == UcCode){
            if(lesson_.get_type() == "T")lesson_t.push_back(lesson_);
            else lesson_remove = lesson_;
            exist = true;
        }
    }
    if(!exist){
        cout << "Could not find Uc! \n";
        return;
    }
    int min = get_min_attendance(UcCode);
    map <pair<string,string >,vector<string>> uc_class = get_uc_class();
    int class_size = uc_class[{UcCode,ClassCode}].size();
    if(class_size <= min){
        cout << "Can´t remove from class!" << '\n';
        return;
    }
    new_schedule.remove_lesson(lesson_remove);
    for ( auto le:lesson_t)new_schedule.remove_lesson(le);
    students.erase(user);
    user.set_schedule(new_schedule);
    students.insert(user);
}
/**
 * Adiciona um estudante de uma uc a uma determinada turma,desde que cumpra as normas.
 * @param StudentCode estudante que vai ser adicionado
 * @param UcCode uc a que vai ser adicionado
 * @param ClassCode class a que vai ser adicionado.
 */
void Schedule_Manager::automatic_add(string StudentCode,string UcCode, string ClassCode) {
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
    if(user.get_belong_ucs().size() > 6){
        cout << "You can't add any more Lessons to your schedule. \n";
        return;
    }
    int min = get_min_attendance(UcCode);
    map <pair<string,string >,vector<string>> uc_class = get_uc_class();
    int class_size = uc_class[{UcCode,ClassCode}].size();
    if(class_size >= min + 4){
        cout << "Class full!"<< '\n';
        return;
    }
    Lesson lesson_tp;
    vector<Lesson> lesson_t;
    bool enconter_lesson = false;
    for(auto turma : classes){
        if(ClassCode == turma.get_classCode()){
            for(auto aula: turma.get_schedule().get_lessons())
                if(UcCode == aula.get_uc_code()){
                    if(aula.get_type() == "T")lesson_t.push_back(aula);
                    else lesson_tp = aula;
                    enconter_lesson = true;
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
        if(lesson_.get_weekday() == lesson_tp.get_weekday()){
            if((lesson_tp.get_start_time() + lesson_tp.get_duration() > lesson_.get_start_time()) && (lesson_tp.get_start_time() < lesson_.get_start_time() + lesson_.get_duration())){
                cout << "Lesson Overlap, you can't add this lesson to your schedule. \n";
                return;
            }
        }
    }
    Schedule schedule = user.get_schedule();
    schedule.add_lesson(lesson_tp);
    for(auto le : lesson_t)schedule.add_lesson(le);
    students.erase(user);
    user.set_schedule(schedule);
    students.insert(user);
}
/**
 * Altera um estudante de uc ou de turma,desde que cumpra as normas.
 * @param StudentCode estudante que vai ser alterado
 * @param to_UcCode uc a que vai ser retirado
 * @param to_ClassCode class a que vai ser retirado
 * @param from_UcCode uc a que vai ser adicionado
 * @param from_ClassCode class a que vai ser adicionado.
 */
void Schedule_Manager::automatic_switch(string StudentCode,string from_ClassCode,string from_UcCode,string to_ClassCode,string to_UcCode) {
    automatic_remove(StudentCode,to_UcCode,to_ClassCode);
    automatic_add(StudentCode,from_UcCode,from_ClassCode);
}
/**
 * Permite ao utilizador ver o historico de alterações feitas e desfazer a mais recente.
 */
void Schedule_Manager::print_history() {
    vector<string> historic;
    while(!(changes.empty())){
        string change = changes.front();
        historic.push_back(change);
        changes.pop();
    }
    bool cloose = false;
    while (true){
        cout << "---------------------------------------------Changes---------------------------------------------" <<'\n';
        int i = 1;
        for(auto change:historic){
            cout << "|"<<i<<"-"<<change<<'|'<<'\n';
            i++;
        }
        cout << "-------------------------------------------------------------------------------------------------"<<'\n';
        cout << "Do you want to undo the last change?(Y/N) ";
        char k;
        cin >> k;
        if(_toupper(k) == 'Y'){
            if(historic.size() > 0){
                stringstream in(historic.back());
                vector<string> Code;
                string word;
                while(in >> word){
                    Code.push_back(word);
                }
                if(Code[0]=="Added")automatic_remove(Code[2],Code[8].substr(0,Code[8].size()-1),Code[5]);
                else if(Code[0]=="Removed")automatic_add(Code[2],Code[8].substr(0,Code[8].size()-1),Code[5]);
                else {
                    automatic_switch(Code[2],Code[5],Code[8],Code[11],Code[14].substr(0,Code[14].size()-1));
                }

                historic.pop_back();
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
/**
 * Guarda todos os pedidos feitos pelo utilizador quando desliga o programa.
 * Complexidade : O(n), sendo n o número de changes.
 */
void Schedule_Manager::save_requests() {
    ofstream out;
    out.open("../Read_Info/requests.csv");
    if (!out.is_open()){
        cout << "File not found!"<<'\n';
    }
    while(!(changes.empty())){
        out << changes.front()<< '\n';
        changes.pop();
    }
}
/**
 * Carrega todos os pedidos feitos anteriormente pelo utilizador quando liga o programa.
 */
void Schedule_Manager::load_request() {
    ifstream in;
    in.open("../Read_Info/requests.csv");
    if (!in.is_open()){
        cout << "File not found!"<<'\n';
    }
    while(in){
        string line;
        while(getline(in,line)){
            changes.push(line);
            stringstream in(line);
            vector <string> Code;
            string word;
            while(in >> word){
                Code.push_back(word);
            }
            if(Code[0]=="Added")automatic_add(Code[2],Code[8].substr(0,Code[8].size()-1),Code[5]);
            else if(Code[0]=="Removed")automatic_remove(Code[2],Code[8].substr(0,Code[8].size()-1),Code[5]);
            else automatic_switch(Code[2],Code[11],Code[14].substr(0,Code[14].size()-1),Code[5],Code[8]);
        }
    }
}



