#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include"soldiers.h"

#define pi 3.14159265359
#define hexagon_radii 50

typedef struct color{
    Uint32 color;
    bool is_used;
}color;

typedef struct hexagon{
    Sint16 x_coordinates[6];
    Sint16 y_coordinates[6];
}hexagon;

typedef struct arrow{
    Sint16 x_coordinates[7];
    Sint16 y_coordinates[7];
}arrow;

extern color* colors;

hexagon* creatingHexagons(center hexagonCenter, Sint16 radius);
center* createMapTemplate(SDL_Renderer* rend); // the return will be an array containing 46 centers for hexagons
//the return of below function will be a string that shows the user, it's color in game
char* generatingRandomMap(int numOfOponents, int numOfRegions, center* hexagonsCenters); // in this game the maximum number of oponents is 5 and the maximum number of regions is 40 and the minimun number of regions is 10
void putTheMapOnTheRenderer(center* hexagonCenters, SDL_Renderer* rend, char* displayString);
//below function returns the index of the chosen hexagon
int getMousePosition(center* hexagonCenters, SDL_Renderer* rend, bool chosen_territory_for_attack, int mouse_xPosition, int mouse_yPosition);
Uint32 checkClickedIndexColor(char* displayString);
char* map1_menu(center* hexagonsCenters);
char* map2_menu(center* hexagonsCenters);
char* map3_menu(center* hexagonsCenters);
char* map4_menu(center* hexagonsCenters);
char* map_memory(center* hexagonsCenters);

