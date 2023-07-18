
#include "segment.h"
#include "util.h"
#include "utilreel.h"
#include "geo.h"
#include "utilalg.h"
#include "transfo.h"
#include "definition.h"
#include "alg.h"
#include "attr.h"
#include "englobe.h"
#include "global.h"

Segment::Segment ()
{
	s = unSegment;
}

Segment::Segment (const point& p, const point& q)
{
	s = unSegment;
	Segment::p = p;
	Segment::q = q;
}

const	point&	Segment::p1 () const
{
	return(p);
}

void	Segment::p1 (point* &pp)
{
	pp = &p;
}

const	point&	Segment::p2 () const
{
	return(q);
}

void	Segment::p2 (point* &pp)
{
	pp = &q;
}

void	Segment::attributs (const Attributs& a)
{
	Attributs	b = a;

	b.transformation (N);

	Objet::attributs (b);
	p = a.transformation().transforme(p);
	q = a.transformation().transforme(q);
	Touche();
}

void	Segment::attributs (const Attributs* a)
{
	Attributs	b = *a;

	b.transformation (N);

	Objet::attributs (&b);
	p = a->transformation().transforme(p);
	q = a->transformation().transforme(q);
	Touche();
}

Transformation  Segment::Homothetie(const reel& scal) const
{
	vecteur v = p2()-p1();
        return ::Deplacement(p1() - O) * Alignement(X, v) * ::Homothetie(O,Y, scal) * ::Homothetie(O,Z, scal) * Alignement(v, X) * ::Deplacement(O - p1());
}

Transformation  Segment::HomothetieUnitaire(const reel& unite) const
{
	vecteur v = p2()-p1();

        reel	scal = 1 + unite/v.norme();

	if (ppe(scal, reel(0.0))) return N;

	if (inversion) return ::Homothetie(p1(), v, scal);
	else return ::Homothetie(p2(), v, scal);
}

Transformation  Segment::Rotation(const reel& angle) const
{
        return ::Rotation(p1(), p2()-p1(), angle);
}

Transformation  Segment::Deplacement() const
{
        return ::Deplacement(p2()-p1());
}

Transformation  Segment::DeplacementUnitaire(const reel& unite) const
{
        return ::Deplacement((p2()-p1()).unitaire() * unite);
}

Objet*	Segment::copie () const
{
	Segment	*o = new Segment;

	*o = *this;
	if (this->defvol) o->vol = this->vol->copie();
	return(o);
}

point	Segment::unpoint()
{
	reel	t;

	if (ponctuelle) t = 0.5;
	else {
		if (srcrandom) t = Uniforme(0.0,1.0);
		else {
			entier	s,logn;

			if ((n&1) == 1) {
				s = n; logn = 0;
				while (s!=0) {
					s /= 2;
					logn += 1;
				}
				s = 1;
				while (logn>0) {
					s *= 2;
					logn -= 1;
				}
				t = reel(n)/s;
			} else {
				s = n+1; logn = 0;
				while (s!=0) {
					s /= 2;
					logn += 1;
				}
				s = 1;
				while (logn>0) {
					s *= 2;
					logn -= 1;
				}
				t = 1.0 - reel(n+1)/s;
			}
			n += 1;
		}
	}
	
	return(p1() + ((p2()-p1()) * t));
}

void	Segment::reset()
{
	n = 1;
}

const	Englobant&    Segment::volume() const
{
        if (!defvol) {
		((Objet*)this)->vol = new VolVide();
	        ((Objet*)this)->defvol = VRAI;
	}
        return *vol;
}
 

