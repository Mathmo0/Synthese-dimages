//*******************************************************************
//*																	*
//* Programme: lumiere.cpp											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Implantation d'une lumiere.									*
//*																	*
//*******************************************************************

#include "lumiere.h"
#include "couleur.h"

Lumiere::Lumiere()
{
	m_Position = point(0,0,0);

	m_Ambiante = Couleur(0.2,0.2,0.2);
	m_Diffuse = Couleur(0.5,0.5,0.5);

	m_bActive = VRAI;
}

Lumiere::Lumiere(point pos, reel ra, reel ga, reel ba, reel rd, reel gd, reel bd)
{
	m_Position = pos;

	m_Ambiante = Couleur(ra,ga,ba);
	m_Diffuse = Couleur(rd,gd,bd);

	m_bActive = VRAI;
}

Lumiere::Lumiere(const Lumiere& l)
{
	m_Position = l.m_Position;
	m_Ambiante = l.m_Ambiante;
	m_Diffuse = l.m_Diffuse;
	m_bActive = l.m_bActive;
}

void Lumiere::operator=(const Lumiere& l)
{
	m_Position = l.m_Position;
	m_Ambiante = l.m_Ambiante;
	m_Diffuse = l.m_Diffuse;
	m_bActive = l.m_bActive;
}

void Lumiere::Active(booleen b)
{
	m_bActive = b;
}

const booleen& Lumiere::Active() const
{
	return m_bActive;
}


const point& Lumiere::Position() const
{
	return m_Position;
}

void Lumiere::Position(const point& p)
{
	m_Position = p;
}

const Couleur& Lumiere::Ambiante() const
{
	return m_Ambiante;
}

const Couleur& Lumiere::Diffuse() const
{
	return m_Diffuse;
}


void Lumiere::Ambiante(const Couleur& c)
{
	m_Ambiante = c;
}

void Lumiere::Diffuse(const Couleur& c)
{
	m_Diffuse = c;
}
