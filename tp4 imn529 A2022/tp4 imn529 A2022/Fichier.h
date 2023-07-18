//*******************************************************************

//*																	*

//* Programme: fichier.h											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Définition de la classe Fichier. Gestion de la lecture et	*

//*		l'écriture des fichiers sur disque.							*

//*																	*

//*******************************************************************


#ifndef _FICHIER
#define _FICHIER

#include <cstdio>

#include "definition.h"	
#include "chaine.h"
#include "cgcString.h"


class	Fichier 

{
	booleen	neuf;


public:

	FILE	*f;


	booleen	Open(char *, char *);


	// ecriture
	void	Wcarac(char);	
	void	Wentier(entier);
	void	Wreel(reel);
	void	Wchaine(chaine);


	// lecture
	booleen	carac(char&);	
	booleen	mentier(entier&);
	booleen	mreel(reel&);
	booleen	mchaine(chaine&);

	booleen	debut();
	booleen	fin();

	void	Close();
};


//Teste l'existance d'un fichier

booleen FichierExistant(char nom[]);


#endif

