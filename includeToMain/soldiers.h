#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<time.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>

const int FPS=60;
const int soldiersSpeed=75;

typedef struct soldier{
    Uint32 color;
    double x_coordinate;
    double y_coordinate;
    struct soldier* next;
}soldier;

typedef struct center{
    double x_coordinate;
    double y_coordinate;
    Uint32 color;
    bool is_used;
    int numOfSoldiers;
}center;

typedef struct attack{
    int attackerIndex;
    int defenderIndex;
    bool is_soldiersLinkedList_made;
    bool is_finished;
    int numOfSoldiers;
    bool soldiersCounted;
    soldier* firstSoldier;
    struct attack* next;
}attack;

attack* attacks=NULL;

void soldiers_beginigOfTheGame(center* hexagonCenters){
    srand(time(0));
    for(int i=0; i<46; i++){
        if(hexagonCenters[i].is_used==true){
            hexagonCenters[i].numOfSoldiers=8+rand()%8;
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
        shouldBeAdded->is_finished=false;
        shouldBeAdded->soldiersCounted=false;
        shouldBeAdded->firstSoldier=NULL;
        shouldBeAdded->next=NULL;
        return;
    }
    while(temp->next != NULL){
        temp=temp->next;
    }
    temp->next=shouldBeAdded;
    shouldBeAdded->is_soldiersLinkedList_made=false;
    shouldBeAdded->firstSoldier=NULL;
    shouldBeAdded->is_finished=false;
    shouldBeAdded->soldiersCounted=false;
    shouldBeAdded->next=NULL;
}

attack* accessToTheEndOfAttacksLinkedList(){
    attack* temp=attacks;
    while(temp->next != NULL){
        temp=temp->next;
    }
    return temp;
}

void attacksInProgress(center* hexagonsCenters){
    attack* temp=attacks;
    while(temp != NULL){
        if(temp->numOfSoldiers==0){
            temp->is_finished=true;
        }
        else{
            if(temp->is_soldiersLinkedList_made==false && temp->defenderIndex != -1 && temp->is_finished==false){
                temp->firstSoldier=malloc(sizeof(soldier));
                //temp->firstSoldier=malloc(sizeof(soldier));
                temp->firstSoldier->color=hexagonsCenters[temp->attackerIndex].color;
                temp->firstSoldier->x_coordinate=hexagonsCenters[temp->attackerIndex].x_coordinate;
                temp->firstSoldier->y_coordinate=hexagonsCenters[temp->attackerIndex].y_coordinate;
                temp->firstSoldier->next=NULL;
                soldier* tmp=temp->firstSoldier;
                for(int i=0; i<temp->numOfSoldiers-1; i++){
                    soldier* new_toAdd=malloc(sizeof(soldier));
                    new_toAdd->color=hexagonsCenters[temp->attackerIndex].color;
                    new_toAdd->x_coordinate=hexagonsCenters[temp->attackerIndex].x_coordinate;
                    new_toAdd->y_coordinate=hexagonsCenters[temp->attackerIndex].y_coordinate;
                    new_toAdd->next=NULL;
                    tmp->next=new_toAdd;
                    tmp=tmp->next;
                }
                temp->is_soldiersLinkedList_made=true;
            }
            else if(temp->is_soldiersLinkedList_made==true && temp->is_finished==false){
                soldier* tmp=temp->firstSoldier;
                double deltaX=hexagonsCenters[temp->defenderIndex].x_coordinate-tmp->x_coordinate;
                double deltaY=hexagonsCenters[temp->defenderIndex].y_coordinate-tmp->y_coordinate;
                double distance=sqrt(deltaX*deltaX+deltaY*deltaY);
                tmp->x_coordinate+=deltaX/distance*soldiersSpeed/FPS;
                tmp->y_coordinate+=deltaY/distance*soldiersSpeed/FPS;
                double deltaX_attacker=hexagonsCenters[temp->attackerIndex].x_coordinate-tmp->x_coordinate;
                double deltaY_attacker=hexagonsCenters[temp->attackerIndex].y_coordinate-tmp->y_coordinate;
                double distance_attacker=sqrt(deltaX_attacker*deltaX_attacker+deltaY_attacker*deltaY_attacker);
                tmp=tmp->next;
                while(tmp != NULL && distance_attacker > 15){
                    deltaX=hexagonsCenters[temp->defenderIndex].x_coordinate-tmp->x_coordinate;
                    deltaY=hexagonsCenters[temp->defenderIndex].y_coordinate-tmp->y_coordinate;
                    distance=sqrt(deltaX*deltaX+deltaY*deltaY);
                    tmp->x_coordinate+=deltaX/distance*soldiersSpeed/FPS;
                    tmp->y_coordinate+=deltaY/distance*soldiersSpeed/FPS;
                    deltaX_attacker=hexagonsCenters[temp->attackerIndex].x_coordinate-tmp->x_coordinate;
                    deltaY_attacker=hexagonsCenters[temp->attackerIndex].y_coordinate-tmp->y_coordinate;
                    distance_attacker=sqrt(deltaX_attacker*deltaX_attacker+deltaY_attacker*deltaY_attacker);
                    tmp=tmp->next;
                }
                
            }
        }
        if(temp->is_soldiersLinkedList_made==true && temp->is_finished==false && temp->soldiersCounted==false){
            temp->soldiersCounted=true;
            hexagonsCenters[temp->attackerIndex].numOfSoldiers-=temp->numOfSoldiers;
        }
        temp=temp->next; 
    }
}

void displaySoldiers(SDL_Renderer* rend, center* hexagonsCenters){
    attack* temp=attacks;
    while(temp != NULL){
        if(temp->is_soldiersLinkedList_made==true){
            soldier* tmp=temp->firstSoldier;
            while(tmp!=NULL){
                filledCircleColor(rend,tmp->x_coordinate,tmp->y_coordinate,5,tmp->color+0x20000000);
                tmp=tmp->next;
            }
        }
        temp=temp->next;
    }
}

void deletingSoldiers_fromSoldiersLinkedList(soldier* toDelete, attack* thisAttack){
    soldier* temp=thisAttack->firstSoldier;
    soldier* returned;
    if(toDelete==temp){
        thisAttack->firstSoldier=temp->next;
        returned  = toDelete->next;
        free(toDelete);
        toDelete = returned;
        return;
    }
    while(temp != NULL){
        if(toDelete==temp->next){
            temp->next=temp->next->next;
            returned=toDelete->next;
            free(toDelete);
            toDelete=returned;
            return;
        }
        temp=temp->next;
    }
}

void soldiers_collision(center* hexagonsCenters){
    attack* temp=attacks;
    while(temp != NULL){
        if(temp->next != NULL && temp->is_finished==false){
            attack* check=temp->next;
            while(check != NULL){
                if(check->is_finished==false){
                    soldier* tmp1=temp->firstSoldier;
                    while(tmp1 != NULL){
                        soldier* tmp2=check->firstSoldier;
                        while(tmp2 != NULL){
                            if(tmp1->color != tmp2->color){
                                double deltaX=tmp1->x_coordinate-tmp2->x_coordinate;
                                double deltaY=tmp1->y_coordinate-tmp2->y_coordinate;
                                double distance=sqrt(deltaX*deltaX+deltaY*deltaY);
                                if(distance<=10){
                                    deletingSoldiers_fromSoldiersLinkedList(tmp1,temp);
                                    deletingSoldiers_fromSoldiersLinkedList(tmp2,check);
                                }
                            }
                            tmp2=tmp2->next;
                        }
                        tmp1=tmp1->next;
                    }
                }
                check=check->next;
            }
        }
        temp=temp->next;
    }
}


void finishAttack(){
    attack* temp=attacks;
    while(temp != NULL){
        if(temp->is_soldiersLinkedList_made==true && temp->firstSoldier == NULL){
            temp->is_finished=true;
        }
        temp=temp->next;
    }
}

void soldiersCollision_withBase(center* hexagonsCenters){
    attack* temp=attacks;
    while(temp != NULL){
        if(temp->is_finished==false){
            soldier* tmp=temp->firstSoldier;
            while(tmp != NULL){
                for(int i=0; i<46; i++){
                    if(i==temp->defenderIndex){
                        double deltaX=tmp->x_coordinate-hexagonsCenters[i].x_coordinate;
                        double deltaY=tmp->y_coordinate-hexagonsCenters[i].y_coordinate;
                        double distance=sqrt(deltaX*deltaX+deltaY*deltaY);
                        if(tmp->color != hexagonsCenters[i].color && hexagonsCenters[i].is_used==true){
                            if(distance<=15){
                                Uint32 color=tmp->color;
                                deletingSoldiers_fromSoldiersLinkedList(tmp,temp);
                                hexagonsCenters[i].numOfSoldiers--;
                                if(hexagonsCenters[i].numOfSoldiers==-1){
                                    hexagonsCenters[i].numOfSoldiers=1;
                                    hexagonsCenters[i].color=color;
                                }
                            }
                        }
                        else if(temp->attackerIndex != i && hexagonsCenters[i].is_used==true){
                            if(distance<=15){
                                deletingSoldiers_fromSoldiersLinkedList(tmp,temp);
                                hexagonsCenters[i].numOfSoldiers++;
                            }
                        }
                    }
                }
                tmp=tmp->next;
            }
        }
        temp=temp->next;
    }
}

attack* checkForFinishedAttack(){
    attack* temp=attacks;
    while(temp != NULL){
        if(temp->is_finished==true){
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}

void deleteFinishedAttacks(){
    attack* toDelete=checkForFinishedAttack();
    while(toDelete != NULL){
        attack* temp=attacks;
        if(temp==toDelete){
            attacks=temp->next;
            free(toDelete);
        }
        else{
            while(temp != NULL){
                if(temp->next==toDelete){
                    temp->next=temp->next->next;
                    free(toDelete);
                }
                temp=temp->next;
            }
        }
        toDelete=checkForFinishedAttack();
    }
}