/*
 ============================================================================
 Name        : Casse-birque.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "App.h"
#define mRGBA(r,g,b,a)		((Uint32)r<<24|(Uint32)g<<16|(Uint32)b<<8|(Uint32)a<<0)
int main(void) {
	t_app *pApp=AppNew(APP_WIDTH, APP_HEIGHT, mRGBA(0,0,0,0));
	AppRun(pApp);
	AppDel(pApp);
	return EXIT_SUCCESS;
}
