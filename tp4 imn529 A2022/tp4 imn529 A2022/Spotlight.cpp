//*******************************************************************

//*																	*

//* Programme: Spotlight.cpp					 					*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation d'un projecteur.								*

//*																	*

//*******************************************************************



#include "Spotlight.h"
#include "Polygone.h"
#include "inter.h"
#include "utilalg.h"
#include "mat.h"
#include "geo.h"
#include "canon.h"
#include "cmath"

#include "cstdlib" 
#include "MersenneTwister.h"

static MTRand mtranda( 1973 );  // makes new MTRand with given seed


Spotlight::Spotlight( void )
{
}

Spotlight::Spotlight( TypeLumiere type, point pos, reel ra, reel ga, reel ba, reel rd, reel gd, reel bd, reel rph, reel gph, reel bph, vecteur direction, reel angle )
 : Lumiere( type, pos, ra, ga, ba, rd, gd, bd, rph, gph, bph )
{
    m_Angle = ( angle * PI ) / 180;
    m_cosAngle = cos( m_Angle );
    m_Direction = direction;
    m_Direction.normalise();
}


Spotlight::~Spotlight()
{
}


booleen 
Spotlight::Eclaire( const point& Point ) const
{
    vecteur v = Point - m_Position;

    v.normalise();
    reel cosTheta = v * m_Direction;

    if ( cosTheta > m_cosAngle )
        return VRAI;
    else
        return FAUX;
}


const Spotlight& 
Spotlight::operator= ( const Spotlight& spot )
{
    m_Position = spot.Position();
    m_IntensiteAmbiante = spot.IntensiteAmbiante();
    m_Intensite = spot.Intensite();
    m_bActive = spot.Active();
    m_Type = spot.Type();

    m_Angle = spot.m_Angle;
    m_Direction = spot.m_Direction;
    m_cosAngle = spot.m_cosAngle;

    return *this;
}


/*Couleur
Spotlight::IntensiteAmbiante( point pt ) const
{
    return m_IntensiteAmbiante;
}


Couleur
Spotlight::Intensite( point pt ) const
{
    return m_Intensite;
}

*/
const Couleur& 
Spotlight::IntensiteAmbiante( void ) const
{
    return m_IntensiteAmbiante;
}


const Couleur& 
Spotlight::Intensite( void ) const
{
    return m_Intensite;
}

vecteur
Spotlight::RayonAleatoire( void ) const
{
    vecteur direction;

 //   reel u = (reel)rand() / RAND_MAX;
 //   reel v = (reel)rand() / RAND_MAX;

	reel u = mtranda();
	reel v = mtranda();

    // transformation lineaire pour genere le bonne angle phi
    reel a = ( 1 - m_cosAngle ) / m_cosAngle;
    reel b = m_cosAngle;

    v = ( a * ( v * m_cosAngle ) ) + b;

    // trouve les coordonnées sphériques
    reel theta = 2 * PI * u;
    reel phi = acos( v );


    // transforme les coordonnées sphérique en coordonnées universelle
    reel x = cos(theta) * sin( phi );
    reel y = sin(theta) * sin( phi );
    reel z = cos( phi );

    direction = vecteur( x, y, z );

    Transformation trans = Alignement( Z, m_Direction );
    return trans.transforme( direction );
}