/*
 * userInteractions.c
 *
 *  Created on: 31 Mar 2017
 *      Author: eoghancunningham
 */

#include <stdio.h>
#include "crossfireOp.h"

int getNumPlayers(void) {
	int NUM_PLAYERS = 7;
	while ((NUM_PLAYERS < 0) || (NUM_PLAYERS > 6)) {
		printf("Please enter the number of players : \n");
		scanf("%d", &NUM_PLAYERS);
	}
	return NUM_PLAYERS;
}

struct player getPlayer(int num) {
	struct player playerI;
	printf("Input the name of player %d\n", num);
	scanf("%s", &playerI.name);
	printf("Input the type of player %d\n", num);
	printf("(0 for Ogre\n1 for Human\n2 for Elf\n3 for Wizard)\n");
	scanf("%d", &playerI.type);
	return playerI;
}

void getDesiredElement(int boardSize, int * row, int * col){
	printf("Please enter the column and the Row of the desired slot \n");
	printf("Note that size of the board is %d\n", boardSize);

		//it will cycle asking the user to insert the row
		//until the value of the desired row is >= 0 or < of the
		// size of the board
		do {
			printf("Row: ");
			scanf("%d", row);
			printf("%d\n", *row);
			if(row < 0 && *row >= boardSize)
				printf("Error: Incorrect row dimension\n");
		} while(*row < 0 && *row >= boardSize);

		//it will cycle asking the user to insert the column
		//until the value of the desired row is >= 0 or < of the
		// size of the board
		do {
			printf("Column: ");
			scanf("%d", col);
			printf("%d\n", *col);
			if(*col < 0 && *col >= boardSize)
				printf("Error: Incorrect column dimension\n");
		} while(*col < 0 && *col >= boardSize);
}
