/*
 ============================================================================
 Name        : Crossfire2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CrossfireOp.h"

int main(void) {
	int NUM_PLAYERS, boardSize;
	srand(time(NULL));
	struct slot *upLeft;
	struct slot *upRight;
	struct slot *downLeft;
	struct slot *downRight;
	struct player players[6];
	struct slot *currSlot = NULL;
	struct slot	*foundSlots;
	bool explored[7][7];
	int	count = 0;
	int reqDist	= 3;

	boardSize = 7;
	createBoard(boardSize,&upLeft, &upRight, &downLeft, &downRight);
	NUM_PLAYERS = getNumPlayers();
	for(int i=0; i<NUM_PLAYERS; i++){
		players[i] = getPlayer(i+1);
	}
	for(int i=0; i<NUM_PLAYERS; i++){
		switch(players[i].type)
		{
			case 0: players[i] = statfillOgre(players[i]); break;
			case 1: players[i] = statfillElf(players[i]); break;
			case 2: players[i] = statfillHuman(players[i]); break;
			case 3: players[i] = statfillWizard(players[i]); break;
		}
		players[i].pos = *getRandElement(upLeft, upRight, downLeft, downRight);
		printf("player %d is at position (%d,%d)\n", i+1, players[i].pos.row, players[i].pos.column);

	}
	for(int i=0; i<NUM_PLAYERS; i++){
		players[i] = playerMove( players[i], getMoveChoice());
	}
	for(int i=0; i<NUM_PLAYERS; i++){
		printf("player %d is at position (%d,%d)\n", i+1, players[i].pos.row, players[i].pos.column);
	}

	currSlot = reachDesiredElement(3,3,upLeft);
	for(int	i=0; i < 7; i++){
		for(int	j=0; j<7; j++){
			explored[i][j]	=	false;
		 }
	}

	foundSlots = malloc(16*sizeof(struct slot));
	if(currSlot!= NULL){
		findSlots(reqDist, 0, currSlot,	foundSlots,	&count,	explored);
		for(int i=0; i<count; i++){
			printf("(%d,%d)->",foundSlots[i].row, foundSlots[i].column);
		}
	}
	//sample = getRandElement(upLeft, upRight, downLeft, downRight);
	//printf("sample random slot = (%d,%d) type = %d \n", sample.row, sample.column, sample.type);

	return 0;
}
