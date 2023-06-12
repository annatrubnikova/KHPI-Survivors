#include"../inc/header.h"

bool mx_check_load(SDL_Window *win, SDL_Renderer *renderer) {
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = IMG_Load("resource/map1.png");
    if (!surface){
        printf("ne zagruzilos'\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return false;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture){
        printf("%s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return false;
    }

    surface = IMG_Load("resource/front_map1.png");
    if (!surface){
        printf("ne zagruzilos'\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return false;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture){
        printf("%s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return false;
    }

    SDL_FreeSurface(surface);
    return true;
}

t_obstacle *mx_create_obstacle(int x, int y, int width, int height) {
    t_obstacle *obstacle = malloc(sizeof(t_obstacle));
    obstacle->rect.x = x;
    obstacle->rect.y = y;
    obstacle->rect.w = width;
    obstacle->rect.h = height;
    
    return obstacle;
}

void mx_fill_obstacles_map1(t_list **obstacles_map) {
    mx_push_front(obstacles_map, mx_create_obstacle(0, 165, 53, 36));
    mx_push_front(obstacles_map, mx_create_obstacle(31, 586, 77, 50));
    mx_push_front(obstacles_map, mx_create_obstacle(348, 391, 40, 50));
    mx_push_front(obstacles_map, mx_create_obstacle(476, 391, 187, 50));
    mx_push_front(obstacles_map, mx_create_obstacle(710, 185, 187, 50));
    mx_push_front(obstacles_map, mx_create_obstacle(966, 391, 187, 50));
    mx_push_front(obstacles_map, mx_create_obstacle(1214, 391, 40, 50));
    mx_push_front(obstacles_map, mx_create_obstacle(1169, 146, 67, 50));
}

void mx_fill_obstacles_map2(t_list **obstacles_map) {
    mx_push_front(obstacles_map, mx_create_obstacle(111, 439, 183, 72));
    mx_push_front(obstacles_map, mx_create_obstacle(549, 439, 183, 72));
    mx_push_front(obstacles_map, mx_create_obstacle(987, 439, 183, 72));
    mx_push_front(obstacles_map, mx_create_obstacle(354, 182, 183, 72));
    mx_push_front(obstacles_map, mx_create_obstacle(743, 182, 183, 72));
    mx_push_front(obstacles_map, mx_create_obstacle(0, 182, 149, 72));
    mx_push_front(obstacles_map, mx_create_obstacle(1169, 182, 147, 72));
}

void mx_fill_obstacles_map3(t_list **obstacles_map) {
    mx_push_front(obstacles_map, mx_create_obstacle(10, 174, 228, 60));
    mx_push_front(obstacles_map, mx_create_obstacle(1041, 174, 228, 60));
    mx_push_front(obstacles_map, mx_create_obstacle(176, 489, 228, 60));
    mx_push_front(obstacles_map, mx_create_obstacle(876, 489, 228, 60));
}

void mx_draw_server(SDL_Renderer *renderer, t_obstacle *server, int ifif) {
    SDL_Surface *surface = IMG_Load("resource/server.png");
    SDL_Texture *server_t = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, server_t, NULL, &(server->rect));

    if (ifif == 0) {
        surface = IMG_Load("resource/server_broken1.png");
        SDL_Texture *server_b1 = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, server_b1, NULL, &(server->rect));
    }
    else {
        surface = IMG_Load("resource/server_broken2.png");
        SDL_Texture *server_b2 = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, server_b2, NULL, &(server->rect));
    }
    SDL_FreeSurface(surface);
}

void mx_draw_gold_ring(SDL_Renderer *renderer, t_obstacle *server) {
    SDL_Surface *surface = IMG_Load("resource/server_ring.png");
    SDL_Texture *server_t = SDL_CreateTextureFromSurface(renderer, surface);

    t_obstacle *ring = mx_create_obstacle(server->rect.x-3, server->rect.y-3, server->rect.w+6, server->rect.h+6);

    SDL_RenderCopy(renderer, server_t, NULL, &(ring->rect));

    t_obstacle *EE = mx_create_obstacle(587, 535, 104, 108);
    surface = IMG_Load("resource/button.png");
    server_t = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, server_t, NULL, &(EE->rect));

    SDL_FreeSurface(surface);
}

void mx_server_blinks(SDL_Renderer *renderer) {
    int i = rand() % 10;
    if (i == 0) {
        SDL_Surface *surface = IMG_Load("resource/server_blink1.png");
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_FreeSurface(surface);
    }
    else if (i == 1) {
        SDL_Surface *surface = IMG_Load("resource/server_blink2.png");
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_FreeSurface(surface);
    }
    else if (i == 2) {
        SDL_Surface *surface = IMG_Load("resource/server_blink3.png");
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_FreeSurface(surface);
    }
}
