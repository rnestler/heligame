#include "heli.h"
#include "displayNeu.h"
#include "DIO.h"
#include "backend.h"

#ifdef BACKENDPC
#include <stdio.h>

#define DPRINT(...) printf(...)

#else

#define DPRINT

#endif

void heli_init(Heli* heli)
{
	heli->y = 40;
	heli->x = 80;
	heli->speed = 0;
}

void heli_update(Heli* heli, float acc, int dtime)
{
	heli->speed += acc;
	heli->y += heli->speed;

	// is left right needed?
	// left
	if(DIORead(USW1)) {
		heli->x -= 1;
	}
	// right
	else if(DIORead(USW2)) {
		heli->x += 1;
	}

	// should never happen
	if(heli->y > 80) heli->y = 80;
	if(heli->y < 0) heli->y = 0;
}

void heli_draw(Heli* heli)
{
	DisplayDrawCircle(heli->x+0.5, heli->y+0.5, heliRadius);
}

void heli_clear(Heli* heli)
{
	DisplayClearCircle(heli->x+0.5, heli->y+0.5, heliRadius);
}

float heli_get_y(Heli* heli)
{
	return heli->y;
}

#define max(a,b) (a>b? a : b)
#define min(a,b) (a<b? a : b)
// checks collision between heli and a line from (x1,y1) to (x2,y2)
int heli_check_collision(Heli *heli, float x1, float y1, float x2, float y2)
{
//		|(a-p)x r|
//	d = ----------
//			|r|
	float dirx = x2-x1;
	float diry = y2-y1;
	float diffx = heli->x - x1;
	float diffy = heli->y - y1;
	
	float a = dirx*diffy - diry*diffx;
	float r = dirx*dirx + diry*diry;
	a = a*a;

	DPRINT("%f\n", a/r-heliRadius);

	if(a/r<=heliRadius*heliRadius) {
		// check if out of range
		if(heli->x-heliRadius > max(x1,x2)){ DPRINT("xbig\n"); return 0;}
		if(heli->y-heliRadius > max(y1,y2)){ DPRINT("xsmall\n"); return 0;}
		if(heli->x+heliRadius < min(x1,x2)){ DPRINT("ybig\n"); return 0;}
		if(heli->y+heliRadius < min(y1,y2)){ DPRINT("ysmall\n"); return 0;}
		return 1;
	}

	return 0;
}

