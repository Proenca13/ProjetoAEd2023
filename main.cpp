#include <iostream>
#include "Schedule_Manager.h"

int main() {
    Schedule_Manager schedulemanager;
    schedulemanager.load_request();
    while(true){
        schedulemanager.print_menu();
        char i;
        cin >> i;
        bool close = false;
        switch(i){
            case '1':
                while (true) {
                    schedulemanager.consult();
                    char k;
                    cin >> k;
                    bool close_consult = false;
                    switch(k){
                        case '1':
                            schedulemanager.consult_schedule();
                            break;
                        case '2':
                            schedulemanager.consult_students();
                            break;
                        case '3':
                            schedulemanager.number_students();
                            break;
                        case '4':
                            schedulemanager.consult_occuption();
                            break;
                        case '5':
                            schedulemanager.uc_most_students();
                            break;
                        case '6':
                            close_consult = true;
                            break;
                        default:
                            cout << "Invalid input!"<<'\n';
                    }
                    if (close_consult)break;
                }
                break;
            case '2':
                while(true){
                    schedulemanager.request();
                    char k;
                    cin >> k;
                    bool close_request = false;
                    switch (k) {
                        case '1': {
                            schedulemanager.add_uc();
                            break;
                        }
                        case '2': {
                            schedulemanager.remove_uc();
                            break;
                        }
                        case '3': {
                            schedulemanager.switch_students();
                            break;
                        }
                        case '4':
                            close_request = true;
                            break;
                        default:
                            cout << "Invalid input!"<<'\n';
                    }
                    if(close_request)break;
                }
                break;
            case '3':
                schedulemanager.print_history();
                break;
            case '4':
                close = true;
                schedulemanager.save_requests();
                break;
            default:
                cout << "Invalid input!"<<'\n';

        }
        if (close)break;
    }
    return 0;
}
