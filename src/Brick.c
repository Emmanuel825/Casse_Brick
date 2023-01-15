/*
 * Brick.c
 *
 *  Created on: 25 nov. 2022
 *      Author: emmanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include<SDL2/SDL.h>
#include "Brick.h"
#define mRGBA_r(RGBA)		((Uint8)(RGBA>>24))
#define mRGBA_g(RGBA)		((Uint8)(RGBA>>16))
#define mRGBA_b(RGBA)		((Uint8)(RGBA>>8))
#define mRGBA_a(RGBA)		((Uint8)(RGBA>>0))

struct s_brick{
	SDL_Rect birck;
	int width;
	int height;
	int x;
	int y;
	int color;
};

t_brick *BrickNew(int width, int height, int x, int y, int color){
	t_brick *pBrick=(t_brick*)malloc(sizeof(t_brick));
	pBrick->birck.w=width;
	pBrick->birck.h=height;
	pBrick->birck.x=x;
	pBrick->birck.y=y;
	pBrick->color=color;
	return pBrick;
}
void BrickDel(t_brick *pBrick){
	free(pBrick);
}

void BrickDraw(t_brick *pBrick, SDL_Renderer *pRenderer){
	SDL_SetRenderDrawColor(pRenderer, mRGBA_r(pBrick->color), mRGBA_g(pBrick->color), mRGBA_b(pBrick->color), mRGBA_a(pBrick->color));
	SDL_RenderFillRect(pRenderer, &pBrick->birck);
}

SDL_Rect BrickGetFrame(t_brick *pBrick){
	return pBrick->birck;
}
