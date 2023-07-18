//*******************************************************************
//*																	*
//* Programme: cgControl.h											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		cgControl est une classe abstraite qui sert pour la			*
//*		définition de contrôles graphiques de haut niveau.		 	*
//*																	*
//*******************************************************************


#ifndef _cgCONTROL
#define _cgCONTROL


#include "definition.h"
#include "glut.h"
#include "cgcString.h"


typedef unsigned int CONTROL_ID;


class cgControl
{
protected:
	//Contour du controle(aire englobante). Facilite l'intersection
	//avec les controles lors d'une selection
	int m_nLeft, m_nTop, m_nWidth, m_nHeight;


private:
	//Indique si le controle est visible
	booleen m_bVisible;	
	//Indique si le controle est selectionne ou non
	booleen m_bSelectionne;
	//Indique si le controle a le focus
	booleen m_bFocus;
	//Indique si on efface le fond avant de dessiner le controle
	booleen m_bTransparent;


public:
	cgControl(int left, int top, int width, int height);
	~cgControl();


	//Gestion de la visibilité du controle
	booleen Visible() { return m_bVisible; }
	void Visible(booleen v) { m_bVisible = v; }


	booleen Select() { return m_bSelectionne; }
	void Select(booleen v) { m_bSelectionne = v; }


	void Focus(booleen v) { m_bFocus = v; }
	booleen Focus() { return m_bFocus; }


	booleen Transparent() { return m_bTransparent; }
	void Transparent(booleen v) { m_bTransparent = v; }


	//Gestion de l'intersection du controle
	booleen Intersecte(int x, int y);


	//Messages qui peuvent être captés
	virtual void OnDraw() {}


	virtual booleen OnKeyPress(unsigned char key, int x, int y) { return FAUX; }
	virtual booleen OnSpecialKeyPress(int key, int x, int y) { return FAUX; }
	virtual booleen OnMouseDown(int button, int x, int y);
	virtual booleen OnMouseUp(int button, int x, int y);
	virtual booleen OnMouseMove(int x, int y);


protected:
	//Fonctions generales pour aider dans le dessin des controles
	void cgRectangle(int x1, int y1, int x2, int y2);
	void cgRectangleFill(int x1, int y1, int x2, int y2);
	void cgCircle(int x, int y, int r, int nb_division = 12);
	void cgCircleFilled(int x, int y, int r, int nb_division = 12);
	void cgTexte(int x, int y, cgcString texte, int longueur = -1);
};



#endif

