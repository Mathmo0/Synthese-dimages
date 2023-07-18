//*******************************************************************

//*																	*

//* Programme: DisplayOpenGL.h										*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Classe permettant de faire l'affichage des primitives.		*

//*																	*

//*******************************************************************



#ifndef _DISPLAY

#define _DISPLAY



#include "Attr.h"

#include "Camera.h"

#include "Settings.h"



class Display

{

protected:

	Settings settings;		//Settings pour l'affichage de l'editeur



public:

	Display();

	~Display();



	Settings* Settings() { return &settings; }



	//Initialise le mode d'OpenGL

	void InitDisplay();

	

	//Dessine la scene

	void SetupCamera(Camera* pCamera);

	void SetupLighting(Camera* pCamera);



	//Indique un changement de dimension de la fenetre

	void OnChangeSize(int w, int h);



	//Gestion de la grosseur du trait

	void GrosseurTrait(int grosseur);

	int GrosseurTrait();



	void Pointille(short pattern, int facteur);

	void DesactivePointille();



	void CullingFace(booleen c);

	void Gouraud(booleen g);



	//----------------------------------------------------------------

	//Affichage des primitives dans la fenetre pour dessinner la scene

	//----------------------------------------------------------------

	void Ligne(double x1, double y1, double x2, double y2, const Attributs& a);

	void Ligne(double x1, double y1, double z1, double x2, double y2, double z2, const Attributs& a);

	void Polygone(int n, double x[], double y[], const Attributs& a);

	void Polygone(int n, double x[], double y[], double z[], const Attributs& a);

	void Polygone(int n, double x[], double y[], double z[],

				double nx[], double ny[], double nz[],

				const Attributs& a);



protected:

	//Gestion de l'affichage de proprietes des objets

	void Speculaire(const Couleur& p);

	void Diffus(const Attributs& a);

	void ContourPolygone();

};



#endif
