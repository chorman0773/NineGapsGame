/*
 * menutest.c
 *
 *  Created on: Sep 23, 2019
 *      Author: chorm
 */

#include <ConInteract.h>
#include <stdio.h>

int main(){
	const char* ITEMS = {
			"Test 1",
			"Test 2",
			"Test 3",
			"Test 4"
	};
	clearScreen();
	int32_t item = menu(ITEMS,4);
	clearScreen();
	if(item<0){
		printf("You pressed Escape, is this correct [y or n]?>");
		fflush(stdout);
		if(getchar()=='y')
			return 0;
		else
			return 1;
	}
	else{
		printf("You selected %s, is this correct [y or n]?>");
		fflush(stdout);
		if(getchar()=='y')
			return 0;
		else
			return 1;
	}

}

