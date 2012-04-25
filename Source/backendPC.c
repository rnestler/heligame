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

void DisplayDrawLine (int x_start, int y_start, int x_end, int y_end)
{
	int x, y, temp, delta, delta_x, delta_y;

	delta_x = abs(x_end - x_start);
	delta_y = abs(y_end - y_start);
	
	if (delta_x == 0)
		for (y = 0; y <= (y_end-y_start); y++)
			DisplaySetPoint(x_start, y+y_start);
	else if (delta_y == 0)
		for(x = 0; x <= (delta_x); x++)
			DisplaySetPoint(x+x_start, y_start);
	else if (delta_y / delta_x)  //ist Steigung > 1
	{
		if (y_end < y_start)
		{
			temp = y_end;
			y_end = y_start;
			y_start = temp;
			temp = x_end;
			x_end = x_start;
			x_start = temp;
		}
		for(y = 0; y <= (delta_y); y++)
		{
			x = x_start + y * (x_end - x_start) / (delta_y);
			DisplaySetPoint(x, y_start + y);
		}
	}
	else    // ist Steigung < 1
  {
		if (x_end < x_start)
		{
			temp = x_end;
			x_end = x_start;
			x_start = temp;
			temp = y_end;
			y_end = y_start;
			y_start = temp;
		}
		for (x = 0; x <= (delta_x); x++)
		{
			y = y_start + x * (y_end - y_start) / (delta_x);
			DisplaySetPoint(x_start + x, y);
		}
	}
}

void DisplayClrLine (int x_start, int y_start, int x_end, int y_end)
{
	int x, y, temp, delta, delta_x, delta_y;

	delta_x = abs(x_end - x_start);
	delta_y = abs(y_end - y_start);
	
	if (delta_x == 0)
		for (y = 0; y <= (y_end-y_start); y++)
			DisplayClrPoint(x_start, y+y_start);
	else if (delta_y == 0)
		for(x = 0; x <= (delta_x); x++)
			DisplayClrPoint(x + x_start, y_start);
	else if (delta_y / delta_x)  //ist Steigung > 1
	{
		if (y_end < y_start)
		{
			temp = y_end;
			y_end = y_start;
			y_start = temp;
			temp = x_end;
			x_end = x_start;
			x_start = temp;
		}
		for (y = 0; y <= (delta_y); y++)
		{
			x = x_start + y * (x_end - x_start) / (delta_y);
			DisplayClrPoint(x, y_start + y);
		}
	}
	else          // ist Steigung < 1
	{
		if (x_end < x_start)
		{
			temp = x_end;
			x_end = x_start;
			x_start = temp;
			temp = y_end;
			y_end = y_start;
			y_start = temp;		
	  }
		for (x = 0; x <= (delta_x); x++)
		{
			y = y_start + x * (y_end - y_start) / (delta_x);
			DisplayClrPoint(x_start + x, y);
		}
	}
}

// 1 means pressed
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
	return keyState[io];
}
