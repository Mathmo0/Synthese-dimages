/***************************************************************************
                          radiosite.h  -  description 
                             -------------------

Note : ne pas remettre dans le turnin.

 ***************************************************************************/

 #if !defined(__RADIOSITE_H__)
 #define __RADIOSITE_H__

#include "objet.h"


class Piece{
 public:
   Objet*   objscene;  // Pointe sur l'objet atomique associé dans la scène
   Couleur radiosite,   // Radiosité de la pièce (à calculer)
					  diffus,			// Coefficient Diffus
                   emis;         // Coefficient Emis

  // Les attributs suivant sont utilisés pour l'algo de propagation
   point          centre;    // Coordonnée glabale du centre de la pièce
   reel           aire;         // Aire de la pièce
   vecteur     vn, v1, v2;  // vecteur normal et 2 vecteurs permettant la construction de l'hémi-cube
   Couleur     ERaP;  // energie recu à propager...  (delta radiosité)
};

// Numérote les pièces.  Construit un tableau de pièces.
void DeterminerPieces(Objet* scene);

// Calcul les facteurs de formes de tous les pièces.
void CalculFacteursFormes(Objet *scene);

// Calcul la radiosité par Guass Seidel
// Est appelée par le menu "Calcul Radiosité GS" (bouton droit)
void CalculRadiosite_GS(Objet* scene);

// Calcul la radiosité par Propagation
// Est appelée par le menu "Calcul Radiosité Prop" (bouton droit)
void CalculRadiositePropagation(Objet* scene);

#endif
