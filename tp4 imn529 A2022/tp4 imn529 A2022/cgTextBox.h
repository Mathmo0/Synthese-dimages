//*******************************************************************
//*																	*
//* Programme: cgTextBox.h											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Implantation des régions d'éditions. Les régions d'éditions	*
//*		permettent d'entrer du texte via le clavier.				*
//*																	*
//*******************************************************************

#ifndef _cgTEXTBOX
#define _cgTEXTBOX

#include "cgControl.h"
#include "cgcString.h"

class cgTextBox : public cgControl
{
protected:
	cgcString m_texte;

	int m_nLenMax;		//Longueur maximale du texte
	int m_nPosCurseur;	//Position du curseur

public:
	cgTextBox(int left, int top, int len, cgcString texte, booleen transparent = FAUX);
	~cgTextBox();

	cgcString GetText();
	void SetText(cgcString texte);

	//Messages qui peuvent être captés
	virtual void OnDraw();
	virtual booleen OnMouseDown(int button, int x, int y);
	virtual booleen OnKeyPress(unsigned char key, int x, int y);
	virtual booleen OnSpecialKeyPress(int key, int x, int y);
};

#endif

