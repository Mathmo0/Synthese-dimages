
#ifndef	_POINT
#define	_POINT

#include "alg.h"
#include "objet.h"
#include "composante.h"

class Point : public Objet, public Composante 

{
	point	p;


public:
	Point ();
	Point (const point&);
	const	point&	pt() const;
	void	pt(point* &);

	void	attributs (const Attributs&);
	void	attributs (const Attributs*);

	Transformation  Homothetie(const reel&) const;
	Transformation  HomothetieUnitaire(const reel&) const;
	Transformation  Rotation(const reel&) const;
	Transformation  Deplacement() const;
	Transformation  DeplacementUnitaire(const reel&) const;

    void    Ecrire(Fichier *);

    void    Afficher(const Transformation&, const Attributs&) const;

	point	unpoint();
	const   Englobant&      volume() const;

	Objet*	copie() const;
};

#endif

