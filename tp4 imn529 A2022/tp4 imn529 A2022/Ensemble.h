//*******************************************************************
//*																	*
//* Programme: ensemble.h											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Définition des ensembles.									*
//*																	*
//*******************************************************************


#ifndef	_ENSEMBLE
#define	_ENSEMBLE

#include "objet.h"
#include "definition.h"	//booleen entier, reel


class Ensemble : public Objet

{
friend void	Objet::detruire(entier);

protected:
	entier	nbcomp;

	struct LComposantes 

	{
		Objet	*c;
		entier	i;
	} *lcomp;


public:
	Ensemble ();
	~Ensemble ();


	void		ajoute (entier, Objet*);
	void		ajoute (entier, Objet*, const Attributs&);
	void		ajoute (Objet*);
	void		ajoute (Objet*, const Attributs&);

	void		remplace (entier, Objet*, const Attributs&);
	void		remplace (entier, Objet*);
	void		remplace (Objet*, const Attributs&);
	void		remplace (Objet*);

	void		detache (entier);
	void		enleve (entier);
	void		enleve ();

	entier		composantes () const;

	Objet*		composante (entier) const;

	void		Ecrire(Fichier *);

	void		Afficher(const Transformation&, const Attributs&) const;

	booleen		inter(const point&, const vecteur&, reel *);
	const		Englobant&      volume() const;

	Objet*		copie() const;
};

#endif