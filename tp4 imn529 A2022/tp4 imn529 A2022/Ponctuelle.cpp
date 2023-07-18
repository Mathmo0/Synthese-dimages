//*******************************************************************

//*																	*

//* Programme: ponctuelle.cpp	     								*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation d'une lumiere ponctuelle						*

//*																	*

//*******************************************************************


#include "Ponctuelle.h"
#include <cmath>
#include "cstdlib"


Ponctuelle::Ponctuelle( TypeLumiere type, point pos, reel ra, reel ga, reel ba, reel rd, reel gd, reel bd, reel rph, reel gph, reel bph ) :
    Lumiere( type, pos, ra, ga, ba, rd, gd, bd, rph, gph, bph )
{
}

vecteur
Ponctuelle::RayonAleatoire( void ) const
{
    vecteur direction;

    reel theta = 2 * PI * ( (reel)rand() / RAND_MAX );
    reel phi = acos( ( 2 * ( (reel)rand() / RAND_MAX ) ) - 1 );

    reel x = cos(theta) * sin( phi );
    reel y = sin(theta) * sin( phi );
    reel z = cos( phi );

    direction = vecteur( x, y, z );

    return direction;
}