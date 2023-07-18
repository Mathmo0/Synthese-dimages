//*******************************************************************
//*																	*
//* Programme: cgCheckBox.h											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Implantation des checks box.							 	*
//*																	*
//*******************************************************************



#ifndef _cgCHECKBOX
#define _cgCHECKBOX


#include "cgControl.h"
#include "cgcString.h"
#include "definition.h"


#define LAR_CHECK 13


class cgCheckBox : public cgControl
{
protected:
	cgcString m_texte;
	booleen m_bValeur;


	int x,y, w,h;


public:
	cgCheckBox(int left, int top, unsigned int len, cgcString texte, booleen valeur = FAUX, booleen transparent = FAUX);
	~cgCheckBox();


	cgcString GetCaption();
	void SetCaption(cgcString texte);
	

	booleen GetValue();
	void SetValue(booleen value);


	//Messages qui peuvent être captés
	virtual void OnDraw();
	virtual booleen OnMouseUp(int button, int x, int y);
};


#endif

