//*******************************************************************

//*																	*

//* Programme: FenetreAnimation.cpp									*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Fenêtre s'occupant des animations du noyau graphique.		*

//*																	*

//*******************************************************************



#include "FenetreAnimation.h"

#include "cgButton.h"

#include "cgCheckBox.h"

#include "cgSpinner.h"

#include "cgFrame.h"

#include "cgLabel.h"

#include "main.h"



FenetreAnimation::FenetreAnimation(FenetrePrincipale* pFen) : 

			cgForm(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE,

					400,400,

					265,125,

					"Animation")

{

	pFenAff3D = pFen;



	int t = 15;

	int l = 15;

	AddControl(new cgFrame(l-5,t-5,150,100,"Animation "));

	pAnimate = new cgCheckBox(10+l,10+t, 6 ,"Animer");

	CHKBOX_ANIMATE = AddControl(pAnimate);



	AddControl(new cgLabel(5+l,t+50," Slide #"));

	pSlide = new cgSpinner(75+l,t+35,3,0,pFenAff3D->NbScene()+1);

	SPIN_SLIDE = AddControl(pSlide);



	AddControl(new cgLabel(5+l,t+80," Delai:"));

	pDelai = new cgSpinner(75+l,t+65,3,1,999);

	SPIN_DELAI = AddControl(pDelai);



	BTN_FERMER = AddControl(new cgButton(175,20,80,25,"Fermer"));



	//Initialisation des valeurs des controles

	pAnimate->SetValue( FAUX );

	pSlide->SetValue( pFenAff3D->SceneActive()+1 );

	pDelai->SetValue( pApplication->GetWaitTimer()/10 );

}



FenetreAnimation::~FenetreAnimation()

{

	//C'est cgForm qui s'occupe de detruire les controles utilisées

}



void FenetreAnimation::OnChange(CONTROL_ID ID)

{

	if ( ID == CHKBOX_ANIMATE )

	{

		pFenAff3D->Animate(pAnimate->GetValue());

		pFenAff3D->Redraw();

	}

	else if ( ID == SPIN_SLIDE )

	{

		int no_slide = pSlide->GetValue()-1;

		if ( no_slide == pFenAff3D->NbScene() )

		{

			no_slide = 0;

			pSlide->SetValue(no_slide+1);

			Redraw();

		}

		else if ( no_slide == -1 )

		{

			no_slide = pFenAff3D->NbScene()-1;

			pSlide->SetValue(no_slide+1);

			Redraw();			

		}

		pFenAff3D->SceneActive(no_slide);

		pFenAff3D->Redraw();

	}

	else if ( ID == SPIN_DELAI )

	{

		int delai = pDelai->GetValue();

		pApplication->ChangeWaitTimer(delai*10);

	}

	else if	( ID == BTN_FERMER )

		HideWindow();

}



void FenetreAnimation::ChangeSlide(entier no)

{

	pSlide->SetValue(no);

	Redraw();

}



void FenetreAnimation::ChangeAnimate()

{

	pAnimate->SetValue(!pAnimate->GetValue());

	pFenAff3D->Animate(pAnimate->GetValue());

	Redraw();

}