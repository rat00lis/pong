#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <SDL2/SDL_mixer.h>

int submenu_play(SDL_Renderer* renderer, Mix_Chunk *updown, Mix_Chunk *select, int* color, int* color1, int* points); 
int submenu_settings(SDL_Renderer* renderer, Mix_Chunk *updown, Mix_Chunk *select, int* speed, int* music);  
int submenu_exit(SDL_Renderer* renderer, Mix_Chunk *updown, Mix_Chunk *select);    
int menu(SDL_Renderer* renderer, Mix_Chunk *updown, Mix_Chunk *select);            
int controller(int op, SDL_Renderer* renderer, Mix_Chunk *updown, Mix_Chunk *select, int* color, int* color1, int* points, int* speed, int* music); 

int controller(int op, SDL_Renderer* renderer, Mix_Chunk *updown, Mix_Chunk *select, int* color, int* color1, int* points, int* speed, int* music){

    if (op == 0) op = menu(renderer,updown,select);
    if (op == 1) op = submenu_play(renderer,updown,select,color,color1,points);
    if (op == 2) op = submenu_settings(renderer,updown,select,speed,music);
    if (op == 3) op = submenu_exit(renderer,updown,select);
    if (op == 4) return 1;
    if (op == 5) return -1;

}

int menu (SDL_Renderer* renderer, Mix_Chunk *updown, Mix_Chunk *select){
   
    SDL_Texture* background = NULL;
    SDL_Texture* menuplay = NULL;
    SDL_Texture* menusettings = NULL;
    SDL_Texture* menuexit = NULL;
    SDL_Texture* arrows = NULL; 

    SDL_Rect rect_background; rect_background.w = 1280; rect_background.h = 720; rect_background.x = 0; rect_background.y = 0;
    SDL_Rect rect_play; rect_play.w = 240; rect_play.h = 80; rect_play.x = 520; rect_play.y = 320;
    SDL_Rect rect_settings; rect_settings.w = 240; rect_settings.h = 80; rect_settings.x = 520; rect_settings.y = 440;
    SDL_Rect rect_exit; rect_exit.w = 240; rect_exit.h = 80; rect_exit.x = 520; rect_exit.y = 560;

    int runmenu = true;
    int parameter = 0;
    SDL_Event event;
    const unsigned char* key;
    key = SDL_GetKeyboardState(NULL);

    background = IMG_LoadTexture(renderer,"menuimages/background1.png"); 
    menuplay = IMG_LoadTexture(renderer,"menuimages/selectedplay.png");
    menusettings = IMG_LoadTexture(renderer,"menuimages/settings.png");
    menuexit = IMG_LoadTexture(renderer,"menuimages/exit.png");

    while (runmenu){ 
        if (event.type == SDL_QUIT){
                return 5;
        }
        if (parameter == 0){
            menuplay = IMG_LoadTexture(renderer,"menuimages/selectedplay.png");
        }else{
            menuplay = IMG_LoadTexture(renderer,"menuimages/play.png");
        }
        if (parameter == 1){
            menusettings = IMG_LoadTexture(renderer,"menuimages/selectedsettings.png");
        }else{
            menusettings = IMG_LoadTexture(renderer,"menuimages/settings.png");
        }
        if (parameter == 2){
            menuexit = IMG_LoadTexture(renderer,"menuimages/selectedexit.png");
        }else{
            menuexit = IMG_LoadTexture(renderer,"menuimages/exit.png");
        }       

        while (SDL_PollEvent(&event)){
            if (event.type == SDL_KEYDOWN){
                if (key[SDL_SCANCODE_UP] && parameter == 0){
                    Mix_PlayChannel(-1,updown,0);
                    parameter = 2;
                }else if (key[SDL_SCANCODE_UP]){
                    Mix_PlayChannel(-1,updown,0);
                    parameter--;
                }
                if (key[SDL_SCANCODE_DOWN] && parameter == 2){
                    Mix_PlayChannel(-1,updown,0);
                    parameter = 0;
                }else if (key[SDL_SCANCODE_DOWN]){
                    Mix_PlayChannel(-1,updown,0);                   
                    parameter++;
                }
                if (key[SDL_SCANCODE_ESCAPE]) return 3;
                if (key[SDL_SCANCODE_SPACE] && parameter == 0){ 
                    Mix_PlayChannel(-1,select,0);
                    return 1; 
                }
                if (key[SDL_SCANCODE_SPACE] && parameter == 1){ 
                    Mix_PlayChannel(-1,select,0);
                    return 2; 
                }
                if (key[SDL_SCANCODE_SPACE] && parameter == 2){ 
                    Mix_PlayChannel(-1,select,0);
                    return 3; 
                }
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,background,NULL,&rect_background);
        SDL_RenderCopy(renderer,menusettings,NULL,&rect_settings);
        SDL_RenderCopy(renderer,menuplay,NULL,&rect_play);
        SDL_RenderCopy(renderer,menuexit,NULL,&rect_exit);
        SDL_RenderPresent(renderer);
    }
}

int submenu_play(SDL_Renderer* renderer, Mix_Chunk *updown, Mix_Chunk *select, int* color, int* color1, int* points){

    SDL_Texture* play = NULL;
    SDL_Texture* background = NULL;
    SDL_Texture* menuback = NULL;
    SDL_Texture* menuselectpoints = NULL;
    SDL_Texture* menuselectcolor = NULL;
    SDL_Texture* menuselectcolor1 = NULL;

    SDL_Rect rect_background; rect_background.w = 1280; rect_background.h = 720; rect_background.x = 0; rect_background.y = 0;
    SDL_Rect rect_play; rect_play.w = 240; rect_play.h = 80; rect_play.x = 520; rect_play.y = 195;
    SDL_Rect rect_back; rect_back.w = 240; rect_back.h = 80; rect_back.x = 520; rect_back.y = 595;
    SDL_Rect rect_selectpoints; rect_selectpoints.w = 315; rect_selectpoints.h = 80; rect_selectpoints.x = 483; rect_selectpoints.y = 295;
    SDL_Rect rect_selectcolor; rect_selectcolor.w = 315; rect_selectcolor.h = 80; rect_selectcolor.x = 483; rect_selectcolor.y = 395;
    SDL_Rect rect_selectcolor1; rect_selectcolor1.w = 315; rect_selectcolor1.h = 80; rect_selectcolor1.x = 483; rect_selectcolor1.y = 495;

    background = IMG_LoadTexture(renderer,"menuimages/playmenu.png"); 
    play = IMG_LoadTexture(renderer,"menuimages/selectedplay.png");
    menuselectpoints = IMG_LoadTexture(renderer,"menuimages/points5.png");
    menuselectcolor = IMG_LoadTexture(renderer,"menuimages/color1.png");
    menuselectcolor1 = IMG_LoadTexture(renderer,"menuimages/color2.png");
    menuback = IMG_LoadTexture(renderer,"menuimages/exit.png");

    int copycolor = *color;
    int copycolor1 = *color1;
    int copypoints = *points;

    int runmenu = true;
    int parameter = 0;
    SDL_Event event;
    const unsigned char* key;
    key = SDL_GetKeyboardState(NULL);

    while (runmenu){
        if (parameter == 0){
            play = IMG_LoadTexture(renderer,"menuimages/selectedplay.png");
        }else{
            play = IMG_LoadTexture(renderer,"menuimages/play.png");
        }
        if (parameter == 1){
            if (copypoints == 5){
                menuselectpoints = IMG_LoadTexture(renderer,"menuimages/selectedpoints5.png");     
            }
            if (copypoints == 6){
                menuselectpoints = IMG_LoadTexture(renderer,"menuimages/selectedpoints6.png");    
            }
            if (copypoints == 7){
                menuselectpoints = IMG_LoadTexture(renderer,"menuimages/selectedpoints7.png");
            }
            if (copypoints == 8){
                menuselectpoints = IMG_LoadTexture(renderer,"menuimages/selectedpoints8.png");
            }
            if (copypoints == 9){
                menuselectpoints = IMG_LoadTexture(renderer,"menuimages/selectedpoints9.png");
            }
        }else{
            if (copypoints == 5){
                menuselectpoints = IMG_LoadTexture(renderer,"menuimages/points5.png");     
            }
            if (copypoints == 6){
                menuselectpoints = IMG_LoadTexture(renderer,"menuimages/points6.png");    
            }
            if (copypoints == 7){
                menuselectpoints = IMG_LoadTexture(renderer,"menuimages/points7.png");
            }
            if (copypoints == 8){
                menuselectpoints = IMG_LoadTexture(renderer,"menuimages/points8.png");
            }
            if (copypoints == 9){
                menuselectpoints = IMG_LoadTexture(renderer,"menuimages/points9.png");
            }
        }
        if (parameter == 2){
            if (copycolor == 1){
                menuselectcolor = IMG_LoadTexture(renderer,"menuimages/selectedp1color1.png");     
            }
            if (copycolor == 2){
                menuselectcolor = IMG_LoadTexture(renderer,"menuimages/selectedp1color2.png");    
            }
            if (copycolor == 3){
                menuselectcolor = IMG_LoadTexture(renderer,"menuimages/selectedp1color3.png");
            }
            if (copycolor == 4){
                menuselectcolor = IMG_LoadTexture(renderer,"menuimages/selectedp1color4.png");
            }
        }else{
            if (copycolor == 1){
                menuselectcolor = IMG_LoadTexture(renderer,"menuimages/p1color1.png");     
            }
            if (copycolor == 2){
                menuselectcolor = IMG_LoadTexture(renderer,"menuimages/p1color2.png");    
            }
            if (copycolor == 3){
                menuselectcolor = IMG_LoadTexture(renderer,"menuimages/p1color3.png");
            }
            if (copycolor == 4){
                menuselectcolor = IMG_LoadTexture(renderer,"menuimages/p1color4.png");
            }
        }  
        if (parameter == 3){
            if (copycolor1 == 1){
                menuselectcolor1 = IMG_LoadTexture(renderer,"menuimages/selectedp2color1.png");     
            }
            if (copycolor1 == 2){
                menuselectcolor1 = IMG_LoadTexture(renderer,"menuimages/selectedp2color2.png");    
            }
            if (copycolor1 == 3){
                menuselectcolor1 = IMG_LoadTexture(renderer,"menuimages/selectedp2color3.png");
            }
            if (copycolor1 == 4){
                menuselectcolor1 = IMG_LoadTexture(renderer,"menuimages/selectedp2color4.png");
            }
        }else{
            if (copycolor1 == 1){
                menuselectcolor1 = IMG_LoadTexture(renderer,"menuimages/p2color1.png");     
            }
            if (copycolor1 == 2){
                menuselectcolor1 = IMG_LoadTexture(renderer,"menuimages/p2color2.png");    
            }
            if (copycolor1 == 3){
                menuselectcolor1 = IMG_LoadTexture(renderer,"menuimages/p2color3.png");
            }
            if (copycolor1 == 4){
                menuselectcolor1 = IMG_LoadTexture(renderer,"menuimages/p2color4.png");
            }
        }  
        if (parameter == 4){
            menuback = IMG_LoadTexture(renderer,"menuimages/selectedback.png");
        }else{
            menuback = IMG_LoadTexture(renderer,"menuimages/back.png");
        }

        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                return 5;
            }
            if (event.type == SDL_KEYDOWN){

                if (key[SDL_SCANCODE_UP] && parameter == 0){
                    Mix_PlayChannel(-1,updown,0);
                    parameter = 4;
                }else if (key[SDL_SCANCODE_UP]){
                    Mix_PlayChannel(-1,updown,0);
                    parameter--;
                }
                if (key[SDL_SCANCODE_DOWN] && parameter == 4){
                    Mix_PlayChannel(-1,updown,0);
                    parameter = 0;
                }else if (key[SDL_SCANCODE_DOWN]){
                    Mix_PlayChannel(-1,updown,0);
                    parameter++;
                }

                if (parameter == 1){
                    if (key[SDL_SCANCODE_RIGHT] && copypoints == 9){
                        Mix_PlayChannel(-1,updown,0);
                        copypoints = 5;
                    }else if (key[SDL_SCANCODE_RIGHT]){
                        Mix_PlayChannel(-1,updown,0);
                        copypoints++; 
                    }
                    if (key[SDL_SCANCODE_LEFT] && copypoints == 5){
                        Mix_PlayChannel(-1,updown,0);
                        copypoints = 9;
                    }else if (key[SDL_SCANCODE_LEFT]){
                        Mix_PlayChannel(-1,updown,0);
                        copypoints--;
                    }
                }
                if (parameter == 2){
                    if (key[SDL_SCANCODE_RIGHT] && copycolor == 4){
                        Mix_PlayChannel(-1,updown,0);
                        copycolor = 1;
                    }else if (key[SDL_SCANCODE_RIGHT]){
                        Mix_PlayChannel(-1,updown,0);
                        copycolor++;
                    }
                    if (key[SDL_SCANCODE_LEFT] && copycolor == 1){
                        Mix_PlayChannel(-1,updown,0);
                        copycolor = 4;
                    }else if (key[SDL_SCANCODE_LEFT]){
                        Mix_PlayChannel(-1,updown,0);
                        copycolor--;
                    }
                }
                if (parameter == 3){
                    if (key[SDL_SCANCODE_RIGHT] && copycolor1 == 4){
                        Mix_PlayChannel(-1,updown,0);
                        copycolor1 = 1;
                    }else if (key[SDL_SCANCODE_RIGHT]){
                        Mix_PlayChannel(-1,updown,0);
                        copycolor1++;
                    }
                    if (key[SDL_SCANCODE_LEFT] && copycolor1 == 1){
                        Mix_PlayChannel(-1,updown,0);
                        copycolor1 = 4;
                    }else if (key[SDL_SCANCODE_LEFT]){
                        Mix_PlayChannel(-1,updown,0);
                        copycolor1--;
                    }
                }
                if (parameter == 0){
                    if (key[SDL_SCANCODE_SPACE]){
                        Mix_PlayChannel(-1,select,0);
                        *color = copycolor;
                        *color1 = copycolor1;
                        *points = copypoints;
                        return 4;
                    }
                }
                if (parameter == 4){
                    if (key[SDL_SCANCODE_SPACE]){
                        Mix_PlayChannel(-1,select,0);
                        *color = copycolor;
                        *color1 = copycolor1;
                        *points = copypoints;
                        return 0;
                    }
                }
                if (key[SDL_SCANCODE_ESCAPE]){
                    Mix_PlayChannel(-1,select,0);
                    *color = copycolor;
                    *color1 = copycolor1;
                    *points = copypoints;
                    return 0;
                }
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,background,NULL,&rect_background);
        SDL_RenderCopy(renderer,play,NULL,&rect_play);
        SDL_RenderCopy(renderer,menuback,NULL,&rect_back);
        SDL_RenderCopy(renderer,menuselectpoints,NULL,&rect_selectpoints);
        SDL_RenderCopy(renderer,menuselectcolor,NULL,&rect_selectcolor);
        SDL_RenderCopy(renderer,menuselectcolor1,NULL,&rect_selectcolor1);
        SDL_RenderPresent(renderer);
    }
}

