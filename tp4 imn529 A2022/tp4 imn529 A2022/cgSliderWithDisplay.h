//*******************************************************************
//*																	*
//* Programme: cgSliderWithDisplay.h								*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Implantation de slider avec l'affichage de la valeur		*
//*		permettant de choisir une valeur							*
//*		entière.													*
//*																	*
//*******************************************************************

#ifndef _cgSLIDERWITHDISPLAY
#define _cgSLIDERWITHDISPLAY

#include "cgSlider.h"

class cgSliderWithDisplay : public cgSlider
{
protected:
	unsigned int m_nLen;	//Longueur maximale pour l'affichage
	unsigned int m_nDigit;	//Nombre de decimales lors de l'affichage

public:
	cgSliderWithDisplay(int left, int top, int width, double min, double max, int len, int nbdigit = 0, int interespacement = 10, double step = 1.0, double value = 0.0);
	~cgSliderWithDisplay();

	//Messages qui peuvent être captés
	virtual void OnDraw();
};


#endif

