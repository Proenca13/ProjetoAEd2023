#include <iostream>
#include <set>
#include "Functions.h"
#include "UcClass.h"
#include "Student.h"
#include "Schedule_Manager.h"

int main() {
    Schedule_Manager schedulemanager;
    while(true){
        schedulemanager.print_menu();
        int i;
        cin >> i;
        bool close = false;
        switch(i){
            case 1:
                while (true) {
                    schedulemanager.consult();
                    int k;
                    cin >> k;
                    bool close_consult = false;
                    switch(k){
                        case 1:
                            schedulemanager.consult_schedule();
                            break;
                        case 2:
                            schedulemanager.consult_students();
                            break;
                        case 3:
                            schedulemanager.number_students();
                            break;
                        case 4:
                            cout << "4";
                            break;
                        case 5:
                            cout << "5";
                            break;
                        case 6:
                            close_consult = true;
                            break;
                        default:
                            cout << "Invalid input!"<<'\n';
                    }
                    if (close_consult)break;
                }
                break;
            case 2:
                cout << "Request";
                break;
            case 3:
                close = true;
                break;
            default:
                cout << "Invalid input!"<<'\n';
        }
        if (close)break;
    }




    return 0;
}

