#pragma once

#include "list.h"
#include "const.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>

//enum for specifying direction
//hero or an enemy is looking at
enum rotate_dirs {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef struct s_main_char {
    //rect holds position and dimensions
    //of character
    SDL_Rect rect;
    //texture
    SDL_Texture *texture;
    SDL_Surface *surf;
    
    int health;
    int damage;
    int speed_x;
    int speed_y;
    int level;
    //one of the directions from 
    //rotate_dirs enum
    int rotated;
}              t_main_char;

typedef struct s_enemy {
    //rect holds position and dimensions
    //of enemy
    SDL_Rect rect;
    //texture
    SDL_Texture *texture;
    SDL_Surface *surf;
    int index;
    int health;
    int damage;
    int speed_x;
    int speed_y;
    int taimer;
    int gender;
    //one of the directions from 
    //rotate_dirs enum
    int rotated;
    bool isdead;
    bool iscounted;
}              t_enemy;

typedef struct s_bullet {
    //rect holds position and dimensions
    //of bullet
    SDL_Rect rect;
    //texture
    SDL_Texture *texture;
    SDL_Surface *surf;

    int damage;
    int speed_x;
    int speed_y;
}              t_bullet;

typedef struct s_obstacle {
    //rect holds position and dimensions
    //of obstacle
    SDL_Rect rect;
}              t_obstacle;

typedef struct s_other_obj {
    //rect holds position and dimensions
    //of other object
    SDL_Rect rect;
    //texture
    SDL_Texture *texture;
    SDL_Surface *surf;
    //assosiate function with an obj
    //for example a function that is called 
    //when clicking a button
    //can be changed
    void (*associated_func)(); 
}              t_other_obj;

//inits main charachter
t_main_char *mx_init_main_char(const char *sprite_filename, SDL_Rect start_rect);
//draws main character
void mx_draw_main_char(SDL_Renderer *renderer, t_main_char *main_char);
//frees memory for a main character
void mx_free_main_char(t_main_char *m_char);
//creates new instance of a bullet with given paramethers
t_bullet *mx_create_bullet(const char *filename, SDL_Rect rect, int damage, int sp_x, int sp_y);
//draws the bullet on the renderer
void mx_draw_bullet(SDL_Renderer *renderer, t_bullet *bul);
//frees memory for one bullet
void mx_free_bullet(t_bullet **bul);
void mx_free_all_bullets(t_list **bullets);
//also destroys bullets that got out of the screen
//Check if data in a list is NULL please
void mx_update_bullet_positions(t_list *bullets);
bool mx_is_point_in_rect(int x, int y, int h, SDL_Rect rect);
//returns number of bullets that hit enemies
//destoys bullets that have hit
//Check if data in a list is NULL please
int mx_bullet_enemy_collision(t_list *bullets, t_list *enemies);
//creates bullets that go from character to mouse according to hero level
//level 2 and 3 are TODO
void mx_shoot(t_main_char *hero, t_list **bullets, int mouse_x, int mouse_y);

//draws all bullets from the list
void mx_draw_all_bullets(SDL_Renderer *rend, t_list *bullets);

//checks if bullets collided wit hobstacles
//if so - deletes the bulet
//Check if data in a list is NULL please
void mx_bullet_obst_collision(t_list *bullets, t_list *obstacles);
//deletes empty nodes from list
//broken
void mx_cleanup_empty_nodes(t_list **list);
//shecks if enemy bullets hit hero
void mx_enemybullet_hero_collision(t_list *bullets, t_main_char *hero);
//makes an enemy shoot a bullet
void mx_enemy_shoot(t_list **enemy_bullets, t_enemy *enemy, t_main_char *hero);
//returns number of enemies with hp <= 0
//deletes data about them
int mx_count_killed(t_list *enemies, int size, Mix_Chunk *arr[size]);
//spawn jaba
t_enemy *create_boss(char *filename, SDL_Rect rect, int health, int damage);

void mx_bullet_boss_collision(t_list *bullets, t_enemy *enem);
char mx_dir_def2(int m_x, int m_y, t_main_char *hero);
int gameover_win(SDL_Renderer *renderer);

//spawn first enemies
void spawn_1wave(t_list **enemies);
void spawn_2wave(t_list **enemies);
void mx_text_to_screen(SDL_Renderer *rend, SDL_Rect rect, char *str);


//starts first level
int start_1_level(SDL_Renderer *renderer);
int start_2_level(SDL_Renderer *renderer);
int start_3_level(SDL_Renderer *renderer);

char mx_char_movement(const Uint8 *keysPressed, t_main_char *hero, SDL_Renderer *renderer, int i, int j, SDL_Surface *arr[i][j], t_list *obstacles_map1);
bool mx_check_collision(t_main_char *hero, t_list *obstacles_map, char c);
void mx_change_tex(t_main_char *hero, char c, SDL_Renderer *renderer);
void mx_move_anim(t_main_char *hero, char c, SDL_Renderer *renderer, int i, int j, SDL_Surface *arr[i][j]);
void mx_load_sprites(int i, int j, SDL_Surface *arr[i][j]);

t_other_obj *mx_init_butt(const char *filename, SDL_Rect rect);
void mx_draw_main_butt(SDL_Renderer *renderer, t_other_obj *butt);
bool mx_is_Hovered(t_other_obj *butt, int mouse_x, int mouse_y);
void mx_change_butt_tex(t_other_obj *butt, SDL_Renderer *renderer, const char *filename);
int guidewind(SDL_Window *win, SDL_Renderer *renderer, Mix_Chunk *menu_eff);
int madebywind(SDL_Window *win, SDL_Renderer *renderer, Mix_Chunk *menu_eff);
int mainwind (SDL_Window *win, SDL_Renderer *renderer, Mix_Chunk *menu_eff);
int jokewind(SDL_Window *win, SDL_Renderer *renderer, Mix_Chunk *menu_eff);
int trueguidewind(SDL_Window *win, SDL_Renderer *renderer, Mix_Chunk *menu_eff);
bool mx_check_load(SDL_Window *win, SDL_Renderer *renderer);
void mx_draw_gold_ring(SDL_Renderer *renderer, t_obstacle *server);
void mx_draw_server(SDL_Renderer *renderer, t_obstacle *server, int ifif);
t_obstacle *mx_create_obstacle(int x, int y, int width, int height);
void mx_server_blinks(SDL_Renderer *renderer);

void mx_free_enemy(t_enemy *enemy);
void mx_draw_enemy(SDL_Renderer *renderer, t_enemy **enem);
t_enemy *mx_create_enemy(const char *sprite_filename, SDL_Rect start_rect, int index);
void mx_create_enemy_coords(int *x, int *y,int second_dim, int (*obstacles)[second_dim], int obstacle_count);
bool mx_char_enemy_collision(t_main_char *ch, t_enemy *en);
void mx_fill_obstacles_map1(t_list **obstacles_map);
void mx_fill_obstacles_map2(t_list **obstacles_map);
void mx_fill_obstacles_map3(t_list **obstacles_map);

bool mx_enem_col(t_obstacle *obstacle, t_enemy *enemies);
void mx_enemy_move(t_list *obstacles, t_main_char *hero,  t_enemy *enemies, float speed, SDL_Renderer *renderer, int i, int j, SDL_Surface *arr[i][j]);
void mx_enemy_path_speed(t_main_char *hero, t_enemy *enemies, float speed);
void mx_load_enemies(int i, int j, SDL_Surface *arr[i][j]);
void mx_anims_move_enemies(t_enemy *enemies, SDL_Renderer *renderer, int i, int j, SDL_Surface *arr[i][j]);
void mx_draw_all_enemies(t_list *enemies, t_main_char *hero, t_list *obstacles_map, SDL_Renderer *renderer,int i, int j, SDL_Surface *enemy_text[i][j], int k, SDL_Surface *students_text[k][k]);
void mx_load_students(int i, int j, SDL_Surface *arr[i][j]);

int introwind(SDL_Renderer *renderer);
void mx_init_lines(int size, Mix_Chunk *arr[size]);
void mx_kill_line(int size, Mix_Chunk *arr[size]);

char mx_dir_def(int mouse_x, int mouse_y, t_main_char *hero);
void winwin(SDL_Renderer *renderer);

