
#ifndef	_FRACTAL
#define	_FRACTAL

#include "objet.h"

#include "definition.h"

booleen Inter_Cube(const point & p, const vecteur& v, const reel& xmin, const reel & xmax,const reel& ymin,const reel& ymax,const reel& zmin,const reel& zmax);


class Fractal : public Objet {
    int nivsub;

	point pt1,pt2,pt3;

	reel h1,h2;

	vecteur	normal; // vecteur normal lors de l'intersection avec un rayon


public:
	Fractal ();
	Fractal (const point&, const point&, const point&, const int& n,const reel& h1, const reel& h2);

	booleen	inter(const point&, const vecteur&, reel *);
	vecteur	gradient(const point&);
	point	unpoint();

	void    Ecrire(Fichier *) const;

	void    Afficher(const Transformation&, const Attributs&) const;

	const   Englobant&      volume() const;

//  vous devez compléter cette méthode.  Vous pouvez procéder autrement.

	point	milieu(const point&, const point&, const reel& h_inf, const reel& h_sup) const;

//  les méthodes p1, p2 et p3, retourne les points de la base triangulaire du fractal

	point	p1() const;
	point	p2() const;
	point	p3() const;


//  hinf et hsup retourne l'interval de pertubation au premier niveau de subdivision

	reel	hinf () const;

	reel	hsup () const;



//  niveau de subdivision du fractal lors de l'intersection avec un rayon

	int	niv_sub () const;


	Objet*	copie() const;
};

#endif

