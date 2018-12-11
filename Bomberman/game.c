/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "game.h"

/**
 * Initialise la game et la SDL
 * @return 
 */
stGame* game_init(stWindow* window) {
    
    srand(time(NULL));
    
    stGame* game = NULL;
    game = malloc(sizeof(stGame));
    game->screenSize.x = 1280;
    game->screenSize.y = 960;
    game->pWindow = NULL;
    game->pRenderer = NULL;
    game->pTexBomber = NULL;
    game->pTexBomb = NULL;
    game->pTexBrick = NULL;
    game->pFont = NULL;
    game->pTexBoard = NULL;
    game->boardPositionRect.x = 0;
    game->boardPositionRect.y = 0;
    game->boardPositionRect.w = window->screenSize.x;
    game->boardPositionRect.h = window->screenSize.y;
    game->bomberPositionRect.x = game->screenSize.x /2;
    game->bomberPositionRect.y = game->screenSize.y /2;
    game->bomberPositionRect.w = 30;
    game->bomberPositionRect.h = 30;
    game->bombPositionRect.w = 15;
    game->bombPositionRect.h = 15;
    game->score = 0;
    game->hasBomb = 5;
    
    // Initialisation SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "impossible d'initiliaser la SDL %s\n", SDL_GetError());
        game_destroy(game, window);
        return NULL;
    }
    
    // Initalisation de la font
    if(TTF_Init() != 0) {
        fprintf(stderr, "impossible d'initiliaser la SDL_TTF %s\n", TTF_GetError());
        game_destroy(game, window);
        return NULL;
    }
    
    // Charger la police
    game->pFont = TTF_OpenFont("./Arial.ttf", 50);
    if (!game->pFont) {
        fprintf(stderr, "impossible de charger la police choisie : %s\n", TTF_GetError());
    }
    
    // création de la fenêtre
    game->pWindow = SDL_CreateWindow("Bomberman",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            game->screenSize.x, game->screenSize.y, SDL_WINDOW_SHOWN);
    if (game->pWindow) {
        // création du renderer
        game->pRenderer = SDL_CreateRenderer(game->pWindow,-1, SDL_RENDERER_ACCELERATED);
        if (!game->pRenderer) {
            fprintf(stderr, "impossible de créer le renderer %s\n", SDL_GetError());
            game_destroy(game, window);
            return NULL;
        }
    } else {
        fprintf(stderr, "imposible de créer la window SDL %s\n", SDL_GetError());
        game_destroy(game, window);
        return NULL;
    } 
    
    // chargement de la texture du board
    SDL_Surface* surfaceBoard = IMG_Load(".board.png");
    if (!surfaceBoard) {
        fprintf(stderr, "Impossible d'initialiser l'image board.png : %s\n", SDL_GetError());
        game_destroy(game, window);
        return NULL;
    } else {
        game->pTexBoard = SDL_CreateTextureFromSurface(window->pRenderer, surfaceBoard);
        if (!game->pTexBoard) {
            fprintf(stderr, "Impossible d'initialiser la texture : %s\n", SDL_GetError());
            game_destroy(game, window);
            return NULL;
        }
    }
    
    // chargement texture du bomber
    SDL_Surface* surfaceBomber = IMG_Load("./Bomberman.png");
    if (!surfaceBomber) {
        fprintf(stderr, "impossible de charger l'image Bomberman.png %s\n", IMG_GetError());
        game_destroy(game, window);
        return NULL;
    } else {
        game->pTexBomber = SDL_CreateTextureFromSurface(game->pRenderer, surfaceBomber);
        if (!game->pTexBomber) {
            fprintf(stderr, "impossible de créer la texture : %s\n", SDL_GetError());
            game_destroy(game, window);
            return NULL;
        }
        SDL_FreeSurface(surfaceBomber);
    }
    
    
    // chargemennt texture des bombes
    SDL_Surface* surfaceBomb = IMG_Load("./Bomb.png");
    if (!surfaceBomb) {
        fprintf(stderr, "impossible de charger l'image Bomb.png %s\n", IMG_GetError());
        game_destroy(game, window);
        return NULL;
    } else {
        game->pTexBomb = SDL_CreateTextureFromSurface(game->pRenderer, surfaceBomb);
        if (!game->pTexBomb) {
            fprintf(stderr, "impossible de créer la texture : %s\n", SDL_GetError());
            game_destroy(game, window);
            return NULL;
        }
        SDL_FreeSurface(surfaceBomb);
    }
    
    return game;
}

