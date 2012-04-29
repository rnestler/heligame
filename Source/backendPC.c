#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "backend.h"

SDL_Surface *screen = NULL;
TTF_Font *font = NULL;

void hardwareInit()
{
	if(SDL_Init(SDL_INIT_VIDEO)<0) {
		exit(1);
	}
	atexit(SDL_Quit);
	if(TTF_Init() < 0) {
		exit(2);
	}
	atexit(TTF_Quit);
	font = TTF_OpenFont("/usr/share/fonts/TTF/VeraMono.ttf", 8*2);
	if(!font) {
		exit(3);
	}
	printf("The font line skip is: %d\n", TTF_FontLineSkip(font));
	Uint32 flags = SDL_SWSURFACE;
	screen = SDL_SetVideoMode(160*2, 80*2, 16, flags);
}

SDL_Surface *drawtext(char text[] )
{
	if(!font)
		return NULL;
    SDL_Color tmpfontcolor = {0xFF,0xFF,0xFF,0xFF};
    //SDL_Color tmpfontbgcolor = {0, 0, 0, 0};
    SDL_Surface *resulting_text;
 
    resulting_text = TTF_RenderText_Solid(font, text, tmpfontcolor);
 
    return resulting_text;
}

void MIODispWriteText(char text[], int zeile, int spalte)
{
	SDL_Rect rect = { spalte*2*6, zeile*8*2, strlen(text)*6*2, 8*2 };
	SDL_FillRect(screen, &rect, 0x000000);
	SDL_Surface *surface;
	surface = drawtext(text);
	SDL_BlitSurface(surface, NULL, screen, &rect);
	SDL_FreeSurface(surface);
	SDL_UpdateRect(screen, 0, 0, 160*2, 80*2);
}

void DelayMs (int ms)
{
	SDL_Delay(ms);
}

void DisplayClrArea (int x_start, int y_start, int x_end, int y_end)
{
	SDL_Rect rect;
	rect.x = x_start;
	rect.y = y_start;
	rect.w = x_end*2;
	rect.h = y_end*2;
	SDL_FillRect(screen, &rect, 0x000000);
	SDL_UpdateRect(screen, 0, 0, 160*2, 80*2);
}


int DisplaySetPoint (int x, int y)
{
	SDL_Rect rect;
	rect.x = 2*x;
	rect.y = 2*(80-y);
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
	rect.y = 2*(80-y);
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
