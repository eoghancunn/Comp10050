/*
 * player.h
 *
 *  Created on: 3 Mar 2017
 *      Author: eoghancunningham
 */

#ifndef PLAYER_H_
#define PLAYER_H_

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
	int pos;

};

#endif /* PLAYER_H_ */
