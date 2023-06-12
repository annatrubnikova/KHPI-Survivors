#include "../inc/header.h"


t_enemy *mx_create_enemy(const char *sprite_filename, SDL_Rect start_rect, int index) {
    SDL_Surface *surf = IMG_Load(sprite_filename);
    if (surf == NULL){
        return NULL;
    }

    t_enemy *enemy = malloc(sizeof(t_enemy));
    if (enemy == NULL) 
        return NULL;
    enemy->rect = start_rect;
    enemy->surf = surf;
    enemy->health = 30;
    enemy->damage = 2;
    enemy->index = index;
    enemy->rotated = RIGHT;
    enemy->speed_x = 2;
    enemy->speed_y = 2;
    enemy->taimer = 0;
    enemy->isdead = false;
    enemy->iscounted = false;
    enemy->gender = rand() % 2 == 0 ? 0 : 2;
    enemy->texture = NULL;
    return enemy;

    return 0;
}




void mx_draw_enemy(SDL_Renderer *renderer, t_enemy **enem) {
    t_enemy *enemy = *enem;
    //if no texture yet created
    if (enemy == NULL) return;
    if (enemy->texture == NULL) {
        enemy->texture = SDL_CreateTextureFromSurface(renderer, enemy->surf);
    }
    if (enemy->texture == NULL) return;
    if (enemy->health <= 0 && enemy->isdead == false) {
        enemy->isdead = true;
    }
        if(enemy->isdead){
        enemy->taimer++;
        //mx_free_enemy(enemy);
        enemy->rect.x -= enemy->speed_x;
        enemy->rect.y -= enemy->speed_y;
        if (enemy->taimer >= 300) {
            enemy->rect.x = 3000;
            enemy->rect.y = 3000;
            enemy = NULL;
            return;
        }
        }
    SDL_RenderCopy(renderer, enemy->texture, NULL, &(enemy->rect));
    return;
}

void mx_free_enemy(t_enemy *enemy) {
    SDL_FreeSurface(enemy->surf);
    SDL_DestroyTexture(enemy->texture);
    free(enemy);
}


void mx_create_enemy_coords(int *x, int *y,int second_dim, int (*obstacles)[second_dim], int obstacle_count){
        int enemy_x = rand() % SCR_WIDTH;
        int enemy_y = rand() % SCR_HEIGHT;
        for (int j = 0; j < obstacle_count; j++){
                // [][0] - x, [][1] - y, [][2] - width, [][3] - height
            if (((enemy_x >= obstacles[j][0] && enemy_x <= obstacles[j][0] + obstacles[j][2])
            && (enemy_y >= obstacles[j][1] && enemy_y <= obstacles[j][1] + obstacles[j][3]))
            || (enemy_x > SCR_WIDTH - 50 || enemy_y > SCR_HEIGHT - 50)){
                j = 0;
                enemy_x = (rand() % 1280);
                enemy_y = (rand() % 720);
            }
        }
        *x = enemy_x;
        *y = enemy_y;
}

bool mx_char_enemy_collision(t_main_char *ch, t_enemy *en) {
    if (en == NULL) return false;
    if ((ch->rect.x+ en->rect.w) > en->rect.x && (ch->rect.x < (en->rect.x + en->rect.w)) &&
        (ch->rect.y + en->rect.h) > en->rect.y && (ch->rect.y < (en->rect.y + en->rect.h))){
        return true;
    }
    return false;
}

int mx_count_killed(t_list *enemies, int size, Mix_Chunk *arr[size]){
    int killcount = 0;
    for (t_list *node = enemies; node != NULL; node = node->next) {
        t_enemy *enemy = (t_enemy *)(node->data);
        if (enemy == NULL) continue;
            
        if (enemy->health <= 0 && enemy->iscounted == false) {
            killcount++;
            enemy->iscounted = true;
            mx_kill_line(size, arr);
            //mx_free_enemy(enemy);
            //node->data = NULL;
        }
    //return killcount;
    }
    return killcount;
}

t_enemy *create_boss(char *filename, SDL_Rect rect, int health, int damage) {
    SDL_Surface *surf = IMG_Load(filename);
    if (surf == NULL){
        return NULL;
    }

    t_enemy *enemy = malloc(sizeof(t_enemy));
    if (enemy == NULL) 
        return NULL;
    enemy->rect = rect;
    enemy->surf = surf;
    enemy->health = health;
    enemy->damage = damage;
    enemy->index = 0;
    enemy->rotated = RIGHT;
    enemy->speed_x = 0;
    enemy->speed_y = 0;

    enemy->texture = NULL;
    return enemy;
}
