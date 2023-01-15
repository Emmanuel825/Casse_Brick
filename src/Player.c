/*
 * Player.h
 *
 *  Created on: 8 janv. 2023
 *      Author: emmanuel
 */

#include "Player.h"

#define mRGBA_r(RGBA)		((Uint8)(RGBA>>24))
#define mRGBA_g(RGBA)		((Uint8)(RGBA>>16))
#define mRGBA_b(RGBA)		((Uint8)(RGBA>>8))
#define mRGBA_a(RGBA)		((Uint8)(RGBA>>0))
#define mRGBA(r,g,b,a)		((Uint32)r<<24|(Uint32)g<<16|(Uint32)b<<8|(Uint32)a<<0)

struct s_player{
	int color;
	SDL_Rect rect;
};

t_player *NewPlayer(int x, int y, int w, int h, int color){
	t_player *pPlayer=(t_player*)malloc(sizeof(t_player));
	pPlayer->rect=(SDL_Rect){x,y,w,h};
	pPlayer->color=color;

	return pPlayer;
}
void PlayerDel(t_player *pPlayer){
	free(pPlayer);
}

void PlayerDraw(t_player *pPlayer, SDL_Renderer *pRenderer){
	SDL_SetRenderDrawColor(pRenderer, mRGBA_r(pPlayer->color),mRGBA_g(pPlayer->color),mRGBA_b(pPlayer->color),mRGBA_a(pPlayer->color));
	SDL_RenderFillRect(pRenderer, &pPlayer->rect);
}

void PlayerSetX(t_player *pPlayer, int x, SDL_Rect scene){
	if((x-(pPlayer->rect.w/2))<=scene.x){
		pPlayer->rect.x=scene.x;
	}
	else if((x+(pPlayer->rect.w/2))>=(scene.x+scene.w)){
		pPlayer->rect.x=(scene.x+scene.w)-(pPlayer->rect.w);
	}
	else {
		pPlayer->rect.x=x-(pPlayer->rect.w/2);
	}
}

SDL_Rect PlayerGetRect(t_player *pPlayer){
	return pPlayer->rect;
}
