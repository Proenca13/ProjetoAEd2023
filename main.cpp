#include <iostream>
#include <set>
#include "Functions.h"
#include "UcClass.h"
#include "Student.h"

int main() {
    set<UcClass> classes = parsing_classes();
    classes = parsing_schedules(classes);
    set<Student> students = parsing_students(classes);
    for(auto student:students){
        cout << "Name: "<< student.get_name() << " Up: " << student.get_studentCode()<< '\n';
    }



    return 0;
}

