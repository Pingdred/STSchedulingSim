cmake_minimum_required(VERSION 3.25)
project(STSchedulingSim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(Schedulers)

add_executable(
    schedsim 
    Schedulers/Priority.h
    Schedulers/Proc.h
    Schedulers/RR.h
    Schedulers/Scheduler.h
    Schedulers/SJF.h
    Schedulers/SRTF.h
    main.cpp
)