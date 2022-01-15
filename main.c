#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>

#define pi 3.14159265359

const int windowWidth=600;
const int windowHeight=750;

typedef struct color{
    Uint32 color;
    bool is_used;
}color;

typedef struct hexagon{
    Sint16 x_coordinates[6];
    Sint16 y_coordinate[6];
}hexagon;

typedef struct center{
    double x_coordinate;
    double y_coordinate;
    Uint32 color;
    bool is_used;
}center;

hexagon* creatingHexagons(center hexagonCenter);
center* createMapTemplate(SDL_Renderer* rend); // the return will be an array containing 46 centers for hexagons
void generatingRandomMap(int numOfOponents, int numOfRegions, center* hexagonsCenters, SDL_Renderer* rend); // in this game the maximum number of oponents is 5 and the maximum number of regions is 46 and the minimun number of regions is 10

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* gameWindow=SDL_CreateWindow("state.io",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowWidth,windowHeight,0);
    SDL_Renderer* rend=SDL_CreateRenderer(gameWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(rend,0xff,0xff,0xff,0xff);
    SDL_RenderClear(rend);
    center* hexagonsCenters=createMapTemplate(rend);
    generatingRandomMap(5,20,hexagonsCenters,rend);
    SDL_RenderPresent(rend);
    int close=0;
    SDL_Event event;
    while(close != 1){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                close=1;
            }

        }
    }
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();
    return 0;
}

hexagon* creatingHexagons(center hexagonCenter){
    hexagon* shape=malloc(sizeof(hexagon));
    double angle=0;
    for(int i=0; i<6; i++){
        shape->x_coordinates[i]=hexagonCenter.x_coordinate+50*cos(angle);
        shape->y_coordinate[i]=hexagonCenter.y_coordinate+50*sin(angle);
        angle+=pi/3;
    }
    return shape;
}

center* createMapTemplate(SDL_Renderer* rend){
    center* hexagonCenters=malloc(46*sizeof(center));
    center hexagonCenter;
    hexagonCenter.x_coordinate=75;
    hexagonCenter.y_coordinate=100;
    hexagonCenter.color=0x70ffffe0;
    hexagonCenter.is_used=false;
    int centers_counter=0;
    for(int j=0; j<3; j++){
        for(int i=0; i<7; i++){
            hexagon* shape=creatingHexagons(hexagonCenter);
            filledPolygonColor(rend,shape->x_coordinates,shape->y_coordinate,6,hexagonCenter.color);
            free(shape);
            hexagonCenters[centers_counter]=hexagonCenter;
            centers_counter++;
            hexagonCenter.y_coordinate+=2*50*sin(pi/3);
        }
        hexagonCenter.y_coordinate-=3*50*sin(pi/3);
        hexagonCenter.x_coordinate+=50+50*cos(pi/3);
        for(int i=0; i<6; i++){
            hexagon* shape=creatingHexagons(hexagonCenter);
            filledPolygonColor(rend,shape->x_coordinates,shape->y_coordinate,6,hexagonCenter.color);
            free(shape);
            hexagonCenters[centers_counter]=hexagonCenter;
            centers_counter++;
            hexagonCenter.y_coordinate-=2*50*sin(pi/3);
        }
        hexagonCenter.y_coordinate+=50*sin(pi/3);
        hexagonCenter.x_coordinate+=50+50*cos(pi/3);
    }
    for(int i=0; i<7; i++){
        hexagon* shape=creatingHexagons(hexagonCenter);
        filledPolygonColor(rend,shape->x_coordinates,shape->y_coordinate,6,hexagonCenter.color);
        free(shape);
        hexagonCenters[centers_counter]=hexagonCenter;
        centers_counter++;
        hexagonCenter.y_coordinate+=2*50*sin(pi/3);
    }
    /*
    the coordinate of centers will be saved in hexagonCenters[46] array in this order (the indexes are shown below):
    0           13              26              39   
         12              25              38      
    1           14              27              40
         11              24              37
    2           15              28              41
         10              23              36
    3           16              29              42
         9               22              35
    4           17              30              43
         8               21              34
    5           18              31              44
         7               20              33
    6           19              32              45
    */
    return hexagonCenters;
}

void generatingRandomMap(int numOfOponents, int numOfRegions, center* hexagonsCenters, SDL_Renderer* rend){
    srand(time(0));
    //finding the maximum number of regions for each oponent
    int max_region=1;
    while(max_region*numOfOponents<=numOfRegions){
        max_region++;
    }
    max_region--;

    //initializing an array of colors
    color* colors=malloc(6*sizeof(color));
    colors[0].color=0x7000ff00; //green
    colors[1].color=0x70ff0000; //blue
    colors[2].color=0x700000ff; //red
    colors[3].color=0x70cbc0ff; //pink
    colors[4].color=0x70004b96; //brown
    colors[5].color=0x708b008b; //purple
    for(int i=0; i<6; i++){
        colors[i].is_used=false;
    }

    //filling oponents reigons randomly (in i=0 the players reigons are filling and the color of player will be displayed at top of the screen)
    for(int i=0; i<numOfOponents+1; i++){
        //random color for oponent
        int colorIndex=rand()%6;
        while(colors[colorIndex].is_used==true){
            colorIndex=rand()%6;
        }
        Uint32 OponentColor=colors[colorIndex].color;
        colors[colorIndex].is_used=true;

        //generating a random number as oponent's total number of reigons
        int numOfReigons=rand()%max_region+1;

        //finding each reigon randomly
        for(int j=0; j<numOfReigons; j++){
            int reigonIndex=rand()%46;
            while(hexagonsCenters[reigonIndex].is_used==true){
                reigonIndex=rand()%6;
            }
            hexagon* shape=creatingHexagons(hexagonsCenters[reigonIndex]);
            filledPolygonColor(rend,shape->x_coordinates,shape->y_coordinate,6,OponentColor);
            hexagonsCenters[reigonIndex].is_used=true;
        }

        //displaying players color
        if(i==0){
            char displayString[25];
            switch(colorIndex){
                case 0:
                    strcpy(displayString,"Your color is GREEN!");
                    break;
                case 1:
                    strcpy(displayString,"Your color is BLUE!");
                    break;
                case 2:
                    strcpy(displayString,"Your color is RED!");
                    break;
                case 3:
                    strcpy(displayString,"Your color is PINK!");
                    break;
                case 4:
                    strcpy(displayString,"Your color is BROWN!");
                    break;
                case 5:
                    strcpy(displayString,"Your color is PURPLE!");
                    break;
                default:
                    break;
            }
            stringColor(rend,215,25,displayString,0xff000000);
        }
    }
}