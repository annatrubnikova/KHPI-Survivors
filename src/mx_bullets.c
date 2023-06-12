#include "../inc/header.h"

t_bullet *mx_create_bullet(const char *filename, SDL_Rect rect, int damage, int sp_x, int sp_y) {
    t_bullet *bul = malloc(sizeof(t_bullet));
    if (bul == NULL) return NULL;
    bul->rect = rect;
    bul->surf = IMG_Load(filename);
    bul->damage = damage;
    bul->texture = NULL;
    bul->speed_x = sp_x;
    bul->speed_y = sp_y;
    return bul;
}

void mx_draw_bullet(SDL_Renderer *renderer, t_bullet *bul) {
    //if no texture yet created
    if (bul->texture == NULL) {
        bul->texture = SDL_CreateTextureFromSurface(renderer, bul->surf);
    }
    if (bul->texture == NULL) return;
    SDL_RenderCopy(renderer, bul->texture, NULL, &(bul->rect));
    return;
}

void mx_draw_all_bullets(SDL_Renderer *rend, t_list *bullets) {
    for (t_list *tmp = bullets; tmp != NULL; tmp = tmp->next) {
        if (tmp->data == NULL) continue;
        mx_draw_bullet(rend, (t_bullet *)(tmp->data));
    }
}

void mx_free_bullet(t_bullet **bul) {
    SDL_FreeSurface((*bul)->surf);
    SDL_DestroyTexture((*bul)->texture);
    free(*bul);
    *bul = NULL;
}

void mx_free_all_bullets(t_list **bullets) {
    for (t_list *node = *bullets; node != NULL; node = node->next) {
        if (node ->data != NULL) {
            mx_free_bullet((t_bullet **)(&(node->data)));
        } 
    }
    mx_clear_list(bullets);
}

void mx_update_bullet_positions(t_list *bullets) {
    for(t_list *n = bullets; n != NULL; n = n->next ) {
        //if no bullet data(bullet got destroyed/out of screen)
        if (n->data == NULL) continue;

        t_bullet *bul = (t_bullet *)(n->data);
        bul->rect.x += bul->speed_x;
        bul->rect.y += bul->speed_y;

        //bullet out of screen
        if (bul->rect.x + bul->rect.w < 0 
            ||bul->rect.x > SCR_WIDTH 
            ||bul->rect.y + bul->rect.h < 0
            ||bul->rect.y > SCR_HEIGHT) {
            mx_free_bullet(&bul);
            n->data = NULL;
        }
    }
}

int mx_bullet_enemy_collision(t_list *bullets, t_list *enemies) {
    int hitcount = 0;
    for (t_list *bul_n = bullets; bul_n != NULL; bul_n = bul_n->next) {
        t_bullet *bul = (t_bullet *)(bul_n->data);
        //if no bullet data
        if (bul == NULL) continue;
        //center of the bullet
        int x = bul->rect.x + (bul->rect.w / 2);
        int y = bul->rect.y + (bul->rect.h / 2);

        for (t_list *en_n = enemies; en_n != NULL; en_n = en_n->next) {
            t_enemy *enem = (t_enemy *)(en_n->data);
            //if no enemy data
            if (enem == NULL) continue;

            if (mx_is_point_in_rect(x, y, bul->rect.h, enem->rect)) {
                enem->health -= bul->damage;
                hitcount++;
                mx_free_bullet(&bul);
                bul_n->data = NULL;
                break;
            }
        }
    }
    return hitcount;
}

 void mx_bullet_obst_collision(t_list *bullets, t_list *obstacles) {
    for (t_list *bul_n = bullets; bul_n != NULL; bul_n = bul_n->next) {
        t_bullet *bul = (t_bullet *)(bul_n->data);
        //if no bullet data
        if (bul == NULL) continue;
        //center of the bullet
        int x = bul->rect.x + (bul->rect.w / 2);
        int y = bul->rect.y + (bul->rect.h / 2);

        for (t_list *obst_n = obstacles; obst_n != NULL; obst_n = obst_n->next) {
            t_obstacle *obst = (t_obstacle *)(obst_n->data);
            //if no enemy data
            if (obst == NULL) continue;

            if (mx_is_point_in_rect(x, y, bul->rect.h, obst->rect)) {
                mx_free_bullet(&bul);
                bul_n->data = NULL;
                break;
            }
        }
    }
}

void mx_bullet_boss_collision(t_list *bullets, t_enemy *enem) {
    if (enem == NULL) return;
    for (t_list *bul_n = bullets; bul_n != NULL; bul_n = bul_n->next) {
        t_bullet *bul = (t_bullet *)(bul_n->data);
        //if no bullet data
        if (bul == NULL) continue;
        //center of the bullet
        int x = bul->rect.x + (bul->rect.w / 2);
        int y = bul->rect.y + (bul->rect.h / 2);

        if (mx_is_point_in_rect(x, y, bul->rect.h, enem->rect)) {
            enem->health -= bul->damage;
            mx_free_bullet(&bul);
            bul_n->data = NULL;
            break;
        }
    
    }
}



static bool is_equal(void *a, void *b) {
    return a == b;
}

void mx_cleanup_empty_nodes(t_list **list) {
    mx_del_node_if(list, NULL, is_equal);
}

bool mx_is_point_in_rect(int x, int y, int h, SDL_Rect rect) {
    return (x >= rect.x 
            && x <= rect.x + rect.w
            && y + h >= rect.y 
            && y <= rect.y + rect.h);
}
