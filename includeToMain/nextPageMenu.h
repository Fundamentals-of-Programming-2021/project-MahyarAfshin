#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#include "map.h"

const int windowWidth=600;
const int windowHeight=750;
int mouse_xPosition;
int mouse_yPosition;
const int boxesWidth=200;
const int boxesHeight=40;
SDL_Rect dest;
SDL_Rect nameDest;
SDL_Rect secondDest;
SDL_Rect thirdDest;
SDL_Rect fourthDest;
SDL_Rect fifthDest;
SDL_Rect firstClick;
SDL_Rect secondClick;
SDL_Rect thirdClick;

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

int nextPageMenu(SDL_Renderer* rend, SDL_Texture* thirdTex, SDL_Texture* fourthTex, SDL_Texture* fifthTex, SDL_Texture* tex ){
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