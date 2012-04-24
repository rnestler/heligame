#include "heli.h"
#include "displayNeu.h"
#include "DIO.h"
#include "backend.h"

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

