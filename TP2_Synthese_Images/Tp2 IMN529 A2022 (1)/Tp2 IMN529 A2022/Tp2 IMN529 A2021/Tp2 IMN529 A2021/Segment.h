
#ifndef	_SEGMENT
#define	_SEGMENT

#include "definition.h"
#include "alg.h"
#include "objet.h"
#include "composante.h"

class Segment : public Objet, public Composante {
	point	p,q;
	entier	n;
public:
	Segment ();
	Segment (const point&, const point&);
	const	point&	p1() const;
	const	point&	p2() const;
	void	p1(point* &);
	void	p2(point* &);

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
	void	reset();
	const   Englobant&      volume() const;

	Objet*	copie() const;
};

#endif

