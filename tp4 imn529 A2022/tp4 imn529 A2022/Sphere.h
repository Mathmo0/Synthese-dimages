
#ifndef	_SPHERE
#define	_SPHERE

#include "objet.h"

class Sphere : public Objet {
public:
	Sphere ();
	Sphere (const reel&);
	Sphere (const point&);
	Sphere (const point&, const reel&);

	//void	attributs (const Attributs&);

	booleen	inter(const point&, const vecteur&, reel *);
	vecteur	gradient(const point&);
	point	unpoint();
        const   Englobant&      volume() const;

	void    Ecrire(Fichier *);

	void    Afficher(const Transformation&, const Attributs&) const;

	Objet*	copie() const;
};

#endif

