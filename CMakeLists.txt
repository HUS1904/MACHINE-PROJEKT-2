cmake_minimum_required(VERSION 3.27)
project(MACHINE_PROJEKT_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(MACHINE_PROJEKT_2
        Yukon/Main.c
        Yukon/Card.c
        Yukon/Card.h
        Yukon/Load.c
        Yukon/Load.h
        Yukon/Board.c
        Yukon/Board.h
        Yukon/Main.h
        Yukon/Split.c
        Yukon/Split.h
        Yukon/Shuffle.c
        Yukon/shuffle.h
        Yukon/SaveDeck.c
        Yukon/SaveDeck.h
)
