//*******************************************************************

//*																	*

//* Programme: utilreel.cpp											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation d'opérateurs utilitaires algébriques			*

//*																	*

//*******************************************************************


#include "alg.h"
#include "utilreel.h"


#ifdef INLINE
inline
#endif
booleen operator==(const vecteur &v, const vecteur &u)
{
	return (eg(v.x(),u.x()) && eg(v.y(),u.y()) && eg(v.z(),u.z()));
}

#ifdef INLINE
inline
#endif
booleen operator==(const point &p, const point &q)
{
	return (eg(p.x(),q.x()) && eg(p.y(),q.y()) && eg(p.z(),q.z()));
}

#ifdef INLINE
inline
#endif
reel	operator*(const vecteur &v, const vecteur &u)
/* Retourne le produit scalaire x = v1 * v2 */
{
	return (v.x()*u.x() + v.y()*u.y() + v.z()*u.z());
}

#ifdef INLINE
inline
#endif
vecteur	operator*(const vecteur &v, const reel &k)
/* Retourne le produit par un scalaire v2 = v1 * k */
{
	return (vecteur(v.x()*k, v.y()*k, v.z()*k));
}

#ifdef INLINE
inline
#endif
vecteur	operator*(const reel &k, const vecteur &v)
/* Retourne le produit par un scalaire v2 = k * v1 */
{
	return (vecteur(k*v.x(), k*v.y(), k*v.z()));
}

#ifdef INLINE
inline
#endif
vecteur	operator+(const vecteur &v, const vecteur &u)
{
	return (vecteur(v.x() + u.x(), v.y() + u.y(), v.z() + u.z()));
}

#ifdef INLINE
inline
#endif
point	operator+(const point &p, const vecteur &u)
{
	return (point(p.x() + u.x(), p.y() + u.y(), p.z() + u.z()));
}

#ifdef INLINE
inline
#endif
point	operator-(const point &p, const vecteur &u)
{
	return (point(p.x() - u.x(), p.y() - u.y(), p.z() - u.z()));
}

#ifdef INLINE
inline
#endif
point	operator+(const vecteur &u, const point &p)
{
	return (point(p.x() + u.x(), p.y() + u.y(), p.z() + u.z()));
}

#ifdef INLINE
inline
#endif
vecteur	operator-(const vecteur &v)
{
	return (vecteur(-v.x(), -v.y(), -v.z()));
}

#ifdef INLINE
inline
#endif
vecteur	operator-(const vecteur &v, const vecteur &u)
{
	return (vecteur(v.x() - u.x(), v.y() - u.y(), v.z() - u.z()));
}

#ifdef INLINE
inline
#endif
vecteur	operator-(const point &p, const point &q)
{
	return (vecteur(p.x() - q.x(), p.y() - q.y(), p.z() - q.z()));
}

#ifdef INLINE
inline
#endif
vecteur	operator^(const vecteur &v, const vecteur &u)
/* Retourne le produit vectoriel v = v1 X v2 */
{
	return(vecteur(v.y()*u.z() - u.y()*v.z(), v.z()*u.x() - u.z()*v.x(), v.x()*u.y() - u.x()*v.y()));
}


point	operator*(const droite& d1, const droite& d2)
/* le point appartient a d2 */
{
	vecteur	w = d1.mvecteur()^d2.mvecteur();

	if (w.norme()==0) return(d2.mpoint());
	else {
		point	pi;
		reel	k;
		plan(d1.mpoint(),w^d1.mvecteur()).inter (d2, &pi, &k);
		return(pi);
	}
}

point	operator*(const point& p, const droite& d)
{
	reel	k = ((p-d.mpoint())*d.mvecteur())/d.mvecteur().norme2();

	return (d.mpoint() + k*d.mvecteur());
}

point	operator*(const point& pt, const plan& pl)
{
	reel	k = ((pt-pl.mpoint())*pl.normale())/pl.normale().norme2();

	return (pt - k*pl.normale());
}

point	operator*(const droite& d, const plan& p)
/* si d || p alors retourne un point du plan parmi les plus pres de la droite */
{
	if (d.mvecteur()*p.normale() == 0) return(d.mpoint()*p);
	point	pi;
	reel	k;
	p.inter (d, &pi, &k);
	return (pi);
}

vecteur	operator-(const point& p, const droite& d)
{
	reel	k = ((p-d.mpoint())*d.mvecteur())/d.mvecteur().norme2();

	point	pt = d.mpoint() + k*d.mvecteur();

	return (p-pt);
}

vecteur	operator-(const point& pt, const plan& pl)
{
	reel	k = ((pt-pl.mpoint())*pl.normale())/pl.normale().norme2();

	return (k*pl.normale());
}

vecteur	operator-(const droite& d1, const droite& d2)
{
	vecteur	w = d1.mvecteur()^d2.mvecteur();

	if (w.norme()==0) return(d1.mpoint()-d2);
	else return (d1.mpoint()-plan(d2.mpoint(),w));
}

droite	operator*(const plan& p1, const plan& p2)
/* p1 \/ p2 */
{
	if ((p1.normale()^p2.normale()).norme() == 0) return(droite(O,vecteur(0.0,0.0,0.0)));

	vecteur	v = p1.normale()^p2.normale();
	vecteur	u = p1.mpoint()-p2;
	if (u.norme()==0) return(droite(p1.mpoint(),v));

	vecteur	w = p1.normale()^v;
	reel	k = -u.norme2()/(u*w);
	return(droite(p1.mpoint()+k*w, v));
}

vecteur	operator-(const droite& d, const plan& p)
{
	if (d.mvecteur()*p.normale() == 0) return (d.mpoint()-p);
	else return (vecteur(0.0,0.0,0.0));
}

vecteur	operator-(const plan& p1, const plan& p2)
{
	if ((p1.normale()^p2.normale()).norme() == 0) return (p1.mpoint()-p2);
	else return (vecteur(0.0,0.0,0.0));
}


