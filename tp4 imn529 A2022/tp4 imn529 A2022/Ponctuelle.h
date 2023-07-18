//*******************************************************************

//*																	*

//* Programme: ponctuelle.h 										*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation d'une lumiere ponctuelle.						*

//*																	*

//*******************************************************************



#ifndef _LUMIERE_PONCTUELLE

#define _LUMIERE_PONCTUELLE


#include "lumiere.h"


class Ponctuelle : public Lumiere
{
public:

    Ponctuelle( TypeLumiere type, point pos, reel ra, reel ga, reel ba, reel rd, reel gd, reel bd, reel rph, reel gph, reel bph );
    ~Ponctuelle( void );

    vecteur RayonAleatoire( void ) const;
};


#endif