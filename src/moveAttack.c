/*
 * move.c
 *
 *  Created on: 3 Mar 2017
 *      Author: Hugh Ormond
 */
#include <stdio.h>
#include <stdlib.h>
#include "slots.h"
#include "player.h"
#define NUM_PLAYERS 3
#define NUM_SLOTS 5

int main(void) {	//Should take input of playersArray and slotsArray when in main program
	enum slotType slotsArray[NUM_SLOTS] = {ground, hill, hill, ground, city};//Can be removed when in main program*****
	int i,j;
	int moveChoice, moveDirection, attackChoice, attackDirection;	//"bools" used to store whether a player wished to move, which direction if they do, and the same for attacking
	int canMove = 1;	//"bool" which stays at 1 each time a player moves until we find a reason they cannot
	int closest = NUM_SLOTS;	//int for finding the location of the closest player for attacks
	int closeCount = 0;	//int which is incremented if we find 2 players equally close to an attacker, and the choice will be presented
	int otherClosestIndex;	//Index in playersArray of the other closest player if 2 are equally close

	struct player keith = {"Keith", ogre, 100, 100, 100, 100, 100, 100, 0};
	struct player charlie = {"Charlie", wizard, 100, 100, 100, 100, 100, 100, 2};
	struct player mick = {"Mick", human, 100, 100, 100, 100, 100, 100, 4};//Added .life into players.h for use here
	struct player playersArray[NUM_PLAYERS] = {keith, charlie, mick};//Temporary players array until code is joined together, can all be removed****

	setbuf(stdout, NULL);	//Fix eclipse output buffering problem
	for (i = 0; i < NUM_PLAYERS; i++) {	//Loop through each player to ask if they want to move, and where
		printf("%s, would you like to move? (1 for yes, 0 for no)\n", playersArray[i].name);
		scanf("%d", &moveChoice);
		if (moveChoice == 1) {
			puts("Enter 0 to move left, or 1 to move right");
			scanf("%d", &moveDirection);
			canMove = 1;
			if (moveDirection == 0) {	//Perform the relevant checks & actions for moving left
				if (playersArray[i].pos == 0) {	//If a player is on the far left of the board, they cannot move left
					puts("You are on the edge of the board!");
					canMove = 0;
					i--;		//If the player enters an invalid action such as this one, i is decremented so that they are asked again
				}
				else {
					for (j = 0; j < NUM_PLAYERS; j++) {	//Check if any player is on the slot to the left
						if (playersArray[j].pos == playersArray[i].pos - 1) {
							puts("That slot is already occupied!");
							canMove = 0;
							i--;
							break;
						}
					}
					if(canMove) {	//Once all the checks are passed, the player can be moved left
						playersArray[i].pos--;
						switch(slotsArray[playersArray[i].pos]) {	//Switch for the type of slot the player moved too
							case 1:	//Perform stat changes for when the player is on a hill
								if (playersArray[i].dexterity < 50) {
									playersArray[i].strength -= 10;
								} else if (playersArray[i].dexterity >= 60) {
									playersArray[i].strength += 10;
								}
								break;
							case 2:	//and for a city
								if (playersArray[i].smartness > 60) {
									playersArray[i].magic_skills += 10;
								} else if (playersArray[i].smartness <= 50) {
									playersArray[i].dexterity -= 10;
								}
								break;
							//There is no case 0 as flat ground makes no stat changes
						}

					}
				}
			} else if (moveDirection == 1) {	//Now repeat the same checks for moving right
				if(playersArray[i].pos == NUM_SLOTS) {
					puts("You are on the edge of the board!");
					canMove = 0;
					i--;
				}
				else {
					for (j = 0; j < NUM_PLAYERS; j++) {
						if (playersArray[j].pos == playersArray[i].pos + 1) {
							puts("That slot is already occupied!");
							canMove = 0;
							i--;
							break;
						}
					}
					if(canMove) {
						playersArray[i].pos++;
						switch(slotsArray[playersArray[i].pos]) {
							case 1:
								if (playersArray[i].dexterity < 50) {
									playersArray[i].strength -= 10;
								} else if (playersArray[i].dexterity >= 60) {
									playersArray[i].strength += 10;
								}
								break;
							case 2:
								if (playersArray[i].smartness > 60) {
									playersArray[i].magic_skills += 10;
								} else if (playersArray[i].smartness <= 50) {
									playersArray[i].dexterity -= 10;
								}
								break;
						}
					}
				}
			}
			else {	//If the player entered an invalid direction, decrement i and ask them again
				puts("That is not a valid direction");
				i--;
			}
		} else if(moveChoice == 0) {
			puts("Would you like to attack? (1 for yes, 0 for no)");
			scanf("%d", &attackChoice);
			if (attackChoice == 1) {
				if (i != 0) {
					closest = 0;
				}
				else {
					closest = 1;
				}
				closeCount = 0;
				for (j = 1; j < NUM_PLAYERS; j++) {	//Loop through array of players checking for closest distance between players, and if there are 2 at that point
					if (j == i) {
						j++;	//Stop the code from saying the attacker is it's own closest player
					}
					if (abs(playersArray[i].pos - playersArray[j].pos) < abs(playersArray[i].pos - playersArray[closest].pos)) {
						closest = j;	//If we find a closer player than we have before, store it and reset closeCount
						closeCount = 0;
					} else if (abs(playersArray[i].pos - playersArray[j].pos) == abs(playersArray[i].pos - playersArray[closest].pos)) {
						closeCount++;	//If 2 players are equally close to the attacker at the end, we know to ask
						otherClosestIndex = j;
					}
				}
				//printf("Closest = %d, closeCount = %d otherClosestIndex: %d\n", playersArray[closest].pos, closeCount, playersArray[otherClosestIndex].pos);
				if (closeCount != 0 && closest != otherClosestIndex) {
					attackDecision:
					puts("Enter 0 to attack player on left, or 1 to attack player on right");
					scanf("%d", &attackDirection);
					if (attackDirection == 0) {	//Assign closest to the index of the player of the left if it currently the player on the right
						if (playersArray[closest].pos > playersArray[i].pos) {
							closest = otherClosestIndex;
						}
					} else if (attackDirection == 1) {
						if (playersArray[closest].pos < playersArray[i].pos) {
							closest = otherClosestIndex;
						}
					}
					else {
						puts("That is not a valid input");
						goto attackDecision;
					}
				}
				//Once the correct player has been found, we can finally perform the attack according to guidelines
				if (playersArray[closest].strength <= 70) {
					playersArray[closest].life -= 0.5 * playersArray[closest].strength;
				} else {
					playersArray[i].life -= 0.3 * playersArray[closest].strength;
				}

			} else if (attackChoice != 0) {
				puts("That is not a valid option");
				i--;
			}
		} else {
			puts("That is not valid option");
			i--;
		}
	}

	//Finally print the players with their type and health
	for (i = 0; i < NUM_PLAYERS; i++) {
		printf("%s (", playersArray[i].name);
		switch(playersArray[i].type) {
			case(0):
				printf("Elf, ");
				break;
			case(1):
				printf("Human, ");
				break;
			case(2):
				printf("Ogre, ");
				break;
			case(3):
				printf("Wizard, ");
				break;
		}
		printf("%d)\n", playersArray[i].life);
	}

	return 0;
}
