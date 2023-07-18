#include "Settings.h"



Settings::Settings() 

{

	//Variables des settings

	CullFace(FAUX);

	OpenGL(VRAI);

	Gouraud(VRAI);

	PolygoneRemplit(VRAI);

	ContourPolygone(FAUX);

	ExposantPhong(60);

	CouleurContourPolygone(Attributs(Couleur(0.5)));

	Meridiens(21);

	Paralleles(20);

	Nbiter(4);

}



Settings::~Settings()

{

}



void Settings::ChangeStyleSelection(TYPE_SELECTION type_sel)

{

	if ( type_sel == OBJET_SELECTION )

		m_CoulSelection = Couleur(1,0,0);

	else

		m_CoulSelection = Couleur(1,1,0);

}

