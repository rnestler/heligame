/********************************************************************************************
  

  File        : landscape.c
  Author      : 
  Date        : 
  Last Update : 
  Target      : MEGA332, BDM and CodeWarrior
  
********************************************************************************************/
#include "backend.h"
#include "displayNeu.h"
#include <stdlib.h> /* f�r Zufallsgenerator rand() */

#include "landscape.h" 

void initLandscape(Landscape *lndscp, int deltaY)
{
  int j;

  lndscp->nrOfPnts = 0;
  lndscp->xPnts[0] = 0; 
  
  /*erster unterer Eckpunkt am linken Display-Rand */
  lndscp->yBottom[0] = rand()%rangeYHight; 
  
  /*erster oberer Eckpunkt am linken Display-Rand */
  lndscp->yRoof[0] = lndscp->yBottom[0] + deltaY + rand()%rangeAdditionalYDistance; 
  
  lndscp->yBorderLeftBottom = lndscp->yBottom[0];
  lndscp->yBorderLeftRoof = lndscp->yRoof[0];
  
  /*weitere Eckpunkte ...*/
  do 
  {
    lndscp->nrOfPnts++; 
    lndscp->xPnts[lndscp->nrOfPnts] = lndscp->xPnts[lndscp->nrOfPnts - 1]
                                      + minXDistance + rand() % rangeAdditionalXDistance;
    lndscp->yBottom[lndscp->nrOfPnts] = rand() % rangeYHight;
    lndscp->yRoof[lndscp->nrOfPnts] = lndscp->yBottom[lndscp->nrOfPnts] 
                                      + deltaY + rand() % rangeAdditionalYDistance;
  } while (lndscp->xPnts[lndscp->nrOfPnts] <= xMax); 
  /* ... bis rechter Display-Rand �berschritten */
  
  /* Eckpunkte zu Bergz�gen verbinden (zeichnen) */
  for (j = 1; j < lndscp->nrOfPnts; j++) 
  {
    DisplayDrawLine(lndscp->xPnts[j - 1], lndscp->yBottom[j - 1], 
                    lndscp->xPnts[j], lndscp->yBottom[j]);
    DisplayDrawLine(lndscp->xPnts[j-1], lndscp->yRoof[j - 1], 
                    lndscp->xPnts[j], lndscp->yRoof[j]);
  }
  
  /*Schnittpunkt des unteren Linienzugs mit rechtem Displayrand */
  lndscp->yBorderRightBottom = lndscp->yBottom[lndscp->nrOfPnts - 1] 
    + ((lndscp->yBottom[lndscp->nrOfPnts] - lndscp->yBottom[lndscp->nrOfPnts - 1])
       * (xMax - lndscp->xPnts[lndscp->nrOfPnts - 1]))
    / (lndscp->xPnts[lndscp->nrOfPnts] - lndscp->xPnts[lndscp->nrOfPnts - 1]);
  
  /*Schnittpunkt des oberen Linienzugs mit rechtem Displayrand */
  lndscp->yBorderRightRoof = lndscp->yRoof[lndscp->nrOfPnts - 1] 
    + ((lndscp->yRoof[lndscp->nrOfPnts] - lndscp->yRoof[lndscp->nrOfPnts - 1])
       * (xMax - lndscp->xPnts[lndscp->nrOfPnts - 1]))
    / (lndscp->xPnts[lndscp->nrOfPnts] - lndscp->xPnts[lndscp->nrOfPnts - 1]);
  
  /*letztes unteres Teilst�ck am rechten Rand zeichnen */
  DisplayDrawLine(lndscp->xPnts[lndscp->nrOfPnts - 1], lndscp->yBottom[lndscp->nrOfPnts - 1], 
                  xMax, lndscp->yBorderRightBottom); 
  
  /*letztes oberes Teilst�ck am rechten Rand zeichnen */
  DisplayDrawLine(lndscp->xPnts[lndscp->nrOfPnts - 1], lndscp->yRoof[lndscp->nrOfPnts - 1], 
                  xMax, lndscp->yBorderRightRoof); 
}

