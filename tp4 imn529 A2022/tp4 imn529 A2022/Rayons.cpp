// /******************************************************************/
// /*                                                                */   
// /* Mathis MOYSE 22 090 087                                        */   
// /* Hicham MOUSTAQIM 22 090 032                                    */   
// /*                                                                */   
// /*                                                                */   
// /*                                                                */   
// /*                                                                */   
// /*                                                                */   
// /*                                                                */   
// /*                                                                */   
// /*                                                                */   
// /******************************************************************/






#include "rayons.h"
#include "couleurs.h" 
#include "attr.h"
#include "ensemble.h"
#include "point.h"
#include "transfo.h"
#include "inter.h"
#include "vision.h"
#include "util.h"
#include "utilalg.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "main.h"
#include "canon.h"
#include "time.h"

#include "spotlight.h"
#include "photonmap.h"


void Enregistre_pixel (int no_x, int no_y, Couleur intens, Fichier f)
// enregistre la couleur du pixel dans le fichier f
// Chacune des composantes de la couleur doit etre de 0 a 1,
// sinon elle sera ramene a une borne.
 {
     
 	reel r,v,b;
 	char c;
 
 	intens=intens*255.0;
 	r=intens.rouge();
 	if (r<0) r=0;
 	if (r>255)r=255;
 	c=(unsigned char) r;
 	f.Wcarac(c);

 	v=intens.vert();
 	if (v<0) v=0;
 	if (v>255) 
 		v=255;
 	c=(unsigned char) v;
 	f.Wcarac(c);

 	b=intens.bleu();
 	if (b<0) b=0;
 	if (b>255) b=255;
 	c=(unsigned char) b;
 	f.Wcarac(c);

}

Couleur calculer_intensite_rayon(point origine, vecteur direction, Objet& scene, Camera camera);

