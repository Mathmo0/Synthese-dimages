//*******************************************************************

//*																	*

//* Programme: transfo.h											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Définition des tranformations.								*

//*																	*

//*******************************************************************


#ifndef	_TRANSFO
#define	_TRANSFO

#include "alg.h"

class Transformation 

{
	matrice	m;
	matrice	mi;


public:
	Transformation();

	Transformation(const matrice& m, const matrice& mi);
	const	matrice& M() const;
	const	matrice& Mi() const;

	point	transforme(const point& p) const;
	vecteur	transforme(const vecteur& v) const;
	droite	transforme(const droite& d) const;
	plan	transforme(const plan& p) const;

	point	inverse(const point& p) const;
	vecteur	inverse(const vecteur& v) const;
	droite	inverse(const droite& d) const;
	plan	inverse(const plan& p) const;

	Transformation inverse() const;
	Transformation operator*(const Transformation& t) const;

	booleen	neutre() const;

    const Transformation& operator = ( const Transformation& trans );
};

extern	const	Transformation	N;

#endif

