cmake_minimum_required(VERSION 3.10)
project(schedule)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        schedule
        main.cpp
        Student.cpp
        Schedule.cpp
        UcClass.cpp
        Lesson.cpp
        Functions.cpp
        Schedule_Manager.cpp
)
