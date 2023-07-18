
#ifndef	_POLYGONE
#define	_POLYGONE


#include "definition.h"
#include "alg.h"
#include "objet.h"

class Polygone : public Objet {
	entier	nb;
	struct _elem {
		point	pt;
		booleen	defpl; plan	pl;
		booleen	defconvexe; booleen	convexe;
	} *liste;
	booleen	defpl;
	booleen	defconvex;
	plan	pl;
	booleen	convex;
public:
	Polygone ();
	void	ajoute (entier, const point&);
	void	ajoute (const point&);
	entier	sommets () const;
	const	point&		sommet (entier) const;
	void	sommet (entier, point* &);
	const	plan&		mplan (entier) const;
	booleen	convexe ();
	booleen	convexe (entier);
	const	plan&		mplan() const;

	void	attributs (const Attributs&);
	void	attributs (Attributs*);

	void    Ecrire(Fichier *);

	void    Afficher(const Transformation&, const Attributs&) const;

	booleen		inter(const point&, const vecteur&, reel *);
	vecteur		gradient(const point&);
	point		unpoint();
    const   Englobant&      volume() const;



	Objet*		copie() const;

	~Polygone ();
};

#endif

