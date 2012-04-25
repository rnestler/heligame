/********************************************************************************************
  
  File        : landscape.h
  Author      : 
  Date        : 
  Last Update : 
  Target      : MEGA332, BDM and CodeWarrior
  
  Beschreibung: Generiert zwei ungefähr parallel zueinander verlaufende Linienzüge, 
                zwischen denen der Heli fliegen muss.
********************************************************************************************/

#ifndef LANDSCAPE_H
#define LANDSCAPE_H 

typedef struct {
                 int xPnts[30];
                 int yBottom[30];
                 int yRoof[30];
                    
                 int yBorderLeftBottom;
                 int yBorderRightBottom;
                 int yBorderLeftRoof;
                 int yBorderRightRoof;
                    
                 int nrOfPnts;
                } Landscape;
				

/* Minimalabstand zw. zwei Eckpunten in x-Richtung */
static const int minXDistance = 9; 

/* zusätzlicher Abstand in x-Richtung, zufällig zw. 0 und angegebenem Wert */
static const int rangeAdditionalXDistance = 20; 

/* Höhe der unteren Eckpunkte in y-Richtung, 
   zufällig zw. 0 und angegebenem Wert */
static const int rangeYHight = 30; 

/* zusätzlicher Abstand (zu deltaY) zwischen oberen und unteren Eckpunkten, 
   in y-Richtung, zufällig zw. 0 und angegebenem Wert */
static const int rangeAdditionalYDistance = 5; 

/* rechter Displayrand */
static const int xMax = 159; 

/**
* Initialisiert und zeichnet die Linienzüge über die Display-Breite 
* mit zufällig angeordneten Bergspitzen und Talsohlen.
* deltaY: Mindestabstand zwischen unterem und oberem Linienzug.
*/
void initLandscape(Landscape *lndscp, int deltaY);      

/**
* Lässt die Linienzüge um ein Pixel nach links wandern
*/                            
void landscapeFlow(Landscape *lndscp, int deltaY);    

/**
* gibt an, ob ein Punkt (pointX, pointY) den Linienzug (oben oder unten) berührt 
* (oder bereits überschritten hat). 
* Returnwert: 1 = berührt, 0 = berührt nicht
*/
int touch (Landscape *lndscp, int pointX, int pointY);

int getYRoof(Landscape *lndscp, int pointX);
int getYBottom(Landscape *lndscp, int pointX);

#endif //LANDSCAPE_H