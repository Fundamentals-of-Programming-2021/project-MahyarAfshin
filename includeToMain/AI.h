#pragma once

#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#include "map.h"
#include "users.h"

typedef struct attack_check{
    int attackerIndex;
    int defenderIndex;
}attack_check;

typedef struct teams{
    int territories_index[46];
    int numOfTerritories;
    int attackTime;
    Uint32 color;
    attack_check bestAttack;
}teams;

extern teams* oponents;

extern const int windowWidth;
extern const int windowHeight;
extern const int boxesWidth;
extern const int boxesHeight;

int find_totalNumOfOponents(Uint32 playerColor);
int makeOponentsArray(Uint32 playerColor, int num);
int makeTeams(Uint32 playerColor, center* hexagonsCenters, int num);
int setAttackTime_forOponents(Uint32 playerColor, center* hexagonsCenters, int num);
int score_attacks(center* hexagonsCenters, int attackerIndex, int defenderIndex, long long int totalNumOfAttacks, int totalNumOfOponents);
void findTheBestAttack(int oponentIndex, center* hexagonsCenters, long long int totalNumOfAttacks, int totalNumOfOponents);
void AI_attack(center* hexagonsCenters, long long int* totalNumOfAttacks, int totalNumOfOponents, long long int numOfFrames_fromBeginig);
// this function returns 0 if the game isn't finish , -1 if the player lost and 1 if it wins
int check_forWinner(center* hexagonsCenters, Uint32 playerColor);
long long int score_calc(center* hexagonsCenters);
int winnerPage(int state, SDL_Renderer* rend, long long int score);
void deleteOponents(Uint32 playerColor, center* hexagonsCenters);

