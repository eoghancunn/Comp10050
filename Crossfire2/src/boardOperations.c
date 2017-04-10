/*
 * boardCreation.c

 *
 *  Created on: 29 Mar 2017
 *      Author: liliana
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CrossfireOp.h"



/*
 * This function creates the board
 * Parameters:
 * 	size: the size of the board
 * 	upLeft: pointer of pointer to slot at position (0, 0)
 * 	upRight: pointer of pointer to slot at position (0, boardSize -1)
 * 	downLeft: pointer of pointer to slot at position (boardSize -1, 0)
 * 	upLeft: pointer of pointer to slot at position (boardSize - 1, boardSize -1)
 */
void createBoard(int boardSize, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight){
	srand(time(NULL));
	//The board is represented as a pointer of pointer to slots
	//This allocates in memory the space for the pointers to each row of the board
	struct slot ** board = malloc(boardSize * sizeof(struct slot *));


	for(int i =0; i< boardSize; i++){
		//This allocates in memory the space for the slots in each row of the board
		board[i] = malloc(boardSize * sizeof(struct slot));

		//For each slot it sets up the row and column number
		for(int j=0;j < boardSize; j++){
			board[i][j].row = i;
			board[i][j].column = j;
			board[i][j].type = rand() % 3; // each slot is assigned an int between 0 and 2
		}
	}

	//It sets up the adjacent slots for the slots that are
	//not at the borders. These slots have 4 adjacent elements
	for(int i =1; i< boardSize-1; i++){
		for(int j=1;j < boardSize-1; j++){
			board[i][j].up = &board[i-1][j];
			board[i][j].right = &board[i][j+1];
			board[i][j].down = &board[i+1][j];
			board[i][j].left = &board[i][j-1];
		}
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last row, except the slots at the edges.
	//
	for(int j = 1; j < boardSize -1; j++){
		//It sets up the adjacent slots for the slots that are in the first row.
		//These slots don't have an adjacent element on top of them
		// because they are on the first row of the board
		board[0][j].right = &board[0][j+1];
		board[0][j].left = &board[0][j-1];
		board[0][j].down = &board[1][j];

		//It sets up the adjacent slots for the slots that are in the last row.
		//These slots don't have an adjacent element on down them
		// because they are on the last row of the board
		board[boardSize - 1][j].right = &board[boardSize - 1][j+1];
		board[boardSize -1][j].left = &board[boardSize - 1][j-1];
		board[boardSize - 1][j].up = &board[boardSize - 2][j];
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last column, except the slots at the edges.
	//
	for(int i = 1; i < boardSize -1; i++){
		//It sets up the adjacent slots for the slots that are in the first row.
		//These slots don't have an adjacent element on the left
		// because they are on the first column of the board
		board[i][0].right = &board[i][1];
		board[i][0].up = &board[i-1][0];
		board[i][0].down = &board[i+1][0];

		//It sets up the adjacent slots for the slots that are in the last row.
		//These slots don't have an adjacent element on the right
		// because they are on the last column of the board
		board[i][boardSize-1].left = &board[i][boardSize-2];
		board[i][boardSize -1].up = &board[i -1][boardSize-1];
		board[i][boardSize -1].down = &board[i+1][boardSize -1];
	}


	//It sets up the adjacent slots for the slot at position (0,0).
	//This only has only 2 adjacent slots: right and down
	board[0][0].right = &board[0][1];
	board[0][0].down = &board[1][0];

	//It sets up the adjacent slots for the slot at position (0,boardSize -1).
	//This only has only 2 adjacent slots: left and down
	board[0][boardSize-1].left = &board[0][boardSize-2];
	board[0][boardSize -1].down = &board[1][boardSize -1];

	//It sets up the adjacent slots for the slot at position (boarSize -1 ,0).
	//This only has only 2 adjacent slots: up and right
	board[boardSize -1][0].right = &board[boardSize -1][1];
	board[boardSize -1][0].up = &board[boardSize -2][0];

	//It sets up the adjacent slots for the slot at position (boarSize -1 ,boardSize-1).
	//This only has only 2 adjacent slots: up and left
	board[boardSize - 1][boardSize-1].up = &board[boardSize-2][boardSize-1];
	board[boardSize - 1][boardSize -1].left = &board[boardSize -1][boardSize -2];





	//assigns a pointer to slot at position (0, 0)
	*upLeft = &board[0][0];
	//assigns pointer of pointer to slot at position (0, boardSize -1)
	*upRight = &board[0][boardSize -1];
	//assigns pointer of pointer to slot at position ( boardSize -1,)
	*downLeft = &board[boardSize -1][0];
	//assigns pointer of pointer to slot at position (boardSize -1, boardSize -1)
	*downRight = &board[boardSize -1][boardSize -1];
	}



/*
 * This function traverses the board to find a slot at a predefined
 * position (row, column)
 * Parameters:
 * 	row: the row in which the desired slot is located
 * 	column: the column in which the desired slot is located
 * 	initialSlot: the slot from which the slot search should start
 */
struct slot * reachDesiredElement(int row, int column, struct slot * initialSlot){

	bool found = false;
	//current slot
	struct slot * currentSlot = initialSlot;

	//prints the column and the row of the initial slot from which the search starts
	//while the slot is not found
	while(found == false){

		//if the row of the current slot is > of the row of the desired slot,
		//we move up
		if(currentSlot->row > row){
			//the current slot now points to the slot one row up
			currentSlot = currentSlot->up;
			//prints the column and the row of the current slot
			//printf("Current slot (%d, %d) %d -> \n",currentSlot->row,currentSlot->column,currentSlot->type);

		}
		//if the row of the current slot is < of the row of the desired slot,
		//we move down
		if(currentSlot->row < row){
			//the current slot now points to the slot one row down
			currentSlot = currentSlot->down;
			//prints the row and the column of the current slot
			//printf("Current slot (%d, %d) %d -> \n",currentSlot->row,currentSlot->column, currentSlot->type);

		}
		//if the column of the current slot is > of the column of the desired slot,
		//we move left
		if(currentSlot->column > column){
			//the current slot now points to the slot one column left
			currentSlot = currentSlot->left;
			//prints the row and the column of the current slot
			//printf("Current slot (%d, %d) %d -> \n",currentSlot->row,currentSlot->column, currentSlot->type);
		}

		//if the column of the current slot is < of the column of the desired slot,
		//we move right
		if(currentSlot->column < column){
			//the current slot now points to the slot one column right
			currentSlot = currentSlot->right;
			//prints the row and the column of the current slot
			//printf("Current slot (%d, %d) %d -> \n",currentSlot->row,currentSlot->column, currentSlot->type);

		}
		//if the current slot is at a column and a row equal to the desired column and row, respectively
		// we found the slot
		if(currentSlot->column == column && currentSlot->row == row){
			return currentSlot;
			//printf("Found\n");
			found = true;
		}

	}
}

struct slot * getRandElement( struct slot *upLeft, struct slot *upRight,struct slot *downLeft,struct slot *downRight) {
	int row = 6;
	int col = 6;
	if(row >= 7/2){
			if(col >= 7/2)
				return reachDesiredElement(row,col, downRight);
			else
			/*If the the required slot is closer to the down-left
			* corner of the board the search starts from downLeft,
			* which points to slot at position (boardSize-1, 0)*/
				return reachDesiredElement(row,col, downLeft);
		} else {
			/*If the the required slot is closer to the up-right
			* corner of the board the search starts from upRight,
			* which points to slot at position (0, boarSize -1)*/
			if(col >= 7/2)
				return reachDesiredElement(row,col, upRight);
			/*If the the required slot is closer to the up-left
			* corner of the board the search starts from upLeft,
			* which points to slot at position (0, 0)*/
			else return reachDesiredElement(row,col, upLeft);
		}

}
enum direction getMoveChoice(void) {
	enum direction dir;
	printf("Input the direction you wish to move: \n0 for up\n1 for down\n2 for left\n3 for right\nany other value to stay still\n");
	scanf("%d", &dir);
	return dir;
}

struct player playerMove(struct player p, enum direction dir){
	switch(dir) {  							//direction is indicated in input through the enumerated type
	case 0: if (p.pos.up != NULL) {			//checking if the pointer is valid
		p.pos = *(p.pos.up);				//moving the player based on the choice of direction
	} else {puts("this is not a valid move");}; break;
	case 1: if (p.pos.down != NULL) {
		p.pos = *(p.pos.down);
	} else {puts("this is not a valid move");}; break;
	case 2: if (p.pos.left != NULL) {
		p.pos = *(p.pos.left);
	} else {puts("this is not a valid move");}; break;
	case 3: if (p.pos.right != NULL) {
		p.pos = *(p.pos.right);
	} else {puts("this is not a valid move");};break;
	}
	if (p.pos.type == 1) {				//assigning stats based on the type of the slot the player moves to
		if (p.dexterity < 50 ) {
			p.strength -= 10;
		} else if (p.dexterity >= 60){
			p.strength += 10;
		}
	} else if (p.pos.type == 2) {
		if (p.smartness > 60) {
			p.magic_skills += 10;
		} else if (p.smartness <= 50){
			p.dexterity -= 10;
		}
	}
	return p;
}
void findSlots(int reqDist,int currDist,struct slot * currSlot,struct slot * foundSlots,int * count,bool explored[7][7]) {
	if(currDist == reqDist){
		if(explored[currSlot->row][currSlot->column] == false){
			*(foundSlots + *count) = *currSlot;
			(*count)++;
			explored[currSlot->row][currSlot->column] = true;
		}
	}
	else{
		if(currSlot->up != NULL) {
			findSlots(reqDist, currDist+1,	currSlot->up, foundSlots, count, explored);
		}
		if(currSlot->right != NULL)	{
			findSlots(reqDist, currDist+1,	currSlot->right, foundSlots, count,	explored);
		}
		if(currSlot->left != NULL) {
			findSlots(reqDist, currDist+1,	currSlot->left, foundSlots, count, explored);
		}
		if(currSlot->down != NULL){
			findSlots(reqDist, currDist+1,	currSlot->down, foundSlots, count, explored);
		}
	}
}


