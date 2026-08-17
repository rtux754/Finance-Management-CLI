cmake_minimum_required(VERSION 3.10)

project(FinanceAndParfumProject VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Finance_Management main.cpp)
add_executable(Parfum_Database Database_Parfum_CLI/main.cpp)