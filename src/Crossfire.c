/*
 ============================================================================
 Name        : Crossfire.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "player.h"

int main(void) {

	struct player players[6];
	int numPlay = 0;
	printf("Input the number of players : \n");
	scanf("%d", %numPlay);
	for(int i = 0; i<numPlay; i++){
		printf("Input the name of player %d", i);
		fgets(players[i].name, 15, stdin);
		printf("Input the type of player %d", i);
		scanf("%d", &players[i].type);
	}
	for(int i = 0; i<numPlay; i++){
		printf("%s \t %d \n", players[i].name, players[i].type);
	}

}
