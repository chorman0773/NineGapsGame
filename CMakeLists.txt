cmake_minimum_required(VERSION 3.15)
project(NineGapsGame C)

set(CMAKE_C_STANDARD 11)

include_directories(libconinteract/include)
include_directories(random/include)

add_executable(NineGapsGame
        libconinteract/include/ConInteract.h
        libconinteract/src/ClearScreen.c
        libconinteract/src/Menu.c
        libconinteract/src/WaitInput.c
        libconinteract/test/menu.c
        random/include/Random.h
        random/src/Random.c
        random/tests/00nextint.c
        random/tests/01nextintb.c
        src/main.c)
