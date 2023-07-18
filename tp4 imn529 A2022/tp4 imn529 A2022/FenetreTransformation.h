//*******************************************************************
//*																	*
//* Programme: FenetreTransformation.h								*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Fenêtre s'occupant d'appliquer des tranformations(rotation,	*
//*		translations, homothétie) sur les objets de la scène.		*
//*																	*
//*******************************************************************


#ifndef _FENETRETRANSFORMATION
#define _FENETRETRANSFORMATION


#include "FenetrePrincipale.h"
#include "cgForm.h"
#include "cgCheckBox.h"
#include "cgSpinner.h"
#include "cgChoiceBox.h"


class FenetreTransformation : public cgForm
{
protected:
	CONTROL_ID BTN_HOMO_X;
	CONTROL_ID BTN_HOMO_1_X;
	cgChoiceBox* pChoiceBoxX;
	CONTROL_ID CHOICEBOX_X;


	CONTROL_ID BTN_TRANS_KV;
	CONTROL_ID BTN_TRANS_MOINS_KV;
	cgSpinner* pSpinK;
	CONTROL_ID SPIN_K;


	CONTROL_ID BTN_ROT_TETA;
	CONTROL_ID BTN_ROT_MOINS_TETA;
	cgChoiceBox* pChoiceBoxTeta;
	CONTROL_ID CHOICEBOX_TETA;


	CONTROL_ID BTN_FERMER;
	CONTROL_ID BTN_APPLIQUER;


protected:
	//Pointeur sur la fenetre principale pour faire le redessinage
	FenetrePrincipale* pFenAff3D;


	//Facteur pour les transformations sur la selection
	reel xhomo;
	reel teta;
	reel ktrans;


public:
	FenetreTransformation(FenetrePrincipale* pFen);


	virtual void OnChange(CONTROL_ID ID);


protected:
	void ChangerFacteurTranslation();
	void ChangerFacteurHomothetie();
	void ChangerFacteurRotation();
};



#endif

