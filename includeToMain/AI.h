#include "map.h"

typedef struct attack_check{
    int attackerIndex;
    int defenderIndex;
}attack_check;

typedef struct teams{
    int territories_index[46];
    int numOfTerritories;
    int attackTime;
    Uint32 color;
    attack_check bestAttack;
}teams;

teams* oponents=NULL;

int find_totalNumOfOponents(Uint32 playerColor){
    int totalNumOfOponents=0;
    for(int i=0; i<6; i++){
        if(colors[i].is_used==true && colors[i].color != playerColor){
            totalNumOfOponents++;
        }
    }
    return totalNumOfOponents;
} 

int makeOponentsArray(Uint32 playerColor){
    int totalNumOfOponents=find_totalNumOfOponents(playerColor);
    oponents=malloc(totalNumOfOponents*sizeof(teams));
    int count=0;
    for(int i=0; i<6; i++){
        if(colors[i].is_used==true && colors[i].color != playerColor){
            oponents[count].numOfTerritories=0;
            oponents[count].color=colors[i].color;
            count++;
        }
    }
    return totalNumOfOponents;
}

int makeTeams(Uint32 playerColor, center* hexagonsCenters){
    int totalNumOfOponents=makeOponentsArray(playerColor);
    for(int i=0; i<totalNumOfOponents; i++){
        for(int j=0; j<46; j++){
            if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color==oponents[i].color){
                oponents[i].numOfTerritories++;
                oponents[i].territories_index[oponents[i].numOfTerritories-1]=j;
            }
        }
    }
    return totalNumOfOponents;
}

int setAttackTime_forOponents(Uint32 playerColor, center* hexagonsCenters){
    int totalNumOfOponents=makeTeams(playerColor,hexagonsCenters);
    for(int i=0; i<totalNumOfOponents; i++){
        oponents[i].attackTime=rand()%4+2;
        printf("%d\n",oponents[i].attackTime);
    }
    return totalNumOfOponents;
}

int score_attacks(center* hexagonsCenters, int attackerIndex, int defenderIndex, long long int totalNumOfAttacks, int totalNumOfOponents){
    int score=0;
    double deltaX=hexagonsCenters[attackerIndex].x_coordinate-hexagonsCenters[defenderIndex].x_coordinate;
    double deltaY=hexagonsCenters[attackerIndex].y_coordinate-hexagonsCenters[defenderIndex].y_coordinate;
    double distance=sqrt(deltaY*deltaY+deltaX*deltaX);
    score-=5*distance;
    for(int i=0; i<totalNumOfAttacks; i++){
        if(attacks[i].attackerIndex==defenderIndex){
            score+=50;
        }
    }
    score-=100*hexagonsCenters[defenderIndex].numOfSoldiers;
    // for(int i=0; i<totalNumOfOponents; i++){
    //     for(int j=0; j<oponents[i].numOfTerritories; j++){
    //         if(oponents[i].territories_index[j]==attackerIndex){
    //             score-=10*oponents[i].numOfTerritories;
    //         }
    //     }
    // }
    score-=200*(hexagonsCenters[attackerIndex].numOfSoldiers-hexagonsCenters[defenderIndex].numOfSoldiers);
    return score;
}

void findTheBestAttack(int oponentIndex, center* hexagonsCenters, long long int totalNumOfAttacks, int totalNumOfOponents){
    int score=-100000;
    for(int i=0; i<46; i++){
        if(hexagonsCenters[i].is_used==true && hexagonsCenters[i].color != oponents[oponentIndex].color){
            for(int j=0; j<oponents[oponentIndex].numOfTerritories; j++){
                int temp_score=score_attacks(hexagonsCenters,oponents[oponentIndex].territories_index[j],i,totalNumOfAttacks,totalNumOfOponents);
                if(temp_score>score){
                    score=temp_score;
                    oponents[oponentIndex].bestAttack.attackerIndex=oponents[oponentIndex].territories_index[j];
                    oponents[oponentIndex].bestAttack.defenderIndex=i;
                }
            }

        }
    }
}

void AI_attack(center* hexagonsCenters, long long int* totalNumOfAttacks, int totalNumOfOponents, long long int numOfFrames_fromBeginig){
    for(int i=0; i<totalNumOfOponents; i++){
        if(numOfFrames_fromBeginig%(oponents[i].attackTime*240)==10){
            if(i==1){
                printf("we attacked on %lld\n", numOfFrames_fromBeginig);
            }
            findTheBestAttack(i,hexagonsCenters,*totalNumOfAttacks,totalNumOfOponents);
            (*totalNumOfAttacks)++;
            addAnAttack(*totalNumOfAttacks,oponents[i].bestAttack.attackerIndex,hexagonsCenters);
            attacks[*totalNumOfAttacks-1].defenderIndex=oponents[i].bestAttack.defenderIndex;
            hexagonsCenters[attacks[*totalNumOfAttacks-1].attackerIndex].numOfSoldiers=0;
        }
    }
}


// #include"map.h"

// typedef struct bestAttack{
//     int attackerIndex;
//     int defenderIndex;
//     int score;
// }bestAttack;

// typedef struct teams{
//     Uint32 color;
//     int territoryCentersIndex[46];
//     int numOfTerritories;
//     bestAttack attack;
// }teams;

