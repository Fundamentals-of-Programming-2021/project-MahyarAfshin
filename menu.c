#include<stdio.h>
#include<SDL2/SDL_ttf.h>
#include "map.h"

const int windowWidth=600;
const int windowHeight=750;
int mouse_xPosition;
int mouse_yPosition;

int main(){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    SDL_Window* gameWindow=SDL_CreateWindow("state.io",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowWidth,windowHeight,0);
    SDL_Renderer* rend=SDL_CreateRenderer(gameWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    TTF_Font* font = TTF_OpenFont("arial.ttf", 25);
    SDL_SetRenderDrawColor(rend,0xff,0xff,0xff,0xff);
    SDL_RenderClear(rend);
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
        SDL_Surface* image=SDL_LoadBMP("../menuWallpaper.bmp");
        SDL_Texture* tex=SDL_CreateTextureFromSurface(rend,image);
        SDL_FreeSurface(image);
        SDL_Rect destination;
        SDL_QueryTexture(tex,NULL,NULL,&destination.w,&destination.h);
        destination.w=windowWidth;
        destination.h=windowHeight;
        SDL_RenderCopy(rend,tex,NULL,&destination);
        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);
    }
    TTF_CloseFont(font);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(gameWindow);
    TTF_Quit();
    SDL_Quit();
    return 0;
}