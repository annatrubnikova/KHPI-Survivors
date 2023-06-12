#include "../inc/header.h"

void mx_kill_line(int size, Mix_Chunk *arr[size]){
    if (rand() % 100 < 30){
        Mix_PlayChannel(-1, arr[rand() % 4], 0);
    }
}

void mx_init_lines(int size, Mix_Chunk *arr[size]){
    arr[0] = Mix_LoadWAV("resource/google_it.wav");
    arr[1] = Mix_LoadWAV("resource/oracle_is_right.wav");
    arr[2] = Mix_LoadWAV("resource/peer_to_peer.wav");
    arr[3] = Mix_LoadWAV("resource/read_pdf.wav");
    return;
}

