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
	int smartness = 100;
	int strength = 100;
	int magic_skills = 100;
	int luck = 100;
	int dexterity = 100;
	int pos = 0;

};

#endif /* PLAYER_H_ */
