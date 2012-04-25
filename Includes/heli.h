#ifndef HELI_H
#define HELI_H

static const int heliRadius = 5;

typedef struct Heli {
	float x,y;
	float speed;
} Heli;

int heli_check_collision(Heli *heli, float x1, float y1, float x2, float y2);

void heli_init(Heli *heli);

void heli_update(Heli* heli, float acc, int dtime);

void heli_draw(Heli* heli);

void heli_clear(Heli* heli);

float heli_get_y(Heli* heli);

#endif // HELI_H
