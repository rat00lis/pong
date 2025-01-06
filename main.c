#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <time.h>
#include "menu.h"
#include <unistd.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
int anchochem=150;
int altochem=150;
int directionx=1;

int bounce(SDL_Rect a, SDL_Rect b);

int main(){

    SDL_Window* window = NULL;
    SDL_Texture* cheemsizq = NULL;
    SDL_Texture* cheemsder = NULL;
    SDL_Texture* table = NULL;
    SDL_Texture* ball = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event;
    SDL_Surface* surface = NULL;
    SDL_Texture* puntajes1 = NULL;
    SDL_Texture* puntajes2 = NULL;
    SDL_Texture* ganadore = NULL;
    int delay = 0;
    int directionx = 1;
    int directiony = 0;
    int run = true;
    int runmenu = 0;
    int color = 1, color1 = 1, points = 5, speed = 1, controlmusic = 0; 
    int switchmusic = 0;
    int p1=0,p2=0;
    const unsigned char *key;
    srand(time(NULL));
    
    key = SDL_GetKeyboardState(NULL);
      
    if (SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }else{
        window = SDL_CreateWindow("Pong",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL){
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }else{
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            table = IMG_LoadTexture(renderer,"images/table.png");
            ball = IMG_LoadTexture(renderer,"images/ball.png");
            puntajes2 = IMG_LoadTexture(renderer,"images/num/num0.png");            
            puntajes1 = IMG_LoadTexture(renderer,"images/num/num0.png"); 
            
            if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0){
                printf("%s", Mix_GetError());
            }
            
            Mix_Music *musicmenu = Mix_LoadMUS("sounds/ameno.mp3");
            Mix_Music *musicgame = Mix_LoadMUS("sounds/musicgame.mp3");
            Mix_Chunk *bonk = Mix_LoadWAV("sounds/bonk.mp3");
            Mix_Chunk *updown = Mix_LoadWAV("sounds/updown.mp3");
            Mix_Chunk *select = Mix_LoadWAV("sounds/select.mp3");
            Mix_AllocateChannels(10);
            SDL_Rect ganador;
            ganador.x=450;
            ganador.y=200;
            ganador.w=400;
            ganador.h=365;
            SDL_Rect puntaje1;
            puntaje1.x=510;
            puntaje1.y=100;
            puntaje1.w=80;
            puntaje1.h=95;
            SDL_Rect puntaje2;
            puntaje2.x=685;
            puntaje2.y=100;
            puntaje2.w=80;
            puntaje2.h=95;
            SDL_Rect rectable;
            rectable.x = 0;
            rectable.y = 0;
            rectable.w = 1280;
            rectable.h = 720;
            SDL_Rect paddle1;
            paddle1.x = 50; 
            paddle1.y = 300; 
            paddle1.w = 150; 
            paddle1.h = 150; 
            SDL_Rect paddle2;
            paddle2.x = 1075; 
            paddle2.y = 300; 
            paddle2.w = 150;
            paddle2.h = 150; 
            SDL_Rect rectball; 
            rectball.x = 600; 
            rectball.y = 350; 
            rectball.w = 50; 
            rectball.h = 50; 

            while (run){
                if (controlmusic == 0){
                    Mix_PlayMusic(musicmenu,-1);
                }
                while (runmenu == 0){
                    runmenu = controller(runmenu, renderer, updown, select,&color, &color1, &points, &speed, &controlmusic);
                    if (runmenu == -1){
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        return 0;
                    }
                    Mix_PauseMusic();
                    Mix_PlayMusic(musicgame,-1);
                    Mix_VolumeMusic(30); 
                }  
                switch (color){
                    case 1: 
                        cheemsizq = IMG_LoadTexture(renderer,"images/cheems1c1.png");
                        break;
                    case 2:
                        cheemsizq = IMG_LoadTexture(renderer,"images/cheems1c2.png");
                        break;
                    case 3:
                        cheemsizq = IMG_LoadTexture(renderer,"images/cheems1c3.png");
                        break;
                    case 4:
                        cheemsizq = IMG_LoadTexture(renderer,"images/cheems1c4.png");
                        break;
                }
                switch (color1){
                    case 1: 
                        cheemsder = IMG_LoadTexture(renderer,"images/cheems2c1.png");
                        break;
                    case 2:
                        cheemsder = IMG_LoadTexture(renderer,"images/cheems2c2.png");
                        break;
                    case 3:
                        cheemsder = IMG_LoadTexture(renderer,"images/cheems2c3.png");
                        break;
                    case 4:
                        cheemsder = IMG_LoadTexture(renderer,"images/cheems2c4.png");
                        break;
                }
                while (SDL_PollEvent(&event)){
                    if (event.type == SDL_QUIT){
                        run = false;
                    }
                    if (event.type == SDL_KEYDOWN){
                            if (key[SDL_SCANCODE_UP])
                            {
                                if (paddle2.y != -20)
                                {
                                    paddle2.y -= 20;
                                }
                            }
                            if (key[SDL_SCANCODE_DOWN])
                            {

                                if (paddle2.y != 620)
                                {
                                    paddle2.y += 20;
                                }
                                
                            }
                            if (key[SDL_SCANCODE_W])
                            {
                                if (paddle1.y != -20)
                                {
                                    paddle1.y -= 20;
                                }

                            }
                            if (key[SDL_SCANCODE_S])
                            {
                                if (paddle1.y != 620)
                                {
                                    paddle1.y += 20;
                                }
                            } 
                    }
                }
                if (delay == 1){ 
                    rectball.y+=directiony;
                    if (rectball.y - 20 >= 630 || rectball.y<=0){
                        directiony=-directiony;
                    }
                    if (directionx == 1){ 
                        rectball.x += speed*4;
                        if (rectball.x-30 >= 1260){
                            p1++;

                            if(p1==1)
                            {
                                puntajes1=IMG_LoadTexture(renderer,"images/num/num1.png");
                            }
                            if(p1==2)
                            {
                                puntajes1=IMG_LoadTexture(renderer,"images/num/num2.png");
                            }
                            if(p1==3)
                            {
                               puntajes1=IMG_LoadTexture(renderer,"images/num/num3.png");
                            }
                            if(p1==4)
                            {
                                puntajes1=IMG_LoadTexture(renderer,"images/num/num4.png");
                            }
                            if(p1==5)
                            {
                                puntajes1=IMG_LoadTexture(renderer,"images/num/num5.png");
                            }
                            if(p1==6)
                            {
                                puntajes1=IMG_LoadTexture(renderer,"images/num/num6.png");
                            }
                            if(p1==7)
                            {
                                puntajes1=IMG_LoadTexture(renderer,"images/num/num7.png");
                            }
                            if(p1==8)
                            {
                                puntajes1=IMG_LoadTexture(renderer,"images/num/num8.png");
                            }
                            if(p1==9)
                            {
                                puntajes1=IMG_LoadTexture(renderer,"images/num/num9.png");
                            }
                            paddle1.x = 50;
                            paddle1.y = 300;
                            paddle2.x = 1075;
                            paddle2.y = 300;
                            Uint32 timer = SDL_GetTicks() + 1000;
                            while (!SDL_TICKS_PASSED(SDL_GetTicks(),timer)){
                                rectball.x = 600;
                                rectball.y = 350;
                            }
                            switch (rand()%2)
                            {
                            case 0:
                                directiony = rand()%2;
                                break;
                            case 1: 
                                directiony = -rand()%2;
                                break;
                            }
                        }    
                        if (bounce(rectball,paddle2)!=99){
                            Mix_PlayChannel(3, bonk, 0);
                            Mix_Volume(3,128);
                            directiony=bounce(rectball,paddle2);
                            directionx=-directionx;
                        }
                    }
                    if (directionx == -1){ 
                        rectball.x -= speed*4;
                        if (rectball.x+30 <= 0){
                            p2++;
                            if(p2==1)
                            {
                                puntajes2=IMG_LoadTexture(renderer,"images/num/num1.png");
                            }
                            if(p2==2)
                            {
                                puntajes2=IMG_LoadTexture(renderer,"images/num/num2.png");
                            }
                            if(p2==3)
                            {
                               puntajes2=IMG_LoadTexture(renderer,"images/num/num3.png");
                            }
                            if(p2==4)
                            {
                                puntajes2=IMG_LoadTexture(renderer,"images/num/num4.png");
                            }
                            if(p2==5)
                            {
                                puntajes2=IMG_LoadTexture(renderer,"images/num/num5.png");
                            }
                            if(p2==6)
                            {
                                puntajes2=IMG_LoadTexture(renderer,"images/num/num6.png");
                            }
                            if(p2==7)
                            {
                                puntajes2=IMG_LoadTexture(renderer,"images/num/num7.png");
                            }
                            if(p2==8)
                            {
                                puntajes2=IMG_LoadTexture(renderer,"images/num/num8.png");
                            }
                            if(p2==9)
                            {
                                puntajes2=IMG_LoadTexture(renderer,"images/num/num9.png");
                            }
                            paddle1.x = 50;
                            paddle1.y = 300;
                            paddle2.x = 1075;
                            paddle2.y = 300;
                            Uint32 timer = SDL_GetTicks() + 1000;
                            while (!SDL_TICKS_PASSED(SDL_GetTicks(),timer)){
                                rectball.x = 600;
                                rectball.y = 350;
                            }
                            switch (rand()%2)
                            {
                            case 0:
                                directiony = rand()%2;
                                break;
                            case 1: 
                                directiony = -rand()%2;
                                break;
                            }
                        } 
                        if (bounce(rectball,paddle1)!=99){
                            Mix_PlayChannel(3, bonk, 0);
                            Mix_Volume(3,128);
                            directiony=bounce(rectball,paddle1);
                            directionx=-directionx;
                        }
                    }
                    delay = 0;
                }
                delay++;
                
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer,table,NULL,&rectable);
                SDL_RenderCopy(renderer,puntajes1,NULL,&puntaje1);
                SDL_RenderCopy(renderer,puntajes2,NULL,&puntaje2);
                SDL_RenderCopy(renderer,cheemsizq,NULL,&paddle1);
                SDL_RenderCopy(renderer,cheemsder,NULL,&paddle2);
                SDL_RenderCopy(renderer,ball,NULL,&rectball);
                if(p1==points)
                {
                                
                    table = IMG_LoadTexture(renderer,"images/tableblur.png");
                    SDL_RenderCopy(renderer,table,NULL,&rectable);
                    directionx=0;
                    if(color==1)
                    {
                        ganadore=IMG_LoadTexture(renderer,"images/bonk/1bonk1.png");
                    }
                    if(color==2)
                    {
                        ganadore=IMG_LoadTexture(renderer,"images/bonk/1bonk2.png");
                    }
                    if(color==3)
                    {
                        ganadore=IMG_LoadTexture(renderer,"images/bonk/1bonk3.png");
                    }
                    if(color==4)
                    {
                        ganadore=IMG_LoadTexture(renderer,"images/bonk/1bonk4.png");
                    }
                                     
                }
                if(p2==points)
                {
                    table = IMG_LoadTexture(renderer,"images/tableblur.png");
                    SDL_RenderCopy(renderer,table,NULL,&rectable);
                    directionx=0;
                    if(color1==1)
                    {
                        ganadore=IMG_LoadTexture(renderer,"images/bonk/2bonk1.png");
                    }
                    if(color1==2)
                    {
                        ganadore=IMG_LoadTexture(renderer,"images/bonk/2bonk2.png");
                    }
                    if(color1==3)
                    {
                        ganadore=IMG_LoadTexture(renderer,"images/bonk/2bonk3.png");
                    }
                    if(color1==4)
                    {
                        ganadore=IMG_LoadTexture(renderer,"images/bonk/2bonk4.png");
                    }
                                
                    
                                    
                }
                SDL_RenderCopy(renderer,ganadore,NULL,&ganador);
                SDL_RenderPresent(renderer);
            }
        }            
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}

