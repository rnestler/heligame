#ifndef HELI_H
#define HELI_H

typedef struct Heli {
	float x,y;
	float speed;
} Heli;


void heli_init(Heli *heli);

void heli_update(Heli* heli, float acc, int dtime);

void heli_draw(Heli* heli);

void heli_clear(Heli* heli);

float heli_get_y(Heli* heli);

#endif // HELI_H
