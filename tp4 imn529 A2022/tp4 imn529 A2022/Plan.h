
#ifndef	_PLAN
#define	_PLAN

#include "alg.h"
#include "objet.h"
#include "composante.h"

class Plan : public Objet, public Composante {
	plan	p;
public:
	Plan ();
	Plan (const plan&);
	const	plan&	mplan() const;

	void	attributs (const Attributs&);
	void	attributs (const Attributs*);

	Transformation  Homothetie(const reel&) const;
	Transformation  HomothetieUnitaire(const reel&) const;
	Transformation  Rotation(const reel&) const;
	Transformation  Deplacement() const;
	Transformation  DeplacementUnitaire(const reel&) const;

	void    Ecrire(Fichier *);

	void    Afficher(const Transformation&, const Attributs&) const;

	const	Englobant&	volume() const;

	booleen	inter(const point&, const vecteur&, reel *);
	vecteur	gradient(const point&);
	point	unpoint();

	Objet*	copie() const;
};

#endif

