//*******************************************************************

//*																	*

//* Programme: PhotonMap.h      									*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Structure de données pour le photon map.					*

//*																	*

//*******************************************************************



#ifndef _PHOTONMAP

#define _PHOTONMAP

#include "photon.h"
#include "definition.h"


//****************
class PhotonMap
//****************
{
public:

    PhotonMap( int max_photon );        // nombre maximum de photon que le photon map peut contenir
    ~PhotonMap( void );

    void Store( const Couleur power,    // photon power
                const point pos,        // photon position
                const vecteur dir );    // photon direction

    void Balance( void );               // balance le kd-tree avant son utilisation

    void Locate( const point &pos,          // position de la surface
                 const reel max_dist,       // distance maximale pour chercher les photons
                 const entier nphotons,     // nombre de photons a utiliser

                 /** parametre de sortie **/
                 entier &found,             // nombre de photons trouvés
                 reel **dist2,              // pointeur sur un tableau qui donne la distance entre le photon et pos ( tableau de grandeur npphoton + 1 )
                 const Photon ***photonList ) const; // pointeur sur un tableau de pointeur de photons trouvés ( tableau de grandeur npphoton + 1 )
                                                     // ( const Photon **ph = NULL; )

    bool Empty( void ) const;       // indique si le photon map est vide

    int NbPhotons( void ) const;    // retourne le nombre de photons dans le photon map

	const Photon & operator [] ( entier index ) const;	    // operateur [], accede un photon du photon map



private:
    void AllocateNearestPhoton( NearestPhotons * np,
                                const point pos,
                                const reel max_dist,
                                const int nphotons ) const;

    void LocatePhotons( NearestPhotons *const np,      // utiliser pour localiser les photons
                        const int index ) const;        // appeler avec index a 1

    void BalanceSegment( Photon **pbal,
                         Photon **porg,
                         const int index,
                         const int start,
                         const int end );

    void MedianSplit( Photon **p,
                      const int start,
                      const int end,
                      const int median,
                      const int axis );

    Photon *photons;

    int stored_photons;
    int half_stored_photons;
    int max_photons;
    int prev_scale;

    reel bbox_min[3];      // bounding box min ( boite englobant tous les photons )
    reel bbox_max[3];      // bounding box max ( boite englobant tous les photons )

};

#endif

