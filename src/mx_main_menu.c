#include "../inc/header.h"

t_other_obj *mx_init_butt(const char *filename, SDL_Rect rect){
    SDL_Surface *surf = IMG_Load(filename);
    if (surf == NULL) return NULL;
    t_other_obj *butt = malloc(sizeof(t_other_obj));
    if (butt == NULL) return NULL;
    butt->surf = surf;
    butt->texture = NULL;
    butt->rect = rect;
    butt->associated_func = NULL;
    return butt;
}

void mx_draw_main_butt(SDL_Renderer *renderer, t_other_obj *butt){
    if (butt->texture == NULL) {
        butt->texture = SDL_CreateTextureFromSurface(renderer, butt->surf);
    }
    if (butt->texture == NULL) return;
    SDL_RenderCopy(renderer, butt->texture, NULL, &(butt->rect));
    return;
}

bool mx_is_Hovered(t_other_obj *butt, int mouse_x, int mouse_y){
    if (mouse_x < butt->rect.x + butt->rect.w 
        && mouse_x > butt->rect.x
        && mouse_y < butt->rect.y + butt->rect.h
        && mouse_y > butt->rect.y){
        return true;
    }
    else {
        return false;
    }
}

void mx_change_butt_tex(t_other_obj *butt, SDL_Renderer *renderer, const char *filename){
    butt->surf = IMG_Load(filename);
    butt->texture = SDL_CreateTextureFromSurface(renderer, butt->surf);
    return;
}

