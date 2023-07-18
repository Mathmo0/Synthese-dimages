//*******************************************************************

//*																	*

//* Programme: cgSpinner.h											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation de roulettes permettant d'incrémenter ou de	*

//*		décrémenter une valeur numérique.							*

//*																	*

//*******************************************************************



#ifndef _cgSPINNER

#define _cgSPINNER



#include "cgControl.h"



#define LAR_SPIN 16

#define HAUT_SPIN 21



#define SPINNER_NONE	0

#define SPINNER_UP		1

#define SPINNER_DOWN	2



class cgSpinner : public cgControl

{

protected:

	int m_nLen;

	char m_Valeur[10];

	int m_nStep;

	int m_nSelection;

	int m_nMin, m_nMax;		//Valeur min et max du spinner



	int x,y, w,h;



	int m_nPosCurseur;



public:

	cgSpinner(int left, int top, unsigned int len, int min, int max, int step = 1, int valeur = 0 );

	~cgSpinner();



	int GetValue();

	void SetValue(int value);





	//Messages qui peuvent être captés

	virtual void OnDraw();



	virtual booleen OnMouseDown(int button, int x, int y);

	virtual booleen OnMouseUp(int button, int x, int y);

	virtual booleen OnKeyPress(unsigned char key, int x, int y);

	virtual booleen OnSpecialKeyPress(int key, int x, int y);

};



#endif

