
#include "fractal.h"  
#include "geo.h"
#include "canon.h"
#include "util.h"
#include "utilalg.h"
#include "alg.h"
#include "definition.h"
#include "attr.h"
#include "englobe.h"
#include <random>

#define _USE_MATH_DEFINES
#include <cmath>



point	Fractal::milieu(const point& p1, const point& p2, const reel& Hmin, const reel& Hmax) const
{
	// Retourne le point milieu perturbé.
	// Cette méthode devrait être définie et utilisée pour l'intersection d'un rayon avec
	// un fractal ainsi que lors de l'affichage du fractal
	reel    x1, y1, z1, x2, y2, z2;
	reel x, y, z;
	reel seed; //= (4.23 * X ^ 5 + (pi * Y + 0.33) ^ 7 + (41.2 * Z + 4.3333));
	reel seedNorm;


	p1.coordonnees(&x1, &y1, &z1);
	p2.coordonnees(&x2, &y2, &z2);

	//return point((x1+x2)/2, (y1+y2)/2, (z1+z2)/2); // retourne ici seulement le pt milieu non perturbe

	reel Xmax = max(x1, x2) + 2 * Hmax;
	reel Xmin = min(x1, x2) + 2 * Hmin;

	reel Ymax = max(y1, y2) + 2 * Hmax;
	reel Ymin = min(y1, y2) + 2 * Hmin;

	reel Zmax = max(z1, z2) + 2 * Hmax;
	reel Zmin = min(z1, z2) + 2 * Hmin;

	reel seedX;
	reel seedY;
	reel seedZ;

	seed = (5.4 * pow(((x1 + x2) / 2), 4) + pow(PI * ((y1 + y2) / 2) + 0.33, 7) + (12 * ((z1 + z2) / 2) + 4.6)) * pow(-1, floor((x1 + x2) / 2)); //(4.23 * pow(((x1 + x2) / 2), 5) + pow(PI * ((y1 + y2) / 2) + 0.33, 7) + (41.2 * ((z1 + z2) / 2) + 4.3333))

	seedNorm = seed - floor(seed);

	x = ((x1 + x2) / 2) + seedNorm;
	//y = ((y1 + y2) / 2) + seedY * seed;
	//z = ((z1 + z2) / 2) + seedZ * seed;

	if (x > Xmax)
	{
		x = (x1 + x2) / 2;
	}
	else if (x < Xmin)
	{
		x = (x1 + x2) / 2;
	}

	point pm = point(x, ((y1 + y2) / 2), ((z1 + z2) / 2));

	return pm;
}
 

reel	Fractal::hinf () const
{
    return h1;
}

reel	Fractal::hsup () const
{
    return h2;
}


int	Fractal::niv_sub () const
{
    return nivsub;
}


 
point	Fractal::p1 () const
{
    return pt1;
}

point	Fractal::p2 () const
{
    return pt2;
}

point	Fractal::p3 () const
{
    return pt3;
}

Fractal::Fractal ()
{
	s = unFractal;
}

Fractal::Fractal (const point&p1, const point&p2, const point&p3, const int& n, const reel& hinf, const reel& hsup)
{
	s = unFractal;

	pt1 =p1;
	pt2 = p2;
	pt3 = p3;
	nivsub=n;
	h1 = hinf;
	h2 = hsup;
}

Objet*	Fractal::copie () const
{
	Fractal	*o = new Fractal;

	*o->attr = *this->attr;
	o->defvol = this->defvol;
	o->nivsub = this->nivsub;
	o->pt1 = this->pt1;
	o->pt2 = this->pt2;
	o->pt3 = this->pt3;
	o->h1 = this->h1;
	o->h2 = this->h2;
	o->normal = this->normal;

	if (this->defvol) o->vol = this->vol->copie();
	return(o);
}

