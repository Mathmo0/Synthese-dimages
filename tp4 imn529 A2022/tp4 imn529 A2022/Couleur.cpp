//*******************************************************************

//*																	*

//* Programme: couleur.cpp											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation des couleurs.									*

//*																	*

//*******************************************************************



#include "couleur.h"



const	Couleur	BLANC(1.0);

const	Couleur	NOIR(0.0);


#ifdef INLINE
inline
#endif
Couleur::Couleur(const reel& g)
{
	*this = Couleur(g,g,g);
}

#ifdef INLINE
inline
#endif
Couleur::Couleur(const reel& r, const reel& g, const reel& b)
{
	Couleur::r = r;
	Couleur::g = g;
	Couleur::b = b;
}

#ifdef INLINE
inline
#endif
const	reel&	Couleur::rouge() const
{
	return(r);
}

#ifdef INLINE
inline
#endif
const	reel&	Couleur::vert() const
{
	return(g);
}

#ifdef INLINE
inline
#endif
const	reel&	Couleur::bleu() const
{
	return(b);
}

#ifdef INLINE
inline
#endif
Couleur	Couleur::operator*(const Couleur& c) const
{
	Couleur c2;

	c2.r = this->r*c.r;
	c2.g = this->g*c.g;
	c2.b = this->b*c.b;
	return(c2);
}

#ifdef INLINE
inline
#endif
Couleur	Couleur::operator+(const Couleur& c) const
{
	Couleur c2;

	c2.r = this->r+c.r;
	c2.g = this->g+c.g;
	c2.b = this->b+c.b;
	return(c2);
}

#ifdef INLINE
inline
#endif
reel	Couleur::operator-(const Couleur& c) const
{
	reel	x,y,z;

	x = this->r-c.r;
	y = this->g-c.g;
	z = this->b-c.b;
	return(x*x+y*y+z*z);
}

#ifdef INLINE
inline
#endif
booleen	Couleur::operator==(const Couleur& c) const
{
	return (this->r==c.r && this->g==c.g && this->b==c.b);
}

#ifdef INLINE
inline
#endif
booleen	Couleur::operator!=(const Couleur& c) const
{
	return (this->r!=c.r || this->g!=c.g || this->b!=c.b);
}

#ifdef INLINE
inline
#endif
Couleur	Couleur::operator*(const reel& s) const
{
	Couleur c2;

	c2.r = this->r*s;
	c2.g = this->g*s;
	c2.b = this->b*s;
	return(c2);
}


//*********** Modifier >>>>>>>>>>>
#ifdef INLINE
inline
#endif
Couleur	Couleur::operator/(const reel& s) const
{
	Couleur c2;

	c2.r = this->r/s;
	c2.g = this->g/s;
	c2.b = this->b/s;
	return(c2);
}

#ifdef INLINE
inline
#endif
Couleur	Couleur::operator=(const Couleur& c)
{
    this->r = c.r;
    this->g = c.g;
    this->b = c.b;

    return *this;
}
//<<<<<<<<<<< Modifier ***********