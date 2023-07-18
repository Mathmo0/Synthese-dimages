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



	m_IntensiteAmbiante = Couleur(0.2,0.2,0.2);

	m_Intensite = Couleur(0.5,0.5,0.5);



	m_bActive = VRAI;

}



Lumiere::Lumiere( TypeLumiere type, point pos, reel ra, reel ga, reel ba, reel rd, reel gd, reel bd, reel rph, reel gph, reel bph)

{
    m_Type = type;

	m_Position = pos;



	m_IntensiteAmbiante = Couleur(ra,ga,ba);

	m_Intensite = Couleur(rd,gd,bd);

    m_EnergiePhoton = Couleur( rph, gph, bph );



	m_bActive = VRAI;

}



Lumiere::Lumiere(const Lumiere& l)

{

	m_Position = l.m_Position;

	m_IntensiteAmbiante = l.m_IntensiteAmbiante;

	m_Intensite = l.m_Intensite;

	m_bActive = l.m_bActive;

}



void Lumiere::operator=(const Lumiere& l)

{

	m_Position = l.m_Position;

	m_IntensiteAmbiante = l.m_IntensiteAmbiante;

	m_Intensite = l.m_Intensite;

	m_bActive = l.m_bActive;

    m_Type = l.m_Type;
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



const Couleur& Lumiere::IntensiteAmbiante() const

{
	return m_IntensiteAmbiante;
}



const Couleur& Lumiere::Intensite() const

{
	return m_Intensite;
}


/*
Couleur Lumiere::IntensiteAmbiante( point pt ) const
{
    return m_IntensiteAmbiante;
}

Couleur Lumiere::Intensite( point pt ) const
{
    return m_Intensite;
}

*/

void Lumiere::IntensiteAmbiante(const Couleur& c)

{

	m_IntensiteAmbiante = c;

}



void Lumiere::Intensite(const Couleur& c)

{

	m_Intensite = c;

}

const TypeLumiere Lumiere::Type( void ) const
{
    return m_Type;
}

const Couleur& Lumiere::EnergiePhoton() const
{
    return m_EnergiePhoton;
}