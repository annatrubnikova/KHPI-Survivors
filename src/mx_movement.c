#include "../inc/header.h"

char mx_char_movement(const Uint8 *keysPressed, t_main_char *hero, SDL_Renderer *renderer, int i, int j, SDL_Surface *arr[i][j], t_list *obstacles_map) {
    char direct;
    if (keysPressed[SDL_SCANCODE_W]) {
        if (mx_check_collision(hero, obstacles_map, 'w')) {}
        else {
            mx_move_anim(hero, 'w', renderer, i, j, arr);
            hero->rect.y -= hero->speed_y;
            direct = 'w';
        }
    }
    if (keysPressed[SDL_SCANCODE_S]) {
        if (mx_check_collision(hero, obstacles_map, 's')) {}
        else {
            mx_move_anim(hero, 's', renderer, i, j, arr);
            hero->rect.y += hero->speed_y;
            direct = 's';
        }
    }
    if (keysPressed[SDL_SCANCODE_A]) {
        if (mx_check_collision(hero, obstacles_map, 'a')) {}
        else {
            mx_move_anim(hero, 'a', renderer, i, j, arr);
            hero->rect.x -= hero->speed_x;
            direct = 'a';
        }
    }
    if (keysPressed[SDL_SCANCODE_D]) {
        if (mx_check_collision(hero, obstacles_map, 'd')) {}
        else {
            mx_move_anim(hero, 'd', renderer, i, j, arr);
            hero->rect.x += hero->speed_x;
            direct = 'd';
        }
    }
    return direct;
}

bool mx_check_collision(t_main_char *hero, t_list *obstacles_map, char c) {
    if (c == 'w'){
        if (hero->rect.y - 5 < 0) return true;
        for (t_list *tmp = obstacles_map; tmp != NULL; tmp = tmp->next) {
            t_obstacle *obstacle = (t_obstacle *)(tmp->data);
            if ((hero->rect.x >= obstacle->rect.x && hero->rect.x <= (obstacle->rect.x + obstacle->rect.w))
                || (hero->rect.x + GG_WIDTH >= obstacle->rect.x && hero->rect.x + GG_WIDTH <= (obstacle->rect.x + obstacle->rect.w))
                || (hero->rect.x + GG_WIDTH / 2 >= obstacle->rect.x && hero->rect.x + GG_WIDTH / 2 <= (obstacle->rect.x + obstacle->rect.w))) 
            {
                if (hero->rect.y + 50 - hero->speed_y <= (obstacle->rect.y + obstacle->rect.h)
                    && hero->rect.y + 50 - hero->speed_y >= (obstacle->rect.y + obstacle->rect.h - hero->speed_y * 2)) 
                    return true;
            }
        }
    }
    else if (c == 's'){
        if (hero->rect.y + GG_HEIGHT + 5 > SCR_HEIGHT) return true;
        for (t_list *tmp = obstacles_map; tmp != NULL; tmp = tmp->next) {
            t_obstacle *obstacle = (t_obstacle *)(tmp->data);
            if ((hero->rect.x >= obstacle->rect.x && hero->rect.x <= (obstacle->rect.x + obstacle->rect.w))
                || (hero->rect.x + GG_WIDTH >= obstacle->rect.x && hero->rect.x + GG_WIDTH <= (obstacle->rect.x + obstacle->rect.w))
                || (hero->rect.x + GG_WIDTH / 2 >= obstacle->rect.x && hero->rect.x + GG_WIDTH / 2 <= (obstacle->rect.x + obstacle->rect.w))) 
            {
                if (hero->rect.y + GG_HEIGHT + hero->speed_y >= obstacle->rect.y
                    && hero->rect.y + GG_HEIGHT + hero->speed_y <= obstacle->rect.y + hero->speed_y * 2) return true;
            }
        }
    }
    else if (c == 'a'){
        if (hero->rect.x - 5 < 0) return true;
        for (t_list *tmp = obstacles_map; tmp != NULL; tmp = tmp->next) {
            t_obstacle *obstacle = (t_obstacle *)(tmp->data);
            if ((hero->rect.y + GG_HEIGHT >= obstacle->rect.y && hero->rect.y + GG_HEIGHT <= (obstacle->rect.y + obstacle->rect.h))
                || (hero->rect.y + 50 >= obstacle->rect.y && hero->rect.y + 50 <= (obstacle->rect.y + obstacle->rect.h)))
            {
                if (hero->rect.x - hero->speed_x <= (obstacle->rect.x + obstacle->rect.w) 
                    && hero->rect.x - hero->speed_x >= (obstacle->rect.x + obstacle->rect.w - hero->speed_x * 2)) return true;
            }
        }
    }
    else if (c == 'd'){
        if (hero->rect.x + GG_WIDTH + 5 > SCR_WIDTH) return true;
        for (t_list *tmp = obstacles_map; tmp != NULL; tmp = tmp->next) {
            t_obstacle *obstacle = (t_obstacle *)(tmp->data);
            if ((hero->rect.y + GG_HEIGHT >= obstacle->rect.y && hero->rect.y + GG_HEIGHT <= (obstacle->rect.y + obstacle->rect.h))
                || (hero->rect.y + 50 >= obstacle->rect.y && hero->rect.y + 50 <= (obstacle->rect.y + obstacle->rect.h)))
            {
                if (hero->rect.x + GG_WIDTH + hero->speed_x >= obstacle->rect.x
                    &&hero->rect.x + GG_WIDTH + hero->speed_x <= obstacle->rect.x + hero->speed_x * 2) return true;
            }
        }
    }
    return false;
}

