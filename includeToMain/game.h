#pragma once

#include<stdio.h>
#include"potion.h"

extern int mouse_xPosition;
extern int mouse_yPosition;

int startGame(int mapNum, SDL_Renderer* rend, long long int userIndex);