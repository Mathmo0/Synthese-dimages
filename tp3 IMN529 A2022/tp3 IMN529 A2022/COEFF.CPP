//*******************************************************************
//*																	*
//* Programme: coeff.cpp											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Définition des coefficients.								*
//*																	*
//*******************************************************************

#include "coeff.h"
#include <assert.h>

#ifdef INLINE
inline
#endif
Coefficient::Coefficient ()
{
	c = NOIR;
	defc = AUCUN;
}

#ifdef INLINE
inline
#endif
Coefficient::Coefficient (const Couleur& x)
{
	c = x;
	defc = VRAI;
}

#ifdef INLINE
inline
#endif
booleen	Coefficient::defined () const
{
	return(defc==VRAI);
}

#ifdef INLINE
inline
#endif
void	Coefficient::define (const trinary& b)
{
	defc = b;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Coefficient::couleur () const
{
	return c;
}

#ifdef INLINE
inline
#endif
void	Coefficient::couleur (const Couleur& x)
{
	c = x;
}

#ifdef INLINE
inline
#endif
Coefficient& Coefficient::operator*=(const Coefficient& a){
	if (a.defc == VRAI)
	{
		c = a.c;
		defc = VRAI;
	}
	else
	{
		if (a.defc == FAUX)
		{
			c = a.c;
			defc = AUCUN;
		}
	}
	return *this;
}

#ifdef INLINE
inline
#endif
Coefficient	Coefficient::operator*(const Coefficient& a) const
{
	Coefficient b;
	b = *this;
	b*=a;
/*
#if 1
	if (a.defc == VRAI) 
	{
		b.c = a.c;
		b.defc = VRAI;
	} 
	else 
	{
		if (a.defc == FAUX) 
		{
			b.c = a.c;
			b.defc = AUCUN;
		} 
		else 
		{ // a.h == AUCUN
			b.c = this->c;
			b.defc = this->defc;
		}
	}
#else
	switch (a.defc) 
	{
	case VRAI : 
		b.c = a.c;
		b.defc = VRAI;
		break;
	case FAUX : 
		b.c = a.c;
		b.defc = AUCUN;
		break;
	case AUCUN : 
		b.c = this->c;
		b.defc = this->defc;
		break;
	}
#endif
*/
	return(b);
}

Coefficient& Coefficient::operator*=(const Couleur& ac){
	if(defc==VRAI)
		c *= ac;
	return *this;
}
Coefficient& Coefficient::operator*=(const reel& r){
	if(defc==VRAI)
		c *= r;
	return *this;
}

