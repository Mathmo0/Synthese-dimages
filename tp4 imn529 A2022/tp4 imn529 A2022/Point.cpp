
#include "point.h"
#include "geo.h"
#include "utilalg.h"
#include "transfo.h"

#include "definition.h"
#include "alg.h"
#include "attr.h"
#include "englobe.h"

Point::Point ()
{
	s = unPoint;
}

Point::Point (const point& x)
{
	s = unPoint;
	p = x;
}

const	point&	Point::pt () const
{
	return(p);
}

void	Point::pt (point* &pp)
{
	pp = &p;
}

void	Point::attributs (const Attributs& a)
{
	Attributs	b = a;

	b.transformation (N);

	Objet::attributs (b);
	p = a.transformation().transforme(p);
	Touche();
}

void	Point::attributs (const Attributs* a)
{
	Attributs	b = *a;

	b.transformation (N);

	Objet::attributs (&b);
	p = a->transformation().transforme(p);
	Touche();
}

Transformation  Point::Homothetie(const reel& scal) const
{
	return ::Deplacement(pt()-O) * ::Homothetie(O,X,scal)*::Homothetie(O,Y,scal)*::Homothetie(O,Z,scal) * ::Deplacement(O - pt());
}

Transformation  Point::HomothetieUnitaire(const reel&) const
{
	return N;
}

Transformation  Point::Rotation(const reel&) const
{
	return N;
}

Transformation  Point::Deplacement() const
{
	return N;
}

Transformation  Point::DeplacementUnitaire(const reel&) const
{
	return N;
}


Objet*	Point::copie () const
{
	Point	*o = new Point;

	*o = *this;
	if (this->defvol) o->vol = this->vol->copie();
	return(o);
}

point	Point::unpoint()
{
	return(this->pt());
}

const	Englobant&    Point::volume() const
{
        if (!defvol) {
		((Objet*)this)->vol = new VolVide();
	        ((Objet*)this)->defvol = VRAI;
	}
        return *vol;
}
 
