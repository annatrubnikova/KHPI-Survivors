#include"../inc/header.h"

int mainwind (SDL_Window *win, SDL_Renderer *renderer, Mix_Chunk *menu_eff)
{
    int flag = 2;
    int sound = 0;
    SDL_Surface *surface = IMG_Load("resource/main_bgrd.png");
    if (!surface){
        printf("ne zagruzilos'\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        flag = 0;
    }
    SDL_Texture *bgrd = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!bgrd){
        printf("%s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        flag = 0;
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bgrd, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Event evt_main;
    bool isInMenu = true;
    int mouse_x = 0, mouse_y = 0;
    t_other_obj *start_butt = mx_init_butt("resource/play_butt.png", (SDL_Rect){(SCR_WIDTH / 2) - 120, SCR_HEIGHT - 265, 240, 120});
    t_other_obj *guide_butt = mx_init_butt("resource/guide_butt.png", (SDL_Rect){(SCR_WIDTH / 2) - 120, SCR_HEIGHT - 140, 240, 120});
    t_other_obj *madeby_butt = mx_init_butt("resource/made_by.png", (SDL_Rect){30, 30, 150, 75});
    while (isInMenu){
        SDL_GetMouseState(&mouse_x, &mouse_y);
        bool is_hov_start = mx_is_Hovered(start_butt, mouse_x, mouse_y);
        bool is_hov_guide = mx_is_Hovered(guide_butt, mouse_x, mouse_y);
        bool is_hov_madeby = mx_is_Hovered(madeby_butt, mouse_x, mouse_y);
        if ((is_hov_guide || is_hov_start || is_hov_madeby) && sound == 0) {
            Mix_PlayChannel(-1, menu_eff, 0);
            sound = 1;
        }
        if (!is_hov_guide && !is_hov_start && !is_hov_madeby) sound = 0;
        while (SDL_PollEvent(&evt_main)){
            switch (evt_main.type){
                case SDL_MOUSEBUTTONDOWN:
                    if (is_hov_start) {
                        isInMenu = false;
                        flag = 1;
                    }
                    if (is_hov_guide) {
                        isInMenu = false;
                        flag = 3;
                    }
                    if (is_hov_madeby) {
                        isInMenu = false;
                        flag = 4;
                    }
                    break;
                case SDL_KEYDOWN:
                    if (evt_main.key.keysym.sym == SDLK_ESCAPE){
                        isInMenu = false;   
                        flag =  0;
                    }
                    break;

                case SDL_QUIT:
                    isInMenu = false;
                    flag = 0;
                    break;
                default:;
            }
        }
        if (is_hov_start) {
            mx_change_butt_tex(start_butt, renderer, "resource/play_butt_hov.png");
        }
        else {
            mx_change_butt_tex(start_butt, renderer, "resource/play_butt.png");
        }
        if (is_hov_guide) {
            mx_change_butt_tex(guide_butt, renderer, "resource/guide_butt_hov.png");
        }
        else {
            mx_change_butt_tex(guide_butt, renderer, "resource/guide_butt.png");
        }
        if (is_hov_madeby) {
            mx_change_butt_tex(madeby_butt, renderer, "resource/made_by_hov.png");
        }
        else {
            mx_change_butt_tex(madeby_butt, renderer, "resource/made_by.png");
        }
        SDL_RenderCopy(renderer, bgrd, NULL, NULL);
        mx_draw_main_butt(renderer, start_butt);
        mx_draw_main_butt(renderer, guide_butt);
        mx_draw_main_butt(renderer, madeby_butt);
        SDL_RenderPresent(renderer);
    }
    if (flag == 3) flag = guidewind(win, renderer, menu_eff);
    if (flag == 4) flag = madebywind(win, renderer, menu_eff);
    return flag;
}
