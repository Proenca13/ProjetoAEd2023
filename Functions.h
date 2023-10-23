#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include "UcClass.h"
using namespace  std;
set<UcClass> parsing_classes() ;
void parsing_schedules(set<UcClass> classes);
void parsing_students(set<UcClass> classes);
#endif