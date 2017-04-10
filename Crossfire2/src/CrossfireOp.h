/*
 * slot.h
 *
 *  Created on: 31 Mar 2017
 *      Author: eoghancunningham
 */

#ifndef CROSSFIREOP_H_
#define CROSSFIREOP_H_

typedef int bool;
enum { false, true };

enum slotType {
	ground,
	hill,
	city
};

enum direction {
	up,
	down,
	left,
	right
};

struct slot {
	int row;
	int column;

	struct slot *left;
	struct slot *right;
	struct slot *up;
	struct slot *down;

	enum slotType type;

};

enum playertype {
	elf,
	human,
	ogre,
	wizard
};

struct player {
	char name[15];
	enum playertype type;
	int smartness;
	int strength;
	int magic_skills;
	int luck;
	int dexterity;
	int life;
	struct slot pos;

};

struct slot * reachDesiredElement(int row, int column, struct slot * initialSlot); // starts from one corner to find a slot
void getDesiredElement(int boardSize, int * row, int * col);

struct slot * getRandElement( struct slot *upLeft, struct slot *upRight,struct slot *downLeft,struct slot *downRight);
// chooses a random element and calls RDE function to move to that element

void createBoard(int boardSize,	struct slot	**upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight);
//creates the board and assigns the adjacent slots to each slot

struct player getPlayer(int num);
//gets the name and type of each player

struct player statfillOgre(struct player p);
struct player statfillElf(struct player p);
struct player statfillHuman(struct player p);
struct player statfillWizard(struct player p);
//each assigns stats based on the player type

enum direction getMoveChoice(void);
//Asks the user for the direction they wish to move

struct player playerMove(struct player p, enum direction dir);
//moves the player

void findSlots(int reqDist, int currDist, struct slot * currSlot, struct slot * foundSlots, int * count, bool explored[7][7]);




#endif /* CROSSFIREOP_H_ */
