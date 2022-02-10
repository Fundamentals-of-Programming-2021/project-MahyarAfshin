#include"nextPageMenu.h"

bool check_inTheBox(int box_upperLeftCorner_x, int box_upperLeftCorner_y){
    SDL_GetMouseState(&mouse_xPosition,&mouse_yPosition);
    if(mouse_xPosition>=box_upperLeftCorner_x && mouse_xPosition<=box_upperLeftCorner_x+boxesWidth && mouse_yPosition>=box_upperLeftCorner_y && mouse_yPosition<=box_upperLeftCorner_y+boxesHeight){
        return true;
    }
    return false;
}

void typeTheEnteredName(char name[51], SDL_Rect secondDest, SDL_Color color, SDL_Renderer* rend, TTF_Font* enteredName_font){
    SDL_Surface* enteredName=TTF_RenderText_Solid(enteredName_font,name,color);
    SDL_Texture* texture=SDL_CreateTextureFromSurface(rend,enteredName);
    SDL_Rect enteredName_dest;
    SDL_QueryTexture(texture,NULL,NULL,&enteredName_dest.w,&enteredName_dest.h);
    enteredName_dest.x=(secondDest.w-enteredName_dest.w)/2+secondDest.x+1;
    enteredName_dest.y=(secondDest.h-enteredName_dest.h)/2+250+1;
    SDL_RenderCopy(rend,texture,NULL,&enteredName_dest);
    SDL_FreeSurface(enteredName);
    SDL_DestroyTexture(texture);
}

