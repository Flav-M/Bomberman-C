/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   menu.h
 * Author: flavi
 *
 * Created on 11 décembre 2018, 22:39
 */

#ifndef MENU_H
#define MENU_H

#include "window.h"

typedef struct {

    // Police d'écriture
    TTF_Font* pFont;

    // Texture
    SDL_Texture* ptexBackground;
    SDL_Texture* ptexMonoTexture;
    SDL_Texture* ptexMultiTexture;
    SDL_Texture* ptexQuitTexture;
    SDL_Surface* ptexSurface;
    
    // Indique quelle option du menu est selectionée
    int menuOptionSel;
    int intOption;

    // Jeu
    SDL_Rect backgroundPositionRect;
    SDL_Rect monoPositionRect;
    SDL_Rect multiPositionRect;
    SDL_Rect quitPositionRect;
    SDL_Rect destinationText;


} stMenu;

stMenu* menu_init(stWindow* window);
void menu_destroy(stMenu* menu, stWindow* window);
void menu_draw(stMenu* menu, stWindow* window);
int menu_event(stMenu* menu, stWindow* window);
int whereClick(int x, int y, struct SDL_Rect* rect);
void showMonoOption(stMenu* menu, stWindow* window);
void showMultiOption(stMenu* menu, stWindow* window);
void showQuitOption(stMenu* menu, stWindow* window);
int updateMenuOption(stMenu* menu, stWindow* window, SDL_Keycode key);
void showMenuOption(stMenu* menu, stWindow* window, SDL_Texture* texTarget, 
        int x, int y, int width, int heigth, char* name);
void setMenuOptionGlow(stMenu* menu);
int selectMenuOption(stMenu* menu, stWindow* window);

#endif /* MENU_H */

