//*******************************************************************

//*																	*

//* Programme: FenetreSetting.cpp									*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Fenêtre s'occupant des configurations du noyau graphique.	*

//*																	*

//*******************************************************************



#include "FenetreSetting.h"

#include "cgButton.h"

#include "cgCheckBox.h"

#include "cgSpinner.h"

#include "cgFrame.h"

#include "cgLabel.h"



FenetreSetting::FenetreSetting(FenetrePrincipale* pFen) : 

			cgForm(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE,

					425,400,

					345,260,

					"Setting")

{

	pFenAff3D = pFen;



	int t = 15;

	int l = 15;

	AddControl(new cgFrame(l-5,t-5,230,190,"Options "));

	pOpenGL	= new cgCheckBox(10+l,10+t, 6 ,"OpenGL");

//	CHKBOX_OPENGL =	AddControl(pOpenGL);

	pGouraud = new cgCheckBox(10+l,10+t, 6 ,"Gouraud");

	CHKBOX_GOURAUD = AddControl(pGouraud);

	pPolygoneRemplit = new cgCheckBox(10+l,30+t,16, "Remplit polygone");

	CHKBOX_POLYGONE_REMPLIT = AddControl(pPolygoneRemplit);

	pContoursPolygone = new cgCheckBox(10+l,50+t,17, "Contours polygone");

	CHKBOX_CONTOURS_POLYGONE = AddControl(pContoursPolygone);

	pCullFace = new cgCheckBox(10+l,70+t,24, "Affichage faces arrieres");

	CHKBOX_CULL_FACE = AddControl(pCullFace);



	pMeridiens = new cgSpinner(10+l,t+100,2,3,99);

	SPIN_MERIDIENS = AddControl(pMeridiens);

	AddControl(new cgLabel(65+l,t+110," Meridien(s)"));

	pParalleles = new cgSpinner(10+l,t+125,2,1,99);

	SPIN_PARALLELES = AddControl(pParalleles);

	AddControl(new cgLabel(65+l,t+135," Parallele(s)"));



	pNbiter = new cgSpinner(10+l,t+155,2,0,99);

	SPIN_NBITER = AddControl(pNbiter);

	AddControl(new cgLabel(65+l,t+170," Nb iteration(s)"));





	BTN_FERMER = AddControl(new cgButton(255,20,80,25,"Fermer"));



	//Initialisation des valeurs des controles

	pOpenGL->SetValue( pFenAff3D->Display()->Settings()->OpenGL() );

	pGouraud->SetValue( pFenAff3D->Display()->Settings()->Gouraud() );

	pPolygoneRemplit->SetValue( pFenAff3D->Display()->Settings()->PolygoneRemplit() );

	pContoursPolygone->SetValue( pFenAff3D->Display()->Settings()->ContourPolygone() );

	pCullFace->SetValue( !pFenAff3D->Display()->Settings()->CullFace() );

	pMeridiens->SetValue( pFenAff3D->Display()->Settings()->Meridiens() );

	pParalleles->SetValue( pFenAff3D->Display()->Settings()->Paralleles() );

	pNbiter->SetValue( pFenAff3D->Display()->Settings()->Nbiter() );

}



FenetreSetting::~FenetreSetting()

{

	//C'est cgForm qui s'occupe de detruire les controles utilisées

}



void FenetreSetting::OnChange(CONTROL_ID ID)

{

	if ( ID == CHKBOX_OPENGL )

	{

		pFenAff3D->Display()->Settings()->OpenGL(pOpenGL->GetValue());

		pFenAff3D->Redraw();

	}

	else if ( ID == CHKBOX_GOURAUD )

	{

		pFenAff3D->Display()->Settings()->Gouraud(pGouraud->GetValue());

		pFenAff3D->Redraw();

	}

	else if ( ID == CHKBOX_POLYGONE_REMPLIT )

	{

		pFenAff3D->Display()->Settings()->PolygoneRemplit(pPolygoneRemplit->GetValue());

		pFenAff3D->Redraw();

	}

	else if ( ID == CHKBOX_CONTOURS_POLYGONE )

	{

		pFenAff3D->Display()->Settings()->ContourPolygone(pContoursPolygone->GetValue());

		pFenAff3D->Redraw();

	}

	else if ( ID == CHKBOX_CULL_FACE )

	{

		pFenAff3D->Display()->Settings()->CullFace(!pCullFace->GetValue());

		pFenAff3D->Redraw();

	}

	else if ( ID == SPIN_MERIDIENS )

	{

		int nbMeridiens = pMeridiens->GetValue();

		pFenAff3D->Display()->Settings()->Meridiens(nbMeridiens);

		pFenAff3D->Redraw();

	}

	else if ( ID == SPIN_PARALLELES )

	{

		int nbParalleles = pParalleles->GetValue();

		pFenAff3D->Display()->Settings()->Paralleles(nbParalleles);

		pFenAff3D->Redraw();

	}

	else if ( ID == SPIN_NBITER )

	{

		int nbIter = pNbiter->GetValue();

		pFenAff3D->Display()->Settings()->Nbiter(nbIter);

		pFenAff3D->Redraw();

	}



	else if	( ID == BTN_FERMER )

		HideWindow();

}





void FenetreSetting::ChangeGouraud()

{

	pGouraud->SetValue(!pGouraud->GetValue());

	pFenAff3D->Display()->Settings()->Gouraud(pGouraud->GetValue());

	Redraw();

}



void FenetreSetting::ChangePolygoneRemplit()

{

	pPolygoneRemplit->SetValue(!pPolygoneRemplit->GetValue());

	pFenAff3D->Display()->Settings()->PolygoneRemplit(pPolygoneRemplit->GetValue());

	Redraw();

}



void FenetreSetting::ChangeContourPolygone()

{

	pContoursPolygone->SetValue(!pContoursPolygone->GetValue());

	pFenAff3D->Display()->Settings()->ContourPolygone(pContoursPolygone->GetValue());

	Redraw();

}



void FenetreSetting::ChangeCullFace()

{

	pCullFace->SetValue(!pCullFace->GetValue());

	pFenAff3D->Display()->Settings()->CullFace(pCullFace->GetValue());

	Redraw();

}