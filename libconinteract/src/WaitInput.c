/*
 * WaitInput.c
 *
 *  Created on: Sep 23, 2019
 *      Author: chorm
 */

#include <ConInteract.h>

#include <termios.h>
#include <unistd.h>
#include <stdio.h>


#if defined(__GNUC__)
#define unreachable() __builtin_unreachable()
#else

#if !defined(__has_builtin)
#define __has_builtin(n) 0
#endif
#if __has_builtin(__builtin_unreachable)
#define unreachable() __builtin_unreachable()
#else
#include <stdlib.h>
#define unreachable() abort();
#endif

#endif


int waitch(){
	struct termios oldattr, newattr;
	int ch;
	tcgetattr( STDIN_FILENO, &oldattr );
	newattr = oldattr;
	newattr.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
	return ch;
}

void waitInput(){
	waitch();
}

KeyDirection waitDirection(){
	for(;;){
		int ch = waitch();
		//Has Observable-behavior
		//so this loop isn't UB.
		switch(ch){
		case 'w':
		case 'W':
			return KEY_UP;
		case 'a':
		case 'A':
			return KEY_LEFT;
		case 's':
		case 'S':
			return KEY_DOWN;
		case 'd':
		case 'D':
			return KEY_RIGHT;
		case '\033':
			return KEY_ESC;
		case -1:
			return KEY_EOF;
		}
	}
	unreachable();
}