Couleur calcul_intensite_pt_inter(Objet& scene, Camera& camera, vecteur direction, point pt_inter, vecteur vect_normal, Couleurs couleurs) 
{
	Couleur intensite = Couleur(0.0, 0.0, 0.0); 

	// Constantes K
	Couleur Kd = couleurs.diffus();
	Couleur Ka = couleurs.ambiant();
	Couleur Ks = couleurs.speculaire();

	Couleur kr = couleurs.reflechi();
	Couleur kt = couleurs.transmis();

	reel n = 90;

	reel rayon = 0.3;
	entier nb_photons = 200;
	entier found;
	reel* dist2 = NULL; //Liste des distances des photons avec le centre du cercle
	const Photon** ph = NULL; //Liste de photons

	vecteur O = -direction; // Vecteur vers la camera
	bool change = false; // Variable qui indique si on sort ou non d'un objet lors de la refraction

	// On verifie que le vecteur normal et Origine sons du meme cote, en regardant l'angle
	if ((vect_normal * O) < 0)
	{
		vect_normal = -vect_normal;
		change = true;
	}

	// OMBRES
	for (int lumiere = 0; lumiere < camera.NbLumiere(); lumiere++)
	{
		//Lumiere
		const Lumiere* lum = camera.GetLumiere(lumiere);

		const Couleur Kd_lum = lum->Intensite();
		const Couleur Ka_lum = lum->IntensiteAmbiante();


		// Intensites des lumieres
		Couleur Ild = lum->Intensite(); // Intensite de la lumiere diffuse 
		Couleur Ila = lum->IntensiteAmbiante(); // Intensite de la lumiere ambiante

		vecteur L = camera.GetLumiere(lumiere)->Position() - pt_inter; // Vecteur vers la source de lumiere
		
		vecteur H = (L + O) * ((1.0) / (L + O).norme());

		reel distanceLumiere = L.norme(); // Distance entre le point d'intersection et la source lumineuse 

		L.normalise();
		H.normalise();

		reel cos_alpha = H * vect_normal;
		reel cos_theta = L * vect_normal;

		bool illumine = true; // Variable pour indiquer si on doit illuminer le pixel ou non

		reel dist;
		vecteur vn;
		Couleurs cs;


		if (cos_alpha < 0)
		{
			cos_alpha = 0;
		}
		if (cos_theta <= 0)
		{
			cos_alpha = 0; 
		}

		if (Objet_Inter(scene, pt_inter, L, &dist, &vn, &cs)) // On verifie si le rayon intercepte un objet entre pt_inter et la source lumineuse
		{
			if (distanceLumiere <= dist) // On verifie si l'objet est avant ou apres la source lumineuse
			{
				illumine = true;
			}
			else
			{
				illumine = false;
			}
		}
		else
		{
			illumine = true;
		}

		if (illumine == true) // L'objet est en lumiere 
		{			
			intensite = intensite + (Ila * Ka) + (Ild * Kd * cos_theta) + (Ild * Ks * pow(cos_alpha, n));
		}
		else // L'objet est dans l'ombre, on applique uniquement la lumiere ambiante
		{
			intensite = intensite + (Ila * Ka);
		}
	}	

	//CAUSTIQUES
	PhotonMap* CaustiqueMap = pFenAff3D->PhotonTracing()->PhotonMapCaustique();
	CaustiqueMap->Locate(pt_inter, rayon, nb_photons, found, &dist2, &ph);

	if (found > 0)
	{
		Couleur sum = (0, 0, 0);
		reel max_dist = 0;
		for (int p = 1; p <= found; p++)
		{
			//On récupère la distance maximale des photons
			if (dist2[p] > max_dist)
			{
				max_dist = dist2[p];
			}

			const vecteur H = (ph[p]->PhotonDir() - direction).unitaire();

			sum = sum + ((Ks * pow(vect_normal * H, n) / (vect_normal * ph[p]->PhotonDir())) + Kd) * ph[p]->energie();

		}

		intensite = intensite + sum / (PI * max_dist);

		delete[] dist2; // libérer l’espace mémoire
		delete[] ph;
	}
	
	// REFRACTION & REFLEXION (equation de Fresnel) 
	if (kt != Couleur(0.0, 0.0, 0.0))
	{
		// Indices de refraction
		reel vide = 1.0;
		reel air = 1.0003;
		reel eau = 1.33;
		reel verre = 1.5;
		reel diamant = 2.4;

		// les 2 milieux en contact
		reel ni = air;
		reel nt = diamant;

		reel cosi = vect_normal * O;

		if (change) // Si le rayon sort de l'objet on ne prend que le rayon transmis pour ne pas que le rayon reflechi reste à l'interieur de l'objet à l'infini
		{
			std::swap(ni, nt); // On inverse les indices de refraction car on sort de l'objet
			reel nu = ni / nt;

			if ((1 - pow(nu, 2) * (1 - pow((vect_normal * O), 2))) >= 0)
			{
				vecteur T = (nu * (vect_normal * O) - sqrtf(1 - pow(nu, 2) * (1 - pow((vect_normal * O), 2)))) * vect_normal - (nu * O);

				Couleur It = calculer_intensite_rayon(pt_inter, T, scene, camera);

				intensite = intensite + (kt * It);
			}
		}
		else // Le rayon rentre dans l'objet
		{
			// Calcul du rayon reflechi
			vecteur RO = direction - 2 * (direction * vect_normal) * vect_normal;
			Couleur Ir = calculer_intensite_rayon(pt_inter, RO, scene, camera);

			reel nu = ni / nt;

			reel cost = cos(sin(acos(cosi)) * nu);

			reel F_A = pow(((nt * cosi) - (ni * cost)) / ((nt * cosi) + (ni * cost)), 2);
			reel F_B = pow(((ni * cosi) - (nt * cost)) / ((ni * cosi) + (nt * cost)), 2);
			reel F = 0.5 * (F_A + F_B);

			if ((1 - pow(nu, 2) * (1 - pow((vect_normal * O), 2))) >= 0) 
			{
				//Calcul du rayon transmis
				vecteur T = (nu * (vect_normal * O) - sqrtf(1 - pow(nu, 2) * (1 - pow((vect_normal * O), 2)))) * vect_normal - (nu * O);
				Couleur It = calculer_intensite_rayon(pt_inter, T, scene, camera);

				intensite = intensite + ((kr * F) * Ir) + (kt * (1 - F)) * It;
			}
			else // Cas de la reflexion totale interne, on ne prend en compte que la reflexion
			{
				intensite = intensite + (kr * Ir);
			}
		}
	}

	// REFLEXION
	if (kr != Couleur(0.0, 0.0, 0.0) && kt == Couleur(0.0, 0.0, 0.0))
	{
		vecteur RO = direction - 2 * (direction * vect_normal) * vect_normal;
		Couleur Ir = calculer_intensite_rayon(pt_inter, RO, scene, camera);

		intensite = intensite + (kr * Ir);
	}

 	return intensite;
}

