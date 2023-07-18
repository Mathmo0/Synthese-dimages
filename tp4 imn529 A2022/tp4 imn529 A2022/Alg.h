//*******************************************************************

//*																	*

//* Programme: alg.h												*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Définition des points, vecteurs, droites, plans, matrices	*

//*																	*

//*******************************************************************


#ifndef	_ALG
#define	_ALG


#include "definition.h"

class	point 

{
	reel	px,py,pz;


public:
	point();
	point(const reel& x, const reel& y, const reel& z);

	const   reel&   x() const;
	const   reel&   y() const;
	const   reel&   z() const;

	void	coordonnees (reel *x, reel *y, reel *z) const;
};

class	vecteur 

{
	reel	px,py,pz;


public:
	vecteur();
	vecteur(const reel& x, const reel& y, const reel& z);
	vecteur(const point& p, const point& q);

	const   reel&   x() const;
	const   reel&   y() const;
	const   reel&   z() const;

	void	composantes (reel *x, reel *y, reel *z) const;

	reel	norme() const;
	reel	norme2() const;

	vecteur	unitaire() const;
	void	normalise();
};

class	droite 

{
	point	p;
	vecteur	v;


public:
	droite();
	droite(const point& p, const vecteur& v);
	droite(const point& p, const point& q);
	const	point&	mpoint() const;
	const	vecteur& mvecteur() const;
};

class	plan 

{
	point	p;
	vecteur	n;
	reel	a,b,c,d;


public:
	plan();
	plan(const point& p, const vecteur& v);
	plan(const point& p, const point& q, const point& r);
	plan(const point& p, const vecteur& u, const vecteur& v);
	plan(const reel& a, const reel& b, const reel& c, const reel& d);

	void	abcd(reel *a, reel *b, reel *c, reel *d) const;

	const	point&	mpoint() const;
	const	vecteur&	normale() const;

	plan	unitaire() const;
	void	normalise();

	reel	distance (const point& q) const;
	/* Retourne la distance du point au plan. Cette valeur sera :
		NEGATIVE si le point est du cote oppose de la normale au plan;
		NULLE si le point fait partie du plan;
		POSITIVE si le point est du meme cote que la normale au plan; */

	booleen	inter (const droite&, point*, reel *) const;
	booleen	inter (const point&, const vecteur&, point*, reel *) const;
	/* 'p' est le point d'intersection de la droite et du plan.
  	  (retourne FALSE ssi la droite est parallele au plan). */
};

class	matrice 

{
	reel	m[3][4];


public:
	matrice();
	matrice(const reel& a11, const reel& a12, const reel& a13, const reel& a14, const reel& a21, const reel& a22, const reel& a23, const reel& a24, const reel& a31, const reel& a32, const reel& a33, const reel& a34);

	reel&	e(const entier& i, const entier& j);

	friend	point	operator*(const matrice&, const point&);
	/* Calcul M*(x y z 1)t */

	friend	vecteur	operator*(const matrice&, const vecteur&);
	/* Calcul M*(x y z 0)t */

	friend	droite	operator*(const matrice&, const droite&);

	friend	plan	operator*(const matrice&, const plan&);

	friend	plan	mult(const matrice&,const matrice&, const plan&);


	friend	matrice	operator*(const matrice&, const matrice&);

	void	transpose();
	booleen	inverse(matrice *);

	booleen	identite() const;

    const matrice& operator = ( const matrice& mat );
};


extern	const point		O;	/* constante origine = (0,0,0) */



extern	const vecteur	X;	/* constante axe X = (1,0,0) */

extern	const vecteur	Y;	/* constante axe Y = (0,1,0) */

extern	const vecteur	Z;	/* constante axe Z = (0,0,1) */



extern	const matrice	I;	/* matrice identite */

#endif
