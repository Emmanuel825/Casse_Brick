/*
 * App.c
 *
 *  Created on: 24 nov. 2022
 *      Author: emmanuel
 */
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "App.h"
#include "mobile.h"
#include "Brick.h"
#include "Player.h"
#include "Container.h"
#define mRGBA_r(RGBA)		((Uint8)(RGBA>>24))
#define mRGBA_g(RGBA)		((Uint8)(RGBA>>16))
#define mRGBA_b(RGBA)		((Uint8)(RGBA>>8))
#define mRGBA_a(RGBA)		((Uint8)(RGBA>>0))
#define mRGBA(r,g,b,a)		((Uint32)r<<24|(Uint32)g<<16|(Uint32)b<<8|(Uint32)a<<0)
#define mBitToggle(f,m)		((f)^=(m))
#define mIsBitSet(f,m)		(((f)&(m))==(m))
typedef enum e_etat{
	IS_APP_PAUSED	=0x80000000
}t_etat;
struct s_app{
	SDL_Window			*			pWindow;
	SDL_Renderer		*			pRenderer;
	SDL_TimerID						timer;
	SDL_Rect						area;
	SDL_Event						event;
	t_container			*			pMobiles;
	t_container			*			pBricks;
	t_player			*			pPlayer;

	t_etat							etats;
	int								end;
	int colorBkg;
};

void _AppDraw(t_app *pApp);
Uint32 _AppAnimate(Uint32 intervall, t_app *pApp);

/**************************Casse-Brique*************************/
int _AppBrickDel(t_mobile *pMobile, t_brick *pBrick);
int _AppBrickEndGame(t_container *pBrick);
/**************************************************************/

t_app *AppNew(int width, int height, int colorBkg){
	srand((unsigned int)time(NULL));
	t_app *pApp=(t_app*)malloc(sizeof(t_app));
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		fprintf(stderr,"failed to init SDL : %s", SDL_GetError());

	}
	pApp->pWindow=SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if(pApp->pWindow==NULL){
		fprintf(stderr,"failed to create window : %s", SDL_GetError());

	}
	pApp->pRenderer=SDL_CreateRenderer(pApp->pWindow, -1, SDL_RENDERER_ACCELERATED);
	if(pApp->pRenderer==NULL){
		fprintf(stderr,"failed to create accelerated renderer : %s", SDL_GetError());
		pApp->pRenderer=SDL_CreateRenderer(pApp->pWindow, -1, SDL_RENDERER_SOFTWARE);
		if(pApp->pRenderer==NULL){
			fprintf(stderr,"failed to create software renderer : %s", SDL_GetError());

		}
	}
	pApp->pPlayer=NewPlayer(APP_PLAYER_X, APP_PLAYER_Y, APP_PLAYER_WIDTH, 10, mRGBA(0,255,0,0));
	pApp->pMobiles=ContainerNew((t_ptfvV)MobileDel);
	pApp->pBricks=ContainerNew((t_ptfvV)BrickDel);
	int brickSupp=0, brickWidth=0, brickPadding=0;
	for(int i=0;i<APP_BRICK_NB_ROW;i++){
		brickPadding=APP_BRICK_AREA_MARGIN_HRZ;
		for(int k=0;k<APP_BRICK_NB_COL;k++){
			brickWidth=APP_BRICK_WIDTH;
			if(((i%2)!=0) && ((k==0)||(k==APP_BRICK_NB_COL-1))){
				if(brickSupp==0 && k==APP_BRICK_NB_COL-1){
					k--;
					brickSupp=1;
				}
				else {
					brickSupp=0;
					brickWidth=APP_BRICK_WIDTH/2;
				}
			}
			ContainerPushfront(pApp->pBricks, BrickNew(
					brickWidth,
					APP_BRICK_HEIGHT,
					brickPadding,
					((APP_BRICK_AREA_MARGIN_VER)+(APP_BRICK_HEIGHT*i)),
					mRGBA(
							(70+(rand()%105)),
							(70+(rand()%105)),
							(70+(rand()%105)),
							(70+(rand()%105))
						)));
			brickPadding+=brickWidth;
		}
	}
	SDL_SetRenderDrawColor(pApp->pRenderer, mRGBA_r(colorBkg), mRGBA_g(colorBkg), mRGBA_b(colorBkg), mRGBA_a(colorBkg));
	SDL_RenderClear(pApp->pRenderer);
	SDL_RenderPresent(pApp->pRenderer);
	pApp->area=(SDL_Rect){APP_MARGIN_HRZ,APP_MARGIN_VER,APP_AREA_WIDTH,APP_AREA_HEIGHT};
	pApp->timer=SDL_AddTimer(10, (SDL_TimerCallback)_AppAnimate, pApp);
	return pApp;
}

