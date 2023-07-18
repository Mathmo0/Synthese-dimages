//*******************************************************************
//*																	*
//* Programme: cgView.cpp											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		cgView est une fenêtre qui affiche du 3D.					*
//*																	*
//*******************************************************************


#ifndef _cgVIEW
#define _cgVIEW


#include "cgWindow.h"


class cgView : public cgWindow
{
public:
	cgView(	unsigned int style, int x, int y, int w, int h, char * title);
	~cgView();


	virtual void InitWindow() {}


	//Gestion des messages
	virtual void OnDraw() {}
	virtual void OnChangeSize(int w, int h) {}
	virtual void CallBackVisibilityFunc(int visible) {}
	virtual void OnTimer() {}
	virtual void OnKeyPress(unsigned char key, int x, int y) {}
	virtual void OnSpecialKeyPress(int key, int x, int y) {}
	virtual void OnMouseClick(int button, int state, int x, int y) {}
	virtual void OnMouseMoveWithButton(int x, int y) {}
	virtual void OnMouseMove(int x, int y) {}

};



#endif

