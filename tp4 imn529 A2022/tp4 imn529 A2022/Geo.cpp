//*******************************************************************

//*																	*

//* Programme: geo.cpp												*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation des transformations géométriques.				*

//*																	*

//*******************************************************************


#include "geo.h"
#include "utilalg.h"
#include "canon.h"
#include "utilreel.h"

Transformation	Alignement(const vecteur& u0, const vecteur& v0)
/* Retourne la transformation qui aligne le vecteur u sur le vecteur v. */
{
	vecteur	w;
	reel	sina,cosa;

	vecteur u = u0.unitaire();
	vecteur v = v0.unitaire();
	cosa = u*v;
	w = u^v;
	sina = w.norme();
	if (eg(sina,0.0)) { /* u = v || u = -v */
		if (eg(cosa,1.0)) {
			return(N);
		} else { /* cosa = -1 */
			w = u^X;
			if (w.norme()==0.0) {
				w = u^Y;
			}
		}
	}
	return(Rot_sincos(w,sina,cosa));
}

Transformation	Alignement(const point& p, const vecteur& u0, const vecteur& v0)
/* effectue un alignement MINIMAL autour de p. */
{
	vecteur	w;
	reel	sina,cosa;

	vecteur u = u0.unitaire();
	vecteur v = v0.unitaire();
	if (pp((cosa = u*v), 0.0)) { v = -v; cosa = -cosa; }
	w = u^v;
	sina = w.norme();
	if (eg(sina, 0.0)) return(N);
	else return(Translation(p-O)*Rot_sincos(w,sina,cosa)*Translation(O-p));
}

/* TRANSFORMATIONS GEOMETRIQUES */

Transformation	Homothetie (const point& p, const vecteur& v, const reel& r)
/* Retourne la transformation d'un changement d'echelle. */
{
	Transformation d,a,c;
	vecteur	vd;

	vd = vecteur(p,O);
	d = Translation(vd);
	a = Alignement(v,X);
	c = Homo_X(r);
	return(d.inverse() * a.inverse() * c * a * d);
}

Transformation	Rotation (const point& p, const vecteur& v, const reel& r)
/* Retourne la transformation d'une rotation. */
{
	Transformation d,a,c;
	vecteur	vd;

	vd = vecteur(p,O);
	d = Translation(vd);
	a = Alignement(v,X);
	c = Rot_X(r);
	return(d.inverse() * a.inverse() * c * a * d);
}

Transformation	Cisaillement (const point& p, const vecteur& v, const vecteur& w)
/* Retourne la transformation d'un cisaillement. */
{
	Transformation d,a,c;
	vecteur	u;

	u = vecteur(p,O);
	d = Translation(u);
	a = Alignement(v,X);
	u = d.transforme(w);
	u = a.transforme(u);
	c = Cis_X(u);
	return(d.inverse() * a.inverse() * c * a * d);
}

Transformation	Deplacement (const vecteur& v)
/* Retourne la transformation d'un deplacement selon v. */
{
	return(Translation (v));
}

