#include "../inc/header.h"

void mx_text_to_screen(SDL_Renderer *rend, SDL_Rect rect, char *str) {
    TTF_Font *font = TTF_OpenFont("./resource/PublicPixel.ttf", 35);
    SDL_Color color = {255, 0, 0, 255};
    SDL_Surface *surf = TTF_RenderText_Solid(font, str, color);
    SDL_Texture *text = SDL_CreateTextureFromSurface(rend, surf);
    SDL_RenderCopy(rend, text, NULL, &rect);
    SDL_DestroyTexture(text);
    TTF_CloseFont(font);
    SDL_FreeSurface(surf);
}
