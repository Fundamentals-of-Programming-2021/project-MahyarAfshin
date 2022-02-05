#include"map.h"

typedef struct bestAttack{
    int attackerIndex;
    int defenderIndex;
    int score;
}bestAttack;

typedef struct teams{
    Uint32 color;
    int territoryCentersIndex[46];
    int numOfTerritories;
    bestAttack attack;
}teams;

int totalNumOfTeams=0;

teams players[10];

void makeTeams(center* hexagonsCenters){
    int counter=0;
    for(int i=0; i<6; i++){
        if(colors[i].is_used==true){
            players[counter].color=colors[i].color;
            players[counter].numOfTerritories=0;
            counter++;
        }
    }
    for(int i=0; i<counter; i++){
        for(int j=0; j<46; j++){
            if(hexagonsCenters[j].color==players[i].color){
                players[i].numOfTerritories++;
            }
        }
        int tempCounter=0;
        for(int j=0; j<46; j++){
            if(hexagonsCenters[j].color==players[i].color){
                players[i].territoryCentersIndex[tempCounter]=j;
                tempCounter++;
            }
        }
    }
    totalNumOfTeams=counter;
}

int scoring_attacks(center* hexagonsCenters, int attackerIndex, int defenderIndex, long long int totalNumOfAttacks){
    //calculating the maximum distance possible
    double max_deltaX=hexagonsCenters[6].x_coordinate-hexagonsCenters[39].x_coordinate;
    double max_deltaY=hexagonsCenters[6].y_coordinate-hexagonsCenters[39].y_coordinate;
    double max_distance=sqrt(max_deltaX*max_deltaX+max_deltaY*max_deltaY);

    //calculate the maximum diference in soldiers between two territories
    int max_diference=0;
    for(int i=0; i<46; i++){
        for(int j=i+1; j<46; j++){
            if(hexagonsCenters[i].is_used==true && hexagonsCenters[j].is_used==true && hexagonsCenters[i].color != hexagonsCenters[j].color && hexagonsCenters[i].color != 0x70c0c0c0){
                int temp=hexagonsCenters[i].numOfSoldiers-hexagonsCenters[j].numOfSoldiers;
                if(temp>max_diference){
                    max_diference=temp;
                }
            }
        }
    }

    //calculate the maximum teams territory
    int max_numOfTerritories=0;
    for(int i=0; i<totalNumOfTeams; i++){
        if(players[i].numOfTerritories>max_numOfTerritories){
            max_numOfTerritories=players[i].numOfTerritories;
        }
    }

    int score=0;

    double deltaX=hexagonsCenters[attackerIndex].x_coordinate-hexagonsCenters[defenderIndex].x_coordinate;
    double deltaY=hexagonsCenters[attackerIndex].y_coordinate-hexagonsCenters[defenderIndex].y_coordinate;
    double distance=sqrt(deltaX*deltaX+deltaY*deltaY);
    score+=max_distance/distance;
    int soldiersNum_diference=hexagonsCenters[attackerIndex].numOfSoldiers-hexagonsCenters[defenderIndex].numOfSoldiers;
    if(soldiersNum_diference>0){
        score+=max_diference/soldiersNum_diference;
    }

    for(int i=0; i<totalNumOfAttacks; i++){
        if(attacks[i].numOfSoldiers != 0 && attacks[i].attackerIndex==defenderIndex){
            score+=100;
        }
    }

    for(int i=0; i<totalNumOfTeams; i++){
        for(int j=0; j<players[i].numOfTerritories; j++){
            if(players[i].territoryCentersIndex[j]==defenderIndex){
                score+=max_numOfTerritories/players[i].numOfTerritories;
            }
        }
    }

    return score;
}

void findTheBestAttackForEachOponent(center* hexagonsCenters, char* displayString, long long int totalNumOfAttacks){
    Uint32 playerColor=checkClickedIndexColor(displayString);
    for(int i=0; i<totalNumOfTeams; i++){
        if(players[i].color != playerColor){
            players[i].attack.score=0;
            for(int j=0; j<players[i].numOfTerritories; j++){
                for(int k=0; k<46; k++){
                    if(hexagonsCenters[k].is_used==true && hexagonsCenters[k].color != players[i].color){
                        int temp=scoring_attacks(hexagonsCenters,players[i].territoryCentersIndex[j],k,totalNumOfAttacks);
                        if(temp>players[i].attack.score){
                            players[i].attack.score=temp;
                            players[i].attack.attackerIndex=players[i].territoryCentersIndex[j];
                            players[i].attack.defenderIndex=k;
                        }
                    }
                }
            }
        }
    }   
}

void AI_attack(center* hexagonsCenters, char* displayString, long long int totalNumOfAttacks, long long int numOfFrames_fromBegining){
    Uint32 playerColor=checkClickedIndexColor(displayString);
    findTheBestAttackForEachOponent(hexagonsCenters,displayString,totalNumOfAttacks);
    if(numOfFrames_fromBegining%600==500){
        int index=rand()%totalNumOfTeams;
        printf("%d   %d\n",players[index].attack.attackerIndex,players[index].attack.defenderIndex);
        addAnAttack(totalNumOfAttacks,players[index].attack.attackerIndex,hexagonsCenters);
        attacks[totalNumOfAttacks-1].defenderIndex=players[index].attack.defenderIndex;
        hexagonsCenters[attacks[totalNumOfAttacks-1].attackerIndex].numOfSoldiers=0;
    }
}


