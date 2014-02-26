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
#include "game.h"


// Funktions-Prototypen
int initInterrupt(void);

int main (void)
{    
	DPRINT("Starting...\n");
	
	hardwareInit();
	DPRINT("Hardware Initialized!\n");
	int i;
	for(i=0; i<10; i++) {
		MIODispWriteText("testg", i, i);
	}
	//DelayMs(3000);

	Game* game = game_init();
	DPRINT("Game Initialized!\n");
	while(1) {
		game_run(game);
	}
}

