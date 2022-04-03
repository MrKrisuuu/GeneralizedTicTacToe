cmake_minimum_required(VERSION 3.21)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TicTacToe
        Src/Board.cpp
        Inc/Board.h
        Src/Cleaner.cpp
        Inc/Cleaner.h
        main.cpp
        Src/Others.cpp
        Inc/Others.h
        Src/Printer.cpp
        Inc/Printer.h Inc/Parameters.h Inc/States.h Src/States.cpp)
