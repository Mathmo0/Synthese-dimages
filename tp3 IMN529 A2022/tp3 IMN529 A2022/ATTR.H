//*******************************************************************
//*																	*
//* Programme: attr.h												*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Définition des attributs.									*
//*																	*
//*******************************************************************

#ifndef	_ATTRIBUTS
#define	_ATTRIBUTS

#include "definition.h"
#include "couleur.h"
#include "couleurs.h"
#include "coeff.h"
#include "transfo.h"


class BaseAttributs
{
protected:
	Coefficient	cd;
	Coefficient	td;
	Coefficient	cs;
	Coefficient	ts;
	Coefficient	ca;
	Coefficient	ta;
	Coefficient	cr;
	Coefficient	ct;
	Coefficient	co;
	Coefficient	ce;

public:
	BaseAttributs() {};
	BaseAttributs(const Couleur&);

	Couleurs couleurs() const; // point ?

	const	Couleur&	diffus() const;
	void	diffus(const Couleur &);
	void	diffus(const Coefficient &);
	void	diffus(Coefficient *&);

	const	Couleur&	t_diffus() const;
	void	t_diffus(const Couleur &);
	void	t_diffus(const Coefficient &);
	void	t_diffus(Coefficient *&);

	const	Couleur&	speculaire() const;
	void	speculaire(const Couleur &);
	void	speculaire(const Coefficient &);
	void	speculaire(Coefficient *&);

	const	Couleur&	t_speculaire() const;
	void	t_speculaire(const Couleur &);
	void	t_speculaire(const Coefficient &);
	void	t_speculaire(Coefficient *&);

	const	Couleur&	ambiant() const;
	void	ambiant(const Couleur &);
	void	ambiant(const Coefficient &);
	void	ambiant(Coefficient *&);

	const	Couleur&	t_ambiant() const;
	void	t_ambiant(const Couleur &);
	void	t_ambiant(const Coefficient &);
	void	t_ambiant(Coefficient *&);

	const	Couleur&	reflechi() const;
	void	reflechi(const Couleur &);
	void	reflechi(const Coefficient &);
	void	reflechi(Coefficient *&);

	const	Couleur&	transmis() const;
	void	transmis(const Couleur &);
	void	transmis(const Coefficient &);
	void	transmis(Coefficient *&);

	const	Couleur&	ombre() const;
	void	ombre(const Couleur &);
	void	ombre(const Coefficient &);
	void	ombre(Coefficient *&);

	const	Couleur&	emis() const;
	void	emis(const Couleur &);
	void	emis(const Coefficient &);
	void	emis(Coefficient *&);

	BaseAttributs& operator*=(const BaseAttributs&);
	BaseAttributs& operator*=(const Couleur&);

	BaseAttributs operator*(const Couleur&) const;

	BaseAttributs& operator*= (const reel&);
	BaseAttributs operator*(const reel&) const;
};


class Attributs : public BaseAttributs{
protected:
	booleen	defhl,defin,deft;
	booleen	hl;					//highlight
	booleen	h;					//hide
	booleen l;					//lock

	Transformation t;

public:
	Attributs();
	Attributs(const Couleur&);
	Attributs(const booleen&);
	Attributs(const Transformation&);

	void	highlight(TYPE_SELECTION);
	TYPE_SELECTION	highlight() const;

	void	hide(const trinary&);
	booleen	hide() const;

	void	lock(const trinary&);
	booleen	lock() const;

	booleen	defcentre() const;
	const	point&	centre() const;
	void	centre(const point&);

	booleen	deftransformation() const;
	void	undeftransformation();
	const	Transformation& transformation() const;
	void	transformation(const Transformation&); // remplace la transfo

	Attributs operator*(const Attributs &) const;

	Attributs inverse() const;
};

extern	const	Attributs ATTR;

#endif

