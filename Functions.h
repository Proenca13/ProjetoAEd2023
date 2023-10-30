#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include "UcClass.h"
#include "Student.h"
#include <iomanip>
using namespace  std;
set<UcClass> parsing_classes() ;
set<UcClass> parsing_schedules(set<UcClass> classes);
set<Student> parsing_students(set<UcClass> classes);
#endif