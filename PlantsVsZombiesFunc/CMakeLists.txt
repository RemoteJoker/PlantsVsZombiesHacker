cmake_minimum_required(VERSION 3.16)

project(PlantsVsZombiesFunc LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Network)


add_library(PlantsVsZombiesFunc SHARED
  plantsvszombiesfunc.cpp
  plantsvszombiesfunc.h
  cheatfunc.h cheatfunc.cpp
)

target_link_libraries(PlantsVsZombiesFunc PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(PlantsVsZombiesFunc PRIVATE Qt6::Network)
target_compile_definitions(PlantsVsZombiesFunc PRIVATE PLANTSVSZOMBIESFUNC_LIBRARY)
