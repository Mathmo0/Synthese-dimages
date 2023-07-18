//*******************************************************************

//*																	*

//* Programme: FenetreCamera.cpp									*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Fenêtre permettant de modifier la position de la caméra		*

//*		dans la scène.												*

//*																	*

//*******************************************************************



#include "FenetreCamera.h"

#include "cgButton.h"

#include "cgCheckBox.h"

#include "cgSpinner.h"

#include "cgFrame.h"

#include "cgLabel.h"



FenetreCamera::FenetreCamera(FenetrePrincipale* pFen) : 

			cgForm(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE,

					425,10,

					350,320,

					"Caméra")

{

	pFenAff3D = pFen;



	int t = 15;

	int l = 15;

	AddControl(new cgFrame(l-5,t-5,205,115,"Mouvements "));

	BTN_HAUT =		AddControl(new cgButton( 70+l,3+t,60,23,"Haut"));

	BTN_BAS =		AddControl(new cgButton( 70+l,51+t,60,23,"Bas"));

	BTN_GAUCHE =	AddControl(new cgButton( 38+l,27+t,60,23,"Gauche"));

	BTN_DROITE =	AddControl(new cgButton(101+l,27+t,60,23,"Droite"));



	BTN_AVANCE =	AddControl(new cgButton( 10+l,80+t,85,25,"Avance"));

	BTN_RECULE =	AddControl(new cgButton(100+l,80+t,85,25,"Recule"));



	l = 225;

	AddControl(new cgFrame(l-5,t-5,120,110,"Options "));

	pVHFixe = new cgCheckBox(10+l,10+t,7, "VH Fixe");

	CHKBOX_VH_FIXE =	AddControl(pVHFixe);

	pPRFixe = new cgCheckBox(10+l,27+t,7, "PR Fixe");

	CHKBOX_PR_FIXE =	AddControl(pPRFixe);



	BTN_HORAIRE =		AddControl(new cgButton( 5+l,45+t,100,25,"Horaire"));

	BTN_ANTIHORAIRE =	AddControl(new cgButton( 5+l,75+t,100,25,"Anti-Horaire"));



	t = 145;

	l = 15;

	AddControl(new cgFrame(10,t-5,205,43,"Deplacement "));

	pSpinPas = new cgSpinner(10+l,t+10,2,-99,99,0);

	SPIN_PAS = AddControl(pSpinPas);

	AddControl(new cgLabel(78,t+23,"= i"));

	AddControl(new cgLabel(120+l,t+23,"pas = 2^i"));



	l = 225;

	AddControl(new cgFrame(l-5,t-5,120,60,"Distance "));

	BTN_DOPLUS =	AddControl(new cgButton( 14+l,5+t,40,20,"Do +"));

	BTN_DOMOINS =	AddControl(new cgButton( 59+l,5+t,40,20,"Do -"));

	BTN_DVPLUS =	AddControl(new cgButton( 14+l,30+t,40,20,"Dv +"));

	BTN_DVMOINS =	AddControl(new cgButton( 59+l,30+t,40,20,"Dv -"));



	t = 200;

	l = 15;

	AddControl(new cgFrame(l-5,t-5,205,50,"Projection "));

	cgcString text[2];

	text[0] = "Parallele";

	text[1] = "Perspective";

	pParallele = new cgRadioButton(30,205, 2, text, RADIO_VERTICAL,0,VRAI);

	RADIO_PARALLELE = AddControl(pParallele);



	t = 265;

	l = 15;

	AddControl(new cgFrame(l-5,t-5,205,50,"Fenetre "));

	BTN_FEN_F2 = AddControl(new cgButton( 5+l,10+t,90,25,"Fenetre*2"));

	BTN_FEN_D2 = AddControl(new cgButton( 100+l,10+t,90,25,"Fenetre/2"));



	BTN_FERMER = AddControl(new cgButton(240,210,80,25,"Fermer"));



	//Initialisation des valeurs des controles

	pVHFixe->SetValue( pFenAff3D->Scene()->GetpCamera()->GetVHFixe() );

	pPRFixe->SetValue( pFenAff3D->Scene()->GetpCamera()->GetPRFixe() );



//	pSpinPas->SetValue( pFenAff3D->Scene()->GetpCamera()->GetPas() );

	// il n'y a pas de membre "pas" alors "step" est utilisé : pas de sens

	pSpinPas->SetValue( 0.0 );



	pParallele->SetSelection( pFenAff3D->Scene()->GetpCamera()->perspective() );

}



void FenetreCamera::OnChange(CONTROL_ID ID)

{

	if		( ID == BTN_HAUT )

		pFenAff3D->Scene()->GetpCamera()->Up();

	else if ( ID == BTN_BAS )

		pFenAff3D->Scene()->GetpCamera()->Down();

	else if	( ID == BTN_GAUCHE )

		pFenAff3D->Scene()->GetpCamera()->Left();

	else if ( ID == BTN_DROITE )

		pFenAff3D->Scene()->GetpCamera()->Right();

	else if ( ID == BTN_AVANCE )

		pFenAff3D->Scene()->GetpCamera()->Front();

	else if ( ID == BTN_RECULE )

		pFenAff3D->Scene()->GetpCamera()->Back();

	else if ( ID == CHKBOX_VH_FIXE )

		pFenAff3D->Scene()->GetpCamera()->LockVH(pVHFixe->GetValue());

	else if ( ID == CHKBOX_PR_FIXE )

		pFenAff3D->Scene()->GetpCamera()->PRmode(pPRFixe->GetValue());

	else if ( ID == BTN_HORAIRE )

		pFenAff3D->Scene()->GetpCamera()->Horaire();

	else if ( ID == BTN_ANTIHORAIRE )

		pFenAff3D->Scene()->GetpCamera()->AntiHoraire();

	else if ( ID == SPIN_PAS )

		pFenAff3D->Scene()->GetpCamera()->Pas(pSpinPas->GetValue());

	else if ( ID == BTN_DOPLUS )

		pFenAff3D->Scene()->GetpCamera()->DOplus();

	else if ( ID == BTN_DOMOINS )

		pFenAff3D->Scene()->GetpCamera()->DOmoins();

	else if ( ID == BTN_DVPLUS )

		pFenAff3D->Scene()->GetpCamera()->DVplus();

	else if ( ID == BTN_DVMOINS )

		pFenAff3D->Scene()->GetpCamera()->DVmoins();

	else if ( ID == RADIO_PARALLELE )

	{

		pFenAff3D->Scene()->GetpCamera()->perspective(pParallele->GetSelection());

		pFenAff3D->Redraw();		

	}

	else if ( ID == BTN_FEN_F2 )

		pFenAff3D->Scene()->GetpCamera()->FenetreMul2();

	else if ( ID == BTN_FEN_D2 )

		pFenAff3D->Scene()->GetpCamera()->FenetreDiv2();

	else if	( ID == BTN_FERMER )

		HideWindow();



	pFenAff3D->Redraw();

}

