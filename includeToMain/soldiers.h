#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<time.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>

const int FPS=60;
const int soldiersSpeed=50;

typedef struct soldier{
    Uint32 color;
    double x_coordinate;
    double y_coordinate;
    bool awayOfTeritory;
    struct soldier* next;
}soldier;

typedef struct center{
    double x_coordinate;
    double y_coordinate;
    Uint32 color;
    bool is_used;
    int numOfSoldiers;
    soldier* firstSoldier;
}center;

typedef struct attack{
    int attackerIndex;
    int defenderIndex;
    bool is_soldiersLinkedList_made;
    struct attack* next;
}attack;

attack* attacks=NULL;

void soldiers_beginigOfTheGame(center* hexagonCenters){
    srand(time(0));
    for(int i=0; i<46; i++){
        if(hexagonCenters[i].is_used==true){
            hexagonCenters[i].numOfSoldiers=8+rand()%8;
            hexagonCenters[i].firstSoldier=NULL;
        }
    }
}

//bellow function will add a soldier to each hexagon every 2 seconds until it reaches 40 soldiers
void soldiersAddingByTime(center* hexagonCenters, long long int numOfFrames_fromBeginig){
    if(numOfFrames_fromBeginig%120==0){
        for(int i=0; i<46; i++){
            if(hexagonCenters[i].is_used==true && hexagonCenters[i].numOfSoldiers<40 && hexagonCenters[i].color != 0x70c0c0c0){
                hexagonCenters[i].numOfSoldiers++;
            }
        }
    }
}

void addAnAttack_atTail(){
    attack* shouldBeAdded=malloc(sizeof(attack));
    attack* temp=attacks;
    if(temp == NULL){
        attacks=shouldBeAdded;
        shouldBeAdded->is_soldiersLinkedList_made=false;
        shouldBeAdded->next=NULL;
        return;
    }
    while(temp->next != NULL){
        temp=temp->next;
    }
    temp->next=shouldBeAdded;
    shouldBeAdded->is_soldiersLinkedList_made=false;
    shouldBeAdded->next=NULL;
}

attack* accessToTheEndOfAttacksLinkedList(){
    attack* temp=attacks;
    while(temp->next != NULL){
        temp=temp->next;
    }
    return temp;
}

void makingSoldiersLinkedList(center* hexagonsCenters){
    attack* temp=attacks;
    while(temp != NULL){
        if(temp->is_soldiersLinkedList_made==false && temp->defenderIndex != -1){
            hexagonsCenters[temp->attackerIndex].firstSoldier=malloc(sizeof(soldier));
            hexagonsCenters[temp->attackerIndex].firstSoldier->color=hexagonsCenters[temp->attackerIndex].color;
            hexagonsCenters[temp->attackerIndex].firstSoldier->x_coordinate=hexagonsCenters[temp->attackerIndex].x_coordinate;
            hexagonsCenters[temp->attackerIndex].firstSoldier->y_coordinate=hexagonsCenters[temp->attackerIndex].y_coordinate;
            hexagonsCenters[temp->attackerIndex].firstSoldier->awayOfTeritory=false;
            hexagonsCenters[temp->attackerIndex].firstSoldier->next=NULL;
            for(int i=0; i<hexagonsCenters[temp->attackerIndex].numOfSoldiers-1; i++){
                soldier* tmp=hexagonsCenters[temp->attackerIndex].firstSoldier;
                while(tmp->next != NULL){
                    tmp=tmp->next;
                }
                tmp->next=malloc(sizeof(soldier));
                tmp->next->color=hexagonsCenters[temp->attackerIndex].color;
                tmp->next->x_coordinate=hexagonsCenters[temp->attackerIndex].x_coordinate;
                tmp->next->y_coordinate=hexagonsCenters[temp->attackerIndex].y_coordinate;
                tmp->next->awayOfTeritory=false;
                tmp->next->next=NULL;
            }
            temp->is_soldiersLinkedList_made=true;
        }
        temp=temp->next;
    }
}

void attacksInProgress(center* hexagonsCenters){
    attack* temp=attacks;
    while(temp != NULL){
        if(temp->is_soldiersLinkedList_made==true){
            soldier* tmp=hexagonsCenters[temp->attackerIndex].firstSoldier;
            while(tmp!=NULL){
                double deltaX_attacker=hexagonsCenters[temp->attackerIndex].x_coordinate-tmp->x_coordinate;
                double deltaY_attacker=hexagonsCenters[temp->attackerIndex].y_coordinate-tmp->y_coordinate;
                double distance_attacker=sqrt(deltaX_attacker*deltaX_attacker+deltaY_attacker*deltaY_attacker);
                if(distance_attacker > 15){
                    double deltaX=hexagonsCenters[temp->defenderIndex].x_coordinate-tmp->x_coordinate;
                    double deltaY=hexagonsCenters[temp->defenderIndex].y_coordinate-tmp->y_coordinate;
                    double distance=sqrt(deltaX*deltaX+deltaY*deltaY);
                    tmp->awayOfTeritory=true;
                    tmp->x_coordinate+=deltaX/distance*soldiersSpeed/FPS;
                    tmp->y_coordinate+=deltaY/distance*soldiersSpeed/FPS;
                    tmp=tmp->next;
                }
                else{
                    break;
                }
            }
            if(tmp != NULL){
                double deltaX=hexagonsCenters[temp->defenderIndex].x_coordinate-tmp->x_coordinate;
                double deltaY=hexagonsCenters[temp->defenderIndex].y_coordinate-tmp->y_coordinate;
                double distance=sqrt(deltaX*deltaX+deltaY*deltaY);
                tmp->x_coordinate+=deltaX/distance*soldiersSpeed/FPS;
                tmp->y_coordinate+=deltaY/distance*soldiersSpeed/FPS;
            }
        }
        temp=temp->next;
    }
}

void displaySoldiers(SDL_Renderer* rend, center* hexagonsCenters){
    attack* temp=attacks;
    while(temp != NULL){
        if(temp->is_soldiersLinkedList_made==true){
            int insideTeritory_counter=0;
            soldier* tmp=hexagonsCenters[temp->attackerIndex].firstSoldier;
            while(tmp!=NULL){
                filledCircleColor(rend,tmp->x_coordinate,tmp->y_coordinate,5,tmp->color);
                if(tmp->awayOfTeritory==false){
                    insideTeritory_counter++;
                }
                tmp=tmp->next;
            }
            hexagonsCenters[temp->attackerIndex].numOfSoldiers=insideTeritory_counter;
        }
        temp=temp->next;
    }
}

//this function returns true if the clickedIndex is already in attack and false if not
bool checkAttacks_fromStartPoint(int clickedIndex){
    attack* temp=attacks;
    while(temp != NULL){
        if(temp->attackerIndex==clickedIndex){
            return true;
        }
        temp=temp->next;
    }
    return false;
}