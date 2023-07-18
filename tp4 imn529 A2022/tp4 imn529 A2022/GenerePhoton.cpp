//*******************************************************************
//*																	*
//* Programme: GenerePhoton.cpp	       							    *
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Génération de photons.                     					*
//*																	*
//* nom1 : Mathis MOYSE                                             *
//* cip1: 22 090 087                                                *
//*																	*
//* nom2 : Hicham MOUSTAQIM                                         *
//* cip2: 22 090 032                                                *
//*******************************************************************


#include "GenerePhoton.h"
#include "inter.h"
#include "util.h"
#include "utilalg.h"
#include "aff.h"
#include "segment.h"
#include "ensemble.h"
#include "geo.h"
#include "mat.h"
#include <math.h>
#include "Point.h"
#include "time.h"
#include "main.h"

#include "spotlight.h"
#include "ponctuelle.h"
#include "settingTracePhoton.h"

booleen 
GenerePhotons( const Camera& camera, Objet* scene )
{
    const Lumiere* lum = NULL;

    PhotonMap* CaustiqueMap = pFenAff3D->PhotonTracing()->PhotonMapCaustique();

    int nbLum = camera.NbLumiere(); // pour avoir le nombre de lumiere

    printf("\nGeneration des photons...\n");

    clock_t  clk = clock();

    for (int i = 0; i < nbLum; i++)
    {
        lum = camera.GetLumiere(i);

        //les sources lumineuses ponctuelles ne doivent pas lancer de photons
        if (lum->Type() == uneLumierePonctuelle)
        {
            continue;
        }

        for (int j = 0; j < NB_PHOTON_CAUSTIQUE; j++)
        {
            //La puissance totale de la lumière est diviser par le nombre de photon pour repartir la lumière
            Couleur puissance_photon = lum->EnergiePhoton() / NB_PHOTON_CAUSTIQUE;

            point p;
            Couleurs couleurs;
            reel distance = INFINI;
            vecteur vn;

            vecteur direction = lum->RayonAleatoire();
            point origine = lum->Position();

            //Il faut verifier si on intercepte un objet.
            //Si il intercepte au moins un miroir on le fait rebomdir jusqua ce qu'il n'intercepte plus de miroir on enregistre le photon dans son etat avant de rencontrer la surface non miroir
            //si il intercepte aucun miroir (un non miroir des le début) alors on ne l'enregistre pas
            if (Objet_Inter(*scene, origine, direction, &distance, &vn, &couleurs))
            {
                if (couleurs.reflechi() != (0, 0, 0))
                {
                    puissance_photon = puissance_photon * couleurs.reflechi(); //On actualise la puisasnce du photon (il perds de l'energie)
                    origine = origine + direction * distance;
                    direction = Reflechi(direction, vn).unitaire();

                    while (Objet_Inter(*scene, origine, direction, &distance, &vn, &couleurs))
                    {
                        origine = origine + direction * distance;
                        direction = Reflechi(direction, vn).unitaire();

                        if (couleurs.reflechi() == (0, 0, 0))
                        {
                            direction.normalise();
                            CaustiqueMap->Store(puissance_photon, origine, -direction); //On enregistre le photon
                            break;
                        }
                        puissance_photon = puissance_photon * couleurs.reflechi(); //On actualise la puisasnce du photon (il perds de l'energie)
                    }
                }
                else
                {
                    j--; //On n'a pas rencontre de miroir alors on decremente j pour avoir un photon correct (le bon nombre de photons)
                }
            }
        }
    }

    printf( "\nFin du trace de photon\n" );

    printf("Balancement du photon map caustique...\n");
    CaustiqueMap->Balance();
    printf("Fin du balancement du photon map caustique\n\n");

    clk = clock() - clk;
    clk /= CLOCKS_PER_SEC;

    Affiche( *CaustiqueMap, &scene, camera );


    printf( "Temps pour generer les photons : %d:%02d\n\n", clk / 60, clk % 60 );

    return VRAI;
}



void Affiche( const PhotonMap& table, Objet **scene, const Camera& camera )
{
    Attributs* a = new Attributs;

    Couleur cd( 1,1,1 );

    a->diffus( cd );
    a->ambiant( cd );

    Ensemble* ens = new Ensemble;
    const Lumiere* lum = NULL;

    for ( int i = 1; i <= table.NbPhotons(); i += 100 )
    {
        point p1;
        p1 = table[i].position();


        vecteur vec;
        vec = table[i].PhotonDir();

        vec = -vec;

        point p2 = p1 + ( vec );

        Segment* seg = new Segment( p1, p2 );
        seg->attributs( a );
        ens->ajoute( seg );
    }

    // affiche la direction du spot light
    for ( int j = 0; j < camera.NbLumiere(); j++ )
    {
        lum = camera.GetLumiere(j);

        if ( lum->Type() == unSpotlight )
        {
            Spotlight * spot = (Spotlight*)lum;
            // direction du spot light
            point p2 = spot->Position() + ( spot->GetDirection() * 2 );
            Segment* seg = new Segment( spot->Position(), p2 );
    
            seg->attributs( a );
            ens->ajoute( seg );
        }
    }

    ens->attributs( a );

    ((Ensemble*)(*scene))->ajoute( ens );
}