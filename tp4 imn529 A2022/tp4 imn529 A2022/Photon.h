//*******************************************************************

//*																	*

//* Programme: Photon.h           									*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Structure d'un photon.					                    *

//*																	*

//*******************************************************************



#ifndef _PHOTON

#define _PHOTON

#include "alg.h"
#include "couleur.h"




class PhotonMap;


/* Structure d'un photon
 */
//**********************
class Photon
//**********************
{
public:

    friend class PhotonMap;

    Photon( void );
    Photon( reel x, reel y, reel z, reel rouge, reel vert, reel bleu );
    ~Photon( void );

    point position( void ) const;
    Couleur energie( void ) const;

    vecteur PhotonDir( void ) const;                 // direction du photon retourne

protected:
    reel pos[3];                // position du photon
    short plane;                // plan de decoupage ( pour le kd-tree )
    unsigned char theta, phi;   // direction d'ou provient le photon
    reel power[3];              // intensite du photon
};


/* Structure pour localiser 
 * les photons les plus pres
 */
//*****************************
class NearestPhotons
//*****************************
{
public:
    friend class PhotonMap;

protected:
    int max;                    // nombre maximum de photons a chercher
    int found;                  // nombre de photons trouvé
    int got_heap;               // usage interne mettre a 0
    reel pos[3];                // position à partir d'où chercher les photons
    reel *dist2;                // distance au carre entre le photon et la position
    const Photon **index;      // liste de pointeurs de photon ( les photons debute a l'index 1 )
};

#endif
