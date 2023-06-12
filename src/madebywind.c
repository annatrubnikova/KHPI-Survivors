#include"../inc/header.h"

int madebywind(SDL_Window *win, SDL_Renderer *renderer, Mix_Chunk *menu_eff)
{
    int sound = 0;
    int flag = 1;
    SDL_RenderClear(renderer);
    bool MadeBy = true;
    int menu_again = 0;
    SDL_Event evt_title;
    SDL_Surface *surface = IMG_Load("resource/title.png");
    if (!surface){
        printf("ne zagruzilos'\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        flag = 0;
    }
    SDL_Texture *made = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!made){
        printf("%s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        flag = 0;
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, made, NULL, NULL);
    SDL_RenderPresent(renderer);
    t_other_obj *back = mx_init_butt("resource/back_butt.png", (SDL_Rect){0, 10, 120, 60});
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    int mouse_x = 0, mouse_y = 0;
    while (MadeBy){
        SDL_GetMouseState(&mouse_x, &mouse_y);
        SDL_RenderClear(renderer);
        bool is_hov_back = mx_is_Hovered(back, mouse_x, mouse_y);
        if ((is_hov_back) && sound == 0) {
            Mix_PlayChannel(-1, menu_eff, 0);
            sound = 1;
        }
        if (!is_hov_back) sound = 0;
        while (SDL_PollEvent(&evt_title)){
            switch (evt_title.type){
                case SDL_MOUSEBUTTONDOWN:
                    if (is_hov_back) {
                        MadeBy = false;
                        menu_again = 1;
                    }
                    break;
                case SDL_KEYDOWN:
                    if (evt_title.key.keysym.sym == SDLK_ESCAPE){
                        MadeBy = false; 
                        menu_again = 1;
                    }
                    break;
                case SDL_QUIT:
                    MadeBy = false;
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
        SDL_RenderCopy(renderer, made, NULL, NULL);
        //mx_draw_main_butt(renderer, made);
        mx_draw_main_butt(renderer, back);
        SDL_RenderPresent(renderer);
        }
        if (menu_again == 1){
            flag = mainwind(win, renderer, menu_eff);
        }
        return flag;
}
