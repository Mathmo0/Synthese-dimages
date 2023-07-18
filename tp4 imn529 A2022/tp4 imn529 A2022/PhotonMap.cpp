//*******************************************************************

//*																	*

//* Programme: PhotonMap.cpp									    *

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Structure de données pour le photon map.					*

//*																	*

//*******************************************************************


#include <cstdio>
#include <cmath>

#include "PhotonMap.h"


//////////////////
// PhotonMap

//****************************************
PhotonMap::PhotonMap( int max_photon )
//****************************************
{
    stored_photons = 0;
    prev_scale = 1;
    max_photons = max_photon;

    photons = new Photon[ ( max_photons + 1 ) ];

    if ( photons == NULL )
    {
        printf( "PHOTON MAP: Out of memory");
        return;
    }

    bbox_min[0] = bbox_min[1] = bbox_min[2] = 1e8f;
    bbox_max[0] = bbox_max[1] = bbox_max[2] = -1e8f;
}

//*******************************
PhotonMap::~PhotonMap( void )
//*******************************
{
    if ( photons )
    {
        delete [] photons;
        photons = NULL;
    }
}

/* indique si le photon map est vide
 */
//*******************************
bool 
PhotonMap::Empty( void ) const
//*******************************
{
    return ( stored_photons == 0 ? true : false );
}

/* initialise la Structure NearestPhotons pour l'appele de LocatePhotons
 */
//*************************************************************
void 
PhotonMap::AllocateNearestPhoton( NearestPhotons * np,
                                   const point pos,
                                   const reel max_dist,
                                   const int nphotons ) const
//*************************************************************
{
    np->dist2 = new reel[ nphotons + 1 ];
    np->index = new const Photon* [ nphotons + 1 ];

    np->pos[0] = pos.x();
    np->pos[1] = pos.y();
    np->pos[2] = pos.z();
    np->max = nphotons;
    np->found = 0;
    np->got_heap = 0;
    np->dist2[0] = max_dist * max_dist;
}



/* localisation des n photons les plus pres
 * ou n = np.max
 */
//*************************************************************
void 
PhotonMap::Locate( const point &pos,        // position de la surface
             const reel max_dist,           // distance maximale pour chercher les photons
             const entier nphotons,         // nombre de photons a utiliser
             entier &found,                 // nombre de photons trouvés
             reel **dist2,                   // distance au carre entre le photon et pos ( tableau de grandeur npphoton + 1 )
             const Photon ***photonList ) const   // liste des photons trouvés ( tableau de grandeur npphoton + 1 )
//*************************************************************
{
    NearestPhotons nph;

    AllocateNearestPhoton( &nph, pos, max_dist, nphotons );

    LocatePhotons( &nph, 1 );

    *photonList = nph.index;
    *dist2 = nph.dist2;
    found = nph.found;
}


/* localisation des n photons les plus pres
 * ou n = np.max
 */
