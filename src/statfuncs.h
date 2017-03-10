/*
 * statfuncs.h
 *
 *  Created on: 3 Mar 2017
 *      Author: eoghancunningham
 */

#ifndef STATFUNCS_H_
#define STATFUNCS_H_
#include "player.h"
#include <time.h>

struct player statfillOgre(struct player p);
struct player statfillElf(struct player p);
struct player statfillHuman(struct player p);
struct player statfillWizard(struct player p);

struct player statfillOgre(struct player p){
	srand(time(NULL));
	p.smartness = rand() % 21;
	p.strength = 80 + rand() % 21;
	p.dexterity = 80 + rand() % 21;
	p.magic_skills = 0;
	while (((p.luck + p.smartness) > 50) || (p.luck == 0)){
		p.luck = rand() % 45;
	}
	p.life = 100;
	return p;
}
struct player statfillElf(struct player p){
	srand(time(NULL));
	p.smartness = 70 + rand()%31;
	p.strength = 1 + rand()%50;
	p.dexterity = 1 + rand()%100;
	p.magic_skills = 50 + (rand()%31);
	p.luck = 60 + rand() % 41;
	p.life = 100;
	return p;
}
struct player statfillWizard(struct player p){
	srand(time(NULL));
	p.smartness = 90 + rand() % 11;
	p.strength = 1 + rand() % 20;
	p.dexterity = 1 + rand() % 100;
	p.magic_skills = 80 + rand() % 21;
	p.luck = 50 + rand() % 51;
	p.life = 100;
	return p;
}
struct player statfillHuman(struct player p){
	srand(time(NULL));
	int sum = 301;
	while (sum > 300) {
		p.dexterity = 1 + rand() % 100;
		p.luck = 1 + rand() % 100;
		p.magic_skills = 1 + rand() % 100;
		p.smartness = 1 + rand() % 100;
		p.strength = 1 + rand() % 100;
		sum = p.dexterity + p.luck + p.strength + p.magic_skills + p.smartness;
		p.life = 100;
	}
	return p;
}



#endif /* STATFUNCS_H_ */
