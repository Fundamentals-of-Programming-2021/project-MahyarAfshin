#include"soldiers.h"

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
    if(numOfFrames_fromBeginig%60==0){
        for(int i=0; i<46; i++){
            if(hexagonCenters[i].no_end==false){
                if(hexagonCenters[i].is_used==true && hexagonCenters[i].numOfSoldiers<40 && hexagonCenters[i].color != 0x70c0c0c0){
                    hexagonCenters[i].numOfSoldiers+=hexagonCenters[i].soldierAddCoefficient;
                }
            }
            else{
                if(hexagonCenters[i].is_used==true && hexagonCenters[i].color != 0x70c0c0c0){
                    hexagonCenters[i].numOfSoldiers+=hexagonCenters[i].soldierAddCoefficient;
                }
            }
        }
    }
}

void addAnAttack(long long int totalNumOfAttacks, int clickedIndex,center* hexagonsCenters, int tempIndex){
    if(totalNumOfAttacks==1){
        attacks=malloc(sizeof(attack));
    }
    else{
        attacks=realloc(attacks,totalNumOfAttacks*sizeof(attack));
    }
    attacks[totalNumOfAttacks-1].attackerIndex=tempIndex;
    attacks[totalNumOfAttacks-1].defenderIndex=clickedIndex;
    attacks[totalNumOfAttacks-1].numOfSoldiers=hexagonsCenters[tempIndex].numOfSoldiers;
    attacks[totalNumOfAttacks-1].color=hexagonsCenters[tempIndex].color;
    attacks[totalNumOfAttacks-1].firstSoldier=malloc(attacks[totalNumOfAttacks-1].numOfSoldiers*sizeof(soldier));
    for(int i=0; i<attacks[totalNumOfAttacks-1].numOfSoldiers; i++){
        attacks[totalNumOfAttacks-1].firstSoldier[i].color=hexagonsCenters[tempIndex].color;
        attacks[totalNumOfAttacks-1].firstSoldier[i].x_coordinate=hexagonsCenters[tempIndex].x_coordinate;
        attacks[totalNumOfAttacks-1].firstSoldier[i].y_coordinate=hexagonsCenters[tempIndex].y_coordinate;
        attacks[totalNumOfAttacks-1].firstSoldier[i].is_active=true;
        attacks[totalNumOfAttacks-1].firstSoldier[i].speedCoefficient=1;
        attacks[totalNumOfAttacks-1].firstSoldier[i].is_potionActive=false;
    }
}

void attacksInProgress(center* hexagonsCenters, long long int totalNumOfAttacks){
    for(long long int i=0; i<totalNumOfAttacks; i++){
        if(attacks[i].defenderIndex != -1){
            int soldiersNum=attacks[i].numOfSoldiers;
            for(int j=0; j<soldiersNum; j++){
                double deltaX_attacker=attacks[i].firstSoldier[j].x_coordinate-hexagonsCenters[attacks[i].attackerIndex].x_coordinate;
                double deltaY_attacker=attacks[i].firstSoldier[j].y_coordinate-hexagonsCenters[attacks[i].attackerIndex].y_coordinate;
                double distance_attacker=sqrt(deltaX_attacker*deltaX_attacker+deltaY_attacker*deltaY_attacker);
                if(distance_attacker>=15){
                    double deltaX=attacks[i].firstSoldier[j].x_coordinate-hexagonsCenters[attacks[i].defenderIndex].x_coordinate;
                    double deltaY=attacks[i].firstSoldier[j].y_coordinate-hexagonsCenters[attacks[i].defenderIndex].y_coordinate;
                    double distance=sqrt(deltaX*deltaX+deltaY*deltaY);
                    attacks[i].firstSoldier[j].x_coordinate-=deltaX/distance*soldiersSpeed/FPS*attacks[i].firstSoldier[j].speedCoefficient;
                    attacks[i].firstSoldier[j].y_coordinate-=deltaY/distance*soldiersSpeed/FPS*attacks[i].firstSoldier[j].speedCoefficient;
                }
                else{
                    double deltaX=attacks[i].firstSoldier[j].x_coordinate-hexagonsCenters[attacks[i].defenderIndex].x_coordinate;
                    double deltaY=attacks[i].firstSoldier[j].y_coordinate-hexagonsCenters[attacks[i].defenderIndex].y_coordinate;
                    double distance=sqrt(deltaX*deltaX+deltaY*deltaY);
                    attacks[i].firstSoldier[j].x_coordinate-=deltaX/distance*soldiersSpeed/FPS*attacks[i].firstSoldier[j].speedCoefficient;
                    attacks[i].firstSoldier[j].y_coordinate-=deltaY/distance*soldiersSpeed/FPS*attacks[i].firstSoldier[j].speedCoefficient;
                    break;
                }
            }
        }
    }
}

