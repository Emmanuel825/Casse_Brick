/*
 * Player.c
 *
 *  Created on: 8 janv. 2023
 *      Author: emmanuel
 */


#include<SDL2/SDL.h>
#include "mobile.h"

typedef struct s_player t_player;

t_player *NewPlayer(int x, int y, int w, int h, int color);
void PlayerDel(t_player *pPlayer);
void PlayerDraw(t_player *pPlayer, SDL_Renderer *pRenderer);
void PlayerSetX(t_player *pPlayer, int x, SDL_Rect scene);
SDL_Rect PlayerGetRect(t_player *pPlayer);
