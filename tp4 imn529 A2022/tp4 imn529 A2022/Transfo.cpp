//*******************************************************************

//*																	*

//* Programme: transfo.cpp											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation des tranformations.							*

//*																	*

//*******************************************************************



#include "transfo.h"

const Transformation	N(I,I);

Transformation::Transformation()
{
	m = I;
	mi = I;
}

Transformation::Transformation(const matrice& m, const matrice& mi)
{
	this->m = m;
	this->mi = mi;
}

const   matrice& Transformation::M() const
{
	return(m);
}

const   matrice& Transformation::Mi() const
{
	return(mi);
}

point   Transformation::transforme(const point& p) const
{
	return(this->m * p);
}

vecteur Transformation::transforme(const vecteur& v) const
{
	return(this->m * v);
}
;
droite  Transformation::transforme(const droite& d) const
{
	return(this->m * d);
}

plan    Transformation::transforme(const plan& p) const
{
//	return(this->mi * p); /*?*/

return (mult(this->m,this->mi,p));

	
}


point   Transformation::inverse(const point& p) const
{
	return(this->mi * p);
}

vecteur Transformation::inverse(const vecteur& v) const
{
	return(this->mi * v);
}

droite  Transformation::inverse(const droite& d) const
{
	return(this->mi * d);
}

plan    Transformation::inverse(const plan& p) const
{
	return(this->m * p); /*?*/
}

Transformation Transformation::inverse() const
{
	return(Transformation(this->mi, this->m));
}

Transformation Transformation::operator*(const Transformation& t) const
{
	return(Transformation(this->m * t.m, t.mi * this->mi));
}


booleen Transformation::neutre() const
{
	return m.identite();
}

const Transformation& Transformation::operator = ( const Transformation& trans )
{
    m = trans.m;
    mi = trans.mi;

    return *this;
}
