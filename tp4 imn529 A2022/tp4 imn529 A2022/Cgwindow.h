//*******************************************************************
//*																	*
//* Programme: cgWindow.h											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		cgWindow est une classe abstraite. Elle permet de gérer la 	*
//*		création, l'affichage et la destruction des fenêtres.		*
//*																	*
//*																	*
//*******************************************************************


#ifndef _cgWINDOW
#define _cgWINDOW


#include "definition.h"


typedef int TOUCHE_CONTROLE;
#define SHIFT	GLUT_ACTIVE_SHIFT
#define CTRL	GLUT_ACTIVE_CTRL
#define ALT		GLUT_ACTIVE_ALT


class cgWindow
{


private:
	int m_windowID;	//Contient le ID de la fenetre pour GLUT


	int m_left,m_top,m_width,m_height;
	char* m_titre;
	unsigned int m_style;


public:
	//Constructeurs
	cgWindow();
	cgWindow(	unsigned int style,
				int left, int top, 
				int width, int height, 
				char* titre);

	~cgWindow();


	//Change les parametres de la grandeur de la fenetre
	void ChangeSize(int w, int h);


	int Left();
	int Top();
	int Width();
	int Height(); 
	char* Title();
	unsigned int Style();


	void WindowID(int newWindowID);
	int WindowID();


	virtual void InitWindow();


	virtual void Redraw();


	void HideWindow();
	void ShowWindow();


	TOUCHE_CONTROLE GetControlKey();


	//--------------------

	//Gestion des messages

	//--------------------


	//Gestion de l'affichage
	virtual void OnDraw();
	virtual void OnChangeSize(int w, int h);   
	virtual void CallBackVisibilityFunc(int visible);


	//Gestion du timer
	virtual void OnTimer();


	//Gestion du clavier
	virtual void OnKeyPress(unsigned char key, int x, int y);
	virtual void OnSpecialKeyPress(int key, int x, int y);   


	//Gestion de la souris
	virtual void OnMouseClick(int button, int state, int x, int y);
	virtual void OnMouseMoveWithButton(int x, int y);
	virtual void OnMouseMove(int x, int y);


protected:
	void DestroyWindow();
};


#endif

