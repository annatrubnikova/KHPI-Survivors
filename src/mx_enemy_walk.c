#include"../inc/header.h"

void mx_enemy_path_speed(t_main_char *hero, t_enemy *enemies, float speed) {
    if (enemies == NULL) return;
    int x_len = (hero->rect.x - enemies->rect.x);
    int y_len = (hero->rect.y - enemies->rect.y);
    float xy = sqrt( x_len * x_len + y_len * y_len);
    enemies->speed_x = x_len / xy * speed;
    enemies->speed_y = y_len / xy * speed;
}

bool mx_enem_col(t_obstacle *obstacle, t_enemy *enemies) {
    if (enemies == NULL) return false;
    if (((enemies->rect.x + enemies->rect.w >= obstacle->rect.x) && (enemies->rect.x <= obstacle->rect.x + obstacle->rect.w )
        && (enemies->rect.y + enemies->rect.h >= obstacle->rect.y) && (enemies->rect.y <= obstacle->rect.y + obstacle->rect.h))
        || (((enemies->rect.x >= obstacle->rect.x) && (enemies->rect.x <= obstacle->rect.x + obstacle->rect.w ))
        && ((enemies->rect.y >= obstacle->rect.y) && (enemies->rect.y <= obstacle->rect.y + obstacle->rect.h))))
            return true;
    return false;
}
void mx_enemy_move(t_list *obstacles, t_main_char *hero,  t_enemy *enemies, float speed, SDL_Renderer *renderer, int i, int j, SDL_Surface *arr[i][j]) {
    if (enemies == NULL)
        return;
    if (rand() % 15  == 1) {
        mx_enemy_path_speed(hero, enemies, speed);
    }
    if (enemies->health > 0){
        for (t_list *obst = obstacles; obst != NULL; obst = obst->next){
            t_obstacle *obstacle = (t_obstacle *)(obst->data);
            mx_anims_move_enemies(enemies, renderer, 2, 2, arr);
            if (mx_enem_col(obstacle, enemies)) {
                if ((enemies->rect.x + enemies->rect.w > obstacle->rect.x) && (enemies->rect.x < obstacle->rect.x + obstacle->rect.w ) &&
                    (enemies->rect.y + enemies->rect.h > obstacle->rect.y) && (enemies->rect.y < obstacle->rect.y + obstacle->rect.h)) {
                    enemies->rect.y += enemies->speed_x;
                    return;
                }
                else if ((enemies->rect.y + enemies->rect.h >= obstacle->rect.y) && (enemies->rect.y <= obstacle->rect.y + obstacle->rect.h) &&
                    (enemies->rect.x + enemies->rect.w > obstacle->rect.x) && (enemies->rect.x < obstacle->rect.x + obstacle->rect.w )) {
                    enemies->rect.x += enemies->speed_y;
                    
                    return;
                }
        }
        }
        enemies->rect.x += enemies->speed_x;
        enemies->rect.y += enemies->speed_y;

    }
}


void mx_anims_move_enemies(t_enemy *enemies, SDL_Renderer *renderer, int i, int j, SDL_Surface *arr[i][j]){
    if (enemies == NULL) return;
        int p = 0;
        if (enemies->isdead){
            p = (enemies->gender == 0) ? 0 : 2;
        }
        int time = clock() / (CLOCKS_PER_SEC / 75);

        if (enemies->speed_x <= 0) enemies->surf = arr[p][time % 2];
        if (enemies->speed_x >= 0) enemies->surf = arr[p + 1][time % 2];
        if (enemies->texture != NULL) SDL_DestroyTexture(enemies->texture);
    
    enemies->texture = SDL_CreateTextureFromSurface(renderer, enemies->surf);
    return;
}


void mx_load_students(int i, int j, SDL_Surface *arr[i][j]){
    arr[2][0] = IMG_Load(STUDENT_GIRL_RIGHT_MOVE2);
    arr[2][1] = IMG_Load(STUDENT_GIRL_RIGHT_MOVE1);
    arr[3][0] = IMG_Load(STUDENT_GIRL_LEFT_MOVE2);
    arr[3][1] = IMG_Load(STUDENT_GIRL_LEFT_MOVE1);
    arr[1][0] = IMG_Load(STUDENT_LEFT_MOVE1);
    arr[1][1] = IMG_Load(STUDENT_LEFT_MOVE2);
    arr[0][0] = IMG_Load(STUDENT_RIGHT_MOVE1);
    arr[0][1] = IMG_Load(STUDENT_RIGHT_MOVE2);
    return;
}
void mx_load_enemies(int i, int j, SDL_Surface *arr[i][j]){
    arr[0][0] = IMG_Load(ZOMBIE_LEFT_MOVE1);
    arr[0][1] = IMG_Load(ZOMBIE_LEFT_MOVE2);
    arr[1][0] = IMG_Load(ZOMBIE_RIGHT_MOVE1);
    arr[1][1] = IMG_Load(ZOMBIE_RIGHT_MOVE2);
    return;
}

void mx_draw_all_enemies(t_list *enemies, t_main_char *hero, t_list *obstacles_map, SDL_Renderer *renderer,int i, int j, SDL_Surface *enemy_text[i][j], int k, SDL_Surface *students_text[k][k]){
    for (t_list *tmp = enemies; tmp != NULL; tmp = tmp->next) {
        t_enemy *enem = (t_enemy *)(tmp->data);
        if (enem == NULL) continue;
        if (mx_char_enemy_collision(hero,enem) && !enem->isdead)
            hero->health -= enem->damage;
        if(!enem->isdead){
            mx_enemy_move(obstacles_map, hero, enem, 4.5, renderer, 2, 2, enemy_text);
          
        }
        else
            mx_anims_move_enemies(enem, renderer, 4, 2, students_text);
        mx_draw_enemy(renderer, &enem);
    }
}


