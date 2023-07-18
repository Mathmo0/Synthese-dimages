//*******************************************************************

//*																	*

//* Programme: coeff.h												*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Définition des coefficients.								*

//*																	*

//*******************************************************************


#ifndef	_COEFFICIENT
#define	_COEFFICIENT

#include "definition.h"

#include "couleur.h"

class Coefficient 

{
	trinary	defc;
	Couleur	c;


public:
	Coefficient();
	Coefficient(const Couleur&);

	booleen			defined() const;
	const Couleur&	couleur() const;
	void			couleur(const Couleur&);
	void			define(const trinary&);

	Coefficient		operator*(const Coefficient &) const;
    const Coefficient& operator = ( const Coefficient& coeff );
};

#endif

