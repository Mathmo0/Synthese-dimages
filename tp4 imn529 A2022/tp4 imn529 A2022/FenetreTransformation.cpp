//*******************************************************************
//*																	*
//* Programme: FenetreTransformation.cpp							*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Fenêtre s'occupant d'appliquer des tranformations(rotation,	*
//*		translations, homothétie) sur les objets de la scène.		*
//*																	*
//*******************************************************************

#include "FenetreTransformation.h"
#include "cgButton.h"
#include "cgFrame.h"
#include "cgLabel.h"
#include "cgChoiceBox.h"

#include <cmath>			//sqrt

FenetreTransformation::FenetreTransformation(FenetrePrincipale* pFen) 
	: cgForm(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE, 400,350, 345,200,
										"Transformation")
{
	pFenAff3D = pFen;

	int t = 15;
	int l = 15;
	AddControl(new cgFrame(l-5,t-5,230,50,"Homothetie "));
	BTN_HOMO_X = AddControl(new cgButton(10+l,10+t,50,25,"X"));
	BTN_HOMO_1_X = AddControl(new cgButton(65+l,10+t,50,25,"1/X"));
	AddControl(new cgLabel(140,t+25,"x="));
	cgcTableau<cgcString> t1(5);
	t1[0] = "-1"; t1[1] = "rac2"; t1[2] = "rac3"; t1[3] = "2"; t1[4] = "3";
	pChoiceBoxX = new cgChoiceBox(150+l,t+10,4,t1,0);
	CHOICEBOX_X = AddControl(pChoiceBoxX);

	t = 80;
	l = 15;
	AddControl(new cgFrame(l-5,t-5,290,50,"Translation "));
	BTN_TRANS_KV = AddControl(new cgButton(10+l,10+t,50,25,"+kv"));
	BTN_TRANS_MOINS_KV = AddControl(new cgButton(65+l,10+t,50,25,"-kv"));
	pSpinK = new cgSpinner(122+l,t+13,2,-99,99);
	SPIN_K = AddControl(pSpinK);
	AddControl(new cgLabel(190,t+25,"= i"));
	AddControl(new cgLabel(205+l,t+25,"(k = 2^i)"));

	t = 145;
	l = 15;
	AddControl(new cgFrame(l-5,t-5,250,50,"Rotation "));
	BTN_ROT_TETA = AddControl(new cgButton(10+l,10+t,50,25,"teta"));
	BTN_ROT_MOINS_TETA = AddControl(new cgButton(65+l,10+t,50,25,"-teta"));
	AddControl(new cgLabel(140,t+25,"teta="));
	cgcTableau<cgcString> t2(6);
	t2[0] = "PI/180"; t2[1] = "PI/36"; t2[2] = "PI/12"; t2[3] = "PI/4"; t2[4] = "PI/3"; t2[5] = "PI/2"; t2[6] = "PI";
	pChoiceBoxTeta = new cgChoiceBox(170+l,t+10,4,t2,0);
	CHOICEBOX_TETA = AddControl(pChoiceBoxTeta);

	BTN_APPLIQUER = AddControl(new cgButton(255,10,80,25,"Appliquer"));
	BTN_FERMER = AddControl(new cgButton(255,40,80,25,"Fermer"));

	//Initialisation des valeurs des controles
	pSpinK->SetValue( 0 );
	pChoiceBoxTeta->SetValue( 2 );
	pChoiceBoxX->SetValue( 3 );
	ChangerFacteurRotation();
	ChangerFacteurHomothetie();
	ChangerFacteurTranslation();
}

void FenetreTransformation::OnChange(CONTROL_ID ID)
{
	if		( ID == BTN_HOMO_X )
	{
		pFenAff3D->Scene()->Designateur()->Homothetie(xhomo);
		pFenAff3D->Redraw();
	}
	else if	( ID == BTN_HOMO_1_X )
	{
		pFenAff3D->Scene()->Designateur()->Homothetie(1/xhomo);
		pFenAff3D->Redraw();
	}
	else if	( ID == BTN_TRANS_KV )
	{
		pFenAff3D->Scene()->Designateur()->Translation(ktrans);
		pFenAff3D->Redraw();
	}
	else if	( ID == BTN_TRANS_MOINS_KV )
	{
		pFenAff3D->Scene()->Designateur()->Translation(-ktrans);
		pFenAff3D->Redraw();
	}
	else if	( ID == BTN_ROT_TETA )
	{
		pFenAff3D->Scene()->Designateur()->Rotation(teta);
		pFenAff3D->Redraw();
	}
	else if	( ID == BTN_ROT_MOINS_TETA )
	{
		pFenAff3D->Scene()->Designateur()->Rotation(-teta);
		pFenAff3D->Redraw();
	}
	else if	( ID == BTN_APPLIQUER )
	{
		pFenAff3D->Scene()->Designateur()->OkTransformation();
		pFenAff3D->Redraw();
	}
	else if ( ID == CHOICEBOX_X )
		ChangerFacteurHomothetie();
	else if ( ID == SPIN_K )
		ChangerFacteurTranslation();
	else if ( ID == CHOICEBOX_TETA )
		ChangerFacteurRotation();
	else if	( ID == BTN_FERMER )
		HideWindow();
}

//Modifie le facteur utilisé pour la translation d'un objet
void FenetreTransformation::ChangerFacteurTranslation()
{
	ktrans = pow(2.0,pSpinK->GetValue());
}

//Modifie le facteur utilisé pour l'homothétie d'un objet
void FenetreTransformation::ChangerFacteurHomothetie()
{
	int v = pChoiceBoxX->GetValue();

	switch (v) 
	{
		case 0 : xhomo = -1; break;
		case 1 : xhomo = sqrt(2.0); break;
		case 2 : xhomo = sqrt(3.0); break;
		case 3 : xhomo = 2; break;
		case 4 : xhomo = 3; break;
	}
}

//Modifie le facteur utilisé pour la rotation d'un objet
void FenetreTransformation::ChangerFacteurRotation()
{
	int v = pChoiceBoxTeta->GetValue();

	switch (v) 
	{
		case 0 : teta = PI/180;	break;
		case 1 : teta = PI/36;	break;
		case 2 : teta = PI/12;	break;
		case 3 : teta = PI/4;	break;
		case 4 : teta = PI/3;	break;
		case 5 : teta = PI/2;	break;
		case 6 : teta = PI;		break;
	}
}
