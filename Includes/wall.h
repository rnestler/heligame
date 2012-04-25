#ifndef WALL_H
#define WALL_H

typedef struct Wall {
	float x;
	float y1, y2;
} Wall;

void wall_init(Wall *wall, int length, int ymax, int ymin);
void wall_update(Wall *wall, int dtime);
void wall_draw(Wall *wall);
void wall_clear(Wall *wall);

#endif // WALL_H

