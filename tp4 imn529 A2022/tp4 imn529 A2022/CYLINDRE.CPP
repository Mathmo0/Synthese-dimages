
#include "cylindre.h"
#include "geo.h"
#include "utilreel.h"
#include "utilalg.h"
#include "definition.h"
#include "alg.h"
#include "attr.h"
#include "transfo.h"
#include "englobe.h"

extern	"C" double	sqrt(double);

Cylindre::Cylindre ()
{
	s = unCylindre;
}

Cylindre::Cylindre (const point&p1, const point&p2, const reel&r=1.0)
{
	s = unCylindre;
	vecteur	v = p2-p1;
	attr->transformation(Deplacement(p1-O)*Alignement(X,v)*Homothetie(O,X,v.norme())*Homothetie(O,Y,r)*Homothetie(O,Z,r));
}

Objet*	Cylindre::copie () const
{
	Cylindre *o = new Cylindre;

	*o->attr = *this->attr;
	o->defvol = this->defvol;
	if (this->defvol) o->vol = this->vol->copie();
	return(o);
}

booleen	Cylindre::inter(const point& p, const vecteur& v, reel* k)
{
	point	pi;

	const	Transformation *t = &(this->attributs().transformation());

	point	p2 = t->inverse(p);
	vecteur	v2 = t->inverse(v);

	reel	a = v2.y()*v2.y() + v2.z()*v2.z();
	reel	b = 2.0*(v2.y()*p2.y() + v2.z()*p2.z());
	reel	c = p2.y()*p2.y() + p2.z()*p2.z() - 1.0;

	reel	disc = b*b - 4.0*a*c;

	if (ppe(disc,0.0)) return FAUX;

	reel	sq = sqrt(disc);
	reel	k2 = -b - sq;
	if (ppe(k2,0.0)) {
		k2 = -b + sq;
		if (ppe(k2,0.0)) return FAUX;

		k2 /= 2*a;
		if (pge(k2,*k)) return FAUX;

		reel	x = p2.x() + k2*v2.x();
		if (ppe(x, 1.0) && pge(x, 0.0)) { *k = k2; return VRAI; }
		else return FAUX;
	}
	k2 /= 2*a;
	if (pp(k2,*k)) {
		reel	x = p2.x() + k2*v2.x();
		if (ppe(x, 1.0) && pge(x, 0.0)) { *k = k2; return VRAI; }
	}
	k2 = (-b + sq)/2.0/a;
	if (pge(k2,*k)) return FAUX;

	reel	x = p2.x() + k2*v2.x();
	if (ppe(x, 1.0) && pge(x, 0.0)) { *k = k2; return VRAI; }
	else return FAUX;
}

vecteur	Cylindre::gradient(const point&p)
{
	point p2 = this->attributs().transformation().inverse(p);
	return(vecteur(0.0,p2.y(),p2.z()));
}

point	Cylindre::unpoint()
{
	return(attributs().transformation().transforme(point(0.5,0.0,0.0)));
}

const	Englobant&    Cylindre::volume() const
{
        if (!defvol) {
        	((Objet*)this)->vol = new CubeInfini(this->attributs().transformation() *
                   Homothetie (O,Y, 2.0) *
                   Homothetie (O,Z, 2.0) *
                   Deplacement(vecteur(0.0,-0.5,-0.5)));
		((Objet*)this)->defvol = VRAI;
	}
	return *vol;
}
 