/**
 * Détruit jeu et sdl
 * @param game
 */

void game_destroy(stGame* game, stWindow* window){
    if (game) {
        if (game->pTexBoard) {
            SDL_DestroyTexture(game->pTexBoard);
        }
        
        if (game->pTexBomber) {
            SDL_DestroyTexture(game->pTexBomber);
        }
        
        if (game->pTexBomb) {
            SDL_DestroyTexture(game->pTexBomb);
        }
        
        if (game->pRenderer) {
            SDL_DestroyRenderer(game->pRenderer);
        }
        
        if (game->pWindow) {
            SDL_DestroyWindow(game->pWindow);
        }
        
        if (game->pFont) {
            TTF_CloseFont(game->pFont);
        }
        
        TTF_Quit();
        
        SDL_Quit();
    
        free(game);
    }
}


void game_draw(stGame* game, stWindow* window){
    
    // paint it black
    SDL_SetRenderDrawColor(game->pRenderer, 230, 230, 230, 200);
    SDL_RenderClear(window->pRenderer);
    
    // Afficher le board
    SDL_RenderCopy(window->pRenderer, game->pTexBoard, NULL, &game->boardPositionRect);
    
    // affiche le bomber
    SDL_RenderCopy(window->pRenderer, game->pTexBomber, NULL, &game->bomberPositionRect);
    
    // affiche une bombe
    SDL_RenderCopy(window->pRenderer, game->pTexBomb, NULL, &game->bombPositionRect);
    
    // présenter le rendu
    SDL_RenderPresent(window->pRenderer);
}

/**
 * Gestion des touches
 * @param game
 * @return result (qui vaut -1 pour quitter)
 */
int game_event(stGame* game, stWindow* window) {
    int result = 0;
    
    SDL_Event e;
    // récupérer un event
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            // on quitte
            result = -1;
        } else if (e.type == SDL_KEYDOWN) {
            // gestion des touches utiles
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE :
                    // quite le jeu
                    result = -1;
                    break;
                case SDLK_UP:
                case SDLK_DOWN:
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    game_moveBomber(game, e.key.keysym.sym, window);
                case SDLK_SPACE:
                    game_dropBomb(game, window);
                    break;
                default : 
                    fprintf(stderr, "touche inconnue %d\n", e.key.keysym.sym);
                    break;  
            }
        }
    }
    
    return result;
}


/**
 * Pour déplacer le bomber
 * @param game
 * @param direction
 */
void game_moveBomber(stGame* game, SDL_Keycode direction, stWindow* window) {
    if (direction == SDLK_UP) {
        if (game->bomberPositionRect.y > 0) {
            game->bomberPositionRect.y -=10;
        }
    } else if (direction == SDLK_DOWN) {
        if (game->bomberPositionRect.y < (game->screenSize.y - game->bomberPositionRect.h))
            game->bomberPositionRect.y += 10;
    } else if (direction == SDLK_LEFT) {
        if (game->bomberPositionRect.x > 0)
            game->bomberPositionRect.x -=10;
    } else if (direction == SDLK_RIGHT) {
        if (game->bomberPositionRect.x < (game->screenSize.x - game->bomberPositionRect.w))
            game->bomberPositionRect.x += 10;
    } else
        fprintf(stderr, "direction inconnue !!!\n");
}



/**
 * fait apparaître une bombe lorsque le bomber appuie sur la touche espace
 * @param game
 */
void game_dropBomb(stGame* game, stWindow* window) {
    if (game->hasBomb > 0) {
        game->bombPositionRect.x = game->bomberPositionRect.x;
        game->bombPositionRect.y = game->bomberPositionRect.y;
    }
}