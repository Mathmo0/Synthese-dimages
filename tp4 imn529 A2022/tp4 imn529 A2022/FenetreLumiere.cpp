//*******************************************************************

//*																	*

//* Programme: FenetreLumiere.cpp										*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Fenêtre permettant d'allumer ou d'eteindre les lumieres		*

//*		de la scene.												*

//*																	*

//*******************************************************************
#pragma warning(disable : 4996)


#include <cstdlib> 

#include "FenetreLumiere.h"

#include "cgLabel.h"

#include "cgFrame.h"



FenetreLumiere::FenetreLumiere(FenetrePrincipale* pFen) : 

			cgForm(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE,

					5,5,

					550,265,

					"Lumieres")

{

	pFenAff3D = pFen;



	//Il faut au moins 1 lumiere pour pouvoir les changer

	if ( pFen->Scene()->GetCamera().NbLumiere() )

	{

		pActiveAll = new cgCheckBox(20,5, 16, "Lumieres actives");

		ACTIVEALL =	AddControl(pActiveAll);

		pActiveAll->SetValue(pFen->Scene()->GetCamera().LumiereActiveScene());



		AddControl(new cgLabel(290,18,"Lumiere: "));

		pChoixLumiere = new cgSpinner(360,6,1,1,pFen->Scene()->GetCamera().NbLumiere());

		SPIN_LUMIERE = AddControl(pChoixLumiere);

		pChoixLumiere->SetValue(1);



		char strLum[10] = "Lumiere  ";

		char c[10];

		itoa(pChoixLumiere->GetValue(),c,10);

		strLum[8] = c[0];



		int t = 40; int l = 15;

		AddControl(new cgFrame(l-10,t-5,540,190,""));

		pActive = new cgCheckBox(5+l,t-10,9, strLum);

		ACTIVE =	AddControl(pActive);



		t += 20;

		AddControl(new cgLabel(13,t,"Couleur ambiante"));

		AddControl(new cgLabel(23,t+25,"R"));

		pLumAmbR = new cgSliderWithDisplay(24+l,t+10,100, 0.0, 1.0, 1, 2, 10, 0.01, 10);

		LUM_AMB_R = AddControl(pLumAmbR);

		AddControl(new cgLabel(195,t+25,"G"));

		pLumAmbG = new cgSliderWithDisplay(196+l,t+10,100, 0.0, 1.0, 1, 2, 10, 0.01, 10);

		LUM_AMB_G = AddControl(pLumAmbG);

		AddControl(new cgLabel(370,t+25,"B"));

		pLumAmbB = new cgSliderWithDisplay(371+l,t+10,100, 0.0, 1.0, 1, 2, 10, 0.01, 10);

		LUM_AMB_B = AddControl(pLumAmbB);



		t += 60;

		AddControl(new cgLabel(13,t,"Couleur diffuse"));

		AddControl(new cgLabel(23,t+25,"R"));

		pLumDifR = new cgSliderWithDisplay(24+l,t+10,100, 0.0, 1.0, 1, 2, 10, 0.01, 10);

		LUM_DIF_R = AddControl(pLumDifR);

		AddControl(new cgLabel(195,t+25,"G"));

		pLumDifG = new cgSliderWithDisplay(196+l,t+10,100, 0.0, 1.0, 1, 2, 10, 0.01, 10);

		LUM_DIF_G = AddControl(pLumDifG);

		AddControl(new cgLabel(370,t+25,"B"));

		pLumDifB = new cgSliderWithDisplay(371+l,t+10,100, 0.0, 1.0, 1, 2, 10, 0.01, 10);

		LUM_DIF_B = AddControl(pLumDifB);



		t += 60;

		AddControl(new cgLabel(13,t,"Position"));

		AddControl(new cgLabel(23,t+25,"X: "));

		pPositionX = new cgSpinner(24+l,t+10,4,-9999,9999);

		SPIN_POSX = AddControl(pPositionX);

		pPositionX->SetValue(pFen->Scene()->GetpCamera()->Position(pChoixLumiere->GetValue()-1).x());

		AddControl(new cgLabel(195,t+25,"Y: "));

		pPositionY = new cgSpinner(196+l,t+10,4,-9999,9999);

		SPIN_POSY = AddControl(pPositionY);

		pPositionY->SetValue(pFen->Scene()->GetpCamera()->Position(pChoixLumiere->GetValue()-1).y());

		AddControl(new cgLabel(370,t+25,"Z: "));

		pPositionZ = new cgSpinner(371+l,t+10,4,-9999,9999);

		SPIN_POSZ = AddControl(pPositionZ);

		pPositionZ->SetValue(pFen->Scene()->GetpCamera()->Position(pChoixLumiere->GetValue()-1).z());	

	}



	BTN_FERMER = AddControl(new cgButton(435,235,80,25,"Fermer"));



	ChangeLumiere();

}



