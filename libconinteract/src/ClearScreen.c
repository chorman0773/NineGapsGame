/*
 * ClearScreen.c
 *
 *  Created on: Sep 23, 2019
 *      Author: chorm
 */

#include <ConInteract.h>
#include <stdlib.h>
#include <stdio.h>

void clearScreen(){
	printf("\e[0m\e[2J\e[H");
}
