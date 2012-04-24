#include <SDL/SDL.h>
#include "target.h"

SDL_Surface *screen = NULL;

void hardwareInit()
{
	if(SDL_Init(SDL_INIT_VIDEO)<0) {
		exit(1);
	}
	atexit(SDL_Quit);
	Uint32 flags = SDL_SWSURFACE;
	screen = SDL_SetVideoMode(160*2, 80*2, 16, flags);
}

void DelayMs (int ms) {
	SDL_Delay(ms);
}

int DisplaySetPoint (int x, int y)
{
	SDL_Rect rect;
	rect.x = 2*x;
	rect.y = 2*y;
	rect.w = 2;
	rect.h = 2;
	return SDL_FillRect(screen,
			            &rect,
						0xFFFFFF);
}

int DisplayClrPoint (int x, int y)
{
	SDL_Rect rect;
	rect.x = 2*x;
	rect.y = 2*y;
	rect.w = 2;
	rect.h = 2;
	return SDL_FillRect(screen,
			            &rect,
						0x000000);
}

void DisplayDrawCircle(int x0, int y0, int radius)
{
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
 
    DisplaySetPoint(x0, y0 + radius);
    DisplaySetPoint(x0, y0 - radius);
    DisplaySetPoint(x0 + radius, y0);
    DisplaySetPoint(x0 - radius, y0);
 
    while(x < y) 
    {
       if(f >= 0) 
       {
          y--;
          ddF_y += 2;
          f += ddF_y;
       }
      
       x++;
       ddF_x += 2;
       f += ddF_x + 1;
 
       DisplaySetPoint(x0 + x, y0 + y);
       DisplaySetPoint(x0 - x, y0 + y);
       DisplaySetPoint(x0 + x, y0 - y);
       DisplaySetPoint(x0 - x, y0 - y);
       DisplaySetPoint(x0 + y, y0 + x);
       DisplaySetPoint(x0 - y, y0 + x);
       DisplaySetPoint(x0 + y, y0 - x);
       DisplaySetPoint(x0 - y, y0 - x);
    }
	SDL_UpdateRect(screen, 0, 0, 160*2, 80*2);
}
 
void DisplayClearCircle(int x0, int y0, int radius)
{
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
 
    DisplayClrPoint(x0, y0 + radius);
    DisplayClrPoint(x0, y0 - radius);
    DisplayClrPoint(x0 + radius, y0);
    DisplayClrPoint(x0 - radius, y0);
 
    while(x < y) 
    {
       if(f >= 0) 
       {
          y--;
          ddF_y += 2;
          f += ddF_y;
       }
      
       x++;
       ddF_x += 2;
       f += ddF_x + 1;
 
       DisplayClrPoint(x0 + x, y0 + y);
       DisplayClrPoint(x0 - x, y0 + y);
       DisplayClrPoint(x0 + x, y0 - y);
       DisplayClrPoint(x0 - x, y0 - y);
       DisplayClrPoint(x0 + y, y0 + x);
       DisplayClrPoint(x0 - y, y0 + x);
       DisplayClrPoint(x0 + y, y0 - x);
       DisplayClrPoint(x0 - y, y0 - x);
    }
}

int DIORead(int io)
{
	// ugly hack, check SDL events here
	// this works because this function is called regularly
	SDL_Event event;
    if ( SDL_PollEvent(&event) ) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
        }
    }

	Uint8 *keyState;
	keyState=SDL_GetKeyState(NULL);

	switch(io) {
		case USW0:
			return !keyState[SDLK_w];
		case USW1:
			return !keyState[SDLK_a];
		case USW2:
			return !keyState[SDLK_d];
	}
	return 0;
}
