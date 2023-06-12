#include "../inc/header.h"

t_main_char *mx_init_main_char(const char *sprite_filename, SDL_Rect start_rect) {
    SDL_Surface *surf = IMG_Load(sprite_filename);
    if (surf == NULL) return NULL;

    t_main_char *m_char = malloc(sizeof(t_main_char));
    if (m_char == NULL) return NULL;

    m_char->rect = start_rect;
    m_char->surf = surf;
    m_char->health = 1000;
    m_char->damage = 10;
    m_char->level = 1;
    m_char->rotated = RIGHT;
    m_char->speed_x = 5;
    m_char->speed_y = 5;
    m_char->texture = NULL;
    
    return m_char;
}

void mx_draw_main_char(SDL_Renderer *renderer, t_main_char *main_char) {
    //if no texture yet created
    if (main_char->texture == NULL) {
        main_char->texture = SDL_CreateTextureFromSurface(renderer, main_char->surf);
    }
    if (main_char->texture == NULL) return;
    SDL_RenderCopy(renderer, main_char->texture, NULL, &(main_char->rect));
    return;
}

void mx_free_main_char(t_main_char *m_char) {
    SDL_FreeSurface(m_char->surf);
    SDL_DestroyTexture(m_char->texture);
    free(m_char);
}

void mx_shoot(t_main_char *hero, t_list **bullets, int mouse_x, int mouse_y) {
    int pl_x = hero->rect.x + (hero->rect.w / 2);
    int pl_y = hero->rect.y + (hero->rect.h / 2);
    //define bullet speed vector direction
    int x_sp = mouse_x - pl_x;
    int y_sp = mouse_y - pl_y;
    double abs_speed = sqrt(x_sp * x_sp + y_sp * y_sp);
    //correcting coeficient to make proper speed
    double coef = ABS_BUL_SP / abs_speed;
    x_sp *= coef;
    y_sp *= coef;
    //create bullets 

    SDL_Rect bulbox = (SDL_Rect){50, 50, 20, 20};
    int h_x = hero->rect.x + (hero->rect.w / 2);
    int h_y = hero->rect.y + (hero->rect.h / 2);
    bulbox.x = h_x;
    bulbox.y = h_y;
    t_bullet *bul = mx_create_bullet(BULLET1, bulbox, hero->damage, x_sp, y_sp);
    
    mx_push_front(bullets, bul);
}