void displaySoldiers(SDL_Renderer* rend, center* hexagonsCenters, long long int totalNumOfAttacks){
    for(long long int i=0; i<totalNumOfAttacks; i++){
        if(attacks[i].defenderIndex != -1){
            int soldiersNum=attacks[i].numOfSoldiers;
            for(int j=0; j<soldiersNum; j++){
                filledCircleColor(rend,attacks[i].firstSoldier[j].x_coordinate,attacks[i].firstSoldier[j].y_coordinate,5,attacks[i].firstSoldier[j].color+0x50000000);
            }
        }
    }
}

void deleteSoldier(int attackIndex, int soldierIndex, int soldiersNum){
    for(int count=soldierIndex; count<soldiersNum-1; count++){
        attacks[attackIndex].firstSoldier[count]=attacks[attackIndex].firstSoldier[count+1];
    }
    attacks[attackIndex].numOfSoldiers--;
    attacks[attackIndex].firstSoldier=realloc(attacks[attackIndex].firstSoldier,attacks[attackIndex].numOfSoldiers*sizeof(soldier));
}

void soldiersCollision(long long int totalNumOfAttacks){
    for(long long int i=0; i<totalNumOfAttacks; i++){
        if(attacks[i].defenderIndex != -1){
            int soldiersNum=attacks[i].numOfSoldiers;
            for(long long int j=i+1; j<totalNumOfAttacks; j++){
                if(attacks[j].defenderIndex != -1 && attacks[i].firstSoldier[0].color != attacks[j].firstSoldier[0].color){
                    int soldiersNum_checker=attacks[j].numOfSoldiers;
                    for(int k=0; k<soldiersNum; k++){
                        for(int l=0; l<soldiersNum_checker; l++){
                            double deltaX=attacks[i].firstSoldier[k].x_coordinate-attacks[j].firstSoldier[l].x_coordinate;
                            double deltaY=attacks[i].firstSoldier[k].y_coordinate-attacks[j].firstSoldier[l].y_coordinate;
                            double distance=sqrt(deltaY*deltaY+deltaX*deltaX);
                            if(distance<=10){
                                attacks[i].firstSoldier[k].is_active=false;
                                attacks[j].firstSoldier[l].is_active=false;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i=0; i<totalNumOfAttacks; i++){
        int index=0;
        for(int j=0; j<attacks[i].numOfSoldiers; j++){
            if(attacks[i].firstSoldier[j].is_active==true){
                attacks[i].firstSoldier[index]=attacks[i].firstSoldier[j];
                index++;
            }
        }
        attacks[i].numOfSoldiers=index;
        attacks[i].firstSoldier=realloc(attacks[i].firstSoldier,attacks[i].numOfSoldiers*sizeof(soldier));
    }
}

void soldiersCollisionWithBase(long long int totalNumOfAttacks, center* hexagonsCenters){
    for(long long int i=0; i<totalNumOfAttacks; i++){
        if(attacks[i].defenderIndex != -1){
            int soldiersNum=attacks[i].numOfSoldiers;
            for(int j=0; j<soldiersNum; j++){
                for(int k=0; k<46; k++){
                    if(attacks[i].firstSoldier[0].color != hexagonsCenters[k].color && attacks[i].defenderIndex==k){
                        Uint32 toChange_color=attacks[i].firstSoldier[0].color;
                        double deltaX=attacks[i].firstSoldier[j].x_coordinate-hexagonsCenters[k].x_coordinate;
                        double deltaY=attacks[i].firstSoldier[j].y_coordinate-hexagonsCenters[k].y_coordinate;
                        double distance=sqrt(deltaX*deltaX+deltaY*deltaY);
                        if(distance<=15){
                            attacks[i].firstSoldier[j].is_active=false;
                            hexagonsCenters[k].numOfSoldiers--;
                            if(hexagonsCenters[k].numOfSoldiers==-1){
                                hexagonsCenters[k].numOfSoldiers=1;
                                hexagonsCenters[k].color=attacks[i].color;
                                hexagonsCenters[k].centerColor=hexagonsCenters[k].color+0x8f000000;
                                
                            }
                        }
                    }
                    else if(attacks[i].firstSoldier[0].color == hexagonsCenters[k].color && attacks[i].defenderIndex==k){
                        Uint32 toChange_color=attacks[i].firstSoldier[0].color;
                        double deltaX=attacks[i].firstSoldier[j].x_coordinate-hexagonsCenters[k].x_coordinate;
                        double deltaY=attacks[i].firstSoldier[j].y_coordinate-hexagonsCenters[k].y_coordinate;
                        double distance=sqrt(deltaX*deltaX+deltaY*deltaY);
                        if(distance<=15){
                            attacks[i].firstSoldier[j].is_active=false;
                            hexagonsCenters[k].numOfSoldiers++;
                        }
                    }
                }
            }
        }
    }
    for(int i=0; i<totalNumOfAttacks; i++){
        int index=0;
        for(int j=0; j<attacks[i].numOfSoldiers; j++){
            if(attacks[i].firstSoldier[j].is_active==true){
                attacks[i].firstSoldier[index]=attacks[i].firstSoldier[j];
                index++;
            }
        }
        attacks[i].numOfSoldiers=index;
        attacks[i].firstSoldier=realloc(attacks[i].firstSoldier,attacks[i].numOfSoldiers*sizeof(soldier));
    }
}

long long int findFinishedAttack(long long int totalNumOfAttacks){
    for(int i=0; i<totalNumOfAttacks; i++){
        if(attacks[i].numOfSoldiers==0){
            return i;
        }
    }
    return -1;
}

void deleteFinishedAttacks(long long int* totalNumOfAttacks){
    int deletedIndex=findFinishedAttack(*totalNumOfAttacks);
    while(deletedIndex != -1){
        for(int count=deletedIndex; count<(*totalNumOfAttacks)-1; count++){
            attacks[count]=attacks[count+1];
        }
        (*totalNumOfAttacks)--;
        attacks=realloc(attacks,(*totalNumOfAttacks)*sizeof(attack));
        deletedIndex=findFinishedAttack(*totalNumOfAttacks);
    }
}

void updateTheSpeedCoefficient(long long int totalNumOfAttacks, center* hexagonsCenters){
    for(long long int i=0; i<totalNumOfAttacks; i++){
        for(int j=0; j<attacks[i].numOfSoldiers; j++){
            for(int k=0; k<46; k++){
                if(hexagonsCenters[k].color==attacks[i].color){
                    attacks[i].firstSoldier[j].speedCoefficient=hexagonsCenters[k].speedCoefficient;
                    break;
                }
            }
        }
    }
}

void update_isPotionActive(long long int totalNumOfAttacks, center* hexagonsCenters){
    for(long long int i=0; i<totalNumOfAttacks; i++){
        for(int j=0; j<attacks[i].numOfSoldiers; j++){
            for(int k=0; k<46; k++){
                if(hexagonsCenters[k].color==attacks[i].color){
                    attacks[i].firstSoldier[j].is_potionActive=hexagonsCenters[k].is_potionActive;
                    break;
                }
            }
        }
    }
}