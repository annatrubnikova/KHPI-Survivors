#include"../inc/header.h"

int jokewind(SDL_Window *win, SDL_Renderer *renderer, Mix_Chunk *menu_eff)
{
    int sound = 0;
    int flag = 2;
    int delay = 0;
    SDL_RenderClear(renderer);
    bool Joke = true;
    int menu_again = 0;
    SDL_Event evt_joke;
    t_other_obj *joke = mx_init_butt("resource/joke.png", (SDL_Rect){(SCR_WIDTH / 2) - 250, (SCR_HEIGHT / 2) - 250, 500, 500});
    t_other_obj *back = mx_init_butt("resource/back_butt.png", (SDL_Rect){0, 10, 120, 60});
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    int mouse_x = 0, mouse_y = 0;
    while (Joke){
        SDL_GetMouseState(&mouse_x, &mouse_y);
        SDL_RenderClear(renderer);
        bool is_hov_back = mx_is_Hovered(back, mouse_x, mouse_y);
        if ((is_hov_back) && sound == 0) {
            Mix_PlayChannel(-1, menu_eff, 0);
            sound = 1;
        }
        if (!is_hov_back) sound = 0;
        while (SDL_PollEvent(&evt_joke)){
            switch (evt_joke.type){
                case SDL_MOUSEBUTTONDOWN:
                    if (is_hov_back) {
                        Joke = false;
                        menu_again = 1;
                    }
                    break;
                case SDL_KEYDOWN:
                    if (evt_joke.key.keysym.sym == SDLK_ESCAPE){
                        Joke = false; 
                        menu_again = 1;
                    }
                    break;
                case SDL_QUIT:
                    Joke = false;
                    flag = 0;
                    break;
                default:;
                
            }
        }
        delay++;
        if (delay == 150) break;
        if (is_hov_back) {
            mx_change_butt_tex(back, renderer, "resource/back_butt_hov.png");
        }
        else {
            mx_change_butt_tex(back, renderer, "resource/back_butt.png");
        }
        mx_draw_main_butt(renderer, joke);
        mx_draw_main_butt(renderer, back);
        SDL_RenderPresent(renderer);
        }
        if (menu_again == 1){
            flag = mainwind(win, renderer, menu_eff);
        }
        if (delay == 150) flag = trueguidewind(win, renderer, menu_eff);
        return flag;
}
