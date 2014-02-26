#include "wall.h"
#include <stdlib.h>
#include "displayNeu.h"
#include "backend.h"

void wall_init(Wall *wall, int length, int ymax, int ymin)
{
	DPRINT("%i, %i, %i ->", length, ymax, ymin);
	wall->x=160;
	wall->y1=ymin+(rand()%(ymax-ymin-length));
	wall->y2=wall->y1+length;
	DPRINT("%i, %i\n", wall->y1, wall->y2);
}
void wall_update(Wall *wall, int dtime)
{
	wall->x-=1;
}

void wall_draw(Wall *wall)
{
	DisplayDrawLine(wall->x,wall->y1,wall->x,wall->y2);
}

void wall_clear(Wall *wall)
{
	DisplayClrLine(wall->x,wall->y1,wall->x,wall->y2);
}