int display_scoreBoard(SDL_Renderer* rend, SDL_Texture* thirdTex, SDL_Texture* fourthTex, SDL_Texture* fifthTex, SDL_Texture* tex, long long int userIndex){
    bubble_sort_users();
    TTF_Font* enteredName_font=TTF_OpenFont("../resources/Exported Fonts/Annai MN/AnnaiMN.ttf", 15);
    SDL_Color color={0,0,0,255};
    //creating textures
    SDL_Texture* user1_tex;
    SDL_Texture* user2_tex;
    SDL_Texture* user3_tex;
    SDL_Texture* user4_tex;
    SDL_Texture* user5_tex;
    SDL_Texture* user6_tex;
    SDL_Texture* user7_tex;
    SDL_Texture* user8_tex;
    char string[100];
    sprintf(string,"%s (%lld)",users[0].name,users[0].score);
    SDL_Surface* gameName=TTF_RenderText_Solid(enteredName_font,string,color);
    user1_tex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_QueryTexture(user1_tex,NULL,NULL,&user1_dest.w,&user1_dest.h);
    user1_dest.x=(windowWidth-boxesWidth)/2+(boxesWidth-user1_dest.w)/2;
    user1_dest.y=100+(boxesHeight-user1_dest.h)/2;

    if(numOfUsers>1){
        sprintf(string,"%s (%lld)",users[1].name,users[1].score);
        gameName=TTF_RenderText_Solid(enteredName_font,string,color);
        user2_tex=SDL_CreateTextureFromSurface(rend,gameName);
        SDL_FreeSurface(gameName);
        SDL_QueryTexture(user2_tex,NULL,NULL,&user2_dest.w,&user2_dest.h);
        user2_dest.x=(windowWidth-boxesWidth)/2+(boxesWidth-user2_dest.w)/2;
        user2_dest.y=150+(boxesHeight-user2_dest.h)/2;
    }

    if(numOfUsers>2){
        sprintf(string,"%s (%lld)",users[2].name,users[2].score);
        gameName=TTF_RenderText_Solid(enteredName_font,string,color);
        user3_tex=SDL_CreateTextureFromSurface(rend,gameName);
        SDL_FreeSurface(gameName);
        SDL_QueryTexture(user3_tex,NULL,NULL,&user3_dest.w,&user3_dest.h);
        user3_dest.x=(windowWidth-boxesWidth)/2+(boxesWidth-user3_dest.w)/2;
        user3_dest.y=200+(boxesHeight-user3_dest.h)/2;
    }

    if(numOfUsers>3){
        sprintf(string,"%s (%lld)",users[3].name,users[3].score);
        gameName=TTF_RenderText_Solid(enteredName_font,string,color);
        user4_tex=SDL_CreateTextureFromSurface(rend,gameName);
        SDL_FreeSurface(gameName);
        SDL_QueryTexture(user4_tex,NULL,NULL,&user4_dest.w,&user4_dest.h);
        user4_dest.x=(windowWidth-boxesWidth)/2+(boxesWidth-user4_dest.w)/2;
        user4_dest.y=250+(boxesHeight-user4_dest.h)/2;
    }

    if(numOfUsers>4){
        sprintf(string,"%s (%lld)",users[4].name,users[4].score);
        gameName=TTF_RenderText_Solid(enteredName_font,string,color);
        user5_tex=SDL_CreateTextureFromSurface(rend,gameName);
        SDL_FreeSurface(gameName);
        SDL_QueryTexture(user5_tex,NULL,NULL,&user5_dest.w,&user5_dest.h);
        user5_dest.x=(windowWidth-boxesWidth)/2+(boxesWidth-user5_dest.w)/2;
        user5_dest.y=300+(boxesHeight-user5_dest.h)/2;
    }

    if(numOfUsers>5){
        sprintf(string,"%s (%lld)",users[5].name,users[5].score);
        gameName=TTF_RenderText_Solid(enteredName_font,string,color);
        user6_tex=SDL_CreateTextureFromSurface(rend,gameName);
        SDL_FreeSurface(gameName);
        SDL_QueryTexture(user6_tex,NULL,NULL,&user6_dest.w,&user6_dest.h);
        user6_dest.x=(windowWidth-boxesWidth)/2+(boxesWidth-user6_dest.w)/2;
        user6_dest.y=350+(boxesHeight-user6_dest.h)/2;
    }

    if(numOfUsers>6){
        sprintf(string,"%s (%lld)",users[6].name,users[6].score);
        gameName=TTF_RenderText_Solid(enteredName_font,string,color);
        user7_tex=SDL_CreateTextureFromSurface(rend,gameName);
        SDL_FreeSurface(gameName);
        SDL_QueryTexture(user7_tex,NULL,NULL,&user7_dest.w,&user7_dest.h);
        user7_dest.x=(windowWidth-boxesWidth)/2+(boxesWidth-user7_dest.w)/2;
        user7_dest.y=400+(boxesHeight-user7_dest.h)/2;
    }

    if(numOfUsers>7){
        sprintf(string,"%s (%lld)",users[7].name,users[7].score);
        gameName=TTF_RenderText_Solid(enteredName_font,string,color);
        user8_tex=SDL_CreateTextureFromSurface(rend,gameName);
        SDL_FreeSurface(gameName);
        SDL_QueryTexture(user8_tex,NULL,NULL,&user8_dest.w,&user8_dest.h);
        user8_dest.x=(windowWidth-boxesWidth)/2+(boxesWidth-user8_dest.w)/2;
        user8_dest.y=450+(boxesHeight-user8_dest.h)/2;
    }

    
    int close=0;
    SDL_Event event;
    while(close != 1){
        SDL_SetRenderDrawColor(rend,0xff,0xff,0xff,0xff);
        SDL_RenderClear(rend);
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                close=1;
            }
        }
        SDL_RenderCopy(rend,tex,NULL,&dest);
        SDL_RenderCopy(rend,thirdTex,NULL,&thirdDest);
        SDL_RenderCopy(rend,fourthTex,NULL,&fourthDest);
        SDL_RenderCopy(rend,fifthTex,NULL,&fifthDest);
        SDL_RenderCopy(rend,user1_tex,NULL,&user1_dest);
        if(numOfUsers>1){
            SDL_RenderCopy(rend,user2_tex,NULL,&user2_dest);
        }
        if(numOfUsers>2){
            SDL_RenderCopy(rend,user3_tex,NULL,&user3_dest);
        }
        if(numOfUsers>3){
            SDL_RenderCopy(rend,user4_tex,NULL,&user4_dest);
        }
        if(numOfUsers>4){
            SDL_RenderCopy(rend,user5_tex,NULL,&user5_dest);
        }
        if(numOfUsers>5){
            SDL_RenderCopy(rend,user6_tex,NULL,&user6_dest);
        }
        if(numOfUsers>6){
            SDL_RenderCopy(rend,user7_tex,NULL,&user7_dest);
        }
        if(numOfUsers>7){
            SDL_RenderCopy(rend,user8_tex,NULL,&user8_dest);
        }
        boxColor(rend,(windowWidth-boxesWidth)/2,100,(windowWidth+boxesWidth)/2,100+boxesHeight,0x300000ff);
        boxColor(rend,(windowWidth-boxesWidth)/2,150,(windowWidth+boxesWidth)/2,150+boxesHeight,0x300000ff);
        boxColor(rend,(windowWidth-boxesWidth)/2,200,(windowWidth+boxesWidth)/2,200+boxesHeight,0x300000ff);
        boxColor(rend,(windowWidth-boxesWidth)/2,250,(windowWidth+boxesWidth)/2,250+boxesHeight,0x300000ff);
        boxColor(rend,(windowWidth-boxesWidth)/2,300,(windowWidth+boxesWidth)/2,300+boxesHeight,0x300000ff);
        boxColor(rend,(windowWidth-boxesWidth)/2,350,(windowWidth+boxesWidth)/2,350+boxesHeight,0x300000ff);
        boxColor(rend,(windowWidth-boxesWidth)/2,400,(windowWidth+boxesWidth)/2,400+boxesHeight,0x300000ff);
        boxColor(rend,(windowWidth-boxesWidth)/2,450,(windowWidth+boxesWidth)/2,450+boxesHeight,0x300000ff);
        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS); 
    }
    SDL_DestroyTexture(user1_tex);
    if(numOfUsers>1){
        SDL_DestroyTexture(user2_tex);
    }
    if(numOfUsers>2){
        SDL_DestroyTexture(user3_tex);
    }
    if(numOfUsers>3){
        SDL_DestroyTexture(user4_tex);
    }
    if(numOfUsers>4){
        SDL_DestroyTexture(user5_tex);
    }
    if(numOfUsers>5){
        SDL_DestroyTexture(user6_tex);
    }
    if(numOfUsers>6){
        SDL_DestroyTexture(user7_tex);
    }
    if(numOfUsers>7){
        SDL_DestroyTexture(user8_tex);
    }
    TTF_CloseFont(enteredName_font);
    return close;

}

