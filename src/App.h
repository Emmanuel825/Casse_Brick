/*
 * App.h
 *
 *  Created on: 24 nov. 2022
 *      Author: emmanuel
 */

#define APP_WIDTH					1000
#define APP_HEIGHT					1000
#define APP_MARGIN_HRZ				((APP_WIDTH*10)/100)
#define APP_MARGIN_VER				((APP_HEIGHT*10)/100)
#define APP_AREA_WIDTH				(APP_WIDTH-(2*APP_MARGIN_HRZ))
#define APP_AREA_HEIGHT				(APP_HEIGHT-(2*APP_MARGIN_VER))
#define APP_MOBILE_HEIGHT			10
#define APP_MOBILE_WIDTH			10
#define APP_BRICK_NB_COL			3
#define APP_BRICK_NB_ROW			3
#define APP_BRICK_AREA_WIDTH		(APP_AREA_WIDTH+2)
#define APP_BRICK_AREA_HEIGHT		((APP_AREA_HEIGHT*20)/100)
#define APP_BRICK_AREA_MARGIN_VER	((APP_MARGIN_VER)+1)
#define APP_BRICK_AREA_MARGIN_HRZ	((APP_MARGIN_HRZ)+2)
#define APP_BRICK_WIDTH				((APP_BRICK_AREA_WIDTH)/APP_BRICK_NB_COL)
#define APP_BRICK_HEIGHT			((APP_BRICK_AREA_HEIGHT)/APP_BRICK_NB_ROW)
#define APP_PLAYER_X				((APP_AREA_WIDTH+APP_MARGIN_HRZ)/2)
#define APP_PLAYER_Y				((APP_AREA_HEIGHT*90)/100)
#define APP_PLAYER_WIDTH			((APP_AREA_WIDTH)/10)

typedef struct s_app t_app;

t_app *AppNew(int width, int height, int colorBkg);
void AppDel(t_app *pApp);
int AppRun(t_app *pApp);