void landscapeFlow(Landscape *lndscp, int deltaY)
{
  int j;
  
  /*erstes unteres Teilst�ck am linken Rand l�schen */
  DisplayClrLine(0, lndscp->yBorderLeftBottom, 
                 lndscp->xPnts[1], lndscp->yBottom[1]); 
  
  /*erstes oberes Teilst�ck am linken Rand l�schen */  
  DisplayClrLine(0, lndscp->yBorderLeftRoof, 
                 lndscp->xPnts[1], lndscp->yRoof[1]); 
  
  /*alten Linienzug in der Mitte l�schen */
  for (j = 2; j < lndscp->nrOfPnts; j++) 
  {
    DisplayClrLine(lndscp->xPnts[j - 1], lndscp->yBottom[j - 1], 
                   lndscp->xPnts[j], lndscp->yBottom[j]);
    DisplayClrLine(lndscp->xPnts[j - 1], lndscp->yRoof[j - 1], 
                   lndscp->xPnts[j], lndscp->yRoof[j]);
  }
 
  
  /*letztes unteres Teilst�ck am rechten Rand l�schen */
  DisplayClrLine(lndscp->xPnts[lndscp->nrOfPnts - 1], lndscp->yBottom[lndscp->nrOfPnts - 1], 
                 xMax, lndscp->yBorderRightBottom); 
  
  /*letztes oberes Teilst�ck am rechten Rand l�schen */
  DisplayClrLine(lndscp->xPnts[lndscp->nrOfPnts - 1], lndscp->yRoof[lndscp->nrOfPnts - 1], 
                 xMax, lndscp->yBorderRightRoof); 
  
  /* alle Eckpunkte ein Pixel nach links schieben */
  for (j = 0; j <= lndscp->nrOfPnts; j++) 
  {
    lndscp->xPnts[j]--;
  }
  
  /* wenn hinterster Eckpunkt in Rahmen tritt --> neuer, zus�tzlicher Punkt am rechten Ende des Linienzugs */
  if (lndscp->xPnts[lndscp->nrOfPnts] < 160) 
  {
    lndscp->nrOfPnts++;
    lndscp->xPnts[lndscp->nrOfPnts] = lndscp->xPnts[lndscp->nrOfPnts - 1]
                                              + minXDistance + rand() % rangeAdditionalXDistance;
    lndscp->yBottom[lndscp->nrOfPnts] = rand() % rangeYHight;
    lndscp->yRoof[lndscp->nrOfPnts] = lndscp->yBottom[lndscp->nrOfPnts] 
                                              + deltaY + rand() % rangeAdditionalYDistance;
  }
  
  /* wenn zweitvorderster Eckpunkt am linken Rand aus Rahmen tritt --> Rochade und ein Punkt weniger */
  if (lndscp->xPnts[1] < 0) 
  {
    for(j = 0; j < lndscp->nrOfPnts ; j++)
    {
      lndscp->xPnts[j] = lndscp->xPnts[j + 1];
      lndscp->yBottom[j] = lndscp->yBottom[j + 1];
      lndscp->yRoof[j] = lndscp->yRoof[j + 1];
    }
    lndscp->nrOfPnts--;
  }
  
  /* neuer Schnittpunkt des unteren Linienzugs mit linkem Displayrand */
  lndscp->yBorderLeftBottom = lndscp->yBottom[0] 
    + ((lndscp->yBottom[1] - lndscp->yBottom[0])
       * (0 - lndscp->xPnts[0]))
    / (lndscp->xPnts[1] - lndscp->xPnts[0]);
  
  /* neuer Schnittpunkt des oberen Linienzugs mit linkem Displayrand */
  lndscp->yBorderLeftRoof = lndscp->yRoof[0] 
    + ((lndscp->yRoof[1]-lndscp->yRoof[0])
       * (0 - lndscp->xPnts[0]))
    / (lndscp->xPnts[1] - lndscp->xPnts[0]);
  
  /*erstes unteres Teilst�ck am linken Rand zeichnen */
  DisplayDrawLine(0, lndscp->yBorderLeftBottom, 
                  lndscp->xPnts[1], lndscp->yBottom[1]); 
  
  /*erstes oberes Teilst�ck am linken Rand zeichnen */  
  DisplayDrawLine(0, lndscp->yBorderLeftRoof, 
                  lndscp->xPnts[1], lndscp->yRoof[1]); 
  
  /* neuen Linienzug in der Mitte zeichnen */
  for (j = 2; j < lndscp->nrOfPnts; j++) 
  {
    DisplayDrawLine(lndscp->xPnts[j - 1],  lndscp->yBottom[j - 1], 
                    lndscp->xPnts[j], lndscp->yBottom[j]);
    DisplayDrawLine(lndscp->xPnts[j - 1],  lndscp->yRoof[j - 1], 
                    lndscp->xPnts[j], lndscp->yRoof[j]);
  }
  
  /* neuer Schnittpunkt des unteren Linienzugs mit rechtem Displayrand */
  lndscp->yBorderRightBottom = lndscp->yBottom[lndscp->nrOfPnts - 1] 
    + ((lndscp->yBottom[lndscp->nrOfPnts] - lndscp->yBottom[lndscp->nrOfPnts - 1])
       * (xMax - lndscp->xPnts[lndscp->nrOfPnts - 1]))
    / (lndscp->xPnts[lndscp->nrOfPnts] - lndscp->xPnts[lndscp->nrOfPnts - 1]);
  
  /* neuer Schnittpunkt des oberen Linienzugs mit rechtem Displayrand */
  lndscp->yBorderRightRoof = lndscp->yRoof[lndscp->nrOfPnts - 1] 
    + ((lndscp->yRoof[lndscp->nrOfPnts] - lndscp->yRoof[lndscp->nrOfPnts - 1])
       * (xMax - lndscp->xPnts[lndscp->nrOfPnts - 1]))
    / (lndscp->xPnts[lndscp->nrOfPnts] - lndscp->xPnts[lndscp->nrOfPnts - 1]);
  
  /* letztes unteres Teilst�ck am rechten Rand zeichnen */
  DisplayDrawLine(lndscp->xPnts[lndscp->nrOfPnts - 1], lndscp->yBottom[lndscp->nrOfPnts - 1], 
                  xMax, lndscp->yBorderRightBottom); 
  
  /* letztes oberes Teilst�ck am rechten Rand */
  DisplayDrawLine(lndscp->xPnts[lndscp->nrOfPnts - 1], lndscp->yRoof[lndscp->nrOfPnts - 1], 
                  xMax, lndscp->yBorderRightRoof); 
}


