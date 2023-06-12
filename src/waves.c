#include"../inc/header.h"

int wave1(void *enemies) {
    t_list **list = (t_list **)(enemies);
    SDL_Rect rect = (SDL_Rect){100, 100, GG_WIDTH , GG_HEIGHT};
    t_enemy *zombie;
    
    for (int i = 0; i < 5; i++){
        zombie = mx_create_enemy(ZOMBIE, rect, 0);
        mx_push_front(list, zombie);
        rect.x += 70;
    }
    SDL_Delay(5000);

    rect.y = SCR_HEIGHT - 100;
    rect.x = 400;
    for (int i = 0; i < 7; i++){
        zombie = mx_create_enemy(ZOMBIE, rect, 0);
        mx_push_front(list, zombie);
        rect.x += 70;
    }

    SDL_Delay(5000);
    
    rect.y = SCR_HEIGHT / 4;
    rect.x = 200;    
    for (int i = 0; i < 7; i++){
         zombie = mx_create_enemy(ZOMBIE, rect, 0);
        mx_push_front(list, zombie);
        rect.y += 50;
    }
    SDL_Delay(5000);

    rect.y = SCR_HEIGHT - 200;
    rect.x = SCR_WIDTH / 2 + 300;
        for (int i = 0; i < 6; i++){
         zombie = mx_create_enemy(ZOMBIE, rect, 0);
        mx_push_front(list, zombie);
        rect.y += 50;
        rect.x += 50;
        SDL_Delay(200);
    }
    return 0;
}


int wave2(void *enemies) {
    SDL_Delay(1000);
    t_list **list = (t_list **)(enemies);
    SDL_Rect rect = (SDL_Rect){100, 100, GG_WIDTH , GG_HEIGHT};
    t_enemy *zombie;
    
    for (int i = 0; i < 12; i++){
        zombie = mx_create_enemy(ZOMBIE, rect, 0);
        mx_push_front(list, zombie);
        rect.x += 70;
    }
    SDL_Delay(8000);

    rect.y = SCR_HEIGHT - 150;
    rect.x = 100;
    for (int i = 0; i < 12; i++){
        zombie = mx_create_enemy(ZOMBIE, rect, 0);
        mx_push_front(list, zombie);
        rect.x += 70;
        SDL_Delay(200);
    }

    SDL_Delay(5000);
    
    rect.y = SCR_HEIGHT / 2;
    rect.x = 400;
    for (int i = 0; i < 6; i++){
        zombie = mx_create_enemy(ZOMBIE, rect, 0);
        mx_push_front(list, zombie);
        rect.x += 120;
        SDL_Delay(300);
    }
    return 0;
}

void spawn_1wave(t_list **enemies) {
    SDL_CreateThread(wave1, "wave1", (void *)enemies);
}

void spawn_2wave(t_list **enemies) {
    SDL_CreateThread(wave2, "wave2", (void *)enemies);
}
