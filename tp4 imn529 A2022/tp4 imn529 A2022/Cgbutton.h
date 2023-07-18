//*******************************************************************
//*																	*
//* Programme: cgButton.h											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Implantation des bouttons graphiques.					 	*
//*																	*
//*******************************************************************


#ifndef _cgBUTTON
#define _cgBUTTON


#include "cgControl.h"
#include "cgcString.h"


class cgButton : public cgControl
{
protected:
	cgcString m_titre;


	int x,y,w,h;


public:
	cgButton(int left, int top, int width, int height, cgcString title);
	~cgButton();


	cgcString GetCaption();
	void SetCaption(cgcString titre);


	//Messages qui peuvent être captés
	virtual void OnDraw();
	virtual booleen OnMouseMove(int x, int y);
};



#endif