int submenu_settings(SDL_Renderer* renderer, Mix_Chunk *updown, Mix_Chunk *select, int* speed, int* music){
   
    SDL_Texture* background = NULL;
    SDL_Texture* menuback = NULL;
    SDL_Texture* menuspeed = NULL;
    SDL_Texture* menumusic = NULL;

    SDL_Rect rect_background; rect_background.w = 1280; rect_background.h = 720; rect_background.x = 0; rect_background.y = 0;
    SDL_Rect rect_back; rect_back.w = 240; rect_back.h = 80; rect_back.x = 520; rect_back.y = 450;
    SDL_Rect rect_speed; rect_speed.w = 259; rect_speed.h = 80; rect_speed.x = 510; rect_speed.y = 250;
    SDL_Rect rect_music; rect_music.w = 390; rect_music.h = 80; rect_music.x = 445; rect_music.y = 350;

    background = IMG_LoadTexture(renderer,"menuimages/settingsmenu.png"); 
    menuspeed = IMG_LoadTexture(renderer,"menuimages/selectedspeed1.png");
    menumusic = IMG_LoadTexture(renderer,"menuimages/musiconoff.png");
    menuback = IMG_LoadTexture(renderer,"menuimages/back.png");

    int copyspeed = *speed;
    int copymusic = *music;

    int runmenu = true;
    int parameter = 0;
    SDL_Event event;
    const unsigned char* key;
    key = SDL_GetKeyboardState(NULL);

    while (runmenu){
        if (parameter == 0){
            if (copyspeed == 1){
                 menuspeed = IMG_LoadTexture(renderer,"menuimages/selectedspeed1.png");     
            }
            if (copyspeed == 2){
                menuspeed = IMG_LoadTexture(renderer,"menuimages/selectedspeed2.png");    
            }
            if (copyspeed == 3){
                menuspeed = IMG_LoadTexture(renderer,"menuimages/selectedspeed3.png");
            }
        }else{ 
            if (copyspeed == 1){
                menuspeed = IMG_LoadTexture(renderer,"menuimages/speed1.png");
            }
            if (copyspeed == 2){
                menuspeed = IMG_LoadTexture(renderer,"menuimages/speed2.png");
            }
            if (copyspeed == 3){
                menuspeed = IMG_LoadTexture(renderer,"menuimages/speed3.png");
            }
        }
        if (parameter == 1){
            if (copymusic ==  0){ 
                menumusic = IMG_LoadTexture(renderer,"menuimages/selectedmusicon.png");
            }
            if (copymusic == 1){
                menumusic = IMG_LoadTexture(renderer,"menuimages/selectedmusicoff.png");
            }
        }else{
            if (copymusic ==  0){ 
                menumusic = IMG_LoadTexture(renderer,"menuimages/musicon.png");
            }
            if (copymusic == 1){
                menumusic = IMG_LoadTexture(renderer,"menuimages/musicoff.png");
            }
        }
        if (parameter == 2){
            menuback = IMG_LoadTexture(renderer,"menuimages/selectedback.png");
        }else{
            menuback = IMG_LoadTexture(renderer,"menuimages/back.png");
        }   
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                return 5;
            }
            if (event.type == SDL_KEYDOWN){
                if (key[SDL_SCANCODE_UP] && parameter == 0){
                    Mix_PlayChannel(-1,updown,0);
                    parameter = 2;
                }else if (key[SDL_SCANCODE_UP]){
                    Mix_PlayChannel(-1,updown,0);
                    parameter--;
                }
                if (key[SDL_SCANCODE_DOWN] && parameter == 2){
                    Mix_PlayChannel(-1,updown,0);
                    parameter = 0;
                }else if (key[SDL_SCANCODE_DOWN]){
                    Mix_PlayChannel(-1,updown,0);
                    parameter++;
                }

                if (parameter == 0){
                    if (key[SDL_SCANCODE_RIGHT] && copyspeed == 3){
                        Mix_PlayChannel(-1,updown,0);
                        copyspeed = 1;
                    }else if (key[SDL_SCANCODE_RIGHT]){
                        Mix_PlayChannel(-1,updown,0);
                        copyspeed++;
                    } 
                    if (key[SDL_SCANCODE_LEFT] && copyspeed == 1){
                        Mix_PlayChannel(-1,updown,0);
                        copyspeed = 3;
                    }else if (key[SDL_SCANCODE_LEFT]){
                        Mix_PlayChannel(-1,updown,0);
                        copyspeed--;
                    }
                }
                if (parameter == 1){
                    if (key[SDL_SCANCODE_RIGHT] && copymusic == 1){
                        Mix_PlayChannel(-1,updown,0);
                        copymusic = 0;
                    }else if (key[SDL_SCANCODE_RIGHT]){
                        Mix_PlayChannel(-1,updown,0);
                        copymusic++;
                    }
                    if (key[SDL_SCANCODE_LEFT] && copymusic == 0){
                        Mix_PlayChannel(-1,updown,0);
                        copymusic = 0; 
                    }else if (key[SDL_SCANCODE_LEFT]){
                        Mix_PlayChannel(-1,updown,0);
                        copymusic--;
                    }
                }
                if (key[SDL_SCANCODE_SPACE] && parameter == 2){
                    Mix_PlayChannel(-1,select,0);
                    *speed = copyspeed;
                    *music = copymusic;
                    return 0;
                }
                if (key[SDL_SCANCODE_ESCAPE]){
                    *speed = copyspeed;
                    *music = copymusic;
                    Mix_PlayChannel(-1,select,0);
                    return 0;
                }
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,background,NULL,&rect_background);
        SDL_RenderCopy(renderer,menuspeed,NULL,&rect_speed);
        SDL_RenderCopy(renderer,menuback,NULL,&rect_back);
        SDL_RenderCopy(renderer,menumusic,NULL,&rect_music);
        SDL_RenderPresent(renderer);
    }
}

