/*
 * DirectionalInput.h
 *
 *  Created on: Sep 23, 2019
 *      Author: chorm
 */

#ifndef INCLUDE_CONINTERACT_H_
#define INCLUDE_CONINTERACT_H_

#ifdef __cplusplus
extern"C"{
#endif

#include <stdint.h>


typedef enum KeyDirection{
	KEY_UP = 1, KEY_DOWN = 2, KEY_LEFT = 3, KEY_RIGHT = 4, KEY_ESC = 0,
	KEY_EOF = -1
} KeyDirection;


enum{
	MENU_CLOSE = -1
};

/*
 * Waits for some input from the keyboard, but does not return it.
 * In most cases, waitch() is more useful
 */
void waitInput();
/**
 * Gets the next character inputted on the keyboard without buffering or echoing.
 * Related to getch from Windows CRT and libncurses
 */
int waitch();
/**
 * Waits for a character that is a directional input, where WASD is used for direction (case-insensitive).
 * If escape is pressed, returns KEY_ESC. If End of Input is encountered (should never occur), returns KEY_EOF.
 * Other inputs are discarded. waitch() is more useful if these inputs are required
 */
KeyDirection waitDirection();
/**
 * Displays a navigable menu with a given list of items.
 * The selection is returned, or -1 if the menu is exited with ESC.
 */
int32_t menu(const char* title, const char*const items[],int32_t length);
/**
 * Clears the Console Screen.
 */
void clearScreen();



#ifdef __cplusplus
};
#endif

#endif /* INCLUDE_CONINTERACT_H_ */