void AppDel(t_app *pApp){
	SDL_RemoveTimer(pApp->timer);
	PlayerDel(pApp->pPlayer);
	ContainerDel(pApp->pBricks);
	ContainerDel(pApp->pMobiles);
	if(pApp->pRenderer)	SDL_DestroyRenderer(pApp->pRenderer);
	if(pApp->pWindow)SDL_DestroyWindow(pApp->pWindow);
	SDL_Quit();
	free(pApp);
}

int AppRun(t_app *pApp){
	printf("test\n");
	pApp->end=0;
	//SDL_Rect rect;
	/*ContainerPushfront(
		pApp->pMobiles,
		MobileNew(
				APP_MOBILE_WIDTH,
				APP_MOBILE_HEIGHT,
				APP_WIDTH/2,
				APP_HEIGHT/2,
				mRGBA(
						(100+(rand()%155)),
						(100+(rand()%155)),
						(100+(rand()%155)),
						(100+(rand()%155))
					),
					//(SDL_Point){(-10+rand()%20),-5}
					(SDL_Point){3,-10}
				)
			);*/
	while(!pApp->end){
		if(SDL_PollEvent(&pApp->event)){
			switch(pApp->event.type){
				case SDL_QUIT:
					pApp->end=1;
					break;
				case SDL_KEYDOWN:
					switch(pApp->event.key.keysym.sym){
						case SDLK_ESCAPE:
							pApp->event.type=SDL_QUIT;
							SDL_PushEvent(&pApp->event);
							break;
						case SDLK_p:
							mBitToggle(pApp->etats, IS_APP_PAUSED);
							break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					switch(pApp->event.button.button){
						case SDL_BUTTON_LEFT:
							ContainerPushfront(
									pApp->pMobiles,
									MobileNew(
											APP_MOBILE_WIDTH,
											APP_MOBILE_HEIGHT,
											pApp->event.motion.x,
											pApp->event.motion.y,
											mRGBA(
													(100+(rand()%155)),
													(100+(rand()%155)),
													(100+(rand()%155)),
													(100+(rand()%155))
												),
												//(SDL_Point){(-10+rand()%20),-5}
												(SDL_Point){3,-10}
											)
										);
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					PlayerSetX(pApp->pPlayer, pApp->event.motion.x, pApp->area);
				default:
					break;
			}
		}
		//if(_AppBrickEndGame(pApp->pBricks)<0)quit=1;
	}
	return 0;
}

Uint32 _AppAnimate(Uint32 interval, t_app *pApp){
	if(!mIsBitSet(pApp->etats, IS_APP_PAUSED)){
		ContainerParse(pApp->pMobiles, (t_ptfvVV)MobileMove, &pApp->area);
		ContainerIntersect(pApp->pMobiles, pApp->pBricks, (t_ptfiVV)_AppBrickDel);
		_AppDraw(pApp);
	}
	pApp->end=_AppBrickEndGame(pApp->pBricks);
	return interval;
}
void _AppDraw(t_app *pApp){
	SDL_SetRenderDrawColor(pApp->pRenderer, 0, 0, 0, 0);
	SDL_RenderClear(pApp->pRenderer);
	SDL_SetRenderDrawColor(pApp->pRenderer, 0, 0, 255, 0);
	SDL_RenderDrawRect(pApp->pRenderer, &pApp->area);
	ContainerParse(pApp->pMobiles, (t_ptfvVV)MobileDraw, pApp->pRenderer);
	ContainerParse(pApp->pBricks, (t_ptfvVV)BrickDraw, pApp->pRenderer);
	PlayerDraw(pApp->pPlayer, pApp->pRenderer);
	SDL_RenderPresent(pApp->pRenderer);
}

int _AppBrickDel(t_mobile *pMobile, t_brick *pBrick, t_player *pPlayer){
	int retour=0;
	SDL_Rect mobile=MobileGetFrame(pMobile);
	SDL_Rect brick=BrickGetFrame(pBrick);
	SDL_Rect player=PlayerGetRect(pPlayer);
	printf("\n");
	if((mobile.y<=(brick.y+brick.h) || (((mobile.y+mobile.h)>brick.y)&&(mobile.y+mobile.h)<(brick.y+brick.h))) && (mobile.w+mobile.x)<=(brick.w+brick.x) && (mobile.x+mobile.w)>=(brick.x)){
		//if(mobile.y>=((brick.y+brick.h)))MobileSetSpeedY(pMobile, -1);
		//else MobileSetSpeedX(pMobile, -1);
		if((mobile.y>brick.y)&&(mobile.y<(brick.y+brick.h-11)))MobileSetSpeedX(pMobile, -1);
		else MobileSetSpeedY(pMobile, -1);
		retour=1;
	}
	if(mobile.y+mobile.h>=player.y){
		if(mobile.x>=player.x && mobile.x<=(player.x+player.w)){

		}
	}
	return retour;
}

int _AppBrickEndGame(t_container *pBrick){
	if(ContainerGetNbElem(pBrick)==0)return 1;
	return 0;
}