int submenu_exit(SDL_Renderer* renderer, Mix_Chunk *updown, Mix_Chunk *select){
    
    SDL_Texture* background = NULL;
    SDL_Texture* menuyesno = NULL;

    SDL_Rect rect_background; rect_background.w = 1280; rect_background.h = 720; rect_background.x = 0; rect_background.y = 0;
    SDL_Rect rect_yesno; rect_yesno.w = 263; rect_yesno.h = 80; rect_yesno.x = 508; rect_yesno.y = 300;
    
    background = IMG_LoadTexture(renderer,"menuimages/exitmenu.png"); 
    menuyesno = IMG_LoadTexture(renderer,"menuimages/selectedyes.png");

    int parameter = 0;
    int runmenu = true;
    SDL_Event event;
    const unsigned char* key;
    key = SDL_GetKeyboardState(NULL);

    while (runmenu){   
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                return 5;
            }
            if (event.type == SDL_KEYDOWN){
                if (key[SDL_SCANCODE_RIGHT] && parameter == 1){
                    Mix_PlayChannel(1,updown,0);
                    menuyesno = IMG_LoadTexture(renderer,"menuimages/selectedyes.png");
                    parameter = 0;
                }else if (key[SDL_SCANCODE_RIGHT]){
                    Mix_PlayChannel(1,updown,0);
                    parameter = 1;
                    menuyesno = IMG_LoadTexture(renderer,"menuimages/selectedno.png");
                }
                if (key[SDL_SCANCODE_LEFT] && parameter == 0){
                    Mix_PlayChannel(1,updown,0);
                    parameter = 1;
                    menuyesno = IMG_LoadTexture(renderer,"menuimages/selectedno.png");
                }else if (key[SDL_SCANCODE_LEFT]){
                    Mix_PlayChannel(1,updown,0);
                    parameter = 0;
                    menuyesno = IMG_LoadTexture(renderer,"menuimages/selectedyes.png");
                }
                if (parameter == 0){
                    if (key[SDL_SCANCODE_SPACE]){
                        Mix_PlayChannel(2,select,0);
                        return 5;
                    }
                }
                if (parameter == 1){
                    if (key[SDL_SCANCODE_SPACE]){
                        Mix_PlayChannel(2,select,0);
                        return 0;
                    }
                }
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,background,NULL,&rect_background);
        SDL_RenderCopy(renderer,menuyesno,NULL,&rect_yesno);
        SDL_RenderPresent(renderer);
    } 
}