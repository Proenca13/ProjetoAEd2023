//
// Created by Rodrigo Resende on 09/10/2023.
//

#ifndef SCHEDULE_UCCLASS_H
#define SCHEDULE_UCCLASS_H

#include <string>
#include "Schedule.h"

using namespace std;
class UcClass {
public:
    UcClass(string classCode, Schedule schedule);
    string get_classCode() const;
    Schedule get_schedule() const;
    void set_classCode(string classCode);
    void set_schedule(Schedule schedule);
    bool operator<(UcClass uclass) const;

private:
    string classCode_;
    Schedule schedule_;
};


#endif //SCHEDULE_UCCLASS_H
