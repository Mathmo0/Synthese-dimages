
#include "sphere.h"
#include "geo.h"
#include "utilreel.h"
#include "utilalg.h"

#include "definition.h"
#include "alg.h"
#include "attr.h"
#include "transfo.h"
#include "englobe.h"

extern	"C" double	sqrt(double);

Sphere::Sphere ()
{

	s = uneSphere;
}

Sphere::Sphere (const point&p)
{
	s = uneSphere;
	attr->transformation(Deplacement(p-O));
}

Sphere::Sphere (const reel&r)
{
	s = uneSphere;
	attr->transformation(Homothetie(O,X,r)*Homothetie(O,Y,r)*Homothetie(O,Z,r));
}

Sphere::Sphere (const point&p, const reel&r)
{
	s = uneSphere;
	attr->transformation(Deplacement(p-O)*Homothetie(O,X,r)*Homothetie(O,Y,r)*Homothetie(O,Z,r));
}

Objet*	Sphere::copie () const
{
	Sphere	*o = new Sphere;

	*o->attr = *this->attr;
	o->defvol = this->defvol;
	if (this->defvol) o->vol = this->vol->copie();
	return(o);
}

booleen	Sphere::inter(const point& p, const vecteur& v, reel* k)
{
	point	pi;

	const	Transformation *t = &(this->attributs().transformation());

	point	p2 = t->inverse(p);
	vecteur	v2 = t->inverse(v);

	reel	a = v2.x()*v2.x() + v2.y()*v2.y() + v2.z()*v2.z();
	reel	b = 2.0*(v2.x()*p2.x() + v2.y()*p2.y() + v2.z()*p2.z());
	reel	c = p2.x()*p2.x() + p2.y()*p2.y() + p2.z()*p2.z() - 1.0;

	reel	disc = b*b - 4.0*a*c;

	if (ppe(disc,0.0)) return FAUX;

	reel	sq = sqrt(disc);
	reel	k2 = -b - sq;
	if (ppe(k2,0.0)) {
		k2 = -b + sq;
		if (ppe(k2,0.0)) return FAUX;
	}
	k2 /= 2*a;
	if (pp(k2,*k)) { *k = k2; return VRAI; }
	else return FAUX;
}

vecteur	Sphere::gradient(const point&p)
{
	return(this->attributs().transformation().inverse(p)-O);
}

point	Sphere::unpoint()
{
	return(attributs().transformation().transforme(O));
}

const	Englobant&    Sphere::volume() const
{
        if (!defvol) {
        	((Objet*)this)->vol = new CubeInfini(this->attributs().transformation() *
                   	Homothetie (O,X, 2.0) *
                   	Homothetie (O,Y, 2.0) *
                   	Homothetie (O,Z, 2.0) *
                   	Deplacement(vecteur(-0.5,-0.5,-0.5)));
		((Objet*)this)->defvol = VRAI;
	}
	return *vol;
}
 
