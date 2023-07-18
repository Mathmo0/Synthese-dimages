//*******************************************************************
//*																	*
//* Programme: FenetreDesignateur.h									*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Fenêtre s'occupant du désignateur.							*
//*																	*
//*******************************************************************


#ifndef _FENETREDESIGNATEUR
#define _FENETREDESIGNATEUR


#include "FenetrePrincipale.h"
#include "cgForm.h"
#include "cgButton.h"


class FenetreDesignateur : public cgForm
{
protected:
	CONTROL_ID BTN_UP;
	CONTROL_ID BTN_DOWN;
	CONTROL_ID BTN_PLUS_Z;
	CONTROL_ID BTN_MOINS_Z;


	CONTROL_ID BTN_UP_COMPO;
	CONTROL_ID BTN_DOWN_COMPO;


	CONTROL_ID BTN_PRINT_SELECT;
	CONTROL_ID BTN_PRINT_SCENE;
	CONTROL_ID BTN_PRINT_PATH;
	CONTROL_ID BTN_PRINT_COMPOSANTE;


	CONTROL_ID BTN_EPSMUL;
	CONTROL_ID BTN_EPSDIV;


	CONTROL_ID BTN_FERMER;


protected:
	FenetrePrincipale* pFenAff3D;


public:
	FenetreDesignateur(FenetrePrincipale* pFen);


	virtual void OnChange(CONTROL_ID ID);
};



#endif