int touch (Landscape *lndscp, int pointX, int pointY)
{
  int j = 0;
  while (1)
  {
  j++;
    if (pointX <= lndscp->xPnts[j])
    {
      if (
           /* ber�hrt oberen Linienzug NICHT */
           ((pointX - lndscp->xPnts[j]) * (lndscp->yRoof[j - 1] - lndscp->yRoof[j]) 
             - (pointY - lndscp->yRoof[j]) * (lndscp->xPnts[j - 1] - lndscp->xPnts[j]) 
           < 0) 
           &&
           /* ber�hrt unteren Linienzug NICHT */
           ((pointX - lndscp->xPnts[j]) * (lndscp->yBottom[j - 1] - lndscp->yBottom[j])
             - (pointY - lndscp->yBottom[j]) * (lndscp->xPnts[j - 1] - lndscp->xPnts[j]) 
           > 0)
         ) 
        return 0;
      else 
        return 1;
    }
  } 
}

int getYRoof(Landscape *lndscp, int pointX)
{
  int j = 0;
  while (1)
  {
  j++;
    if (pointX <= lndscp->xPnts[j])
    {
      return lndscp->yRoof[j-1] 
	         + ((lndscp->yRoof[j] - lndscp->yRoof[j-1])
			    * (pointX - lndscp->xPnts[j-1])) 
				/ (lndscp->xPnts[j] - lndscp->xPnts[j-1]);
    }
  } 
}

int getYBottom(Landscape *lndscp, int pointX)
{
  int j = 0;
  while (1)
  {
  j++;
    if (pointX <= lndscp->xPnts[j])
    {
      return lndscp->yBottom[j-1] 
	         + ((lndscp->yBottom[j] - lndscp->yBottom[j-1])
			    * (pointX - lndscp->xPnts[j-1])) 
				/ (lndscp->xPnts[j] - lndscp->xPnts[j-1]);
    }
  } 
}
