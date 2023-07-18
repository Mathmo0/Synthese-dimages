//*******************************************************************

//*																	*

//* Programme: geo.h												*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Définition des transformations géométriques.				*

//*																	*

//*******************************************************************


#include "transfo.h"
#include "alg.h"

#include "definition.h"

Transformation	Alignement(const vecteur& u, const vecteur& v);
Transformation	Alignement(const point& p, const vecteur& u, const vecteur& v);

Transformation	Homothetie (const point& p, const vecteur& v, const reel& r);

Transformation	Rotation (const point& p, const vecteur& v, const reel& r);

Transformation	Cisaillement (const point& p, const vecteur& v, const vecteur& w);

Transformation	Deplacement (const vecteur& v);

