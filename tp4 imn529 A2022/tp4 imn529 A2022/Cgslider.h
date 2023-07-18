//*******************************************************************
//*																	*
//* Programme: cgSlider.h											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Implantation de slider permettant de choisir une valeur		*
//*		entière.													*
//*																	*
//*******************************************************************


#ifndef _cgSLIDER
#define _cgSLIDER

#include "cgControl.h"

class cgSlider : public cgControl
{
protected:
	int x,y,w,h;			//Position de l'affichage. On a de besoin de ces valeurs
							//car je veux pouvoir hériter cette classe pour pouvoir
							//afficher la valeur courante a droite


	int m_nInterEspacement;	//Espacement en pixel entre chaque ligne verticale noire


	double m_nValeur;
	double m_nMin, m_nMax;	//Valeur min et max du slider
	double m_nStep;			//Valeur de deplacement entre 2 marques
	double m_nRatio;


public:
	cgSlider(int left, int top, int width, double min, double max, int interespacement = 10, double step = 1.0, double value = 0.0);
	~cgSlider();


	double GetValue();
	void SetValue(double value);


	//Messages qui peuvent être captés
	virtual void OnDraw();

	virtual booleen OnMouseDown(int button, int x, int y);
	virtual booleen OnMouseMove(int x, int y);
	virtual booleen OnSpecialKeyPress(int key, int x, int y);
};



#endif