int thirdPageMenu(SDL_Renderer* rend, SDL_Texture* thirdTex, SDL_Texture* fourthTex, SDL_Texture* fifthTex, SDL_Texture* tex, long long int userIndex){
    TTF_Font* enteredName_font=TTF_OpenFont("../resources/Exported Fonts/Annai MN/AnnaiMN.ttf", 15);
    SDL_Color color={0,0,0,255};
    //creating textures
    SDL_Surface* gameName=TTF_RenderText_Solid(enteredName_font,"Map 1",color);
    SDL_Texture* map1_tex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_QueryTexture(map1_tex,NULL,NULL,&map1_dest.w,&map1_dest.h);
    map1_dest.x=(windowWidth-boxesWidth)/2+(boxesWidth-map1_dest.w)/2;
    map1_dest.y=200+(boxesHeight-map1_dest.h)/2;
    gameName=TTF_RenderText_Solid(enteredName_font,"Map 2",color);
    SDL_Texture* map2_tex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_QueryTexture(map2_tex,NULL,NULL,&map2_dest.w,&map2_dest.h);
    map2_dest.x=(windowWidth-boxesWidth)/2+(boxesWidth-map2_dest.w)/2;
    map2_dest.y=250+(boxesHeight-map2_dest.h)/2;
    gameName=TTF_RenderText_Solid(enteredName_font,"Map 3",color);
    SDL_Texture* map3_tex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_QueryTexture(map3_tex,NULL,NULL,&map3_dest.w,&map3_dest.h);
    map3_dest.x=(windowWidth-boxesWidth)/2+(boxesWidth-map3_dest.w)/2;
    map3_dest.y=300+(boxesHeight-map3_dest.h)/2;
    gameName=TTF_RenderText_Solid(enteredName_font,"Map 4",color);
    SDL_Texture* map4_tex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_QueryTexture(map4_tex,NULL,NULL,&map4_dest.w,&map4_dest.h);
    map4_dest.x=(windowWidth-boxesWidth)/2+(boxesWidth-map4_dest.w)/2;
    map4_dest.y=350+(boxesHeight-map4_dest.h)/2;
    gameName=TTF_RenderText_Solid(enteredName_font,"Random Map",color);
    SDL_Texture* randomMap_tex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_QueryTexture(randomMap_tex,NULL,NULL,&randomMap_dest.w,&randomMap_dest.h);
    randomMap_dest.x=(windowWidth-boxesWidth)/2+(boxesWidth-randomMap_dest.w)/2;
    randomMap_dest.y=400+(boxesHeight-randomMap_dest.h)/2;
    gameName=TTF_RenderText_Solid(enteredName_font,"Map 0",color);
    SDL_Texture* memoryMap_tex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_QueryTexture(memoryMap_tex,NULL,NULL,&memoryMap_dest.w,&memoryMap_dest.h);
    memoryMap_dest.x=(windowWidth-boxesWidth)/2+(boxesWidth-memoryMap_dest.w)/2;
    memoryMap_dest.y=150+(boxesHeight-memoryMap_dest.h)/2;


    int close=0;
    SDL_Event event;
    while(close != 1){
        SDL_SetRenderDrawColor(rend,0xff,0xff,0xff,0xff);
        SDL_RenderClear(rend);
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                close=1;
            }
            else if(event.type==SDL_MOUSEBUTTONDOWN){
                if(check_inTheBox((windowWidth-boxesWidth)/2,200)==true){
                    close=startGame(1,rend,userIndex);
                }
                else if(check_inTheBox((windowWidth-boxesWidth)/2,250)==true){
                    close=startGame(2,rend,userIndex);
                }
                else if(check_inTheBox((windowWidth-boxesWidth)/2,300)==true){
                    close=startGame(3,rend,userIndex);
                }
                else if(check_inTheBox((windowWidth-boxesWidth)/2,350)==true){
                    close=startGame(4,rend,userIndex);
                }
                else if(check_inTheBox((windowWidth-boxesWidth)/2,400)==true){
                    close=startGame(5,rend,userIndex);
                }
                else if(check_inTheBox((windowWidth-boxesWidth)/2,150)==true){
                    close=startGame(0,rend,userIndex);
                }
            }
        }
        SDL_RenderCopy(rend,tex,NULL,&dest);
        SDL_RenderCopy(rend,thirdTex,NULL,&thirdDest);
        SDL_RenderCopy(rend,fourthTex,NULL,&fourthDest);
        SDL_RenderCopy(rend,fifthTex,NULL,&fifthDest);
        SDL_RenderCopy(rend,map1_tex,NULL,&map1_dest);
        SDL_RenderCopy(rend,map2_tex,NULL,&map2_dest);
        SDL_RenderCopy(rend,map3_tex,NULL,&map3_dest);
        SDL_RenderCopy(rend,map4_tex,NULL,&map4_dest);
        SDL_RenderCopy(rend,randomMap_tex,NULL,&randomMap_dest);
        SDL_RenderCopy(rend,memoryMap_tex,NULL,&memoryMap_dest);
        boxColor(rend,(windowWidth-boxesWidth)/2,150,(windowWidth+boxesWidth)/2,150+boxesHeight,0x300000ff);
        boxColor(rend,(windowWidth-boxesWidth)/2,200,(windowWidth+boxesWidth)/2,200+boxesHeight,0x300000ff);
        boxColor(rend,(windowWidth-boxesWidth)/2,250,(windowWidth+boxesWidth)/2,250+boxesHeight,0x300000ff);
        boxColor(rend,(windowWidth-boxesWidth)/2,300,(windowWidth+boxesWidth)/2,300+boxesHeight,0x300000ff);
        boxColor(rend,(windowWidth-boxesWidth)/2,350,(windowWidth+boxesWidth)/2,350+boxesHeight,0x300000ff);
        boxColor(rend,(windowWidth-boxesWidth)/2,400,(windowWidth+boxesWidth)/2,400+boxesHeight,0x300000ff);
        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS); 
    }
    SDL_DestroyTexture(map1_tex);
    SDL_DestroyTexture(map2_tex);
    SDL_DestroyTexture(map3_tex);
    SDL_DestroyTexture(map4_tex);
    SDL_DestroyTexture(randomMap_tex);
    TTF_CloseFont(enteredName_font);
    return close;
}

