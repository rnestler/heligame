/********************************************************************************************

	Display-Driver for MIO with MEGA332 (MC68332)

	File        : displayNeu.h
	Author      : Rudolf Brunner rudolf.brunner@gmx.ch
	Date        : 14.10.04
	Target      : MC68332
	
	last update : Danilo Just 30.04.2009
	
  Beschreibung: Dies ist ein Treiber für das Display auf dem MIO-Board und implementiert die
  wesentlichen Funktion um das Display anzusprechen.
  
  Das RAM des Displays wird in drei virtuelle Displays aufgeteilt. Das entsprechende 
  virtuelle Display kann über DisplaySetLayer(x) festgelegt werden.
  
  Aufteilung des Display-RAMs (8kByte von 64kByte bestückt)
  
              VD0                          VD1                        VD2
  0x0000 +------------+     0x0a80  +------------+     0x1500  +------------+
         | text area  |             | text area  |             | text area  |
         |            |             |            |             |            |
  0x01ff +------------+     0x0c7f  +------------+     0x16ff  +------------+
  0x0200 |  graphics  |     0x0c80  |  graphics  |     0x1700  |  graphics  |
         |    area    |             |    area    |             |    area    |
  0x0a7f +------------+     0x14ff  +------------+     0x1f7f  +------------+
  
   
    (0/0)                                                                (159/79)
      *--------------------------+               +--------------------------+
      |Text-Mode                 |               |                          |
      |                          |               |                          |
      |      (Zeile/Spalte)      |               |           (x/y)          |
      |                          |               |                          |
      |                          |               |Grafik-Mode               |
      +--------------------------+               *--------------------------+
                              (10/25)          (0/0)
  
********************************************************************************************/

#ifndef _DISPLAY_H
#define _DISPLAY_H


/********************************************************************************************
	DIPSLAY FUNCTIONS 
********************************************************************************************/

//Initialisierung des Displays auf den Textbereich 0
int DisplayInit (void);

//selektiert einen von drei Text- und Grafikbereichen
int DisplaySetLayer (int layer);


//Text: Schreibt einen mit \0 terminierten String auf das Display
int DisplayWriteText (char* text, int zeile, int spalte);

//Text: Schreibt ein Zeichen auf das Display
int DisplayWriteChar (char c, int zeile, int spalte);

//Text: Löscht die oberste Zeile und schiebt die unteren eine nach
int DisplayShift (void);

//Text: Setzt den Cursor an die angegebene Position (Blink)
int DisplaySetCursor (int zeile, int spalte);

//Text: Entfernt den Cursor (No-Blink)
int DisplayRemoveCursor (void);

//Text: Gibt ein Zeichen an der akutellen Cursorposition aus
int DisplayPutChar (char c);

//Text: Löscht eine Textzeile vom Display im entsprechenden Bereich 1 2 oder 3
int DisplayClrTextRow (int zeile);

//Text: Löscht den ganzen Text vom Dipslay im entsprechenden Bereich 1 2 oder 3
int DisplayClrText (void);

//Text: Liest einen String vom Display Ram (nur zeilenweise möglich)
int DisplayReadText (char* text, int laenge, int zeile, int spalte);



//Grafik: Setzt einen Punkt auf dem Display x: 0..159, y: 0..79
int DisplaySetPoint (int x, int y);

//Grafik: Löscht einen Punkt auf dem Display x: 0..159, y: 0..79
int DisplayClrPoint (int x, int y);

//Grafik: Zeichnet eine Linie auf dem Display vom Punkt1 zu Punkt2
void DisplayDrawLine (int x_start, int y_start, int x_end, int y_end);

//Grafik: Löscht eine Linie auf dem Display vom Punkt1 zu Punkt2
void DisplayClrLine (int x_start, int y_start, int x_end, int y_end);

//Grafik: Zeichnet ein Rechteck zwischen Punkt1 und Punkt2
void DisplayDrawRect (int x1, int y1, int x2, int y2);

//Grafik: Löscht ein Rechteck zwischen Punkt1 und Punkt2
void DisplayClrRect (int x1, int y1, int x2, int y2);

//Grafik: Füllt eine Fläche zwischen Punkt1 und Punkt2
void DisplayFillArea (int x_start, int y_start, int x_end, int y_end);

//Grafik: Löscht eine Fläche zwischen Punkt1 und Punkt2
void DisplayClrArea (int x_start, int y_start, int x_end, int y_end);

//Grafik: zeichnet eine Kreislinie um den Mittelpunkt x0/y0 mit Radius radius
void DisplayDrawCircle(int x0, int y0, int radius);

//Grafik: Löscht eine Kreislinie um den Mittelpunkt x0/y0 mit Radius radius
void DisplayClearCircle(int x0, int y0, int radius);

//Grafik: zeichnet einen ausgefüllten Kreis um den Mittelpunkt x0/y0 mit Radius radius
void DisplayDrawFullCircle(int x0, int y0, int radius);

//Grafik: löscht einen ausgefüllten Kreis um den Mittelpunkt x0/y0 mit Radius radius
void DisplayClearFullCircle(int x0, int y0, int radius);
 

#endif	/* #ifndef _DISPLAY_H */
