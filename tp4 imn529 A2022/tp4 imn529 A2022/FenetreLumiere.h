//*******************************************************************
//*																	*
//* Programme: FenetreLumiere.h										*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Fenêtre permettant d'allumer ou d'eteindre les lumieres		*
//*		de la scene.												*
//*																	*
//*******************************************************************


#ifndef _FENETRELUMIERE
#define _FENETRELUMIERE

#include "FenetrePrincipale.h"
#include "cgForm.h"
#include "cgButton.h"
#include "cgCheckBox.h"
#include "cgSliderWithDisplay.h"
#include "cgSpinner.h"


class FenetreLumiere : public cgForm
{
protected:
	cgCheckBox* pActiveAll;
	CONTROL_ID ACTIVEALL;

	cgSpinner* pChoixLumiere;
	CONTROL_ID SPIN_LUMIERE;

	cgSliderWithDisplay* pLumAmbR;
	CONTROL_ID LUM_AMB_R;
	cgSliderWithDisplay* pLumAmbG;
	CONTROL_ID LUM_AMB_G;
	cgSliderWithDisplay* pLumAmbB;
	CONTROL_ID LUM_AMB_B;


	cgSliderWithDisplay* pLumDifR;
	CONTROL_ID LUM_DIF_R;
	cgSliderWithDisplay* pLumDifG;
	CONTROL_ID LUM_DIF_G;
	cgSliderWithDisplay* pLumDifB;
	CONTROL_ID LUM_DIF_B;

	cgCheckBox* pActive;
	CONTROL_ID ACTIVE;

	cgSpinner* pPositionX;
	CONTROL_ID SPIN_POSX;
	cgSpinner* pPositionY;
	CONTROL_ID SPIN_POSY;
	cgSpinner* pPositionZ;
	CONTROL_ID SPIN_POSZ;


	CONTROL_ID BTN_FERMER;


protected:
	FenetrePrincipale* pFenAff3D;


	void SetAmbiante();
	void SetDiffuse();
	void SetPosition();


public:
	FenetreLumiere(FenetrePrincipale* pFen);


	void ChangeLumiere();

	virtual void OnChange(CONTROL_ID ID);
};



#endif
