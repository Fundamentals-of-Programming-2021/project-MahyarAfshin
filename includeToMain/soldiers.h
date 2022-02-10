#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>

extern const int FPS;
extern const int soldiersSpeed;

typedef struct soldier{
    Uint32 color;
    double x_coordinate;
    double y_coordinate;
    bool is_active;
    int speedCoefficient;
    bool is_potionActive;
}soldier;

typedef struct center{
    double x_coordinate;
    double y_coordinate;
    Uint32 color;
    bool is_used;
    int numOfSoldiers;
    int speedCoefficient;
    bool no_end;
    int soldierAddCoefficient;
    bool is_potionActive;
    Uint32 centerColor;
}center;

typedef struct attack{
    Uint32 color;
    int attackerIndex;
    int defenderIndex;
    int numOfSoldiers;
    soldier* firstSoldier;
}attack;

extern attack* attacks;

void soldiers_beginigOfTheGame(center* hexagonCenters);
void soldiersAddingByTime(center* hexagonCenters, long long int numOfFrames_fromBeginig);
void addAnAttack(long long int totalNumOfAttacks, int clickedIndex,center* hexagonsCenters, int tempIndex);
void attacksInProgress(center* hexagonsCenters, long long int totalNumOfAttacks);
void displaySoldiers(SDL_Renderer* rend, center* hexagonsCenters, long long int totalNumOfAttacks);
void deleteSoldier(int attackIndex, int soldierIndex, int soldiersNum);
void soldiersCollision(long long int totalNumOfAttacks);
void soldiersCollisionWithBase(long long int totalNumOfAttacks, center* hexagonsCenters);
long long int findFinishedAttack(long long int totalNumOfAttacks);
void deleteFinishedAttacks(long long int* totalNumOfAttacks);
void updateTheSpeedCoefficient(long long int totalNumOfAttacks, center* hexagonsCenters);
void update_isPotionActive(long long int totalNumOfAttacks, center* hexagonsCenters);