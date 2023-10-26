//
// Created by joao on 23-10-2023.
//

#include "Schedule_Manager.h"

using namespace std;
Schedule_Manager::Schedule_Manager() {}
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
Schedule Schedule_Manager::consult_schedule() {};
