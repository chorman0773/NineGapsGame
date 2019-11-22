# NineGapsGame
Nine Gaps Game.

Copyright (c) 2019 Connor Horman
This program is licensed under the terms of the MIT License. See `/LICENSE` for details. 

The program under `/random` is distributed under the terms of the MIT License, and is Copyright (C) 2019 Connor Horman. See `/random/LICENSE` for details.
The program under `/libconinteract` is distributed under the terms of the MIT License, and is Copyright (C) 2019 Connor Horman. See `/libconinteract/LICENSE` for details. 

## How to build

The program can be built on Linux or cygwin by entering `make` into the shell. 
Native Windows Support is not provided due to issues in libconinteract. 
MacOS support is not guaranteed. 

## How to play

To play, start the game with `./ninegaps`. Select difficulty with W and S, pressing enter on the difficulty you wish.
A Randomly generated board will be produced, with some gaps (indicated by question marks). The numbers 1-9 appear exactly once in the 3x3 board, with random operations between the rows and columns.
The solutions to each row and column are provided, you will have to solve the equations and recover the values. 
Navigate the board using WASD and place numbers 1-9 on the gaps. 
Consider your choices carefuly, there is only one solution to each board. 
Once you have placed a number in a space (ie. filled a gap), you cannot replace it.
Once you have filled every gap, press enter to check your solution. 
You can press escape in game to return to the menu.

To quit, press escape while in the main menu. 

To play effectively, you will need to solve basic algebra questions (with addition, subtraction, and division). Note that currently, the order of operations is left to write and top to bottom, BEDMAS is not respected. This will be changed in a future version. 