// int totalNumOfTeams=0;

// teams players[10];

// void makeTeams(center* hexagonsCenters){
//     int counter=0;
//     for(int i=0; i<6; i++){
//         if(colors[i].is_used==true){
//             players[counter].color=colors[i].color;
//             players[counter].numOfTerritories=0;
//             counter++;
//         }
//     }
//     for(int i=0; i<counter; i++){
//         for(int j=0; j<46; j++){
//             if(hexagonsCenters[j].color==players[i].color){
//                 players[i].numOfTerritories++;
//             }
//         }
//         int tempCounter=0;
//         for(int j=0; j<46; j++){
//             if(hexagonsCenters[j].color==players[i].color){
//                 players[i].territoryCentersIndex[tempCounter]=j;
//                 tempCounter++;
//             }
//         }
//     }
//     totalNumOfTeams=counter;
// }

// int scoring_attacks(center* hexagonsCenters, int attackerIndex, int defenderIndex, long long int totalNumOfAttacks){
//     //calculating the maximum distance possible
//     double max_deltaX=hexagonsCenters[6].x_coordinate-hexagonsCenters[39].x_coordinate;
//     double max_deltaY=hexagonsCenters[6].y_coordinate-hexagonsCenters[39].y_coordinate;
//     double max_distance=sqrt(max_deltaX*max_deltaX+max_deltaY*max_deltaY);

//     //calculate the maximum diference in soldiers between two territories
//     int max_diference=0;
//     for(int i=0; i<46; i++){
//         for(int j=i+1; j<46; j++){
//             if(hexagonsCenters[i].is_used==true && hexagonsCenters[j].is_used==true && hexagonsCenters[i].color != hexagonsCenters[j].color && hexagonsCenters[i].color != 0x70c0c0c0){
//                 int temp=hexagonsCenters[i].numOfSoldiers-hexagonsCenters[j].numOfSoldiers;
//                 if(temp>max_diference){
//                     max_diference=temp;
//                 }
//             }
//         }
//     }

//     //calculate the maximum teams territory
//     int max_numOfTerritories=0;
//     for(int i=0; i<totalNumOfTeams; i++){
//         if(players[i].numOfTerritories>max_numOfTerritories){
//             max_numOfTerritories=players[i].numOfTerritories;
//         }
//     }

//     int score=0;

//     double deltaX=hexagonsCenters[attackerIndex].x_coordinate-hexagonsCenters[defenderIndex].x_coordinate;
//     double deltaY=hexagonsCenters[attackerIndex].y_coordinate-hexagonsCenters[defenderIndex].y_coordinate;
//     double distance=sqrt(deltaX*deltaX+deltaY*deltaY);
//     score+=max_distance/distance;
//     int soldiersNum_diference=hexagonsCenters[attackerIndex].numOfSoldiers-hexagonsCenters[defenderIndex].numOfSoldiers;
//     if(soldiersNum_diference>0){
//         score+=max_diference/soldiersNum_diference;
//     }

//     for(int i=0; i<totalNumOfAttacks; i++){
//         if(attacks[i].numOfSoldiers != 0 && attacks[i].attackerIndex==defenderIndex){
//             score+=100;
//         }
//     }

//     for(int i=0; i<totalNumOfTeams; i++){
//         for(int j=0; j<players[i].numOfTerritories; j++){
//             if(players[i].territoryCentersIndex[j]==defenderIndex){
//                 score+=max_numOfTerritories/players[i].numOfTerritories;
//             }
//         }
//     }

//     return score;
// }

// void findTheBestAttackForEachOponent(center* hexagonsCenters, char* displayString, long long int totalNumOfAttacks){
//     Uint32 playerColor=checkClickedIndexColor(displayString);
//     for(int i=0; i<totalNumOfTeams; i++){
//         if(players[i].color != playerColor){
//             players[i].attack.score=0;
//             for(int j=0; j<players[i].numOfTerritories; j++){
//                 for(int k=0; k<46; k++){
//                     if(hexagonsCenters[k].is_used==true && hexagonsCenters[k].color != players[i].color){
//                         int temp=scoring_attacks(hexagonsCenters,players[i].territoryCentersIndex[j],k,totalNumOfAttacks);
//                         if(temp>players[i].attack.score){
//                             players[i].attack.score=temp;
//                             players[i].attack.attackerIndex=players[i].territoryCentersIndex[j];
//                             players[i].attack.defenderIndex=k;
//                         }
//                     }
//                 }
//             }
//         }
//     }   
// }

// void AI_attack(center* hexagonsCenters, char* displayString, long long int* totalNumOfAttacks, long long int numOfFrames_fromBegining){
//     Uint32 playerColor=checkClickedIndexColor(displayString);
//     findTheBestAttackForEachOponent(hexagonsCenters,displayString,*totalNumOfAttacks);
//     if(numOfFrames_fromBegining%180==100){
//         int index=rand()%totalNumOfTeams;
//         (*totalNumOfAttacks)++;
//         addAnAttack(*totalNumOfAttacks,players[index].attack.attackerIndex,hexagonsCenters);
//         attacks[*totalNumOfAttacks-1].defenderIndex=players[index].attack.defenderIndex;
//         hexagonsCenters[attacks[*totalNumOfAttacks-1].attackerIndex].numOfSoldiers=0;
//     }
// }