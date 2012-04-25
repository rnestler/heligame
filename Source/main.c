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


// Funktions-Prototypen
int initInterrupt(void);

unsigned int counter = 0;

int main (void)
{    
	Wall wall;
	Heli heli;
	
	hardwareInit();
	heli_init(&heli);
	wall_init(&wall, 10);
   
	while(1)
	{
		DelayMs(100);

		heli_clear(&heli);
		if(DIORead(USW0)) {
			heli_update(&heli, -0.1, 100); // - means up
		}
		else {
			heli_update(&heli, 0.1, 100); // + means down
		}
		wall_clear(&wall);
		wall_update(&wall, 100);
		if(heli_check_collision(&heli, wall.x, wall.y1, wall.x, wall.y2)) {
			heli_init(&heli);
			wall_init(&wall, 10);
		}

		/*
		DisplayDrawLine(0,79,80,79);
		if(heli_check_collision(&heli, 0,79,80,79)) {
			heli_init(&heli);
		}
		DisplayDrawLine(0,0,80,0);
		if(heli_check_collision(&heli, 0,0,80,0)) {
			heli_init(&heli);
		}
		DisplayDrawLine(0,79,80,20);
		if(heli_check_collision(&heli, 0,79,80,20)) {
			heli_init(&heli);
		}
		DisplayDrawLine(20,20,80,20);
		if(heli_check_collision(&heli, 20,20,80,20)) {
			heli_init(&heli);
		}
		*/
		wall_draw(&wall);
		heli_draw(&heli);
	} 
}

