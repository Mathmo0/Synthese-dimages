//*******************************************************************

//*																	*

//* Programme: FenetreDesignateur.cpp								*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Fenêtre s'occupant du désignateur.							*

//*																	*

//*******************************************************************



#include "FenetreDesignateur.h"

#include "cgButton.h"

#include "cgFrame.h"

#include "util.h"

#include "designateur.h"	//UpSelect,DownSelect,Z_Select,mZ_Select

#include "global.h"



FenetreDesignateur::FenetreDesignateur(FenetrePrincipale* pFen) : 

			cgForm(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE,

					10,280,

					295,280,

					"Designateur")

{

	pFenAff3D = pFen;



	int t = 15;

	int l = 15;

	AddControl(new cgFrame(l-5,t-5,195,80,"Objets "));

	BTN_UP = AddControl(new cgButton(10+l,10+t,80,25,"Up"));

	BTN_DOWN = AddControl(new cgButton(95+l,10+t,80,25,"Down"));

	BTN_PLUS_Z = AddControl(new cgButton(10+l,40+t,80,25,"+Z"));

	BTN_MOINS_Z = AddControl(new cgButton(95+l,40+t,80,25,"-Z"));



	t = 110;

	l = 15;

	AddControl(new cgFrame(l-5,t-5,195,50,"Composantes "));

	BTN_UP_COMPO = AddControl(new cgButton(10+l,10+t,80,25,"+Z"));

	BTN_DOWN_COMPO = AddControl(new cgButton(95+l,10+t,80,25,"-Z"));



	t = 175;

	l = 15;

	AddControl(new cgFrame(l-5,t-5,195,50,"Eps "));

	BTN_EPSMUL = AddControl(new cgButton(10+l,10+t,80,25,"Eps*2"));

	BTN_EPSDIV = AddControl(new cgButton(95+l,10+t,80,25,"Eps/2"));



	t = 240;

	l = 15;

	AddControl(new cgFrame(l-5,t-5,273,40,"Debug "));

	BTN_PRINT_SELECT = AddControl(new cgButton(3+l,5+t,55,25,"Select"));

	BTN_PRINT_SCENE = AddControl(new cgButton(64+l,5+t,50,25,"Scene"));

	BTN_PRINT_PATH = AddControl(new cgButton(120+l,5+t,45,25,"Path"));

	BTN_PRINT_COMPOSANTE = AddControl(new cgButton(170+l,5+t,90,25,"Composante"));



	BTN_FERMER = AddControl(new cgButton(215,20,70,25,"Fermer"));

}



void FenetreDesignateur::OnChange(CONTROL_ID ID)

{

	if	( ID == BTN_UP )

	{

		pFenAff3D->Scene()->Designateur()->UpSelect();

		pFenAff3D->Redraw();

	}

	else if	( ID == BTN_DOWN )

	{

		pFenAff3D->Scene()->Designateur()->DownSelect();

		pFenAff3D->Redraw();

	}

	else if	( ID == BTN_PLUS_Z )

	{

		pFenAff3D->Scene()->Designateur()->Z_Select(pFenAff3D->Scene()->Scene());

		pFenAff3D->Redraw();

	}

	else if	( ID == BTN_MOINS_Z )

	{

		pFenAff3D->Scene()->Designateur()->mZ_Select(pFenAff3D->Scene()->Scene());

		pFenAff3D->Redraw();

	}

	else if	( ID == BTN_UP_COMPO )

	{

		pFenAff3D->Scene()->Designateur()->Z_SelectComposante(pFenAff3D->Scene()->Scene());

		pFenAff3D->Redraw();

	}

	else if	( ID == BTN_DOWN_COMPO )

	{

		pFenAff3D->Scene()->Designateur()->mZ_SelectComposante(pFenAff3D->Scene()->Scene());

		pFenAff3D->Redraw();

	}

	else if	( ID == BTN_EPSMUL )

	{

		epselect *= 2;

		pFenAff3D->Redraw();

	}

	else if	( ID == BTN_EPSDIV )

	{

		epselect /= 2;

		pFenAff3D->Redraw();

	}

	else if ( ID == BTN_PRINT_SELECT )

	{

		if ( pFenAff3D->Scene()->Designateur()->OkSelection() )

			Print_Objet(pFenAff3D->Scene()->Designateur()->Selection());

	}

	else if ( ID == BTN_PRINT_SCENE )

		Print_Objet(pFenAff3D->Scene()->Scene());

	else if ( ID == BTN_PRINT_PATH )

		Print_Objet(pFenAff3D->Scene()->Designateur()->Path());

	else if ( ID == BTN_PRINT_COMPOSANTE )

	{

		if ( pFenAff3D->Scene()->Designateur()->OkComposante() )

			Print_Objet(pFenAff3D->Scene()->Designateur()->Composante());

	}

	else if	( ID == BTN_FERMER )

		HideWindow();

}

