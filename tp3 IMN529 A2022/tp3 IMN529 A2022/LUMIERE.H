//*******************************************************************
//*																	*
//* Programme: lumiere.h											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Implantation d'une lumiere.									*
//*																	*
//*******************************************************************

#ifndef _LUMIERE
#define _LUMIERE

#include "transfo.h"
#include "couleur.h"

class Lumiere
{
protected:
	point m_Position;		//Point source lumineuse

	Couleur m_Ambiante;		//Couleur ambiante de la source
	Couleur m_Diffuse;		//Couleur diffuse de la source

	booleen m_bActive;		//Indique si la lumiere est active

public:
	Lumiere();
	Lumiere(point pos, reel ra, reel ga, reel ba, reel rd, reel gd, reel bd);
	~Lumiere() {}

	Lumiere(const Lumiere& l);
	void operator=(const Lumiere& l);

	void Active(booleen b);
	const booleen& Active() const;

	const point& Position() const;
	void Position(const point& p);

	const Couleur& Ambiante() const;
	const Couleur& Diffuse() const;
	void Ambiante(const Couleur& c);
	void Diffuse(const Couleur& c);
};

#endif

