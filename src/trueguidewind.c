#include"../inc/header.h"

int trueguidewind(SDL_Window *win, SDL_Renderer *renderer, Mix_Chunk *menu_eff)
{
    int sound = 0;
    int flag = 1;
    SDL_RenderClear(renderer);
    bool TrueGuide = true;
    int menu_again = 0;
    SDL_Event evt_trueguide;
    t_other_obj *trueguide = mx_init_butt("resource/controls.png", (SDL_Rect){(SCR_WIDTH / 2) - 350, (SCR_HEIGHT / 2) - 300, (SCR_WIDTH / 2), (SCR_WIDTH / 2) - 100});
    t_other_obj *back = mx_init_butt("resource/back_butt.png", (SDL_Rect){0, 10, 120, 60});
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    int mouse_x = 0, mouse_y = 0;
    while (TrueGuide){
        SDL_GetMouseState(&mouse_x, &mouse_y);
        SDL_RenderClear(renderer);
        bool is_hov_back = mx_is_Hovered(back, mouse_x, mouse_y);
        if ((is_hov_back) && sound == 0) {
            Mix_PlayChannel(-1, menu_eff, 0);
            sound = 1;
        }
        if (!is_hov_back) sound = 0;
        while (SDL_PollEvent(&evt_trueguide)){
            switch (evt_trueguide.type){
                case SDL_MOUSEBUTTONDOWN:
                    if (is_hov_back) {
                        TrueGuide = false;
                        menu_again = 1;
                    }
                    break;
                case SDL_KEYDOWN:
                    if (evt_trueguide.key.keysym.sym == SDLK_ESCAPE){
                        TrueGuide = false; 
                        menu_again = 1;
                    }
                    break;
                case SDL_QUIT:
                    TrueGuide = false;
                    flag = 0;
                    break;
                default:;
                
            }
        }
        if (is_hov_back) {
            mx_change_butt_tex(back, renderer, "resource/back_butt_hov.png");
        }
        else {
            mx_change_butt_tex(back, renderer, "resource/back_butt.png");
        }
        mx_draw_main_butt(renderer, trueguide);
        mx_draw_main_butt(renderer, back);
        SDL_RenderPresent(renderer);
        }
        if (menu_again == 1){
            flag = mainwind(win, renderer, menu_eff);
        }
        return flag;
}
