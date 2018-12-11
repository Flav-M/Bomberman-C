/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   game.h
 * Author: flavi
 *
 * Created on 11 décembre 2018, 15:16
 */

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "window.h"


typedef struct {
    
    // Variables de la SDL et de l'écran 
    SDL_Point screenSize;
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;
    
    // Police d'écriture
    TTF_Font* pFont;
    
    // Textures
    SDL_Texture* pTexBomber;
    SDL_Texture* pTexBomb;
    SDL_Texture* pTexBrick;
    SDL_Texture* pTexBoard;
    
    // jeu
    SDL_Rect bomberPositionRect;
    SDL_Rect bombPositionRect;
    SDL_Rect brickPositionRect;
    SDL_Rect boardPositionRect;
    int score;
    int hasBomb;
    
    
} stGame;


stGame* game_init(stWindow* window);
void game_destroy(stGame* game, stWindow* window);
void game_draw(stGame* game, stWindow* window);
int game_event(stGame* game, stWindow* window);
void game_moveBomber(stGame* game, SDL_Keycode direction, stWindow* window);
void game_dropBomb(stGame* game, stWindow* window);



#endif /* GAME_H */