void FenetreLumiere::OnChange(CONTROL_ID ID)

{

	if ( ID == ACTIVEALL )

	{

		pFenAff3D->Scene()->GetpCamera()->LumiereActiveScene(pActiveAll->GetValue());

		pFenAff3D->Redraw();

	}

	else if ( ID == ACTIVE )

	{

		pFenAff3D->Scene()->GetpCamera()->ActiverLumiere(pChoixLumiere->GetValue()-1, pActive->GetValue());

		pFenAff3D->Redraw();

	}

	else if	( ID == SPIN_LUMIERE )

	{

		ChangeLumiere();

		Redraw();

	}

	else if	( ID == LUM_AMB_R || ID == LUM_AMB_G || ID == LUM_AMB_B )

		SetAmbiante();

	else if	( ID == LUM_DIF_R || ID == LUM_DIF_G || ID == LUM_DIF_B )

		SetDiffuse();

	else if	( ID == SPIN_POSX || ID == SPIN_POSY || ID == SPIN_POSZ )

		SetPosition();

	else if	( ID == BTN_FERMER )

		HideWindow();

}



void FenetreLumiere::SetAmbiante()

{

	float valR = ((float)pLumAmbR->GetValue());

	float valG = ((float)pLumAmbG->GetValue());

	float valB = ((float)pLumAmbB->GetValue());



	pFenAff3D->Scene()->GetpCamera()->IntensiteAmbiante(pChoixLumiere->GetValue()-1, Couleur(valR, valG, valB) );

	pFenAff3D->Redraw();

}



void FenetreLumiere::SetDiffuse()

{

	float valR = ((float)pLumDifR->GetValue());

	float valG = ((float)pLumDifG->GetValue());

	float valB = ((float)pLumDifB->GetValue());



	pFenAff3D->Scene()->GetpCamera()->Intensite(pChoixLumiere->GetValue()-1, Couleur(valR, valG, valB) );

	pFenAff3D->Redraw();

}



void FenetreLumiere::SetPosition()

{

	point p = pFenAff3D->Scene()->GetpCamera()->Position(pChoixLumiere->GetValue()-1);



	point pprime(pPositionX->GetValue(),pPositionY->GetValue(),pPositionZ->GetValue());

	pFenAff3D->Scene()->GetpCamera()->Position(pChoixLumiere->GetValue()-1, pprime);

	pFenAff3D->Redraw();

}



void FenetreLumiere::ChangeLumiere()

{

	pActive->SetValue(pFenAff3D->Scene()->GetpCamera()->LumiereActive(pChoixLumiere->GetValue()-1));

	char strLum[10] = "Lumiere  ";

	char c[10];

	itoa(pChoixLumiere->GetValue(),c,10);

	strLum[8] = c[0];

	pActive->SetCaption(strLum);



	Couleur ambiante = pFenAff3D->Scene()->GetpCamera()->IntensiteAmbiante(pChoixLumiere->GetValue()-1);

	pLumAmbR->SetValue(ambiante.rouge());

	pLumAmbG->SetValue(ambiante.vert());

	pLumAmbB->SetValue(ambiante.bleu());



	Couleur diffuse = pFenAff3D->Scene()->GetpCamera()->Intensite(pChoixLumiere->GetValue()-1);

	pLumDifR->SetValue(diffuse.rouge());

	pLumDifG->SetValue(diffuse.vert());

	pLumDifB->SetValue(diffuse.bleu());



	point p = pFenAff3D->Scene()->GetpCamera()->Position(pChoixLumiere->GetValue()-1);

	pPositionX->SetValue(p.x());

	pPositionY->SetValue(p.y());

	pPositionZ->SetValue(p.z());

}