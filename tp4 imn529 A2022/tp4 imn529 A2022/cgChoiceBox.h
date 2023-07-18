//*******************************************************************
//*																	*
//* Programme: cgChoiceBox.h										*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Implantation de choice box. Les choices bos permettent	 	*
//*		d'afficher plusieurs sélections qui sont des chaines de 	*
//*		caractères. On peut changer la sélection courante en		*
//*		pressant sur la flèche haut ou la flèche bas.				*
//*																	*
//*******************************************************************


#ifndef _cgCHOICEBOX
#define _cgCHOICEBOX


#include "cgControl.h"
#include "cgcTableau.h"
#include "cgcString.h"


#define LAR_SPIN 16
#define HAUT_SPIN 21


#define SPINNER_NONE	0
#define SPINNER_UP		1
#define SPINNER_DOWN	2


class cgChoiceBox : public cgControl
{
protected:
	int m_nLen;
	int m_nValeur;
	cgcTableau<cgcString> m_element;
	int m_nStep;
	int m_nSelection;


	int x,y, w,h;


public:
	cgChoiceBox(int left, int top, unsigned int len, cgcTableau<cgcString> t, int value);
	~cgChoiceBox();


	int GetValue();
	void SetValue(int value);


	//Messages qui peuvent être captés
	virtual void OnDraw();
	virtual booleen OnMouseDown(int button, int x, int y);
	virtual booleen OnMouseUp(int button, int x, int y);
};


#endif

