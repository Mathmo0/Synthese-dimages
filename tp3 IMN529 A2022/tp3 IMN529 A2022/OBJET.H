//*******************************************************************
//*																	*
//* Programme: objet.h												*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		D�finition de la classe Objet. Classe g�n�rale pour			*
//*		pouvoir d�finir les propri�t�s globales � tous les objets	*
//*		graphiques.													*
//*																	*
//*******************************************************************

#ifndef	_OBJET
#define	_OBJET

class Ensemble;

#include "typeobjet.h"
#include "attr.h"
#include "englobe.h"
#include "fichier.h"
#include "alg.h"
#include "transfo.h"
#include "definition.h"

class Objet 
{
protected:
	static	entier	NUMERO;
	Attributs	*attr;

	Type		s;
	entier		num;
	entier		nbens;

public:
	struct LEnsembles 
	{
		Ensemble *e;
		entier	i;
	} *lens;

	Englobant	*vol;
	booleen		defvol;

	static entier NbObjet;

public:
						Objet();
	virtual				~Objet();

	void 				detruire(entier);
	void				ensemble(Ensemble*, entier);	// ajoute un parent

	entier				numero() const;

	entier				ensembles() const;	// nb de parents
	Ensemble*			ensemble(entier) const;	// le ieme parent

	virtual	void		attributs (const Attributs&);	// concatene
	const	Attributs&	attributs () const;
	virtual	void		attributs (Attributs*);		// remplace

	Type				type() const;
	virtual	void		Touche();	// change le numero

	virtual	booleen		inter(const point&, const vecteur&, reel *);
	virtual	vecteur		gradient(const point&);
	virtual	point		unpoint();	// uniforme dans objet
	virtual	void		reset();	// reset unpoint
	virtual	const Englobant&	volume() const = 0;

	static	Objet*		Lecture(Fichier &);
	virtual	void		Ecrire(Fichier *) const = 0;

	virtual	void		Afficher(const Transformation&, const Attributs&) const;

	virtual	entier		composantes () const;
	virtual	Objet*		composante (entier) const;

	virtual	Objet*		copie() const = 0;

	virtual	void		detruire();

// *********** Radiosite ********************************//
protected:
      int            numeroPiece0;
      Couleur*  radiosite;
public:
	int              getNumeroPiece0() const;
	void             setNumeroPiece0(int numeropiece0);
	virtual int      getNombrePieces() const;
	virtual void     centrePiece(int numero, point&, vecteur& v1, vecteur& v2, vecteur& vn);
	virtual int      getNumeroPiece(const point& p);
	void             setRadiosite(int numero, const Couleur& c);
	virtual void     mettreRadioDansEmis(const point&, Attributs& c);
	virtual double   calculAirePiece(int numero, const Transformation&) const;
};

#endif