//*****************************************************************************
void
PhotonMap::LocatePhotons( NearestPhotons *const np, const int index ) const
//*****************************************************************************
{
	if (index > max_photons) return;
    const Photon *p = &photons[index];
    reel dist1;

    if ( index <= half_stored_photons )
    {
        dist1 = np->pos[ p->plane ] - p->pos[ p->plane ];

        if ( dist1 > 0.0 )
        // cherche les photons dans la partie droite du plan
        {
            LocatePhotons( np, 2*index+1 );
            if ( dist1 * dist1 < np->dist2[0] )
                LocatePhotons( np, 2*index );
        }
        else
        // cherche les photons dans la partie left du plan
        {
            LocatePhotons( np, 2*index );
            if ( dist1 * dist1 < np->dist2[0] )
                LocatePhotons( np, 2*index + 1 );
        }
    }

    // calcule de la distance au carre de la distance 
    // entre le photon courant et np->pos
    dist1 = p->pos[0] - np->pos[0];
    reel dist2 = dist1 * dist1;
    dist1 = p->pos[1] - np->pos[1];
    dist2 += dist1 * dist1;
    dist1 = p->pos[2] - np->pos[2];
    dist2 += dist1 * dist1;

    if ( dist2 < np->dist2[0] )
    {
        // un photon a ete trouvé, on l'ajoute a la liste des candidats
        if ( np->found < np->max )
        {
            // heap is not full; use array
            ++(np->found);
            np->dist2[np->found] = dist2;
            np->index[np->found] = p;
        }
        else
        {
            int j, parent;

            if ( np->got_heap == 0 )
            // build heap
            {
                reel dst2;

                const Photon *phot;
                int half_found = np->found >> 1;

                for ( int k = half_found; k >= 1; k-- )
                {
                    parent = k;
                    phot = np->index[k];
                    dst2 = np->dist2[k];

                    while ( parent <= half_found )
                    {
                        j = parent + parent;

                        if ( j < np->found && np->dist2[j] < np->dist2[j+1] )
                            ++j;
                        if ( dst2 >= np->dist2[j] )
                            break;

                        np->dist2[parent] = np->dist2[j];
                        np->index[parent] = np->index[j];
                        parent = j;
                    }

                    np->dist2[parent] = dst2;
                    np->index[parent] = phot;
                }

                np->got_heap = 1;

            }

            // insere le nouveau au max heap
            // detruit le plus gros element, insere le nouveau, and reordene le heap

            parent = 1;
            j = 2;
            
            while ( j <= np->found )
            {
                if ( j < np->found && np->dist2[j] < np->dist2[j+1] )
                    ++j;
                if ( dist2 > np->dist2[j] )
                    break;

                np->dist2[parent] = np->dist2[j];
                np->index[parent] = np->index[j];
                parent = j;
                j+=j;
            }

            if ( np->max == 1 )
            {
                if ( dist2 < np->dist2[parent] )
                {
                    np->index[parent] = p;
                    np->dist2[parent] = dist2;

                    np->dist2[0] = np->dist2[1];
                }
            }
            else
            {
                np->index[parent] = p;
                np->dist2[parent] = dist2;

                np->dist2[0] = np->dist2[1];
            }
        }
    }
}

/* insere le photon dans un tableau
 * avant de la metter dans le kd-tree final
 */
//**********************************************************************************
void
PhotonMap::Store( const Couleur power, const point pos, const vecteur dir )
//**********************************************************************************
{
    if ( stored_photons >= max_photons )
        return;

    ++stored_photons;
    Photon *const node = &photons[stored_photons];



    node->pos[0] = pos.x();
    node->pos[1] = pos.y();
    node->pos[2] = pos.z();

    for ( int i = 0; i < 3; i++ )
    {
        // ajuste le bounding box
        if ( node->pos[i] < bbox_min[i] )
            bbox_min[i] = node->pos[i];
        else if ( node->pos[i] > bbox_max[i] )
            bbox_max[i] = node->pos[i];
    }


    node->power[0] = power.rouge();
    node->power[1] = power.vert();
    node->power[2] = power.bleu();


    // calcule la conversion pour la direction et l'insere dans le tableau
    int theta = int( acos(dir.z()) * (256.0/PI ) );
    if ( theta > 255 )
        node->theta = 255;
    else
        node->theta = (unsigned char) theta;

    int phi = int( atan2(dir.y(),dir.x()) * (256.0/( 2.0*PI )) );
    if ( phi>255 )
        node->phi = 255;
    else if ( phi<0 )
        node->phi = (unsigned char)(phi+256);
    else
        node->phi = (unsigned char)phi;
}


/* creer un kd-tree balancer a gauche du tableau
 * la fonction doit etre appele avant d'utiliser le photon map
 * pour faire le rendu
 */
//***************************
void
PhotonMap::Balance( void )
//***************************
{
    if ( stored_photons > 1 )
    {
        // allocation de 2 tableaux temporaire
        Photon **pa1 = new Photon*[stored_photons+1];
        Photon **pa2 = new Photon*[stored_photons+1];

        for ( int k = 1; k <= stored_photons; k++ )
            pa2[k] = &photons[k];

        BalanceSegment( pa1, pa2, 1, 1, stored_photons );
        if ( pa2 )
        {
            delete [] pa2;
            pa2 = NULL;
        }

        // reorganisation du kd-tree balancer ( fait un heap )
        int d, j=1, foo=1;
        Photon foo_photon = photons[j];

        for ( int i = 1; i <= stored_photons; i++ )
        {
            d = (int)(pa1[j] - photons);
            pa1[j] = NULL;

            if ( d != foo )
                photons[j] = photons[d];
            else
            {
                photons[j] = foo_photon;

                if ( i < stored_photons )
                {
                    for ( ; foo <= stored_photons; foo++ )
                        if ( pa1[foo] != NULL )
                            break;

                    foo_photon = photons[foo];
                    j = foo;
                }

                continue;
            }
            
            j = d;
        }
        
        if ( pa1 )
        {
            delete [] pa1;
            pa1 = NULL;
        }
    }

    half_stored_photons = stored_photons / 2 /*- 1*/;
}

