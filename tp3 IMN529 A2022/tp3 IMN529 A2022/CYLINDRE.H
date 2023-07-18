
#ifndef	_CYLINDRE
#define	_CYLINDRE

#include "objet.h"

class Cylindre : public Objet 
{
public:
	Cylindre ();
	Cylindre (const point&, const point&, const reel&r);

	//void	attributs (const Attributs&);

	void    Ecrire(Fichier *) const;

	void    Afficher(const Transformation&, const Attributs&) const;

	booleen	inter(const point&, const vecteur&, reel *);
	vecteur	gradient(const point&);

	virtual void mapUV(const point&p, reel& u, reel& v);
	virtual void getUVsensTexture(const point&p, vecteur& u, vecteur&v);

	point	unpoint();
	const   Englobant&      volume() const;

	Objet*	copie() const;
};

#endif

