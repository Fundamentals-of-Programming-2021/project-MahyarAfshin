#include<stdio.h>
#include "game.h"

int mouse_xPosition;
int mouse_yPosition;
 
int main(){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Window* gameWindow=SDL_CreateWindow("state.io",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowWidth,windowHeight,0);
    SDL_Renderer* rend=SDL_CreateRenderer(gameWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(rend,0xff,0xff,0xff,0xff);
    SDL_RenderClear(rend);
    center* hexagonsCenters=createMapTemplate(rend);
    char* displayString=generatingRandomMap(5,20,hexagonsCenters);
    Uint32 playerColor=checkClickedIndexColor(displayString);
    soldiers_beginigOfTheGame(hexagonsCenters);
    int totalNumOfOponents=0;
    totalNumOfOponents=setAttackTime_forOponents(playerColor,hexagonsCenters,totalNumOfOponents);
    long long int numOfFrames_fromBegining=0;
    int close=0;
    SDL_Event event;
    bool chosen_territory_for_attack=false;
    long long int totalNumOfAttacks=0;
    int tempIndex=-1;
    while(close != 1){
        SDL_SetRenderDrawColor(rend,0xff,0xff,0xff,0xff);
        SDL_RenderClear(rend);
        createMapTemplate(rend);
        putTheMapOnTheRenderer(hexagonsCenters,rend,displayString);
        SDL_GetMouseState(&mouse_xPosition,&mouse_yPosition);
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                close=1;
            }
            else if(event.type==SDL_MOUSEBUTTONDOWN){
                int clickedIndex=getMousePosition(hexagonsCenters,rend,chosen_territory_for_attack,mouse_xPosition,mouse_yPosition);
                if(chosen_territory_for_attack==false && clickedIndex != -1 && hexagonsCenters[clickedIndex].color==playerColor){
                    tempIndex=clickedIndex;
                    chosen_territory_for_attack=true;
                }
                else if(clickedIndex != -1 && chosen_territory_for_attack==true ){
                    if(clickedIndex != tempIndex){
                        totalNumOfAttacks++;
                        addAnAttack(totalNumOfAttacks,clickedIndex,hexagonsCenters,tempIndex);
                        hexagonsCenters[attacks[totalNumOfAttacks-1].attackerIndex].numOfSoldiers=0;
                    }
                    chosen_territory_for_attack=false;  
                }
            }
        }
        getMousePosition(hexagonsCenters,rend,chosen_territory_for_attack,mouse_xPosition,mouse_yPosition);
        AI_attack(hexagonsCenters,&totalNumOfAttacks,totalNumOfOponents,numOfFrames_fromBegining);
        attacksInProgress(hexagonsCenters,totalNumOfAttacks);
        soldiersCollision(totalNumOfAttacks);
        soldiersCollisionWithBase(totalNumOfAttacks,hexagonsCenters);
        deleteFinishedAttacks(&totalNumOfAttacks);
        displaySoldiers(rend,hexagonsCenters,totalNumOfAttacks);
        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);
        soldiersAddingByTime(hexagonsCenters,numOfFrames_fromBegining);
        numOfFrames_fromBegining++;
        // int state=check_forWinner(hexagonsCenters,playerColor);
        // if(state != 0){
        //     close=winnerPage(state,rend,);

        // }
        totalNumOfOponents=setAttackTime_forOponents(playerColor,hexagonsCenters,totalNumOfOponents);
    }
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();
    return 0;
}