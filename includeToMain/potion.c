#include"potion.h"

void drawThePotion(SDL_Renderer* rend, Uint32 color, int x_position, int y_position){
    boxColor(rend,x_position,y_position,x_position+20,y_position+10,color);
    filledCircleColor(rend,x_position+10,y_position+20,10,color);
}

void initializePotions(){
    potions=malloc(4*sizeof(potion));
    for(int i=0; i<4; i++){
        potions[i].durationToWait=rand()%4+5;
        potions[i].durationToBeEnabled=rand()%4+5;
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
    if(rand()%360==300){
        int potionIndex=rand()%4;
        potions[potionIndex].is_deployed=true;
        findPotionCoordinates_random(hexagonsCenters,&potions[potionIndex].x_position,&potions[potionIndex].y_position);
        potions[potionIndex].frameDeployed=numOfFrames_fromBegining;
    }
}

void displayPotions(SDL_Renderer* rend, long long int numOfFrames_fromBegining){
    for(int i=0; i<4; i++){
        if(potions[i].is_deployed==true){
            if(numOfFrames_fromBegining-potions[i].frameDeployed<=potions[i].durationToWait*60){
                drawThePotion(rend,potions[i].color,potions[i].x_position,potions[i].y_position);
            }
            else{
                potions[i].is_deployed=false;
            }
        }
    }
}

void soldiersCollision_withPotion(long long int totalNumOfAttacks, int totalNumOfOponents, long long int numOfFrames_fromBegining, center* hexagonsCenters){
    for(int i=0; i<4; i++){
        if(potions[i].is_deployed==true){
            for(long long int j=0; j<totalNumOfAttacks; j++){
                for(int k=0; k<attacks[j].numOfSoldiers; k++){
                    if(attacks[j].firstSoldier[k].x_coordinate>=potions[i].x_position-5 && attacks[j].firstSoldier[k].x_coordinate<=potions[i].x_position+30 && attacks[j].firstSoldier[k].y_coordinate>=potions[i].y_position-5 && attacks[j].firstSoldier[k].y_coordinate<=potions[i].y_position+20 && attacks[j].firstSoldier[k].is_potionActive==false){
                        potions[i].is_deployed=false;
                        potions[i].is_enabled=true;
                        potions[i].frameEnabled=numOfFrames_fromBegining;
                        potions[i].teamColor=attacks[j].firstSoldier[k].color;
                    }
                    else{
                        double deltaX=attacks[j].firstSoldier[k].x_coordinate-potions[i].x_position-10;
                        double deltaY=attacks[j].firstSoldier[k].y_coordinate-potions[i].y_position-20;
                        double distance=sqrt(deltaY*deltaY+deltaX*deltaX);
                        if(distance<=15 && attacks[j].firstSoldier[k].is_potionActive==false){
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
                            hexagonsCenters[j].is_potionActive=true;
                            hexagonsCenters[j].centerColor=potions[i].color;
                        }
                    }
                    break;
                case 1:
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color != potions[i].teamColor && hexagonsCenters[j].color != 0x70c0c0c0){
                            hexagonsCenters[j].speedCoefficient=3;
                        }
                    }
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color==potions[i].teamColor){
                            hexagonsCenters[j].is_potionActive=true;
                            hexagonsCenters[j].centerColor=potions[i].color;
                        }
                    }
                    break;
                case 2:
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color==potions[i].teamColor){
                            hexagonsCenters[j].no_end=true;
                            hexagonsCenters[j].is_potionActive=true;
                            hexagonsCenters[j].centerColor=potions[i].color;
                        }
                    }
                    break;
                case 3:
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color==potions[i].teamColor){
                            hexagonsCenters[j].soldierAddCoefficient=4;
                            hexagonsCenters[j].is_potionActive=true;
                            hexagonsCenters[j].centerColor=potions[i].color;
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
                            hexagonsCenters[j].is_potionActive=false;
                            hexagonsCenters[j].centerColor=hexagonsCenters[j].color+0x8f000000;
                        }
                    }
                    break;
                case 1:
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color != potions[i].teamColor && hexagonsCenters[j].color != 0x70c0c0c0){
                            hexagonsCenters[j].speedCoefficient=1;
                        }
                    }
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color==potions[i].teamColor){
                            hexagonsCenters[j].is_potionActive=false;
                            hexagonsCenters[j].centerColor=hexagonsCenters[j].color+0x8f000000;
                        }
                    }
                    break;
                case 2:
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color==potions[i].teamColor){
                            hexagonsCenters[j].no_end=false;
                            hexagonsCenters[j].is_potionActive=false;
                            hexagonsCenters[j].centerColor=hexagonsCenters[j].color+0x8f000000;
                        }
                    }
                    break;
                case 3:
                    for(int j=0; j<46; j++){
                        if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color==potions[i].teamColor){
                            hexagonsCenters[j].soldierAddCoefficient=1;
                            hexagonsCenters[j].is_potionActive=false;
                            hexagonsCenters[j].centerColor=hexagonsCenters[j].color+0x8f000000;
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

void potionFade(center* hexagonsCenters, long long int numOfFrames_fromBegining){
    for(int i=0; i<4; i++){
        if(potions[i].is_enabled==true){
            for(int j=0; j<46; j++){
                if(numOfFrames_fromBegining-potions[i].durationToBeEnabled && hexagonsCenters[j].color==potions[i].teamColor){
                    Uint32 colorCorrection = ((numOfFrames_fromBegining-potions[i].frameEnabled)*1.0/(60*potions[i].durationToBeEnabled))*255*256*256*256;
                    hexagonsCenters[j].centerColor-=colorCorrection/(256*256*256)*(256*256*256);
                }
            }
        }
    }
}