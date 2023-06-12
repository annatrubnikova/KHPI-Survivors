#include "../inc/header.h"

void winwin(SDL_Renderer *renderer){
    Mix_Music *win_bgm = Mix_LoadMUS("resource/win_sound.mp3");
    Mix_PlayMusic(win_bgm, -1);
    bool isRunning = true;
    SDL_Event evt;
    t_other_obj *win_sign2 = mx_init_butt("resource/win_screen.png", (SDL_Rect){(SCR_WIDTH / 2) - 450, (SCR_HEIGHT / 2) + 100, (SCR_WIDTH / 2) + 250, (SCR_HEIGHT / 2) - 100});
    t_other_obj *win_sign = mx_init_butt("resource/win_screen1.png", (SDL_Rect){(SCR_WIDTH / 2) - 450, (SCR_HEIGHT / 2) - 400, (SCR_WIDTH / 2) + 250, (SCR_HEIGHT / 2) + 200});
    while (isRunning){
        SDL_RenderClear(renderer);
        while(SDL_PollEvent(&evt)){
            switch(evt.type){
                case SDL_KEYDOWN:
                    if (evt.key.keysym.sym == SDLK_ESCAPE){
                        isRunning = false;
                    }
                    break;
                case SDL_QUIT:
                    isRunning = false;
                    break;
            }
        }
        mx_draw_main_butt(renderer, win_sign);
        mx_draw_main_butt(renderer, win_sign2);
        SDL_RenderPresent(renderer);
    }
    Mix_HaltMusic();
    Mix_FreeMusic(win_bgm);
    return;
}

