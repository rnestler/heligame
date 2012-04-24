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


// Funktions-Prototypen
int initInterrupt(void);

unsigned int counter = 0;

int main (void)
{    
	hardwareInit();
	
	Heli heli;
	heli_init(&heli);
   
	while(1)
	{
		DelayMs(100);

		heli_clear(&heli);

		if(DIORead(USW0)) {
			heli_acc(&heli, 0.1);
		}
		else {
			heli_acc(&heli, -0.1);
		}
		heli_update(&heli);
		heli_draw(&heli);
	} 
}

