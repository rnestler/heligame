
// common functions
void DelayMs (int ms);
void hardwareInit();
void MIODispWriteText(char text[], int zeile, int spalte);


#ifdef BACKENDPC
	#include <stdio.h>
	#include <SDL/SDL.h>
	#define USW0        SDLK_w
	#define USW1        SDLK_a
	#define USW2        SDLK_d
	#define USW3        SDLK_s
	#ifdef DEBUG
		#define DPRINT(...) printf(__VA_ARGS__)
	#else
		#define DPRINT(...)
	#endif
#else
	#include "target.h"
	#define DPRINT(...)
#endif

