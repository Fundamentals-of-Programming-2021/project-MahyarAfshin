#pragma once

#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#include<string.h>
#include "game.h"

extern SDL_Rect dest;
extern SDL_Rect nameDest;
extern SDL_Rect secondDest;
extern SDL_Rect thirdDest;
extern SDL_Rect fourthDest;
extern SDL_Rect fifthDest;
extern SDL_Rect firstClick;
extern SDL_Rect secondClick;
extern SDL_Rect thirdClick;
extern SDL_Rect map1_dest;
extern SDL_Rect map2_dest;
extern SDL_Rect map3_dest;
extern SDL_Rect map4_dest;
extern SDL_Rect randomMap_dest;
extern SDL_Rect memoryMap_dest;
extern SDL_Rect user1_dest;
extern SDL_Rect user2_dest;
extern SDL_Rect user3_dest;
extern SDL_Rect user4_dest;
extern SDL_Rect user5_dest;
extern SDL_Rect user6_dest;
extern SDL_Rect user7_dest;
extern SDL_Rect user8_dest;
extern SDL_Rect randomMap_dest1;
extern SDL_Rect randomMap_dest2;
extern SDL_Rect randomMap_dest3;
extern SDL_Rect randomMap_dest4;

bool check_inTheBox(int box_upperLeftCorner_x, int box_upperLeftCorner_y);
void typeTheEnteredName(char name[51], SDL_Rect secondDest, SDL_Color color, SDL_Renderer* rend, TTF_Font* enteredName_font);
int display_scoreBoard(SDL_Renderer* rend, SDL_Texture* thirdTex, SDL_Texture* fourthTex, SDL_Texture* fifthTex, SDL_Texture* tex, long long int userIndex);
int thirdPageMenu(SDL_Renderer* rend, SDL_Texture* thirdTex, SDL_Texture* fourthTex, SDL_Texture* fifthTex, SDL_Texture* tex, long long int userIndex);
int nextPageMenu(SDL_Renderer* rend, SDL_Texture* thirdTex, SDL_Texture* fourthTex, SDL_Texture* fifthTex, SDL_Texture* tex, long long int userIndex);
int randomMap_menu(SDL_Renderer* rend, SDL_Texture* thirdTex, SDL_Texture* fourthTex, SDL_Texture* fifthTex, SDL_Texture* tex, long long int userIndex);
void typeNumbers(char num1[20], char num2[20], SDL_Renderer* rend, SDL_Color color, TTF_Font* enteredName_font);