booleen Inter_Triangle(const point& p1, const point& p2,const point& p3, const point& p, const vecteur& v, reel *k, vecteur *normal)
// Retourne VRAI s'il y a intersection avec le rayon p,v et le triangle p1,p2,p3. Retourne aussi k; le point d'intersection sera à p + *k * v.
// Le vecteur normal est aussi retourné.  le parametre k est utilisé en e/s.  Il y aura intersection seulement si le nouvel intersection est a
// un k plus petit que celui en entree.
   
{

	plan	pl(p1,p2,p3);

	point	pi;
	reel k2;

	k2 = *k;
	if (!pl.inter (p,v, &pi, &k2)) return FAUX;
	if (*k < k2) return FAUX;

	vecteur v1(p1,p2);
	vecteur v2(p2,p3);
	vecteur v3(p3,p1);

	vecteur u1(p1,pi);
	vecteur u2(p2,pi);
	vecteur u3(p3,pi);

	vecteur n1 = v1^u1;
	vecteur n2 = v2^u2;
	vecteur n3 = v3^u3;

	n1.normalise();
	n2.normalise();
	n3.normalise();

	if (n1*n2 < 0.0 || n2*n3 < 0.0 || n1*n3 < 0.0) return FAUX;
	else {
		*k = k2;
		*normal = pl.normale ();
		reel cost = v * *normal;
		if (cost > 0) *normal = -*normal; // devrait etre fait ds le trace de rayons
		return VRAI;
	}
}
booleen Inter_Cube(const point & p, const vecteur& v, const reel& xmin, const reel & xmax,const reel& ymin,const reel& ymax,const reel& zmin,const reel& zmax)
// Retourne VRAI s'il y a intersection du rayon p,v avec le cube canonique xmin, xmax, ymin, ymax, zmin, zmax
   {
   Cube cube(Deplacement(point(xmin,ymin,zmin) - O) *
			 Homothetie (O,X, xmax-xmin) *
			 Homothetie (O,Y, ymax-ymin) *
			 Homothetie (O,Z, zmax-zmin));
   return cube.inter(p,v);
   }

reel min (reel x, reel y)
   {
   if (x<y)
	  return x;
   else
	  return y;
   }

reel max (reel x, reel y)
   {
   if (x>y)
	  return x;
   else
	  return y;
   }

booleen Inter_Fractal(const Fractal& o, const point& p1, const point& p2, const point& p3, int niv, reel h1, reel h2, const point& p, const vecteur& v, reel* k, vecteur *vn)
   {
//	...
	if (Inter_Triangle(p1, p2, p3, p, v, k, vn))
	{
		return VRAI;
	}
	else
	{
		return FAUX;
	}
   }


booleen	Fractal::inter(const point& p, const vecteur& v, reel* k)
{
	Transformation t = attributs().transformation();

	point	pt2 = t.inverse(p);
	vecteur	v2 = t.inverse(v);

	int nbiter = niv_sub(); // le niveau de subdivision du fractal pour le trace de rayons

	point pi;
	reel k2;

	k2 = *k;

	vecteur vn2 = v ^ v2;

// ...
	if(Inter_Fractal (*this, p1(),p2(),p3(), nbiter, hinf(), hsup(), pt2, v2, &k2, &vn2))
	   {
//		   ...

		return VRAI;
	   }
	else
	   return FAUX;


}

vecteur	Fractal::gradient(const point&p)
{
	return normal;
}

point	Fractal::unpoint()
{
	return pt1;
}

const	Englobant&    Fractal::volume() const
{
	if (!defvol) {
		((Objet*)this)->vol = new Infini();
//		Vous pouvez mettre " = new Cube (transformation);" pour définir un volume
//		englobant pour le fractal comme tel, mais ce n'est pas exigé pour le tp2.
//      Voir la procedure Inter_Cube ci-dessus pour figurer la transformation en
//		paramètre.
		((Objet*)this)->defvol = VRAI;
	}
	return *vol;
}
 
