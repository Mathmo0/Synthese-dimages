//*******************************************************************
//*																	*
//* Programme: erreur.h												*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Définition des fonctions pour la gestion des erreurs.		*
//*																	*
//*******************************************************************


#ifndef _ERREUR
#define _ERREUR


#include "definition.h"

#define	Erreur(x,y) _Erreur(x,y,__LINE__,__FILE__)


void _Erreur(const entier& n, char *s, int, char *);


#endif
