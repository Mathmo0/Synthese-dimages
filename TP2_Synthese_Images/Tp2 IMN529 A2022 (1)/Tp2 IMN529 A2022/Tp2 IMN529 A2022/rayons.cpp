/******************************************************************/
/*                                                                */   
/* noms + matricules                                              */   
/*                                                                */   
/*                                                                */   
/*                                                                */   
/*                                                                */   
/*                                                                */   
/*                                                                */   
/*                                                                */   
/*                                                                */   
/*                                                                */   
/******************************************************************/






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
#include <math.h>




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


booleen TraceRayons(const Camera& camera, Objet *scene, const entier& res, char fichier[])
// Genere un rayon pour chacun des pixel et calcul l'intensite de chacun
{ 
	Couleur Intensite (0.0,0.0,0.0);

	entier nb_pixel_x = res;
	entier nb_pixel_y = res;

	Transformation transfInv = Vision_Normee(camera).inverse(); // transformation de vision inverse

// ...

	//Ouverture du fichier pour y enregistrer le trace de rayon
	Fichier f;
	if ( !f.Open(fichier, "wb") ) return FAUX;

	f.Wchaine("P6\r");
	f.Wentier(res); f.Wcarac(' '); f.Wentier(res);	f.Wchaine("\r");
	f.Wentier(255);	f.Wchaine("\r");

	printf("\nDebut du trace de rayons\n");
	printf ("%4d source(s) lumineuse(s)\n", camera.NbLumiere());
// ...

	for (int no_y = 1; no_y <= nb_pixel_y; no_y++)   
	{ 
		for (int no_x = 1; no_x <= nb_pixel_x; no_x++)    
		{
// ...
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


  
