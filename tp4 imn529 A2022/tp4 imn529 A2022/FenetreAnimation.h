//*******************************************************************
//*																	*
//* Programme: FenetreAnimation.h										*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Fenêtre s'occupant des animations du noyau graphique.		*
//*																	*
//*******************************************************************

#ifndef _FENETREANIMATION
#define _FENETREANIMATION

#include "FenetrePrincipale.h"
#include "cgForm.h"
#include "cgCheckBox.h"
#include "cgSpinner.h"

class FenetreAnimation : public cgForm
{
protected:
	CONTROL_ID CHKBOX_ANIMATE;
	CONTROL_ID SPIN_SLIDE;
	CONTROL_ID SPIN_DELAI;

	cgCheckBox* pAnimate;
	cgSpinner* pSlide;
	cgSpinner* pDelai;

	CONTROL_ID BTN_FERMER;

protected:
	FenetrePrincipale* pFenAff3D;

public:
	FenetreAnimation(FenetrePrincipale* pFen);
	~FenetreAnimation();

	void ChangeSlide(entier no);
	void ChangeAnimate();

	virtual void OnChange(CONTROL_ID ID);

};



#endif

