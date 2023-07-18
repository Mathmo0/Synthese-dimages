
#ifndef	_VIDE
#define	_VIDE

#include "objet.h"

class Vide : public Objet {
public:
	Vide ();

	void	attributs (const Attributs&);

	void    Ecrire(Fichier *) const;

	void    Afficher(const Transformation&, const Attributs&) const;

	const   Englobant&      volume() const;

	Objet*	copie() const;
};

#endif

