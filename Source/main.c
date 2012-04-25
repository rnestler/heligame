/********************************************************************************************
  Interrupts

  File        : main.c
  Author      : Danilo Just
  Date        : 14.04.2010
  Last Update : 14.04.2010 djust@hsr.ch
  Target      : MEGA332, BDM and CodeWarrior
  
  Beschreibung: Startup für das Miniprojekt im Modul Computertechnik. Demo für Softtimer,
                Button-Interrupts, Encoder-Interrupts und Displayfunktionen
********************************************************************************************/
#include "backend.h"
#include "DIO.h"
#include "displayNeu.h"
#include "SoftTimer.h"
#include "heli.h"
#include "wall.h"
#include "landscape.h"


// Funktions-Prototypen
int initInterrupt(void);


int main (void)
{    
	Wall wall;
	Heli heli;
	Landscape landscape;
	
	hardwareInit();
	initLandscape(&landscape, 70);
	heli_init(&heli);
	wall_init(&wall, 10);
   
	while(1)
	{
		DelayMs(100);

		heli_clear(&heli);
		if(DIORead(USW0)) {
			//printf("up\n");
			heli_update(&heli, 0.1, 100); // - means up
		}
		else {
			//printf("down\n");
			heli_update(&heli, -0.1, 100); // + means down
		}
		landscapeFlow(&landscape, 70);
		
		wall_clear(&wall);
		wall_update(&wall, 100);
		if(heli_check_collision(&heli, wall.x, wall.y1, wall.x, wall.y2)) {
			heli_init(&heli);
			wall_init(&wall, 10);
		}
		if(touch(&landscape, heli.x, heli.y+heliRadius)) {
			heli_init(&heli);
			wall_init(&wall, 10);
		}
		if(touch(&landscape, heli.x, heli.y-heliRadius)) {
			heli_init(&heli);
			wall_init(&wall, 10);
		}

		wall_draw(&wall);
		heli_draw(&heli);
	} 
}

