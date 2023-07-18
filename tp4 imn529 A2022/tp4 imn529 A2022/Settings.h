#ifndef _SETTINGS

#define _SETTINGS



#include "Definition.h"

#include "Attr.h"



class Settings

{

protected:

	Couleur m_CoulSelection;//Variables pour la couleur d'affichage de la sélection



	booleen m_bCullFace;	//Gestion de l'affichage des faces arrieres

	booleen m_bOpenGL;		//Affichage avec ou sans OpenGL

	booleen m_bAvecGouraud;	//Indique si on utilise Gouraud pour les vecteurs normaux

	entier	m_nExpPhong;	//Exposant de Phong(speculaire)



	booleen	m_bAvecFill;	//Remplissage des polygones ou non

	booleen	m_bAvecFrame;	//Contour des polygones s'il y a un remplissage

	Attributs m_aContourPolygone;	//Indique la couleur des contours de polygones

	

	entier	m_nMeridiens;	//Nombre de meridiens

	entier	m_nParalleles;	//Nombre de Paralleles

	entier	m_nNbiter;	    //Nombre de subdivision pour les fractals (OpenGL)



public:

	Settings();

	~Settings();



	booleen OpenGL()			{ return m_bOpenGL; }

	booleen CullFace()			{ return m_bCullFace; }

	entier ExposantPhong()		{ return m_nExpPhong; }

	booleen PolygoneRemplit()	{ return m_bAvecFill; }

	booleen ContourPolygone()	{ return m_bAvecFrame; }

	Attributs CouleurContourPolygone() { return m_aContourPolygone; }

	booleen Gouraud()			{ return m_bAvecGouraud; }

	entier Meridiens()			{ return m_nMeridiens; }

	entier Paralleles()			{ return m_nParalleles; }

	entier Nbiter()				{ return m_nNbiter; }



	void Gouraud(booleen v)			{ m_bAvecGouraud = v; }

	void CullFace(booleen v)		{ m_bCullFace = v; }

	void OpenGL(booleen v)			{ m_bOpenGL = v; }

	void ExposantPhong(entier n)	{ m_nExpPhong = n; }

	void PolygoneRemplit(booleen v) { m_bAvecFill = v; }

	void ContourPolygone(booleen v) { m_bAvecFrame = v; }

	void CouleurContourPolygone(Attributs a) { m_aContourPolygone = a; }

	void Meridiens(entier n)		{ m_nMeridiens = n; }

	void Paralleles(entier n)		{ m_nParalleles = n; }

	void Nbiter(entier n)			{ m_nNbiter = n; }





	void ChangeStyleSelection(TYPE_SELECTION coul_sel);

	Couleur CoulSelection() { return m_CoulSelection; }

};



#endif

