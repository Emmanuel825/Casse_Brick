/*
 * mobile.h
 *
 *  Created on: 24 nov. 2022
 *      Author: emmanuel
 */

#include <SDL2/SDL.h>
typedef struct s_mobile t_mobile;

t_mobile *MobileNew(int width, int height, int x, int y, int color, SDL_Point speed);
void MobileDel(t_mobile *pMobile);
void MobileMove(t_mobile *pMobile, SDL_Rect *area);
void MobileDraw(t_mobile *pMobile, SDL_Renderer *pRenderer);
void MobileSetSpeedX(t_mobile *pMobile, int speed);
void MobileSetSpeedY(t_mobile *pMobile, int speed);
SDL_Rect MobileGetFrame(t_mobile *pMobile);
