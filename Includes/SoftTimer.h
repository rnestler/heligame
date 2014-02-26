/*****************************************************************************
  SoftTimer for ARM-Platform with OKI-H5003
------------------------------------------------------------------------------  
  File        : SoftTimer.h
  Author      : Erwin Braendle    
  Date Issued : 30.04.2009
  Last Change : 04.05.2009 djust, HW-Timer und Timer-ISR hinzugefügt 
  Target      : ESP Embedded System ARM-Platform
------------------------------------------------------------------------------  
  Description : This module offers a set of functions to handle SoftTimer 
                based Applications.
*****************************************************************************/
#ifndef __SOFTTIMER_H
#define __SOFTTIMER_H

// --- Defines
#define ST_COUNT    8      //Number of SoftTimers

// --- Typedefs
typedef enum {INTERVAL=1, ONESHOT=2} tSTmode;      //SoftTimer Modes

// --- Function Prototypes
void ST_Init (void);                                  //init SoftTimer
void ST_Tick (void);                                  //tick SoftTimer
int ST_Create (tSTmode mode, void(*pFkt)(void));      //create Timer
int ST_Start (int id, int time);                      //start Timer
int ST_Restart (int id);                              //restart Timer
int ST_Stop (int id);                                 //stop Timer
int ST_Resume (int id);                               //resume Timer
int ST_Delete (int id);                               //delete Timer

#endif /* #ifndef __SOFTTIMER_H */
