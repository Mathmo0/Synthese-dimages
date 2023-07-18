
#ifndef	_DROITE
#define	_DROITE

#include "alg.h"
#include "objet.h"
#include "composante.h"

class Droite : public Objet, public Composante {
	droite	d;
public:
	Droite ();
	Droite (const droite&);
const	droite&	mdroite() const;

	void	attributs (const Attributs&);
	void	attributs (const Attributs*);

    Transformation  Homothetie(const reel&) const;
    Transformation  HomothetieUnitaire(const reel&) const;
    Transformation  Rotation(const reel&) const;
    Transformation  Deplacement() const;
    Transformation  DeplacementUnitaire(const reel&) const;

    void    Ecrire(Fichier *) const;

    void    Afficher(const Transformation&, const Attributs&) const;

    const   Englobant&      volume() const;

	Objet*	copie() const;
};

#endif

