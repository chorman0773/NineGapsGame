/*
 * main.c
 *
 *  Created on: Sep 26, 2019
 *      Author: chorm
 *
 *  Copyright (C) 2019 Connor Horman. All Rights Reserved.
 */

#include <Random.h>
#include <ConInteract.h>
#include <stdio.h>

/**
 * Swap the value at a with the value at b.
 */
static void swap(int* a,int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * Returns val, wrapping at 0 and max.
 * In particular, returns val%max.
 *
 * If the macro NOWRAP is defined, instead, clamps val to [0,max).
 */
static int wrap(int val,int max){
#ifdef NOWRAP
	if(val<0)
		return 0;
	else if(val>=max)
		return max-1;
	else
		return val;
#else
	while(val<0)
		val +=max;
	while(val>=max)
		val -=max;
	return val;
#endif
}

/**
 * Shuffles values from arr[0] to arr[len-1], using an n-pass selection shuffle algorithm.
 * For each pass
 * 	for each index, i, in the array, pick a random index, j, and swap arr[i] with arr[j]
 */
static void randomShuffle(Random* rand,int* arr,int len,int passc){
	for(;passc>0;passc--)
		for(int i = 0;i<len;i++)
			swap(&arr[i],&arr[Random_nextIntb(rand,len)]);
}


/**
 * Solves the rows of the flat 2-dimensional array at arr.
 * Addition is used between all values in the row.
 * Places the solutions into rowSums[0..nrows].
 */
static void solveRows(int* arr,int* rowSums,int* rowOps){
	rowSums[0] = arr[0];
    rowSums[1] = arr[3];
    rowSums[2] = arr[6];
	for(int i = 0;i<3;i++)
	    for(int j = 1;j<3;j++)
	        switch(rowOps[i*3+j]) {
	        case 0:
	            rowSums[i] += arr[i*3+j];
	            break;
	        case 1:
	            rowSums[i] -= arr[i*3+j];
	            break;
	        case 2:
	            rowSums[i] *= arr[i*3+j];
	            break;
            }

}

/**
 * Solves the columns of the flat 2-dimensional array at arr.
 * Places the solutions into rowSums[0..ncols].
 */
static void solveCols(int* arr,int* colSums,int* ops){
	colSums[0] = arr[0];
	colSums[1] = arr[1];
	colSums[2] = arr[2];
    for(int i = 0;i<3;i++)
        for(int j = 1;j<3;j++)
            switch(ops[j*3+i]) {
                case 0:
                    colSums[i] += arr[j*3+i];
                    break;
                case 1:
                    colSums[i] -= arr[j*3+i];
                    break;
                case 2:
                    colSums[i] *= arr[j*3+i];
                    break;
            }
}

/**
 * Cheap hack with ascii. "Hides" count indecies in the array,
 *  by replacing the value at that index with 15, the value that satisfies 0x30+n=0x3F ('0'+n='?').
 * Each index is visited by this method at most once, so exactly count indecies are always replaced.
 * Exception: If count is greater than len, then all indecies are replaced instead.
 *
 * Implementation Note: I should be forbidden from making C programs, as I am prone to using hacks like this.
 */
static void hide(Random* rand,int* arr,int len,int count,int hideval){
	if(count>len)
		count = len;
	for(int i = 0;i<count;i++){
		int pos;
		do{
			pos = Random_nextIntb(rand,len);
		}while(arr[pos]==hideval);
		arr[pos] = hideval;
	}
}

int main(){
    const char ops[3] = "+-*";
    int difficulty;
    //Initialize difficulty list. The Null pointer indicates the end of the list, so length does not need to be passed in to the function
    const char* const difficulties[] = {"Easy","Medium","Hard","Extreme",0};
    //Initialize the Psuedorandom Number Generator
    Random* rand = Random_new();
    Random_seed(rand);
	//Select Difficulty using the menu function, exit on -1 (which is triggered by pressing escape
    while((difficulty=menu("Please Select your difficulty (Navigate with W and S, press Enter to select, or Escape to quit)",difficulties))!=-1){
        //Set Initial Cursor Positions
        int cursorx = 0;
        int cursory = 0;
        //Menu is Zero Indexed, but are calculation expects Easy to be 1,
        // So Change it here
        difficulty++;

        //Initialize numbers to [1..9]
        //This along with randomShuffle ensures that each number in [1,9] is used exactly once.
        //Also allocate space for rowSums and colSums, but don't do anything with that space
        int numbers[] = {1,2,3,4,5,6,7,8,9};
        int rowSums[3];
        int colSums[3];
        int rowOps[9]; //Allocate space for 9 operations. The first column is unused, but makes calculations easier
        int colOps[9]; // Same here, but first row is unused

        //Shuffle the rows.
        //Use 12-pass selection shuffle to distribute properly,
        //and avoid lack of proper distribution introduced by Selection Shuffle
        // and the PRNG.
        randomShuffle(rand,numbers,9,12);
        Random_intsb(rand,rowOps,9,0,3);
        Random_intsb(rand,colOps,9,0,3);
        //After shuffling, solve the rows and colums
        solveRows(numbers,rowSums,rowOps);
        solveCols(numbers,colSums,colOps);
        //Now hide entries in the array by replacing them with '?'
        hide(rand,numbers,9,difficulty*2+1,'?'-'0'); //Dirty Dirty Hacks
        int dir;
        do{
            clearScreen();
            printf("   %c   %c   %c\n",cursorx==0?'|':' ',cursorx==1?'|':' ',cursorx==2?'|':' ');
            printf("   %c   %c   %c\n",cursorx==0?'v':' ',cursorx==1?'v':' ',cursorx==2?'v':' ');
            for(int i = 0;i<3;i++){
                if(i!=0) {
                    printf(" ");
                    for (int j = 0; j < 3; j++)
                        printf("  %c ", ops[colOps[i * 3 + j]]);
                    printf("\n");
                }
                printf("%s ",cursory==i?"->":"  ");
                for (int j = 0; j < 3; j++) {
                    if(j!=0)
                        printf("%c ",ops[rowOps[i*3+j]]);
                    printf("%c ",'0'+numbers[i * 3 + j]);
                }
                printf("= %2d\n",rowSums[i]);
            }
            printf("   =   =   =\n");
            printf("   %2d  %2d  %2d\n",colSums[0],colSums[1],colSums[2]);
            printf("Navigate Screen (WASD), Press a number (1-9) to insert it into the selected position, Press Enter when finished, or Escape to quit>\n");
            dir = waitch();
            switch(dir){
            case 'W':
            case 'w':
                cursory--;
            break;
            case 'A':
            case 'a':
                cursorx--;
            break;
            case 'S':
            case 's':
                cursory++;
            break;
            case 'D':
            case 'd':
                cursorx++;
            break;
            case '\n':
                goto check_break; //Check if a player presses enter. 
            case '\033':
                goto quit;//End this game without solving with Escape is pressed, return to the menu
            default:
                if(dir>'0'&&dir<='9'){
                    if(numbers[cursorx+3*cursory]==('?'-'0'))
                        numbers[cursorx+3*cursory] = dir-'0';
                }
            break;
            }
            cursorx = wrap(cursorx,3);
            cursory = wrap(cursory,3);
        }while(true);
        check_break: ;
        int check[3];
        bool hasSolved = true;
        solveRows(numbers,check,rowOps);
        for(int y = 0;y<3;y++)
            if(rowSums[y]!=check[y])
                hasSolved=false,printf("Incorrect Solution on row %d, expected %d\n",y+1,rowSums[y]);
        solveCols(numbers,check,colOps);
        for(int y = 0;y<3;y++)
            if(colSums[y]!=check[y])
		        hasSolved=false,printf("Incorrect Solution on column %d, expected %d\n",y+1,colSums[y]);
        if(hasSolved)
            puts("Congratulations, you solved the puzzle.");
        printf("Press any key to return to the menu>");
        waitch();
        quit: ;
	}
    clearScreen();
    Random_free(rand); // Release the Psuedo-random Number generator. 
    //This is important as the generator is allowed to initialize a lock that needs to be uninitialized
}