int bounce(SDL_Rect a, SDL_Rect b)
{
    if(a.x>=b.x+anchochem || a.x+50 <= b.x
        || a.y>=b.y+altochem || a.y+50<b.y)
    {
        return 99;
    }
    else
    {
        if(b.x>=5)
        {
            if(a.x<=b.x+(anchochem/2)&&a.x+50 >= b.x)
            {
                if(a.y<=b.y+(altochem/3)&&a.y+50>=b.y)
                {
                    return -2;
                }
                if(a.y<=b.y+(2*(altochem/3))&&a.y+50>=b.y+(altochem/3))
                {
                    return 0;
                }
                if(a.y<=b.y+altochem&&a.y+50>=b.y+(2*(altochem/3)))
                {
                    return 2;
                }
            }
            if(a.x<=b.x+anchochem &&a.x+50 >= b.x+(anchochem/2))
            {
                if(a.y<=b.y+(altochem/3)&&a.y+50>=b.y)
                {
                    return -3;
                }
                if(a.y<=b.y+(2*(altochem/3))&&a.y+50>=b.y+(altochem/3))
                {
                    return 0;
                }
                if(a.y<=b.y+altochem&&a.y+50>=b.y+(2*(altochem/3)))
                {
                    return 3;
                }
            }
        }
        else
        {
            if(a.x<=b.x+(anchochem/2)&&a.x+50 >= b.x)
            {
                if(a.y<=b.y+(altochem/3)&&a.y+50>=b.y)
                {
                    return -3;
                }
                if(a.y<=b.y+(2*(altochem/3))&&a.y+50>=b.y+(altochem/3))
                {
                    return 0;
                }
                if(a.y<=b.y+altochem&&a.y+50>=b.y+(2*(altochem/3)))
                {
                    return 3;
                }
            }
            if(a.x<=b.x+anchochem &&a.x+50 >= b.x+(anchochem/2))
            {
                if(a.y<=b.y+(altochem/3)&&a.y+50>=b.y)
                {
                    return -2;
                }
                if(a.y<=b.y+(2*(altochem/3))&&a.y+50>=b.y+(altochem/3))
                {
                    return 0;
                }
                if(a.y<=b.y+altochem&&a.y+50>=b.y+(2*(altochem/3)))
                {
                    return 2;
                }
            }
        }
    }
}


