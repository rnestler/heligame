/********************************************************************************************
  Digital I/O on TPU Channels MEGA332 (MC68332)

  File        : DIO.h
  Author      : Rudolf Brunner rudolf.brunner@gmx.ch
  Date        : 02.04.2002
  Last Update : 07.08.2003 Rudolf Brunner rudolf.brunner@gmx.ch
                10.12.2008 Danilo Just
  Target      : MEGA332, MetroTRK and CodeWarrior
  
  Beschreibung: Mit diesem Code wird es ermöglicht die Taster unter dem LCD einzulesen. 
                Schreiben macht wenig Sinn, kann aber grundsätzlich initialisiert werden.

           		Zulässige Kanäle sind: USW0, USW1, USW2, USW3
  
  Examples      init all inputs: 		DIOInitAll(FALSE);
                init USW1 as an output: DIOInit(USW1,TRUE);
                init USW2 as an input : DIOInit(USW2,FALSE);
                read from USW0        : val = DIORead(USW0);
                
  execution time for "DIOInit()"  is about 41us
  execution time for "DIORead()"  is about 9us
********************************************************************************************/
#ifndef __DIO_H
#define __DIO_H

#define FALLING_EDGE 1
#define RISING_EDGE  2
#define NO_EDGE      3

void Wait4Usw0RisingEdge (void);
void Wait4Usw1RisingEdge (void);
void Wait4Usw2RisingEdge (void);
void Wait4Usw3RisingEdge (void);
void Wait4Usw0FallingEdge (void);
void Wait4Usw1FallingEdge (void);
void Wait4Usw2FallingEdge (void);
void Wait4Usw3FallingEdge (void);

void DIOInit (int ch, int out);			
void DIOInitAll (int out);
int DIORead  (int ch);
unsigned char DIOReadAll (void);

#endif  /* #ifndef __DIO_H */