void mx_change_tex(t_main_char *hero, char c, SDL_Renderer *renderer){
    if (c == 'w') hero->surf = IMG_Load(MC_UP_STAND);
    else if (c == 's') hero->surf = IMG_Load(MC_DOWN_STAND);
    else if (c == 'a') hero->surf = IMG_Load(MC_LEFT_STAND);
    else if (c == 'd') hero->surf = IMG_Load(MC_RIGHT_STAND);
    if (hero->texture != NULL) SDL_DestroyTexture(hero->texture);
    hero->texture = SDL_CreateTextureFromSurface(renderer, hero->surf);
    return;
}

void mx_move_anim(t_main_char *hero, char c, SDL_Renderer *renderer, int i, int j, SDL_Surface *arr[i][j]){
    int time = clock() / (CLOCKS_PER_SEC / 22);
    if (c == 'w') hero->surf = arr[1][time % 3];
    if (c == 's') hero->surf = arr[0][time % 3];
    if (c == 'a') hero->surf = arr[2][time % 3];
    if (c == 'd') hero->surf = arr[3][time % 3];
    if (hero->texture != NULL) SDL_DestroyTexture(hero->texture);
    hero->texture = SDL_CreateTextureFromSurface(renderer, hero->surf);
    return;
}

void mx_load_sprites(int i, int j, SDL_Surface *arr[i][j]){
    arr[0][0] = IMG_Load(MC_DOWN_MOVE1);
    arr[0][1] = IMG_Load(MC_DOWN_STAND);
    arr[0][2] = IMG_Load(MC_DOWN_MOVE2);
    arr[1][0] = IMG_Load(MC_UP_MOVE1);
    arr[1][1] = IMG_Load(MC_UP_STAND);
    arr[1][2] = IMG_Load(MC_UP_MOVE2);
    arr[2][0] = IMG_Load(MC_LEFT_MOVE1);
    arr[2][1] = IMG_Load(MC_LEFT_STAND);
    arr[2][2] = IMG_Load(MC_LEFT_MOVE2);
    arr[3][0] = IMG_Load(MC_RIGHT_MOVE1);
    arr[3][1] = IMG_Load(MC_RIGHT_STAND);
    arr[3][2] = IMG_Load(MC_RIGHT_MOVE2);
    return;
}

char mx_dir_def(int mouse_x, int mouse_y, t_main_char *hero) {
    int xv = mouse_x - hero->rect.x;
    int yv = mouse_y - hero->rect.y;

    if (abs(xv) >= abs(yv)) {
        if (xv >= 0) return 'd';
        else return 'a';
    }
    else {
        if (yv >= 0) return 's';
        else return 'w';
    }

}