#define swap( ph, a, b ) { Photon *ph2 = ph[a]; ph[a] = ph[b]; ph[b] = ph2; }

/* separe le tableau de photons en 2 autour de la mediane
 * les photons en dessous de la mediane sont placés dans la moitié inférieure
 * et les photons au dessu de la mediane sont placés dans la moitié supérieure
 * le critere de comparaison est l'axe passé en parametre
 */
//******************************************
void
PhotonMap::MedianSplit( Photon **p, 
                         const int start, 
                         const int end, 
                         const int median, 
                         const int axis )
//******************************************
{
    int left = start;
    int right = end;

    while ( right > left )
    {
        const reel v = p[right]->pos[axis];
        int i = left - 1;
        int j = right;

        for(;;)
        {
            while ( p[++i]->pos[axis] < v )
                ;

            while ( p[--j]->pos[axis] > v && j>left )
                ;

            if ( i >= j )
                break;

            swap(p,i,j);
        }

        swap(p,i,right);
        if ( i >= median )
            right = i-1;
        if ( i <= median )
            left = i+1;
    }
}

/* balance le kd-tree
 */
//********************************************
void 
PhotonMap::BalanceSegment( Photon **pbal, 
                            Photon **porg, 
                            const int index, 
                            const int start, 
                            const int end )
//********************************************
{
    // calcule la nouvelle mediane

    int median = 1;
    while( (4*median) <= (end-start+1) )
        median += median;

    if ( (3*median) <= (end-start+1) )
    {
        median += median;
        median += start-1;
    }
    else
        median = end - median + 1;


    // cherche l'axe qui permet de separal les photons en 2
    
    int axis = 2;
    if ( (bbox_max[0] - bbox_min[0]) > (bbox_max[1] - bbox_min[1]) &&
         (bbox_max[0] - bbox_min[0]) > (bbox_max[2] - bbox_min[2]) )
        axis = 0;
    else if ( (bbox_max[1] - bbox_min[1]) > (bbox_max[2] - bbox_min[2]) )
        axis = 1;

    // partitionne autour de la mediane

    MedianSplit( porg, start, end, median, axis );

    pbal[ index ] = porg[ median ];
    pbal[ index ]->plane = axis;

    // recursivement, balancé la partie de droite et la partie gauche

    if ( median > start )
    // balance le segment de gauche
    {
        if ( start < median - 1 )
        {
            const reel tmp = bbox_max[axis];
            bbox_max[axis] = pbal[index]->pos[axis];
            BalanceSegment( pbal, porg, 2*index, start, median - 1 );
            bbox_max[axis] = tmp;
        }
        else
        {
            pbal[ 2*index ] = porg[start];
        }
    }

    if ( median < end )
    // balance le segment de droite
    {
        if ( median + 1 < end )
        {
            const reel tmp = bbox_min[axis];
            bbox_min[axis] = pbal[index]->pos[axis];
            BalanceSegment( pbal, porg, 2*index+1, median+1, end );
            bbox_min[axis] = tmp;
        }
        else
        {
            pbal[ 2*index+1 ] = porg[end];
        }
    }
}

/* retourne le nombre de photons dans le photon map
 */
//***********************************
int 
PhotonMap::NbPhotons( void ) const
//***********************************
{
    return stored_photons;
}

/* accede un photon du photon map
 */
//********************************************
const Photon & 
PhotonMap::operator [] ( entier index ) const
//********************************************
{
    if ( index < 1 )
	    return photons[ 1 ];
    else if ( index > stored_photons )
        return photons[stored_photons];
    else
        return photons[index];
}