int nextPageMenu(SDL_Renderer* rend, SDL_Texture* thirdTex, SDL_Texture* fourthTex, SDL_Texture* fifthTex, SDL_Texture* tex, long long int userIndex){
    TTF_Font* enteredName_font=TTF_OpenFont("../resources/Exported Fonts/Annai MN/AnnaiMN.ttf", 15);
    SDL_Color color={0,0,0,255};
    //creating textures
    SDL_Surface* gameName=TTF_RenderText_Solid(enteredName_font,"New Game",color);
    SDL_Texture* firstClick_tex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_QueryTexture(firstClick_tex,NULL,NULL,&firstClick.w,&firstClick.h);
    firstClick.x=(windowWidth-boxesWidth)/2+(boxesWidth-firstClick.w)/2;
    firstClick.y=250+(boxesHeight-firstClick.h)/2;
    gameName=TTF_RenderText_Solid(enteredName_font,"Resume Game",color);
    SDL_Texture* secondClick_tex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_QueryTexture(secondClick_tex,NULL,NULL,&secondClick.w,&secondClick.h);
    secondClick.x=(windowWidth-boxesWidth)/2+(boxesWidth-secondClick.w)/2;
    secondClick.y=300+(boxesHeight-secondClick.h)/2;
    gameName=TTF_RenderText_Solid(enteredName_font,"Score Board",color);
    SDL_Texture* thirdClick_tex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_QueryTexture(thirdClick_tex,NULL,NULL,&thirdClick.w,&thirdClick.h);
    thirdClick.x=(windowWidth-boxesWidth)/2+(boxesWidth-thirdClick.w)/2;
    thirdClick.y=350+(boxesHeight-thirdClick.h)/2;


    int close=0;
    SDL_Event event;
    while(close !=1 ){
        SDL_SetRenderDrawColor(rend,0xff,0xff,0xff,0xff);
        SDL_RenderClear(rend);
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                close=1;
            }
            else if(event.type==SDL_MOUSEBUTTONDOWN){
                if(check_inTheBox((windowWidth-boxesWidth)/2,250)==true){
                    close=thirdPageMenu(rend,thirdTex,fourthTex,fifthTex,tex,userIndex);
                }
                else if(check_inTheBox((windowWidth-boxesWidth)/2,350)==true){
                    close=display_scoreBoard(rend,thirdTex,fourthTex,fifthTex,tex,userIndex);
                }
            }
        }
        SDL_RenderCopy(rend,tex,NULL,&dest);
        SDL_RenderCopy(rend,thirdTex,NULL,&thirdDest);
        SDL_RenderCopy(rend,fourthTex,NULL,&fourthDest);
        SDL_RenderCopy(rend,fifthTex,NULL,&fifthDest);
        SDL_RenderCopy(rend,firstClick_tex,NULL,&firstClick);
        SDL_RenderCopy(rend,secondClick_tex,NULL,&secondClick);
        SDL_RenderCopy(rend,thirdClick_tex,NULL,&thirdClick);
        boxColor(rend,(windowWidth-boxesWidth)/2,250,(windowWidth+boxesWidth)/2,250+boxesHeight,0x300000ff);
        boxColor(rend,(windowWidth-boxesWidth)/2,300,(windowWidth+boxesWidth)/2,300+boxesHeight,0x300000ff);
        boxColor(rend,(windowWidth-boxesWidth)/2,350,(windowWidth+boxesWidth)/2,350+boxesHeight,0x300000ff);
        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);   
    }
    SDL_DestroyTexture(firstClick_tex);
    SDL_DestroyTexture(secondClick_tex);
    SDL_DestroyTexture(thirdClick_tex);
    TTF_CloseFont(enteredName_font);
    return close;
}