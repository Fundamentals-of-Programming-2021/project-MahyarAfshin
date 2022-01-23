#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include"soldiers.h"

#define pi 3.14159265359
#define hexagon_radii 50

typedef struct color{
    Uint32 color;
    bool is_used;
}color;

typedef struct hexagon{
    Sint16 x_coordinates[6];
    Sint16 y_coordinates[6];
}hexagon;

typedef struct arrow{
    Sint16 x_coordinates[7];
    Sint16 y_coordinates[7];
}arrow;

hexagon* creatingHexagons(center hexagonCenter, Sint16 radius);
center* createMapTemplate(SDL_Renderer* rend); // the return will be an array containing 46 centers for hexagons
//the return of below function will be a string that shows the user, it's color in game
char* generatingRandomMap(int numOfOponents, int numOfRegions, center* hexagonsCenters); // in this game the maximum number of oponents is 5 and the maximum number of regions is 40 and the minimun number of regions is 10
void putTheMapOnTheRenderer(center* hexagonCenters, SDL_Renderer* rend, char* displayString);
//below function returns the index of the chosen hexagon
int getMousePosition(center* hexagonCenters, SDL_Renderer* rend, bool chosen_territory_for_attack, int mouse_xPosition, int mouse_yPosition);

hexagon* creatingHexagons(center hexagonCenter, Sint16 radius){
    hexagon* shape=malloc(sizeof(hexagon));
    double angle=0;
    for(int i=0; i<6; i++){
        shape->x_coordinates[i]=hexagonCenter.x_coordinate+radius*cos(angle);
        shape->y_coordinates[i]=hexagonCenter.y_coordinate+radius*sin(angle);
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
    hexagonCenter.numOfSoldiers=0;
    int centers_counter=0;
    for(int j=0; j<3; j++){
        for(int i=0; i<7; i++){
            hexagon* shape=creatingHexagons(hexagonCenter,hexagon_radii);
            filledPolygonColor(rend,shape->x_coordinates,shape->y_coordinates,6,hexagonCenter.color);
            free(shape);
            hexagonCenters[centers_counter]=hexagonCenter;
            centers_counter++;
            hexagonCenter.y_coordinate+=2*50*sin(pi/3);
        }
        hexagonCenter.y_coordinate-=3*50*sin(pi/3);
        hexagonCenter.x_coordinate+=50+50*cos(pi/3);
        for(int i=0; i<6; i++){
            hexagon* shape=creatingHexagons(hexagonCenter,hexagon_radii);
            filledPolygonColor(rend,shape->x_coordinates,shape->y_coordinates,6,hexagonCenter.color);
            free(shape);
            hexagonCenters[centers_counter]=hexagonCenter;
            centers_counter++;
            hexagonCenter.y_coordinate-=2*50*sin(pi/3);
        }
        hexagonCenter.y_coordinate+=50*sin(pi/3);
        hexagonCenter.x_coordinate+=50+50*cos(pi/3);
    }
    for(int i=0; i<7; i++){
        hexagon* shape=creatingHexagons(hexagonCenter,hexagon_radii);
        filledPolygonColor(rend,shape->x_coordinates,shape->y_coordinates,6,hexagonCenter.color);
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

char* generatingRandomMap(int numOfOponents, int numOfReigons, center* hexagonsCenters){
    //initializing the displaying string
    char* displayString=malloc(25*sizeof(char));
    displayString[0]='\0';

    int numOfUsedHexagons=0;
    srand(time(0));
    //finding the maximum number of regions for each oponent
    int max_region=1;
    while(max_region*(numOfOponents+1)<numOfReigons){
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
        int numOfReigonsForPlayer=rand()%max_region+1;

        //finding each reigon randomly
        for(int j=0; j<numOfReigonsForPlayer; j++){
            int reigonIndex=rand()%46;
            while(hexagonsCenters[reigonIndex].is_used==true){
                reigonIndex=rand()%6;
            }
            hexagonsCenters[reigonIndex].color=OponentColor;
            hexagonsCenters[reigonIndex].is_used=true;
        }
        numOfUsedHexagons+=numOfReigonsForPlayer;

        //displaying players color
        if(i==0){
            //char displayString[25];
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
        }
    }

    //filling impartial hexagons
    for(int i=0; i<numOfReigons-numOfUsedHexagons; i++){
        int reigonIndex=rand()%46;
        while(hexagonsCenters[reigonIndex].is_used==true){
            reigonIndex=rand()%6;
        }
        hexagonsCenters[reigonIndex].color=0x70c0c0c0;
        hexagonsCenters[reigonIndex].is_used=true;
    }

    free(colors);
    return displayString;
}

void putTheMapOnTheRenderer(center* hexagonsCenters, SDL_Renderer* rend, char* displayString){
    for(int i=0; i<46; i++){
        if(hexagonsCenters[i].is_used==true){
            hexagon* shape=creatingHexagons(hexagonsCenters[i],hexagon_radii);
            filledPolygonColor(rend,shape->x_coordinates,shape->y_coordinates,6,hexagonsCenters[i].color);
            filledCircleColor(rend,hexagonsCenters[i].x_coordinate,hexagonsCenters[i].y_coordinate,10,hexagonsCenters[i].color+0x8f000000);
            char soldiersNumber[50];
            sprintf(soldiersNumber,"%d",hexagonsCenters[i].numOfSoldiers);
            stringColor(rend,hexagonsCenters[i].x_coordinate-strlen(soldiersNumber)*4,hexagonsCenters[i].y_coordinate+12,soldiersNumber,0xff000000);
        }
    }
    stringColor(rend,215,25,displayString,0xff000000);
}

int getMousePosition(center* hexagonCenters, SDL_Renderer* rend, bool chosen_territory_for_attack, int mouse_xPosition, int mouse_yPosition){
    if(chosen_territory_for_attack==false){
        stringColor(rend,75,725,"Choose your own territory you want to use for attacking!",0xff000000);
    }
    else{
        stringColor(rend,135,725,"Choose your oponent territory to attack!",0xff000000);
    }
    for(int i=0; i<46; i++){
        double distance=sqrt((mouse_yPosition-hexagonCenters[i].y_coordinate)*(mouse_yPosition-hexagonCenters[i].y_coordinate)+(mouse_xPosition-hexagonCenters[i].x_coordinate)*(mouse_xPosition-hexagonCenters[i].x_coordinate));
        if(distance<(double) 50*sin(pi/3) && hexagonCenters[i].is_used==true){
            hexagon* shape=creatingHexagons(hexagonCenters[i],hexagon_radii+10);
            filledPolygonColor(rend,shape->x_coordinates,shape->y_coordinates,6,hexagonCenters[i].color-0x35000000);
            return i;
        }
    }
    return -1; 
}

