cmake_minimum_required(VERSION 3.16)
project(project2_jfrandsen)

set(CMAKE_CXX_STANDARD 14)

add_executable(
    project2_jfrandsen 
    main.cpp 
    Customer.h Customer.cpp 
    Logger.h Logger.cpp 
    Distribution.h
    ExponentialDistribution.h ExponentialDistribution.cpp
    UniformDistribution.h UniformDistribution.cpp
    VaccinationCenter.h VaccinationCenter.cpp
    VaccinationStation.h VaccinationStation.cpp
    Clerk.h Clerk.cpp
    SynchronizedQueue.h
    StatsHelper.h StatsHelper.cpp)
    
