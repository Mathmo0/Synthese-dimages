//*******************************************************************

//*																	*

//* Programme: couleur.h											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Définition des couleurs.									*

//*																	*

//*******************************************************************



#ifndef _COULEUR
#define _COULEUR


#include "definition.h"


class	Couleur 

{
	reel	r,g,b;


public:

	Couleur() {}
	Couleur(const reel&);
	Couleur(const reel&,const reel&,const reel&);
	const	reel&	rouge() const;
	const	reel&	vert() const;
	const	reel&	bleu() const;

	Couleur	operator*(const Couleur&) const;
	Couleur	operator+(const Couleur&) const;
	booleen	operator==(const Couleur&) const;
	booleen	operator!=(const Couleur&) const;
	reel	operator-(const Couleur&) const;
	Couleur	operator*(const reel&) const;

//*********** Modifier >>>>>>>>>>>
	Couleur	operator/(const reel&) const;
	Couleur	operator=(const Couleur&);
//<<<<<<<<<<< Modifier ***********
};


extern	const	Couleur	BLANC;

extern	const	Couleur	NOIR;


#endif
