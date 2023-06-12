#include "../inc/header.h"

int main()
{
    //init everything needed for game operation 
    //TODO
    srand(time(NULL));


    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return 0;
    TTF_Init();
    SDL_Window *win = SDL_CreateWindow("Window",
                                        SDL_WINDOWPOS_CENTERED, 
                                        SDL_WINDOWPOS_CENTERED,
                                        SCR_WIDTH, SCR_HEIGHT, 0);
    if (win == NULL){
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,
                                                 SDL_RENDERER_PRESENTVSYNC
                                                |SDL_RENDERER_ACCELERATED);
   
    if (!renderer){
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_DisplayMode dm;
    if (SDL_GetDisplayMode(0, 0, &dm) != 0){
        printf("get dm error\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    //the menu screen
    //can be done by using a loop similar to the main one
    //show background image
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        printf("sound error\n");
        return 1;
    }
    Mix_Music *main_bgm = Mix_LoadMUS("resource/menu.mp3");
    Mix_Chunk *menu_eff = Mix_LoadWAV("resource/menu_hov.wav");
    Mix_PlayMusic(main_bgm, -1);
    int flag = mainwind(win, renderer, menu_eff);
    if (flag == 0) return 0;
    flag = introwind(renderer);
    if (flag == 0) return 0;
    Mix_HaltMusic();
    Mix_Chunk *shoot_sound = Mix_LoadWAV("resource/shoot.wav");
    
    //bgrd
    start_1_level(renderer);
    start_2_level(renderer);
    start_3_level(renderer);
    winwin(renderer);
    //START OF THE LEVEL LOADING
    Mix_FreeChunk(shoot_sound);
    Mix_FreeMusic(main_bgm);
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}

int start_1_level(SDL_Renderer *renderer) {
    int kills = 0;

    SDL_Surface *surface = IMG_Load("resource/map1.png");
    SDL_Texture *map1 = SDL_CreateTextureFromSurface(renderer, surface);
    surface = IMG_Load("resource/front_map1.png");
    SDL_Texture *front_map1 = SDL_CreateTextureFromSurface(renderer, surface);

    t_main_char *hero = mx_init_main_char(MC_DOWN_STAND,
                                         (SDL_Rect){625, 300, GG_WIDTH, GG_HEIGHT});
    if (hero == NULL) return 1;
      t_list *enemies = NULL;
    t_list *bullets = NULL;
    
    //t_list *enemy_bullets = NULL;

    Mix_Chunk *shoot_sound = Mix_LoadWAV("resource/shoot.wav");
    Mix_Chunk *kill_lines[4];
    Mix_Chunk *zombie = Mix_LoadWAV("resource/zombie_sound.wav");
    mx_init_lines(4, kill_lines);
    t_list *obstacles_map1 = NULL;
    mx_fill_obstacles_map1(&obstacles_map1);
    Mix_Music *bgm = Mix_LoadMUS("resource/park.mp3");

    SDL_Event evt;
    bool isRunning = true;
    const Uint8 *keysPressed;
    char direct;
    SDL_Surface *sprites[4][3];
    mx_load_sprites(4, 3, sprites);
    SDL_Surface *enemy_text[2][2];
    mx_load_enemies(2, 2, enemy_text);
    SDL_Surface *students_text[4][2];
    mx_load_students(4, 2, students_text);
    int mouse_x = 0, mouse_y = 0;
    double last_shot = clock();
    //the main game loop
    spawn_1wave(&enemies);
    Mix_PlayMusic(bgm, -1);
    while (isRunning)
    {
        SDL_RenderClear(renderer);
        SDL_GetMouseState(&mouse_x, &mouse_y);
        //Deal with user input during the game
        //TODO
        // CHeck every event in event queue
        while (SDL_PollEvent(&evt))
        {
            //parse event types
            switch (evt.type)
            {
                case SDL_KEYDOWN:
                    keysPressed = SDL_GetKeyboardState(NULL);
                    // End program execution on ESC
                    if (evt.key.keysym.sym == SDLK_ESCAPE){
                        isRunning = false;
                        //exit(1);
                        break;  
                        //exit(1); 
                    }
                    direct = mx_char_movement(keysPressed, hero, renderer, 4, 3, sprites, obstacles_map1);
                   // SDL_Delay(10);
                    break;

                case SDL_KEYUP:
                    mx_change_tex(hero, direct, renderer);
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    if ((double)((clock() - last_shot) / CLOCKS_PER_SEC * 3) > 0.3){
                        mx_change_tex(hero, mx_dir_def(mouse_x, mouse_y, hero), renderer);
                        mx_shoot(hero, &bullets, mouse_x, mouse_y);
                        Mix_PlayChannel(-1, shoot_sound, 0);
                        last_shot = clock();
                    }
                    break;

                case SDL_QUIT:
                    // .End program execution on quit
                    isRunning = false;
                    exit(1);
                    break;
                default:
                    //mx_change_tex(hero, direct, renderer);
                    break;
            }
        }

        mx_update_bullet_positions(bullets);

        mx_bullet_obst_collision(bullets, obstacles_map1);

        mx_bullet_enemy_collision(bullets, enemies);
        kills +=  mx_count_killed(enemies, 4, kill_lines);
        char hpbuff[20];
        sprintf(hpbuff, "HP: %i", hero->health);
        //printf("%s\n", hpbuff);
        mx_text_to_screen(renderer, (SDL_Rect){0, 0, 200, 50}, hpbuff);

        if (hero->health <= 0) {
            //printf("Game over\nPomer vid krinzhy\n");
            gameover_win(renderer);
            exit(1);
        }
        if (kills >= 25) {
            isRunning = false;
        }
        //Display all entities from corresponding lists
        SDL_RenderCopy(renderer, map1, NULL, NULL);
        
        mx_draw_all_enemies(enemies, hero, obstacles_map1, renderer, 2, 2, enemy_text, 4, students_text);
        mx_draw_all_bullets(renderer, bullets);
        mx_draw_main_char(renderer, hero);
        SDL_RenderCopy(renderer, front_map1, NULL, NULL);
        mx_text_to_screen(renderer, (SDL_Rect){0, 0, 200, 50}, hpbuff);
        SDL_RenderPresent(renderer);
        if (rand() % 100 < 2){
            Mix_PlayChannel(-1, zombie, 0);
        }

        SDL_Delay(16);
    }
    //Free all allocated memory
    //TODO
    mx_free_main_char(hero);
    mx_free_all_bullets(&bullets);
    /*
    for (t_list *tmp = enemies; tmp != NULL; tmp = tmp->next) {
            t_enemy *enem = (t_enemy *)(tmp->data);
            if (enem == NULL) continue;
            mx_free_enemy(enem);
            tmp->data = NULL;
    }*/
    mx_clear_list(&enemies);
    
    Mix_HaltMusic();
    Mix_FreeMusic(bgm);
    Mix_FreeChunk(shoot_sound);
    Mix_FreeChunk(zombie);
    for (int i = 0; i < 4; i++){
        Mix_FreeChunk(kill_lines[i]);
    }
    return 0;
}


int start_2_level(SDL_Renderer *renderer) {
    int kills = 0;
    SDL_Surface *surface = IMG_Load("resource/map2.png");
    SDL_Texture *map2 = SDL_CreateTextureFromSurface(renderer, surface);
    surface = IMG_Load("resource/front_map2.png");
    SDL_Texture *front_map2 = SDL_CreateTextureFromSurface(renderer, surface);

    t_main_char *hero = mx_init_main_char(MC_DOWN_STAND,
                                         (SDL_Rect){625, 300, GG_WIDTH, GG_HEIGHT});
    if (hero == NULL) return 1;
      t_list *enemies = NULL;
    t_list *bullets = NULL;
    
    //t_list *enemy_bullets = NULL;

    Mix_Music *campus_bgm = Mix_LoadMUS("resource/campus_sound.mp3");
    Mix_Chunk *shoot_sound = Mix_LoadWAV("resource/shoot.wav");
    Mix_Chunk *kill_lines[4];
    Mix_Chunk *zombie = Mix_LoadWAV("resource/zombie_sound.wav");
    mx_init_lines(4, kill_lines);
    t_list *obstacles_map2 = NULL;
    mx_fill_obstacles_map2(&obstacles_map2);



    SDL_Event evt;
    bool isRunning = true;
    const Uint8 *keysPressed;
    char direct;
    SDL_Surface *sprites[4][3];
    mx_load_sprites(4, 3, sprites);
    SDL_Surface *enemy_text[2][2];
    mx_load_enemies(2, 2, enemy_text);
    SDL_Surface *students_text[4][2];
    mx_load_students(4, 2, students_text);
    int mouse_x = 0, mouse_y = 0;
    double last_shot = clock();
    //the main game loop
    spawn_2wave(&enemies);
    Mix_PlayMusic(campus_bgm, -1);
    while (isRunning)
    {
        SDL_RenderClear(renderer);
        SDL_GetMouseState(&mouse_x, &mouse_y);
        //Deal with user input during the game
        //TODO
        // CHeck every event in event queue
        while (SDL_PollEvent(&evt))
        {
            //parse event types
            switch (evt.type)
            {
                case SDL_KEYDOWN:
                    keysPressed = SDL_GetKeyboardState(NULL);
                    // End program execution on ESC
                    if (evt.key.keysym.sym == SDLK_ESCAPE){
                        isRunning = false;  
                        //exit(1);
                        //exit(1); 
                    }
                    direct = mx_char_movement(keysPressed, hero, renderer, 4, 3, sprites, obstacles_map2);
                   // SDL_Delay(10);
                    break;

                case SDL_KEYUP:
                    mx_change_tex(hero, direct, renderer);
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    if ((double)((clock() - last_shot) / CLOCKS_PER_SEC * 3) > 0.3){
                        mx_change_tex(hero, mx_dir_def(mouse_x, mouse_y, hero), renderer);
                        mx_shoot(hero, &bullets, mouse_x, mouse_y);
                        Mix_PlayChannel(-1, shoot_sound, 0);
                        last_shot = clock();
                    }
                    break;

                case SDL_QUIT:
                    // .End program execution on quit
                    isRunning = false;
                    exit(1);
                    break;
                default:
                    //mx_change_tex(hero, direct, renderer);
                    break;
            }
        }

        mx_update_bullet_positions(bullets);

        mx_bullet_obst_collision(bullets, obstacles_map2);

        mx_bullet_enemy_collision(bullets, enemies);
        kills += mx_count_killed(enemies, 4, kill_lines);
        char hpbuff[20];
        sprintf(hpbuff, "HP: %i", hero->health);

        if (hero->health <= 0) {
            //printf("Game over\nPomer vid krinzhy\n");
            gameover_win(renderer);
            exit(1);
        }
        if (kills >= 30) {
            isRunning = false;
        }

        //Display all entities from corresponding lists
        SDL_RenderCopy(renderer, map2, NULL, NULL);
        
        mx_draw_all_enemies(enemies, hero, obstacles_map2, renderer, 2, 2, enemy_text, 4, students_text);
        
        mx_draw_all_bullets(renderer, bullets);
        mx_draw_main_char(renderer, hero);
        SDL_RenderCopy(renderer, front_map2, NULL, NULL);
         mx_text_to_screen(renderer, (SDL_Rect){0, 0, 200, 50}, hpbuff);
        SDL_RenderPresent(renderer);
        if (rand() % 100 < 2){
            Mix_PlayChannel(-1, zombie, 0);
        }

        SDL_Delay(16);
    }
    Mix_HaltMusic();
    //Free all allocated memory
    //TODO
    mx_free_main_char(hero);
    mx_free_all_bullets(&bullets);
    
    /*for (t_list *tmp = enemies; tmp != NULL; tmp = tmp->next) {
            t_enemy *enem = (t_enemy *)(tmp->data);
            if (enem == NULL) continue;
            mx_free_enemy(enem);
            tmp->data = NULL;
    }*/
    mx_clear_list(&enemies);
    Mix_FreeMusic(campus_bgm);
    Mix_FreeChunk(zombie);
    Mix_FreeChunk(shoot_sound);
    for (int i = 0; i < 4; i++){
        Mix_FreeChunk(kill_lines[i]);
    }
    return 0;
}


int start_3_level(SDL_Renderer *renderer) {
    int kills = 0;
    SDL_Surface *surface = IMG_Load("resource/map3.png");
    SDL_Texture *map3 = SDL_CreateTextureFromSurface(renderer, surface);
    surface = IMG_Load("resource/front_map3.png");
    SDL_Texture *front_map3 = SDL_CreateTextureFromSurface(renderer, surface);
    t_obstacle *server = mx_create_obstacle(601, 10, 76, 224);
    int ifif = 0;
    int isBossDied = 0;

    t_main_char *hero = mx_init_main_char(MC_DOWN_STAND,
                                         (SDL_Rect){625, 300, GG_WIDTH, GG_HEIGHT});
    if (hero == NULL) return 1;
      t_list *enemies = NULL;
    t_list *bullets = NULL;
    t_enemy *boss = create_boss(FROG, (SDL_Rect){SCR_WIDTH / 2 - 75, 20, 150, 150}, 400, 100);
    
    t_list *enemy_bullets = NULL;

    Mix_Music *server_bgm = Mix_LoadMUS("resource/server.mp3");
    Mix_Chunk *shoot_sound = Mix_LoadWAV("resource/shoot.wav");
    Mix_Chunk *zombie = Mix_LoadWAV("resource/zombie_sound.wav");
    Mix_Chunk *zhaba = Mix_LoadWAV("resource/zhaba.wav");
    Mix_Chunk *kill_lines[4];
    mx_init_lines(4, kill_lines);
    t_list *obstacles_map3 = NULL;
    mx_fill_obstacles_map3(&obstacles_map3);



    SDL_Event evt;
    bool isRunning = true;
    const Uint8 *keysPressed;
    char direct;
    SDL_Surface *sprites[4][3];
    mx_load_sprites(4, 3, sprites);
    SDL_Surface *enemy_text[2][2];
    SDL_Surface *students_text[4][2];
    mx_load_students(4, 2, students_text);
    mx_load_enemies(2, 2, enemy_text);
    int mouse_x = 0, mouse_y = 0;
    double last_shot = clock();
    double last_shot_boss = clock();
    Mix_PlayMusic(server_bgm, -1);
    //the main game loop
    //spawn_1wave(&enemies);
    while (isRunning)
    {
        SDL_RenderClear(renderer);
        SDL_GetMouseState(&mouse_x, &mouse_y);
        //Deal with user input during the game
        //TODO
        // CHeck every event in event queue
        while (SDL_PollEvent(&evt))
        {
            //parse event types
            switch (evt.type)
            {
                case SDL_KEYDOWN:
                    keysPressed = SDL_GetKeyboardState(NULL);
                    // End program execution on ESC
                    if (evt.key.keysym.sym == SDLK_ESCAPE){
                        isRunning = false;  
                        //exit(1); 
                    }
                    if (evt.key.keysym.sym == SDLK_e){
                        isRunning = false;
                    }
                    direct = mx_char_movement(keysPressed, hero, renderer, 4, 3, sprites, obstacles_map3);
                   // SDL_Delay(10);
                    break;

                case SDL_KEYUP:
                    mx_change_tex(hero, direct, renderer);
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    if ((double)((clock() - last_shot) / CLOCKS_PER_SEC * 3) > 0.3){
                        mx_change_tex(hero, mx_dir_def(mouse_x, mouse_y, hero), renderer);
                        mx_shoot(hero, &bullets, mouse_x, mouse_y);
                        Mix_PlayChannel(-1, shoot_sound, 0);
                        last_shot = clock();
                    }
                    break;

                case SDL_QUIT:
                    // .End program execution on quit
                    isRunning = false;
                    exit(1);
                    break;
                default:
                    //mx_change_tex(hero, direct, renderer);
                    break;
            }
        }
        
        if ((double)((clock() - last_shot_boss) / CLOCKS_PER_SEC) > 0.6){
            mx_enemy_shoot(&enemy_bullets, boss, hero);

            if(boss != NULL) Mix_PlayChannel(-1, zhaba, 0);
            //Mix_PlayChannel(-1, shoot_sound, 0);
            last_shot_boss = clock();
        }


        mx_update_bullet_positions(enemy_bullets);
        mx_update_bullet_positions(bullets);

        mx_bullet_obst_collision(enemy_bullets, obstacles_map3);
        mx_bullet_obst_collision(bullets, obstacles_map3);

        mx_enemybullet_hero_collision(enemy_bullets, hero);
        char hpbuff[20];
        sprintf(hpbuff, "HP: %i", hero->health);
        if (hero->health <= 0) {
            //printf("Game over\nPomer vid krinzhy\n");
            gameover_win(renderer);
            exit(1);
        }
        if (kills >= 15) isRunning = false;

        mx_bullet_enemy_collision(bullets, enemies);
        mx_bullet_boss_collision(bullets, boss);
        
        mx_count_killed(enemies, 4, kill_lines);
        SDL_RenderCopy(renderer, map3, NULL, NULL);
        if (boss != NULL) {
            if (boss->health <= 0) {
                isBossDied = 1;
                mx_free_enemy(boss);
                boss = NULL;
            }    
        }
        if (isBossDied) {
            if (ifif == 0) {
                if (hero->rect.x >= 509 && hero->rect.x <= 713
                    && hero->rect.y >= 122 && hero->rect.y <= 271) {
                    mx_draw_gold_ring(renderer, server);
                }
                ifif++;
                mx_draw_server(renderer, server, 0);
            }
            else if (ifif == 1) {
                if (hero->rect.x >= 509 && hero->rect.x <= 713
                    && hero->rect.y >= 122 && hero->rect.y <= 271) {
                    mx_draw_gold_ring(renderer, server);
                }
                ifif--;
                mx_draw_server(renderer, server, 1);
            }
        }
        
        mx_draw_all_enemies(enemies, hero, obstacles_map3, renderer, 2, 2, enemy_text, 4, students_text);

        mx_draw_enemy(renderer, &boss);
        mx_draw_all_bullets(renderer, bullets);
        mx_draw_all_bullets(renderer, enemy_bullets);
        mx_draw_main_char(renderer, hero);
        SDL_RenderCopy(renderer, front_map3, NULL, NULL);
        mx_server_blinks(renderer);

         mx_text_to_screen(renderer, (SDL_Rect){0, 0, 200, 50}, hpbuff);
        SDL_RenderPresent(renderer);
        if (rand() % 100 < 2){
            Mix_PlayChannel(-1, zombie, 0);
        }

        SDL_Delay(16);
    }
    //Free all allocated memory
    //TODO
    Mix_HaltMusic();
    mx_free_main_char(hero);
    mx_free_all_bullets(&bullets);
    
    for (t_list *tmp = enemies; tmp != NULL; tmp = tmp->next) {
            t_enemy *enem = (t_enemy *)(tmp->data);
            if (enem == NULL) continue;
            mx_free_enemy(enem);
            tmp->data = NULL;
    }
    mx_clear_list(&enemies);
    
    Mix_FreeMusic(server_bgm);
    Mix_FreeChunk(shoot_sound);
    Mix_FreeChunk(zombie);
    Mix_FreeChunk(zhaba);
    for (int i = 0; i < 4; i++){
        Mix_FreeChunk(kill_lines[i]);
    }
    return 0;
}



