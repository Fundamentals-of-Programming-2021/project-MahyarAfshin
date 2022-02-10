#include<stdio.h>
#include<string.h>
#include"nextPageMenu.h"

const int windowWidth=600;
const int windowHeight=750;
const int boxesWidth=200;
const int boxesHeight=40;
int mouse_xPosition;
int mouse_yPosition;
color* colors=NULL;
SDL_Rect dest;
SDL_Rect nameDest;
SDL_Rect secondDest;
SDL_Rect thirdDest;
SDL_Rect fourthDest;
SDL_Rect fifthDest;
SDL_Rect firstClick;
SDL_Rect secondClick;
SDL_Rect thirdClick;
SDL_Rect map1_dest;
SDL_Rect map2_dest;
SDL_Rect map3_dest;
SDL_Rect map4_dest;
SDL_Rect randomMap_dest;
SDL_Rect memoryMap_dest;
SDL_Rect user1_dest;
SDL_Rect user2_dest;
SDL_Rect user3_dest;
SDL_Rect user4_dest;
SDL_Rect user5_dest;
SDL_Rect user6_dest;
SDL_Rect user7_dest;
SDL_Rect user8_dest;
potion* potions=NULL;
const int FPS=60;
const int soldiersSpeed=75;
attack* attacks=NULL;
user* users=NULL;
long long int numOfUsers=0;
teams* oponents=NULL;
SDL_Rect randomMap_dest1;
SDL_Rect randomMap_dest2;
SDL_Rect randomMap_dest3;
SDL_Rect randomMap_dest4;

int main(){
    srand(time(0));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    SDL_Window* gameWindow=SDL_CreateWindow("state.io",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowWidth,windowHeight,0);
    SDL_Renderer* rend=SDL_CreateRenderer(gameWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    TTF_Font* font = TTF_OpenFont("../resources/Exported Fonts/Annai MN/AnnaiMN.ttf", 45);
    TTF_Font* font_enterName = TTF_OpenFont("../resources/Exported Fonts/Annai MN/AnnaiMN.ttf", 20);
    TTF_Font* enteredName_font=TTF_OpenFont("../resources/Exported Fonts/Annai MN/AnnaiMN.ttf", 15);
    SDL_SetRenderDrawColor(rend,0xff,0xff,0xff,0xff);
    SDL_RenderClear(rend);

    //creating textures
    SDL_Surface* surface=IMG_Load("../resources/menuFirstPage.png");
    SDL_Texture* tex=SDL_CreateTextureFromSurface(rend,surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(tex,NULL,NULL,&dest.w,&dest.h);
    dest.w=windowWidth;
    dest.h=windowHeight;
    dest.x=0;
    dest.y=0;
    SDL_Color color={0,0,0,255};
    SDL_Surface* gameName=TTF_RenderText_Solid(font,"State.io",color);
    SDL_Texture* nameTex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_QueryTexture(nameTex,NULL,NULL,&nameDest.w,&nameDest.h);
    nameDest.x=(windowWidth-nameDest.w)/2;
    nameDest.y=50;
    gameName=TTF_RenderText_Solid(font_enterName,"please enter your full name here then press enter:",color);
    SDL_Texture* secondTex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_QueryTexture(secondTex,NULL,NULL,&secondDest.w,&secondDest.h);
    secondDest.x=(windowWidth-secondDest.w)/2;
    secondDest.y=200;
    gameName=TTF_RenderText_Solid(enteredName_font,"created by: Mahyar Afshinmehr",color);
    SDL_Texture* thirdTex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_QueryTexture(thirdTex,NULL,NULL,&thirdDest.w,&thirdDest.h);
    thirdDest.x=(windowWidth-thirdDest.w)/2;
    thirdDest.y=550;
    gameName=TTF_RenderText_Solid(enteredName_font,"FOP Final Project Fall 2021",color);
    SDL_Texture* fourthTex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_QueryTexture(fourthTex,NULL,NULL,&fourthDest.w,&fourthDest.h);
    fourthDest.x=(windowWidth-fourthDest.w)/2;
    fourthDest.y=600;
    gameName=TTF_RenderText_Solid(enteredName_font,"student number: 400109735",color);
    SDL_Texture* fifthTex=SDL_CreateTextureFromSurface(rend,gameName);
    SDL_FreeSurface(gameName);
    SDL_QueryTexture(fifthTex,NULL,NULL,&fifthDest.w,&fifthDest.h);
    fifthDest.x=(windowWidth-fifthDest.w)/2;
    fifthDest.y=650;
    
    int close=0;
    SDL_Event event;
    char name[51];
    name[0]='\0';
    while(close != 1){
        SDL_SetRenderDrawColor(rend,0xff,0xff,0xff,0xff);
        SDL_RenderClear(rend);
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                close=1;
            }
            else if(event.type==SDL_TEXTINPUT){
                strcat(name,event.text.text);
            }
            else if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_BACKSPACE && strlen(name)){
                name[strlen(name)-1]='\0';
            }
            else if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_RETURN && strlen(name)){
                long long int userIndex=add_new_user(name);
                close=nextPageMenu(rend,thirdTex,fourthTex,fifthTex,tex,userIndex);
            }
        }
        SDL_RenderCopy(rend,tex,NULL,&dest);
        SDL_RenderCopy(rend,nameTex,NULL,&nameDest);
        SDL_RenderCopy(rend,secondTex,NULL,&secondDest);
        SDL_RenderCopy(rend,thirdTex,NULL,&thirdDest);
        SDL_RenderCopy(rend,fourthTex,NULL,&fourthDest);
        SDL_RenderCopy(rend,fifthTex,NULL,&fifthDest);
        boxColor(rend,secondDest.x-1,250,secondDest.x+486,290,0x300000ff);
        typeTheEnteredName(name,secondDest,color,rend,enteredName_font);
        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);
    }
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(nameTex);
    SDL_DestroyTexture(secondTex);
    SDL_DestroyTexture(thirdTex);
    SDL_DestroyTexture(fourthTex);
    SDL_DestroyTexture(fifthTex);
    TTF_CloseFont(font_enterName);
    TTF_CloseFont(enteredName_font);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(gameWindow);
    TTF_Quit();
    SDL_Quit();
    return 0;
}