Couleur calculer_intensite_rayon(point origine, vecteur direction, Objet &scene, Camera camera)
{
	Couleur intensite = Couleur(0.0, 0.0, 0.0);
  	reel distance;
 	vecteur vect_normal;
 	Couleurs couleurs;

	if (Objet_Inter(scene, origine, direction, &distance, &vect_normal, &couleurs))
 	{
 		point pt_inter = origine + direction * distance;
 		return calcul_intensite_pt_inter(scene, camera, direction, pt_inter, vect_normal, couleurs); // On calcul l'intensite au point d'intersection
 	}
 	else
 	{
 		return Couleur(0.0, 0.0, 0.0); // Couleur du fond de la scene, noir TP1
 	}

}


booleen TraceRayons(const Camera& camera, Objet *scene, const entier& res, char fichier[])
// Genere un rayon pour chacun des pixel et calcul l'intensite de chacun
{ 
	Couleur Intensite(0.0,0.0,0.0);
 	entier nb_pixel_x = res;
 	entier nb_pixel_y = res;

 	Transformation transfInv = Vision_Normee(camera).inverse(); // Transformation de vision inverse 

 	point Point_Origine_CU = camera.PO(); // Point en CU

 	//Ouverture du fichier pour y enregistrer le trace de rayon
 	Fichier f;
 	if ( !f.Open(fichier, "wb") ) return FAUX;

	f.Wchaine("P6\r");
	f.Wentier(res); f.Wcarac(' '); f.Wentier(res);	f.Wchaine("\r");
	f.Wentier(255);	f.Wchaine("\r");

	printf("\nDebut du trace de rayons\n");
	printf ("%4d source(s) lumineuse(s)\n", camera.NbLumiere());

	// Calcul de delta_x et delta_y et initialisation Point Milieu (PM)
	reel delta_x = 2.0 / nb_pixel_x;
	reel delta_y = 2.0 / nb_pixel_y;

	for (int no_y = 1; no_y <= nb_pixel_y; no_y++)   
	{ 
		for (int no_x = 1; no_x <= nb_pixel_x; no_x++)
		{
			reel x = 1 - delta_x / 2.0 - (no_x - 1) * delta_x;
			reel y = 1 - delta_y / 2.0 -(no_y - 1) * delta_y;
			reel z = 1;

			point PM = point(x, y, z);

			vecteur dir = (transfInv.transforme(PM) - Point_Origine_CU);
			dir.normalise();

			// Appel de la fonction calculer_intensite
			Intensite = calculer_intensite_rayon(Point_Origine_CU, dir, *scene, camera); 

			Enregistre_pixel(no_x, no_y,Intensite, f);
	}
		//Imprime le # de ligne rendu

	if ( no_y % 15 == 0 ) printf("\n");
		printf ("%3d ", no_y);	
	}
	printf ("\n\nFin du trace de rayons.\n");


	f.Close();
	return VRAI;
}