#include"AI.h"

typedef struct potion{
    Uint32 color;
    int durationToWait;
    int durationToBeEnabled;
    int x_position;
    int y_position;
    bool is_deployed;
    long long int frameDeployed;
    long long int frameEnabled;
    bool is_enabled;
    Uint32 teamColor;
}potion;

potion* potions=NULL;
FILE* file;
FILE* fuckYou;

void drawThePotion(SDL_Renderer* rend, Uint32 color, int x_position, int y_position){
    boxColor(rend,x_position,y_position,x_position+20,y_position+10,color);
    filledCircleColor(rend,x_position+10,y_position+20,10,color);
}

void initializePotions(){
    potions=malloc(4*sizeof(potion));
    for(int i=0; i<4; i++){
        potions[i].durationToWait=rand()%4+4;
        potions[i].durationToBeEnabled=rand()%4+4;
        potions[i].is_deployed=false;
        potions[i].is_enabled=false;
    }
    potions[0].color=0xff00d7ff; //gold
    potions[1].color=0xff13458b; //saddle brown
    potions[2].color=0xff006400; //dark green
    potions[3].color=0xffffff00; //cyan
}

void findPotionCoordinates_random(center* hexagonsCenters, int* x_position, int* y_position){
    int firstRegionIndex=rand()%46;
    while(hexagonsCenters[firstRegionIndex].is_used==false || hexagonsCenters[firstRegionIndex].color == 0x70c0c0c0){
        firstRegionIndex=rand()%46;
    }
    int secondRegionIndex=rand()%46;
    while(hexagonsCenters[secondRegionIndex].is_used==false || firstRegionIndex==secondRegionIndex){
        secondRegionIndex=rand()%46;
    }

    if(hexagonsCenters[firstRegionIndex].x_coordinate>hexagonsCenters[secondRegionIndex].x_coordinate){
        int deltaX=hexagonsCenters[firstRegionIndex].x_coordinate-hexagonsCenters[secondRegionIndex].x_coordinate;
        *x_position=deltaX/2+hexagonsCenters[secondRegionIndex].x_coordinate-10;
    }
    else{
        int deltaX=hexagonsCenters[secondRegionIndex].x_coordinate-hexagonsCenters[firstRegionIndex].x_coordinate;
        *x_position=deltaX/2+hexagonsCenters[firstRegionIndex].x_coordinate-10;
    }
    if(hexagonsCenters[firstRegionIndex].y_coordinate>hexagonsCenters[secondRegionIndex].y_coordinate){
        int deltaY=hexagonsCenters[firstRegionIndex].y_coordinate-hexagonsCenters[secondRegionIndex].y_coordinate;
        *y_position=deltaY/2+hexagonsCenters[secondRegionIndex].y_coordinate;
    }
    else{
        int deltaY=hexagonsCenters[secondRegionIndex].y_coordinate-hexagonsCenters[firstRegionIndex].y_coordinate;
        *y_position=deltaY/2+hexagonsCenters[firstRegionIndex].y_coordinate;
    }

}

void deployPotion(long long int numOfFrames_fromBegining, center* hexagonsCenters){
    if(numOfFrames_fromBegining%900==800){
        int potionIndex=rand()%4;
        fprintf(file,"%d\n",potionIndex);
        potions[potionIndex].is_deployed=true;
        findPotionCoordinates_random(hexagonsCenters,&potions[potionIndex].x_position,&potions[potionIndex].y_position);
        potions[potionIndex].frameDeployed=numOfFrames_fromBegining;
    }
}

void displayPotions(SDL_Renderer* rend, long long int numOfFrames_fromBegining){
    for(int i=0; i<4; i++){
        if(potions[i].is_deployed==true){
            fprintf(fuckYou,"%d\n",i);
            if(numOfFrames_fromBegining-potions[i].frameDeployed<=potions[i].durationToWait*60){
                drawThePotion(rend,potions[i].color,potions[i].x_position,potions[i].y_position);
            }
            else{
                potions[i].is_deployed=false;
            }
        }
    }
}

void soldiersCollision_withPotion(long long int totalNumOfAttacks, int totalNumOfOponents, long long int numOfFrames_fromBegining){
    for(int i=0; i<4; i++){
        if(potions[i].is_deployed==true){
            for(long long int j=0; j<totalNumOfAttacks; j++){
                for(int k=0; k<attacks[j].numOfSoldiers; k++){
                    if(attacks[j].firstSoldier[k].x_coordinate>=potions[i].x_position && attacks[j].firstSoldier[k].x_coordinate<=potions[i].x_position+20 && attacks[j].firstSoldier[k].y_coordinate>=potions[i].y_position && attacks[j].firstSoldier[k].y_coordinate<=potions[i].y_position+10 ){
                        potions[i].is_deployed=false;
                        potions[i].is_enabled=true;
                        potions[i].frameEnabled=numOfFrames_fromBegining;
                        potions[i].teamColor=attacks[j].firstSoldier[k].color;
                    }
                    else{
                        double deltaX=attacks[j].firstSoldier[k].x_coordinate-potions[i].x_position-10;
                        double deltaY=attacks[j].firstSoldier[k].y_coordinate-potions[i].y_position-20;
                        double distance=sqrt(deltaY*deltaY+deltaX*deltaX);
                        if(distance<=15){
                            potions[i].is_deployed=false;
                            potions[i].is_enabled=true;
                            potions[i].frameEnabled=numOfFrames_fromBegining;
                            potions[i].teamColor=attacks[j].firstSoldier[k].color;
                        }
                    }
                }
            }
        }
    }
}

void potionsLogic(long long int numOfFrames_fromBegining, center* hexagonsCenters){
    for(int i=0; i<4; i++){
        if(potions[i].is_enabled==true && numOfFrames_fromBegining-potions[i].frameEnabled<=potions[i].durationToBeEnabled*60){
            switch (i){
                case 0:
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color==potions[i].teamColor){
                            hexagonsCenters[j].speedCoefficient=5;
                        }
                    }
                    break;
                case 1:
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color != potions[i].teamColor && hexagonsCenters[j].color != 0x70c0c0c0){
                            hexagonsCenters[j].speedCoefficient=3;
                        }
                    }
                    break;
                case 2:
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color==potions[i].teamColor){
                            hexagonsCenters[j].no_end=true;
                        }
                    }
                    break;
                case 3:
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color==potions[i].teamColor){
                            hexagonsCenters[j].soldierAddCoefficient=4;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        else if(potions[i].is_enabled==true && numOfFrames_fromBegining-potions[i].frameEnabled>potions[i].durationToBeEnabled*60){
            switch (i){
                case 0:
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color==potions[i].teamColor){
                            hexagonsCenters[j].speedCoefficient=1;
                        }
                    }
                    break;
                case 1:
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color != potions[i].teamColor && hexagonsCenters[j].color != 0x70c0c0c0){
                            hexagonsCenters[j].speedCoefficient=1;
                        }
                    }
                    break;
                case 2:
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color==potions[i].teamColor){
                            hexagonsCenters[j].no_end=false;
                        }
                    }
                    break;
                case 3:
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color==potions[i].teamColor){
                            hexagonsCenters[j].soldierAddCoefficient=1;
                        }
                    }
                    break;
                default:
                    break;
            }
            potions[i].is_enabled=false;
        }

    }
}