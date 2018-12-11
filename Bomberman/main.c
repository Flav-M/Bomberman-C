/* 
 * File:   main.c
 * Author: flavi
 *
 * Created on 11 décembre 2018, 15:14
 */

#include "game.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    stWindow* window = window_init();
    
    stGame* game = game_init(window);
    stMenu* menu = menu_init(window);
    
    int quit = 0;
    int menu_select = 0;
    while (quit != -1) {
        while (menu_select != -1) {
            switch (menu_select) {
                case 1:
                    // dessiner le menu
                    menu_draw(menu, window);
                    // gestion des events
                    menu_select = menu_event(menu, window);
                    SDL_Delay(20):
                    break;
                case 2:
                    // dessinef le jeu multi
                    game_draw(game, window);
                    // gestion des events
                    menu_select = game_event(game, window);
                    SDL_Delay(20);
                    break;
                case 3:
                    // dessiner le jeu solo
                    solo_draw(solo, window);
                    // Gerer les events
                    menu_select = solo_event(solo, window);
                    SDL_Delay(20);
                    break;
                case -1:
                    break;
                default:
                    break;
            }
        }
        
        quit = -1;
    }
    
    menu_destroy(menu, window);
    solo_destroy(solo, window);
    game_destroy(game, window);
    window_destroy(window);
    
    return (EXIT_SUCCESS);
}

