//*******************************************************************

//*																	*

//* Programme: FenetreSetting.h										*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Fenêtre s'occupant des configurations du noyau graphique.	*

//*																	*

//*******************************************************************



#ifndef _FENETRESETTING

#define _FENETRESETTING



#include "FenetrePrincipale.h"

#include "cgForm.h"

#include "cgCheckBox.h"

#include "cgSpinner.h"



class FenetreSetting : public cgForm

{

protected:

	CONTROL_ID CHKBOX_OPENGL;

	cgCheckBox* pOpenGL;

	CONTROL_ID CHKBOX_GOURAUD;

	cgCheckBox* pGouraud;

	CONTROL_ID CHKBOX_POLYGONE_REMPLIT;

	cgCheckBox* pPolygoneRemplit;

	CONTROL_ID CHKBOX_CONTOURS_POLYGONE;

	cgCheckBox* pContoursPolygone;

	CONTROL_ID CHKBOX_CONTOUR_NOIRS;

	cgCheckBox* pContourNoirs;

	CONTROL_ID CHKBOX_CULL_FACE;

	cgCheckBox* pCullFace;



	cgSpinner* pMeridiens;

	CONTROL_ID SPIN_MERIDIENS;

	cgSpinner* pParalleles;

	CONTROL_ID SPIN_PARALLELES;



	cgSpinner* pNbiter;

	CONTROL_ID SPIN_NBITER;

	

	CONTROL_ID BTN_FERMER;



protected:

	FenetrePrincipale* pFenAff3D;



public:

	FenetreSetting(FenetrePrincipale* pFen);

	~FenetreSetting();



	void SetParalleles();

	void SetMeridiens();

	void SetNbiter();



	void ChangeGouraud();

	void ChangePolygoneRemplit();

	void ChangeContourPolygone();

	void ChangeCullFace();



	virtual void OnChange(CONTROL_ID ID);

};



#endif

