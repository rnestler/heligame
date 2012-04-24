#include "heli.h"
#include "displayNeu.h"
#include "DIO.h"
#include "target.h"

void heli_init(Heli* heli)
{
	heli->y = 40;
	heli->x = 80;
	heli->speed = 0;
}

void heli_acc(Heli* heli, float acc)
{
	heli->speed += acc;
}

void heli_update(Heli* heli)
{
	heli->y += heli->speed;
	if(DIORead(USW1)) {
		heli->x += 0.5;
	}
	if(DIORead(USW2)) {
		heli->x -= 0.5;
	}

	// should never happen
	if(heli->y > 80) heli->y = 80;
	if(heli->y < 0) heli->y = 0;
}

void heli_draw(Heli* heli)
{
	DisplayDrawCircle(heli->x, heli->y, 5);
}

void heli_clear(Heli* heli)
{
	DisplayClearCircle(heli->x, heli->y, 5);
}

float heli_get_y(Heli* heli)
{
	return heli->y;
}

