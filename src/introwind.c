#include "../inc/header.h"

int introwind(SDL_Renderer *renderer){
    SDL_RenderClear(renderer);
    int flag = 1;
    t_other_obj *intro = mx_init_butt("resource/intro.png", (SDL_Rect){(SCR_WIDTH / 2) - 400, (SCR_HEIGHT / 2) - 300, (SCR_WIDTH / 2) + 200, (SCR_HEIGHT / 2) + 300});
    bool isReading = true;
    SDL_Event evt;
    while (isReading){
        SDL_RenderClear(renderer);
        while(SDL_PollEvent(&evt)){
            switch(evt.type){
                case SDL_KEYDOWN:
                    if (evt.key.keysym.sym == SDLK_RETURN) isReading = false;
                    if (evt.key.keysym.sym == SDLK_ESCAPE){
                        isReading = false; 
                        flag = 0;
                    }
                    break;
                case SDL_QUIT:
                    isReading = false;
                    flag = 0;
                    break;
            }
        }
        mx_draw_main_butt(renderer, intro);
        SDL_RenderPresent(renderer);
    }
    return flag;
}

