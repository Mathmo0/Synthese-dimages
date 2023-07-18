//*******************************************************************

//*																	*

//* Programme: Spotlight.h											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation d'un projecteur.       						*

//*																	*

//*******************************************************************



#ifndef _SPOTLIGHT

#define _SPOTLIGHT

#include "Lumiere.h"
#include "Objet.h"

class Spotlight : public Lumiere
{
public:

    Spotlight ( void );
    Spotlight ( TypeLumiere type, point pos, reel ra, reel ga, reel ba, reel rd, reel gd, reel bd, reel rph, reel gph, reel bph, vecteur direction, reel angle );

    ~Spotlight ( void );

    // methodes qui indique si point est eclaire par le spotlight
    booleen Eclaire( const point& Point ) const;

    const Spotlight& operator= ( const Spotlight& spot );

    vecteur RayonAleatoire( void ) const;

//	Couleur IntensiteAmbiante( point pt ) const;
//	Couleur Intensite( point pt ) const;

    const Couleur& IntensiteAmbiante() const;
	const Couleur& Intensite() const;

    const reel GetAngle( void )   { return m_Angle; }
    const vecteur & GetDirection( void )    { return m_Direction; }


protected:

    reel m_Angle;                       // defini l'angle d'ouverture du spotlight
    vecteur m_Direction;                // defini la direction dans laquelle eclair le spotlight
    reel m_cosAngle;                    // cosinus de l'angle entre le vecteur direction et vecteur direction transformé
                                        // d'une rotation de m_Angle

private:

};

#endif //_SPOTLIGHT