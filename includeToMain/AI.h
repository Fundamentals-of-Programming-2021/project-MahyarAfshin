#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
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

const int windowWidth=600;
const int windowHeight=750;
const int boxesWidth=200;
const int boxesHeight=40;

int find_totalNumOfOponents(Uint32 playerColor){
    int totalNumOfOponents=0;
    for(int i=0; i<6; i++){
        if(colors[i].is_used==true && colors[i].color != playerColor){
            totalNumOfOponents++;
        }
    }
    return totalNumOfOponents;
} 

int makeOponentsArray(Uint32 playerColor, int num){
    int totalNumOfOponents=find_totalNumOfOponents(playerColor);
    if(num==0){
        oponents=malloc(totalNumOfOponents*sizeof(teams));
    }
    else{
        free(oponents);
        oponents=malloc(totalNumOfOponents*sizeof(teams));
    }
    int count=0;
    for(int i=0; i<6; i++){
        if(colors[i].is_used==true && colors[i].color != playerColor){
            oponents[count].numOfTerritories=0;
            oponents[count].color=colors[i].color;
            count++;
        }
    }
    oponents=realloc(oponents,(totalNumOfOponents+1)*sizeof(teams));
    oponents[totalNumOfOponents].numOfTerritories=0;
    oponents[totalNumOfOponents].color=playerColor;
    return totalNumOfOponents;
}

int makeTeams(Uint32 playerColor, center* hexagonsCenters, int num){
    int totalNumOfOponents=makeOponentsArray(playerColor,num);
    for(int i=0; i<totalNumOfOponents+1; i++){
        for(int j=0; j<46; j++){
            if(hexagonsCenters[j].is_used==true && hexagonsCenters[j].color==oponents[i].color){
                oponents[i].numOfTerritories++;
                oponents[i].territories_index[oponents[i].numOfTerritories-1]=j;
            }
        }
    }
    return totalNumOfOponents;
}

int setAttackTime_forOponents(Uint32 playerColor, center* hexagonsCenters, int num){
    int totalNumOfOponents=makeTeams(playerColor,hexagonsCenters,num);
    for(int i=0; i<totalNumOfOponents; i++){
        oponents[i].attackTime=rand()%4+2;
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
    if(hexagonsCenters[attackerIndex].numOfSoldiers-hexagonsCenters[defenderIndex].numOfSoldiers >=0){
        score+=100*(hexagonsCenters[attackerIndex].numOfSoldiers-hexagonsCenters[defenderIndex].numOfSoldiers);
    }
    else{
        score=-1000000;
    }
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
            findTheBestAttack(i,hexagonsCenters,*totalNumOfAttacks,totalNumOfOponents);
            (*totalNumOfAttacks)++;
            addAnAttack(*totalNumOfAttacks,oponents[i].bestAttack.defenderIndex,hexagonsCenters,oponents[i].bestAttack.attackerIndex);
            hexagonsCenters[attacks[*totalNumOfAttacks-1].attackerIndex].numOfSoldiers=0;
        }
    }
}

// this function returns 0 if the game isn't finish , -1 if the player lost and 1 if it wins
int check_forWinner(center* hexagonsCenters, Uint32 playerColor){
    int map_array[46];
    for(int i=0; i<46; i++){
        map_array[i]=-1;
    }
    for(int i=0; i<46; i++){
        if(hexagonsCenters[i].is_used==true){
            if(hexagonsCenters[i].color==playerColor){
                map_array[i]=1;
            }
            else{
                map_array[i]=0;
            }
        }
    }
    int index=1;
    for(int i=0; i<46; i++){
        if(map_array[i]==-1 || map_array[i]==0){
            continue;
        }
        else{
            index=-1;
            break;
        }
    }
    if(index==1){
        return -1;
    }
    index=1;
    for(int i=0; i<46; i++){
        if(map_array[i]==-1 || map_array[i]==1){
            continue;
        }
        else{
            index=-1;
            break;
        }
    }
    if(index==1){
        return 1;
    }
    return 0;
}


int winnerPage(int state, SDL_Renderer* rend){
    TTF_Init();
    SDL_Surface* surface=IMG_Load("../resources/menuFirstPage.png");
    SDL_Texture* tex=SDL_CreateTextureFromSurface(rend,surface);
    SDL_FreeSurface(surface);
    SDL_Rect dest;
    SDL_QueryTexture(tex,NULL,NULL,&dest.w,&dest.h);
    dest.w=windowWidth;
    dest.h=windowHeight;
    dest.x=0;
    dest.y=0;

    char string[50];
    string[0]='\0';
    if(state==1){
        strcat(string,"You Won!");
    }
    else{
        strcat(string,"You Lost!");
    }

    TTF_Font* font=TTF_OpenFont("../resources/Exported Fonts/Annai MN/AnnaiMN.ttf", 15);
    SDL_Color color={0,0,0,255};
    SDL_Surface* gameName=TTF_RenderText_Solid(font,string,color);
    SDL_Texture* nameTex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_Rect nameDest;
    SDL_QueryTexture(nameTex,NULL,NULL,&nameDest.w,&nameDest.h);
    nameDest.x=(windowWidth-nameDest.w)/2;
    nameDest.y=(windowHeight-boxesHeight)/2+(boxesHeight-nameDest.h)/2;

    int close=0;
    SDL_Event event;
    while(close !=1 ){
        SDL_SetRenderDrawColor(rend,0xff,0xff,0xff,0xff);
        SDL_RenderClear(rend);
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                close=1;
            }
        }
        SDL_RenderCopy(rend,tex,NULL,&dest);
        SDL_RenderCopy(rend,nameTex,NULL,&nameDest);
        boxColor(rend,(windowWidth-boxesWidth)/2,(windowHeight-boxesHeight)/2,(windowWidth+boxesWidth)/2,(windowHeight+boxesHeight)/2,0x300000ff);
        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);   
    }
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(nameTex);
    TTF_CloseFont(font);
    TTF_Quit();
    return close;
}