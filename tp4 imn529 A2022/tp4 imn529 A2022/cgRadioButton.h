//*******************************************************************

//*																	*

//* Programme: cgRadioButton.h										*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation des radios boutons.						 	*

//*																	*

//*******************************************************************



#ifndef _cgRADIOBUTTON

#define _cgRADIOBUTTON



#include "cgControl.h"

#include "cgcString.h"

#include "cgcTableau.h"

#include "definition.h"



#define RADIO_HORIZONTAL	VRAI

#define RADIO_VERTICAL		FAUX



class cgRadioButton : public cgControl

{

protected:

	cgcTableau<cgcString> m_Tableau;

	entier m_nSelection;

	

	booleen m_bHorizontal;



public:

	cgRadioButton(int left, int top, entier n, cgcString Tableau[], booleen horizontal = FAUX, entier valeur = 0, booleen transparent = FAUX);

	~cgRadioButton();

	

	booleen GetSelection();

	void SetSelection(int value);



	//Messages qui peuvent être captés

	virtual void OnDraw();

	virtual booleen OnMouseUp(int button, int posX, int posY);

	virtual booleen OnSpecialKeyPress(int key, int x, int y);

};



#endif

