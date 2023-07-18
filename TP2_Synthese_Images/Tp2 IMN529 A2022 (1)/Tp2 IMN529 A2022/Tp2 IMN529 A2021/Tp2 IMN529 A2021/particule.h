
#ifndef	_PARTICULE
#define	_PARTICULE

#include "objet.h"

class Particule : public Objet {
	point	*p;
public:
	Particule ();
	Particule (point*);

	point	*pt() const;

	void	attributs (const Attributs&);

	void    Ecrire(Fichier *) const;

	void    Afficher(const Transformation&, const Attributs&) const;

	const	Englobant&	volume() const;

	Objet*	copie() const;
};

#endif

