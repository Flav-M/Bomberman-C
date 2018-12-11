/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   window.h
 * Author: flavi
 *
 * Created on 11 décembre 2018, 22:34
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "game.h"

typedef struct {
    
    // Variables de la SDL et de l'écran 
    SDL_Point screenSize;
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;
    
    // Police d'écriture
    TTF_Font* pFont;
    
} stWindow;

stWindow* window_init();
void window_destroy(stWindow* window);

#endif /* WINDOW_H */

