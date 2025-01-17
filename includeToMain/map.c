#include"map.h"

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
    for(int i=0; i<46; i++){
        hexagonsCenters[i].speedCoefficient=1;
        hexagonsCenters[i].no_end=false;
        hexagonsCenters[i].soldierAddCoefficient=1;
        hexagonsCenters[i].is_potionActive=false;
    }
    //initializing the displaying string
    char* displayString=malloc(25*sizeof(char));
    displayString[0]='\0';

    int numOfUsedHexagons=0;

    //finding the maximum number of regions for each oponent
    int max_region=1;
    while(max_region*(numOfOponents+1)<numOfReigons){
        max_region++;
    }
    max_region--;

    //initializing an array of colors
    colors=malloc(6*sizeof(color));
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
            reigonIndex=rand()%46;
        }
        hexagonsCenters[reigonIndex].color=0x70c0c0c0;
        hexagonsCenters[reigonIndex].is_used=true;
    }
    for(int i=0; i<46; i++){
        if(hexagonsCenters[i].is_used==true){
            hexagonsCenters[i].centerColor=hexagonsCenters[i].color+0x8f000000;
        }
    }
    return displayString;
}

void putTheMapOnTheRenderer(center* hexagonsCenters, SDL_Renderer* rend, char* displayString){
    for(int i=0; i<46; i++){
        if(hexagonsCenters[i].is_used==true){
            hexagon* shape=creatingHexagons(hexagonsCenters[i],hexagon_radii);
            filledPolygonColor(rend,shape->x_coordinates,shape->y_coordinates,6,hexagonsCenters[i].color);
            filledCircleColor(rend,hexagonsCenters[i].x_coordinate,hexagonsCenters[i].y_coordinate,10,hexagonsCenters[i].centerColor);
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
        stringColor(rend,135,725,"Choose your opponent territory to attack!",0xff000000);
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

Uint32 checkClickedIndexColor(char* displayString){
    switch(displayString[14]){
        case 'G':
            return 0x7000ff00;
        case 'B':
            if(displayString[15]=='L'){
                return 0x70ff0000;
            }
            else{
                return 0x70004b96;
            }
        case 'R':
            return 0x700000ff;
        case 'P':
            if(displayString[15]=='I'){
                return 0x70cbc0ff;
            }
            else{
                return 0x708b008b;
            }
    }
    return 0x00000000;
}

char* map1_menu(center* hexagonsCenters){
    for(int i=0; i<46; i++){
        hexagonsCenters[i].speedCoefficient=1;
        hexagonsCenters[i].no_end=false;
        hexagonsCenters[i].soldierAddCoefficient=1;
        hexagonsCenters[i].is_potionActive=false;
    }
    char* displayString=malloc(25*sizeof(char));
    displayString[0]='\0';
    strcpy(displayString,"Your color is RED!");
    colors=malloc(6*sizeof(color));
    colors[0].color=0x7000ff00; //green
    colors[0].is_used=true;
    colors[1].color=0x70ff0000; //blue
    colors[1].is_used=true;
    colors[2].color=0x700000ff; //red
    colors[2].is_used=true;
    colors[3].color=0x70cbc0ff; //pink
    colors[3].is_used=true;
    colors[4].color=0x70004b96; //brown
    colors[4].is_used=true;
    colors[5].color=0x708b008b; //purple
    colors[5].is_used=true;

    hexagonsCenters[0].is_used=true;
    hexagonsCenters[0].color=0x70c0c0c0;
    hexagonsCenters[1].is_used=true;
    hexagonsCenters[1].color=0x70c0c0c0;
    hexagonsCenters[3].is_used=true;
    hexagonsCenters[3].color=0x7000ff00;
    hexagonsCenters[4].is_used=true;
    hexagonsCenters[4].color=0x70c0c0c0;
    hexagonsCenters[5].is_used=true;
    hexagonsCenters[5].color=0x70cbc0ff;
    hexagonsCenters[6].is_used=true;
    hexagonsCenters[6].color=0x70c0c0c0;
    hexagonsCenters[10].is_used=true;
    hexagonsCenters[10].color=0x70cbc0ff;
    hexagonsCenters[11].is_used=true;
    hexagonsCenters[11].color=0x708b008b;
    hexagonsCenters[18].is_used=true;
    hexagonsCenters[18].color=0x70c0c0c0;
    hexagonsCenters[20].is_used=true;
    hexagonsCenters[20].color=0x700000ff;
    hexagonsCenters[25].is_used=true;
    hexagonsCenters[25].color=0x700000ff;
    hexagonsCenters[29].is_used=true;
    hexagonsCenters[29].color=0x70ff0000;
    hexagonsCenters[30].is_used=true;
    hexagonsCenters[30].color=0x70004b96;
    hexagonsCenters[31].is_used=true;
    hexagonsCenters[31].color=0x70ff0000;
    hexagonsCenters[32].is_used=true;
    hexagonsCenters[32].color=0x70004b96;
    hexagonsCenters[34].is_used=true;
    hexagonsCenters[34].color=0x70c0c0c0;
    hexagonsCenters[35].is_used=true;
    hexagonsCenters[35].color=0x70c0c0c0;
    hexagonsCenters[40].is_used=true;
    hexagonsCenters[40].color=0x70c0c0c0;
    hexagonsCenters[41].is_used=true;
    hexagonsCenters[41].color=0x708b008b;
    hexagonsCenters[45].is_used=true;
    hexagonsCenters[45].color=0x70c0c0c0;
    for(int i=0; i<46; i++){
        if(hexagonsCenters[i].is_used==true){
            hexagonsCenters[i].centerColor=hexagonsCenters[i].color+0x8f000000;
        }
    }

    return displayString;
}

char* map2_menu(center* hexagonsCenters){
    for(int i=0; i<46; i++){
        hexagonsCenters[i].speedCoefficient=1;
        hexagonsCenters[i].no_end=false;
        hexagonsCenters[i].soldierAddCoefficient=1;
        hexagonsCenters[i].is_potionActive=false;
    }
    char* displayString=malloc(25*sizeof(char));
    displayString[0]='\0';
    strcpy(displayString,"Your color is PURPLE!");
    colors=malloc(6*sizeof(color));
    colors[0].color=0x7000ff00; //green
    colors[0].is_used=true;
    colors[1].color=0x70ff0000; //blue
    colors[1].is_used=true;
    colors[2].color=0x700000ff; //red
    colors[2].is_used=true;
    colors[3].color=0x70cbc0ff; //pink
    colors[3].is_used=false;
    colors[4].color=0x70004b96; //brown
    colors[4].is_used=false;
    colors[5].color=0x708b008b; //purple
    colors[5].is_used=true;

    hexagonsCenters[1].is_used=true;
    hexagonsCenters[1].color=0x70c0c0c0;
    hexagonsCenters[2].is_used=true;
    hexagonsCenters[2].color=0x70c0c0c0;
    hexagonsCenters[3].is_used=true;
    hexagonsCenters[3].color=0x70c0c0c0;
    hexagonsCenters[5].is_used=true;
    hexagonsCenters[5].color=0x70ff0000;
    hexagonsCenters[10].is_used=true;
    hexagonsCenters[10].color=0x708b008b;
    hexagonsCenters[11].is_used=true;
    hexagonsCenters[11].color=0x70c0c0c0;
    hexagonsCenters[12].is_used=true;
    hexagonsCenters[12].color=0x70c0c0c0;
    hexagonsCenters[13].is_used=true;
    hexagonsCenters[13].color=0x700000ff;
    hexagonsCenters[15].is_used=true;
    hexagonsCenters[15].color=0x7000ff00;
    hexagonsCenters[16].is_used=true;
    hexagonsCenters[16].color=0x70c0c0c0;
    hexagonsCenters[17].is_used=true;
    hexagonsCenters[17].color=0x70c0c0c0;
    hexagonsCenters[19].is_used=true;
    hexagonsCenters[19].color=0x70c0c0c0;
    hexagonsCenters[21].is_used=true;
    hexagonsCenters[21].color=0x7000ff00;
    hexagonsCenters[26].is_used=true;
    hexagonsCenters[26].color=0x7000ff00;
    hexagonsCenters[29].is_used=true;
    hexagonsCenters[29].color=0x70c0c0c0;
    hexagonsCenters[34].is_used=true;
    hexagonsCenters[34].color=0x70c0c0c0;
    hexagonsCenters[37].is_used=true;
    hexagonsCenters[37].color=0x70c0c0c0;
    hexagonsCenters[41].is_used=true;
    hexagonsCenters[41].color=0x7000ff00;
    hexagonsCenters[43].is_used=true;
    hexagonsCenters[43].color=0x70c0c0c0;
    hexagonsCenters[45].is_used=true;
    hexagonsCenters[45].color=0x70c0c0c0;
    for(int i=0; i<46; i++){
        if(hexagonsCenters[i].is_used==true){
            hexagonsCenters[i].centerColor=hexagonsCenters[i].color+0x8f000000;
        }
    }

    return displayString;
}

char* map3_menu(center* hexagonsCenters){
    for(int i=0; i<46; i++){
        hexagonsCenters[i].speedCoefficient=1;
        hexagonsCenters[i].no_end=false;
        hexagonsCenters[i].soldierAddCoefficient=1;
        hexagonsCenters[i].is_potionActive=false;
    }
    char* displayString=malloc(25*sizeof(char));
    displayString[0]='\0';
    strcpy(displayString,"Your color is BROWN!");
    colors=malloc(6*sizeof(color));
    colors[0].color=0x7000ff00; //green
    colors[0].is_used=true;
    colors[1].color=0x70ff0000; //blue
    colors[1].is_used=true;
    colors[2].color=0x700000ff; //red
    colors[2].is_used=true;
    colors[3].color=0x70cbc0ff; //pink
    colors[3].is_used=true;
    colors[4].color=0x70004b96; //brown
    colors[4].is_used=true;
    colors[5].color=0x708b008b; //purple
    colors[5].is_used=false;

    hexagonsCenters[0].is_used=true;
    hexagonsCenters[0].color=0x70c0c0c0;
    hexagonsCenters[1].is_used=true;
    hexagonsCenters[1].color=0x7000ff00;
    hexagonsCenters[2].is_used=true;
    hexagonsCenters[2].color=0x70c0c0c0;
    hexagonsCenters[3].is_used=true;
    hexagonsCenters[3].color=0x700000ff;
    hexagonsCenters[4].is_used=true;
    hexagonsCenters[4].color=0x70c0c0c0;
    hexagonsCenters[5].is_used=true;
    hexagonsCenters[5].color=0x7000ff00;
    hexagonsCenters[9].is_used=true;
    hexagonsCenters[9].color=0x70ff0000;
    hexagonsCenters[10].is_used=true;
    hexagonsCenters[10].color=0x70cbc0ff;
    hexagonsCenters[11].is_used=true;
    hexagonsCenters[11].color=0x70c0c0c0;
    hexagonsCenters[12].is_used=true;
    hexagonsCenters[12].color=0x70c0c0c0;
    hexagonsCenters[15].is_used=true;
    hexagonsCenters[15].color=0x7000ff00;
    hexagonsCenters[18].is_used=true;
    hexagonsCenters[18].color=0x70004b96;
    hexagonsCenters[22].is_used=true;
    hexagonsCenters[22].color=0x70c0c0c0;
    hexagonsCenters[23].is_used=true;
    hexagonsCenters[23].color=0x70c0c0c0;
    hexagonsCenters[29].is_used=true;
    hexagonsCenters[29].color=0x70c0c0c0;
    hexagonsCenters[35].is_used=true;
    hexagonsCenters[35].color=0x70c0c0c0;
    hexagonsCenters[36].is_used=true;
    hexagonsCenters[36].color=0x700000ff;
    hexagonsCenters[38].is_used=true;
    hexagonsCenters[38].color=0x70c0c0c0;
    hexagonsCenters[39].is_used=true;
    hexagonsCenters[39].color=0x70004b96;
    hexagonsCenters[40].is_used=true;
    hexagonsCenters[40].color=0x70cbc0ff;
    for(int i=0; i<46; i++){
        if(hexagonsCenters[i].is_used==true){
            hexagonsCenters[i].centerColor=hexagonsCenters[i].color+0x8f000000;
        }
    }

    return displayString;
}

char* map4_menu(center* hexagonsCenters){
    for(int i=0; i<46; i++){
        hexagonsCenters[i].speedCoefficient=1;
        hexagonsCenters[i].no_end=false;
        hexagonsCenters[i].soldierAddCoefficient=1;
        hexagonsCenters[i].is_potionActive=false;
    }
    char* displayString=malloc(25*sizeof(char));
    displayString[0]='\0';
    strcpy(displayString,"Your color is GREEN!");
    colors=malloc(6*sizeof(color));
    colors[0].color=0x7000ff00; //green
    colors[0].is_used=true;
    colors[1].color=0x70ff0000; //blue
    colors[1].is_used=false;
    colors[2].color=0x700000ff; //red
    colors[2].is_used=true;
    colors[3].color=0x70cbc0ff; //pink
    colors[3].is_used=true;
    colors[4].color=0x70004b96; //brown
    colors[4].is_used=true;
    colors[5].color=0x708b008b; //purple
    colors[5].is_used=true;

    hexagonsCenters[0].is_used=true;
    hexagonsCenters[0].color=0x70c0c0c0;
    hexagonsCenters[3].is_used=true;
    hexagonsCenters[3].color=0x70c0c0c0;
    hexagonsCenters[4].is_used=true;
    hexagonsCenters[4].color=0x708b008b;
    hexagonsCenters[8].is_used=true;
    hexagonsCenters[8].color=0x70c0c0c0;
    hexagonsCenters[9].is_used=true;
    hexagonsCenters[9].color=0x70c0c0c0;
    hexagonsCenters[10].is_used=true;
    hexagonsCenters[10].color=0x70c0c0c0;
    hexagonsCenters[13].is_used=true;
    hexagonsCenters[13].color=0x700000ff;
    hexagonsCenters[15].is_used=true;
    hexagonsCenters[15].color=0x70c0c0c0;
    hexagonsCenters[16].is_used=true;
    hexagonsCenters[16].color=0x708b008b;
    hexagonsCenters[19].is_used=true;
    hexagonsCenters[19].color=0x70c0c0c0;
    hexagonsCenters[20].is_used=true;
    hexagonsCenters[20].color=0x70c0c0c0;
    hexagonsCenters[21].is_used=true;
    hexagonsCenters[21].color=0x70c0c0c0;
    hexagonsCenters[22].is_used=true;
    hexagonsCenters[22].color=0x70c0c0c0;
    hexagonsCenters[24].is_used=true;
    hexagonsCenters[24].color=0x70c0c0c0;
    hexagonsCenters[25].is_used=true;
    hexagonsCenters[25].color=0x70004b96;
    hexagonsCenters[27].is_used=true;
    hexagonsCenters[27].color=0x70c0c0c0;
    hexagonsCenters[28].is_used=true;
    hexagonsCenters[28].color=0x70c0c0c0;
    hexagonsCenters[30].is_used=true;
    hexagonsCenters[30].color=0x70c0c0c0;
    hexagonsCenters[31].is_used=true;
    hexagonsCenters[31].color=0x70c0c0c0;
    hexagonsCenters[34].is_used=true;
    hexagonsCenters[34].color=0x70cbc0ff;
    hexagonsCenters[36].is_used=true;
    hexagonsCenters[36].color=0x70c0c0c0;
    hexagonsCenters[40].is_used=true;
    hexagonsCenters[40].color=0x70c0c0c0;
    hexagonsCenters[42].is_used=true;
    hexagonsCenters[42].color=0x70cbc0ff;
    hexagonsCenters[43].is_used=true;
    hexagonsCenters[43].color=0x70cbc0ff;
    hexagonsCenters[44].is_used=true;
    hexagonsCenters[44].color=0x7000ff00;
    for(int i=0; i<46; i++){
        if(hexagonsCenters[i].is_used==true){
            hexagonsCenters[i].centerColor=hexagonsCenters[i].color+0x8f000000;
        }
    }
    return displayString;
}

char* map_memory(center* hexagonsCenters){
    for(int i=0; i<46; i++){
        hexagonsCenters[i].speedCoefficient=1;
        hexagonsCenters[i].soldierAddCoefficient=1;
        hexagonsCenters[i].no_end=false;
        hexagonsCenters[i].is_potionActive=false;
    }
    char* displayString=malloc(25*sizeof(char));
    displayString[0]='\0';
    strcpy(displayString,"Your color is BLUE!");
    colors=malloc(6*sizeof(color));
    colors[0].color=0x7000ff00; //green
    colors[0].is_used=false;
    colors[1].color=0x70ff0000; //blue
    colors[1].is_used=true;
    colors[2].color=0x700000ff; //red
    colors[2].is_used=true;
    colors[3].color=0x70cbc0ff; //pink
    colors[3].is_used=false;
    colors[4].color=0x70004b96; //brown
    colors[4].is_used=false;
    colors[5].color=0x708b008b; //purple
    colors[5].is_used=false;

    hexagonsCenters[1].is_used=true;
    hexagonsCenters[1].color=0x70ff0000;
    hexagonsCenters[3].is_used=true;
    hexagonsCenters[3].color=0x70ff0000;
    hexagonsCenters[5].is_used=true;
    hexagonsCenters[5].color=0x70ff0000;
    hexagonsCenters[9].is_used=true;
    hexagonsCenters[9].color=0x70ff0000;
    hexagonsCenters[10].is_used=true;
    hexagonsCenters[10].color=0x70ff0000;
    hexagonsCenters[15].is_used=true;
    hexagonsCenters[15].color=0x70ff0000;
    hexagonsCenters[18].is_used=true;
    hexagonsCenters[18].color=0x70ff0000;
    hexagonsCenters[36].is_used=true;
    hexagonsCenters[36].color=0x70ff0000;
    hexagonsCenters[39].is_used=true;
    hexagonsCenters[39].color=0x70ff0000;
    hexagonsCenters[40].is_used=true;
    hexagonsCenters[40].color=0x70ff0000;
    hexagonsCenters[43].is_used=true;
    hexagonsCenters[43].color=0x70ff0000;
    hexagonsCenters[45].is_used=true;
    hexagonsCenters[45].color=0x70ff0000;
    hexagonsCenters[24].is_used=true;
    hexagonsCenters[24].color=0x700000ff;
    for(int i=0; i<46; i++){
        if(hexagonsCenters[i].is_used==true){
            hexagonsCenters[i].centerColor=hexagonsCenters[i].color+0x8f000000;
        }
    }

    return displayString;
}

