/*
 * Brick.h
 *
 *  Created on: 25 nov. 2022
 *      Author: emmanuel
 */


typedef struct s_brick t_brick;

t_brick *BrickNew(int width, int height, int x, int y, int color);
void BrickDel(t_brick *pBrick);
void BrickDraw(t_brick *pBrick, SDL_Renderer *pRenderer);
SDL_Rect BrickGetFrame(t_brick *pBrick);
