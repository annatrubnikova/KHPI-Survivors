#include "../inc/header.h"

void mx_enemy_shoot(t_list **enemy_bullets, t_enemy *enemy, t_main_char *hero) {
    if (enemy == NULL || hero == NULL) return;
    int pl_x = hero->rect.x + (hero->rect.w / 2);
    int pl_y = hero->rect.y + (hero->rect.h / 2);
    //define bullet speed vector direction
    int x_sp = pl_x - (enemy->rect.x + enemy->rect.w / 2);
    int y_sp = pl_y - (enemy->rect.y + enemy->rect.h / 2);
    double abs_speed = sqrt(x_sp * x_sp + y_sp * y_sp);
    //correcting coeficient to make proper speed
    double coef = ABS_ENEMY_BUL_SP / abs_speed;
    x_sp *= coef;
    y_sp *= coef;

    SDL_Rect bulbox = (SDL_Rect){50, 50, 50, 50};
    int h_x = enemy->rect.x + (enemy->rect.w / 2) - 25;
    int h_y = enemy->rect.y + (enemy->rect.h / 2) - 25;
    bulbox.x = h_x;
    bulbox.y = h_y;
    t_bullet *bul = mx_create_bullet(BULLET2, bulbox, enemy->damage, x_sp, y_sp);

    mx_push_front(enemy_bullets, bul);
}

void mx_enemybullet_hero_collision(t_list *bullets, t_main_char *hero) {
    if (hero == NULL) return;
    for (t_list *bul_n = bullets; bul_n != NULL; bul_n = bul_n->next) {
        t_bullet *bul = (t_bullet *)(bul_n->data);
        //if no bullet data
        if (bul == NULL) continue;
        //center of the bullet
        int x = bul->rect.x + (bul->rect.w / 2);
        int y = bul->rect.y + (bul->rect.h / 2);

        if (mx_is_point_in_rect(x, y, bul->rect.h, hero->rect)) {
            hero->health -= bul->damage;
            mx_free_bullet(&bul);
            bul_n->data = NULL;
        }
    }
}


