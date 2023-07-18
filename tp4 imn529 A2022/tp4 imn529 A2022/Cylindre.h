
#ifndef	_CYLINDRE
#define	_CYLINDRE

#include "objet.h"

class Cylindre : public Objet 

{
public:
	Cylindre ();
	Cylindre (const point&, const point&, const reel&r);

	//void	attributs (const Attributs&);

	void    Ecrire(Fichier *);

	void    Afficher(const Transformation&, const Attributs&) const;

	booleen	inter(const point&, const vecteur&, reel *);
	vecteur	gradient(const point&);
	point	unpoint();
	const   Englobant&      volume() const;

	Objet*	copie() const;
};

#endif

