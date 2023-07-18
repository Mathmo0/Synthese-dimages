//*******************************************************************

//*																	*

//* GenerePhoton.h	    	           							    *

//*																	*

//*******************************************************************

//*																	*

//*******************************************************************


#include "PhotonMap.h"

#include "camera.h"

#include "Objet.h"

#include "cstdlib"



booleen GenerePhotons( const Camera& pv, Objet *scene );


void Affiche( const PhotonMap& table, Objet **scene, const Camera& camera );