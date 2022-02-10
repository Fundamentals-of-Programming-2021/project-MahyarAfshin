#pragma once

#include"AI.h"

typedef struct potion{
    Uint32 color;
    int durationToWait;
    int durationToBeEnabled;
    int x_position;
    int y_position;
    bool is_deployed;
    long long int frameDeployed;
    long long int frameEnabled;
    bool is_enabled;
    Uint32 teamColor;
}potion;

extern potion* potions;
extern FILE* file;
extern FILE* fuckYou;

void drawThePotion(SDL_Renderer* rend, Uint32 color, int x_position, int y_position);
void initializePotions();
void findPotionCoordinates_random(center* hexagonsCenters, int* x_position, int* y_position);
void deployPotion(long long int numOfFrames_fromBegining, center* hexagonsCenters);
void displayPotions(SDL_Renderer* rend, long long int numOfFrames_fromBegining);
void soldiersCollision_withPotion(long long int totalNumOfAttacks, int totalNumOfOponents, long long int numOfFrames_fromBegining, center* hexagonsCenters);
void potionsLogic(long long int numOfFrames_fromBegining, center* hexagonsCenters);
void potionFade(center* hexagonsCenters, long long int numOfFrames_fromBegining);

