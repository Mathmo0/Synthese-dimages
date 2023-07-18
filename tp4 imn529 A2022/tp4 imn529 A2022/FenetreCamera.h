//*******************************************************************
//*																	*
//* Programme: FenetreCamera.h										*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Fenêtre permettant de modifier la position de la caméra		*
//*		dans la scène.												*
//*																	*
//*******************************************************************



#ifndef _FENETRECAMERA

#define _FENETRECAMERA



#include "FenetrePrincipale.h"

#include "cgCheckBox.h"

#include "cgSpinner.h"

#include "cgForm.h"

#include "cgRadioButton.h"



class FenetreCamera : public cgForm

{

protected:

	CONTROL_ID BTN_GAUCHE;

	CONTROL_ID BTN_DROITE;

	CONTROL_ID BTN_HAUT;

	CONTROL_ID BTN_BAS;

	CONTROL_ID BTN_AVANCE;

	CONTROL_ID BTN_RECULE;



	CONTROL_ID CHKBOX_VH_FIXE;

	cgCheckBox* pVHFixe;

	cgCheckBox* pPRFixe;

	CONTROL_ID CHKBOX_PR_FIXE;

	CONTROL_ID BTN_HORAIRE;

	CONTROL_ID BTN_ANTIHORAIRE;



	cgSpinner* pSpinPas;

	CONTROL_ID SPIN_PAS;



	CONTROL_ID BTN_DOPLUS;

	CONTROL_ID BTN_DOMOINS;

	CONTROL_ID BTN_DVPLUS;

	CONTROL_ID BTN_DVMOINS;



	cgRadioButton* pParallele;

	CONTROL_ID RADIO_PARALLELE;



	CONTROL_ID BTN_FEN_F2;

	CONTROL_ID BTN_FEN_D2;



	CONTROL_ID BTN_FERMER;



protected:

	FenetrePrincipale* pFenAff3D;



public:

	FenetreCamera(FenetrePrincipale* pFen);



	virtual void OnChange(CONTROL_ID ID);

};



#endif

