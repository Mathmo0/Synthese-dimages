
#ifndef	_FRACTAL
#define	_FRACTAL

#include "objet.h"
#include "definition.h"

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

	void Affiche_fractal(point p1, point p2, point p3, int nb_sub, reel hmin, reel hmax, const Transformation& v, const Attributs& a) const;

	void    Afficher(const Transformation&, const Attributs&) const;

	const   Englobant&      volume() const;

//  vous devez compl�ter cette m�thode.  Vous pouvez proc�der autrement.
	point	milieu(const point&, const point&, const reel& h_inf, const reel& h_sup) const;

//  les m�thodes p1, p2 et p3, retourne les points de la base triangulaire du fractal
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

