//*******************************************************************

//*																	*

//* Programme: englobe.h											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Définition des volume englobant.							*

//*																	*

//*******************************************************************


#ifndef _ENGLOBANT
#define _ENGLOBANT

#include "attr.h"
#include "transfo.h"
#include "definition.h"

#include "alg.h"

class Englobant 

{
protected:
	Transformation t;


public:
	Englobant();
	void	transformation(const Transformation &t2);
	const	Transformation&	transformation() const;

	point	transforme(const point &p) const;
	point	inverse(const point &p) const;

	virtual	booleen	infini() const;
	virtual	booleen	vide() const;

	virtual	booleen	inter(const point& p, const vecteur& v) const = 0;
	virtual	booleen	inter(const point& p, const vecteur& v, reel *k) const = 0;

	virtual	void    Afficher (const Transformation& v, const Attributs& a) const = 0;

	virtual	Englobant	*copie() const = 0;
	virtual	~Englobant();
};

class VolVide : public Englobant 

{
public:
	VolVide() {};

	booleen	vide() const;

	booleen	inter(const point& p, const vecteur& v) const;
	booleen	inter(const point& p, const vecteur& v, reel *k) const;

	void    Afficher (const Transformation& v, const Attributs& a) const;

	Englobant	*copie() const;
};

class Infini : public Englobant 

{
public:
	//Infini() {};

	booleen	infini() const;

	booleen	inter(const point& p, const vecteur& v) const;
	booleen	inter(const point& p, const vecteur& v, reel *k) const;

	void    Afficher (const Transformation& v, const Attributs& a) const;

	Englobant	*copie() const;
};

class Cube : public Englobant 

{
public:
	Cube();
	Cube(const Transformation&);

	booleen	inter(const point& p, const vecteur& v) const;
	booleen	inter(const point& p, const vecteur& v, reel *k) const;

	void    Afficher (const Transformation& v, const Attributs& a) const;

	Englobant	*copie() const;
};

class CubeInfini : public Cube 

{
public:
	CubeInfini();
	CubeInfini(const Transformation&);

	booleen	inter(const point& p, const vecteur& v) const;
	booleen	inter(const point& p, const vecteur& v, reel *k) const;

	Englobant	*copie() const;
};

class Carre : public Englobant 

{
public:
	Carre();
	Carre(const Transformation&);

	booleen	inter(const point& p, const vecteur& v) const;
	booleen	inter(const point& p, const vecteur& v, reel *k) const;

	void    Afficher (const Transformation& v, const Attributs& a) const;

	Englobant	*copie() const;
};


extern void	Englobe(const Englobant& v1, const Englobant& v2, Englobant** v);


#endif

