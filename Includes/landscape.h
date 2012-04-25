/********************************************************************************************
  
  File        : landscape.h
  Author      : 
  Date        : 
  Last Update : 
  Target      : MEGA332, BDM and CodeWarrior
  
  Beschreibung: Generiert zwei ungef�hr parallel zueinander verlaufende Linienz�ge, 
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

/* zus�tzlicher Abstand in x-Richtung, zuf�llig zw. 0 und angegebenem Wert */
static const int rangeAdditionalXDistance = 20; 

/* H�he der unteren Eckpunkte in y-Richtung, 
   zuf�llig zw. 0 und angegebenem Wert */
static const int rangeYHight = 30; 

/* zus�tzlicher Abstand (zu deltaY) zwischen oberen und unteren Eckpunkten, 
   in y-Richtung, zuf�llig zw. 0 und angegebenem Wert */
static const int rangeAdditionalYDistance = 5; 

/* rechter Displayrand */
static const int xMax = 159; 

/**
* Initialisiert und zeichnet die Linienz�ge �ber die Display-Breite 
* mit zuf�llig angeordneten Bergspitzen und Talsohlen.
* deltaY: Mindestabstand zwischen unterem und oberem Linienzug.
*/
void initLandscape(Landscape *lndscp, int deltaY);      

/**
* L�sst die Linienz�ge um ein Pixel nach links wandern
*/                            
void landscapeFlow(Landscape *lndscp, int deltaY);    

/**
* gibt an, ob ein Punkt (pointX, pointY) den Linienzug (oben oder unten) ber�hrt 
* (oder bereits �berschritten hat). 
* Returnwert: 1 = ber�hrt, 0 = ber�hrt nicht
*/
int touch (Landscape *lndscp, int pointX, int pointY);

int getYRoof(Landscape *lndscp, int pointX);
int getYBottom(Landscape *lndscp, int pointX);

#endif //LANDSCAPE_H