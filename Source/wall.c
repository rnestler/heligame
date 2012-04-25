#include "wall.h"
#include <stdlib.h>
#include "displayNeu.h"

void wall_init(Wall *wall, int length)
{
	wall->x=160;
	wall->y1=rand()%80;
	wall->y2=wall->y1+length;
}
void wall_update(Wall *wall, int dtime)
{
	wall->x-=1;

	if(wall->x<=0) {
		int length;
		wall->x=160;
		length = wall->y2-wall->y1+1;
		wall->y1=rand()%80;
		wall->y2=wall->y1+length;
	}
}

void wall_draw(Wall *wall)
{
	DisplayDrawLine(wall->x,wall->y1,wall->x,wall->y2);
}

void wall_clear(Wall *wall)
{
	DisplayClrLine(wall->x,wall->y1,wall->x,wall->y2);
}
