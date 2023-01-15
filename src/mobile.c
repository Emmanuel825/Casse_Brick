/*
 * mobile.c
 *
 *  Created on: 24 nov. 2022
 *      Author: emmanuel
 */


#include "mobile.h"
#define mRGBA_r(RGBA)	((Uint8)(RGBA>>24))
#define mRGBA_g(RGBA)	((Uint8)(RGBA>>16))
#define mRGBA_b(RGBA)	((Uint8)(RGBA>>8))
#define mRGBA_a(RGBA)	((Uint8)(RGBA>>0))

struct s_mobile{
	int color;
	SDL_Rect mobile;
	SDL_Point speed;
};

t_mobile *MobileNew(int width, int height, int x, int y, int color, SDL_Point speed){
	t_mobile *pMobile=(t_mobile*)malloc(sizeof(t_mobile));
	pMobile->mobile=(SDL_Rect){x, y, width, height};
	pMobile->color=color;
	pMobile->speed=speed;
	return pMobile;
}
void MobileDel(t_mobile *pMobile){
	free(pMobile);
}
void MobileMove(t_mobile *pMobile, SDL_Rect *area){
	pMobile->mobile.x+=pMobile->speed.x;
	pMobile->mobile.y+=pMobile->speed.y;
	if(((pMobile->mobile.x+pMobile->mobile.w)>=(area->x+area->w))||((pMobile->mobile.x)<=area->x)){
		pMobile->speed.x*=-1;
	}
	if(((pMobile->mobile.y+pMobile->mobile.h)>=(area->y+area->h))||((pMobile->mobile.y)<=area->y)){
		pMobile->speed.y*=-1;
	}
}

void MobileDraw(t_mobile *pMobile, SDL_Renderer *pRenderer){
	SDL_SetRenderDrawColor(pRenderer, mRGBA_r(pMobile->color), mRGBA_g(pMobile->color), mRGBA_b(pMobile->color), mRGBA_a(pMobile->color));
	SDL_RenderFillRect(pRenderer, &pMobile->mobile);
}


SDL_Rect MobileGetFrame(t_mobile *pMobile){
	return pMobile->mobile;
}
void MobileSetSpeedX(t_mobile *pMobile, int speed){
	pMobile->speed.x*=speed;
}

void MobileSetSpeedY(t_mobile *pMobile, int speed){
	pMobile->speed.y*=speed;
}
