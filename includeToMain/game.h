#include<stdio.h>
#include"potion.h"

int mouse_xPosition;
int mouse_yPosition;

int startGame(int mapNum, SDL_Renderer* rend){
    SDL_SetRenderDrawColor(rend,0xff,0xff,0xff,0xff);
    SDL_RenderClear(rend);
    center* hexagonsCenters=createMapTemplate(rend);
    char* displayString;
    switch(mapNum){
        case 0:
            displayString=map_memory(hexagonsCenters);
            break;
        case 1:
            displayString=map1_menu(hexagonsCenters);
            break;
        case 2:
            displayString=map2_menu(hexagonsCenters);
            break;
        case 3:
            displayString=map3_menu(hexagonsCenters);
            break;
        case 4:
            displayString=map4_menu(hexagonsCenters);
            break;
        case 5:
            displayString=generatingRandomMap(5,30,hexagonsCenters);
            break;
    }
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
    initializePotions();
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
        printf("1\n");
        fflush(stdout);
        AI_attack(hexagonsCenters,&totalNumOfAttacks,totalNumOfOponents,numOfFrames_fromBegining);
        printf("2\n");
        fflush(stdout);
        attacksInProgress(hexagonsCenters,totalNumOfAttacks);
        printf("3\n");
        fflush(stdout);
        soldiersCollision(totalNumOfAttacks);
        printf("4\n");
        fflush(stdout);
        soldiersCollisionWithBase(totalNumOfAttacks,hexagonsCenters);
        printf("5\n");
        fflush(stdout);
        deleteFinishedAttacks(&totalNumOfAttacks);
        printf("6\n");
        fflush(stdout);
        displaySoldiers(rend,hexagonsCenters,totalNumOfAttacks);
        printf("7\n");
        fflush(stdout);
        deployPotion(numOfFrames_fromBegining,hexagonsCenters);
        printf("8\n");
        fflush(stdout);
        displayPotions(rend,numOfFrames_fromBegining);
        printf("9\n");
        fflush(stdout);
        soldiersCollision_withPotion(totalNumOfAttacks,totalNumOfOponents,numOfFrames_fromBegining);
        potionsLogic(numOfFrames_fromBegining,hexagonsCenters);
        updateTheSpeedCoefficient(totalNumOfAttacks,hexagonsCenters);
        deleteOponents(playerColor,hexagonsCenters);
        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);
        soldiersAddingByTime(hexagonsCenters,numOfFrames_fromBegining);
        numOfFrames_fromBegining++;
        int state=check_forWinner(hexagonsCenters,playerColor);
        if(state != 0){
            long long int score=score_calc(hexagonsCenters);
            if(state==-1){
                score*=-1;
            }
            users[numOfUsers-1].score=+score;
            updateUsers();
            close=winnerPage(state,rend,score);
        }
        totalNumOfOponents=setAttackTime_forOponents(playerColor,hexagonsCenters,totalNumOfOponents);
    }
    return close;
}