//*******************************************************************

//*																	*

//* Programme: cgWindow.cpp											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		cgWindow est une classe abstraite. Elle permet de gérer la 	*

//*		création, l'affichage et la destruction des fenêtres.		*

//*																	*

//*																	*

//*******************************************************************



#include "cgWindow.h"

#include "glut.h"



cgWindow::cgWindow()

{



}



cgWindow::cgWindow(unsigned int style,

				   int left, int top, 

				   int width, int height, 

				   char* titre)

{

	m_style = style;

	m_left = left;

	m_top = top;

	m_width = width;

	m_height = height;

	m_titre = titre;

}



cgWindow::~cgWindow()

{

	DestroyWindow();

}



void cgWindow::DestroyWindow()

{

	glutDestroyWindow(m_windowID);

}



void cgWindow::InitWindow()

{

	//fonction qui doit etre redéfini dans la classe enfant

}



void cgWindow::HideWindow()

{

	int w = glutGetWindow();

	

	glutSetWindow(WindowID());

	glutHideWindow();



	glutSetWindow(w);

}



void cgWindow::ShowWindow()

{

	int w = glutGetWindow();

	

	glutSetWindow(WindowID());

	glutShowWindow();

	

	glutSetWindow(w);

}



TOUCHE_CONTROLE cgWindow::GetControlKey()

{

	return glutGetModifiers();

}



void cgWindow::Redraw() 

{

	int w = glutGetWindow();

	if ( w != WindowID() )

	{

		glutSetWindow(WindowID());

		OnDraw() ; 

		glutSetWindow(w);

	}

	else

		OnDraw() ; 

}



void cgWindow::OnDraw()

{

	//fonction qui doit etre redéfini dans la classe enfant

}



void  cgWindow::OnChangeSize(int w, int h)

{

	//fonction qui doit etre redéfini dans la classe enfant

}



void cgWindow::CallBackVisibilityFunc(int visible)

{

	//fonction qui doit etre redéfini dans la classe enfant

}



void cgWindow::OnTimer()

{

	//fonction qui doit etre redéfini dans la classe enfant

}



void cgWindow::OnKeyPress(unsigned char key, int x, int y)

{

	//fonction qui doit etre redéfini dans la classe enfant

}



void cgWindow::OnSpecialKeyPress(int key, int x, int y)

{

	//fonction qui doit etre redéfini dans la classe enfant

}   



void cgWindow::OnMouseClick(int button, int state, int x, int y)

{

	//fonction qui doit etre redéfini dans la classe enfant

}



void cgWindow::OnMouseMove(int x, int y)

{

	//fonction qui doit etre redéfini dans la classe enfant

}



void cgWindow::OnMouseMoveWithButton(int x, int y)

{

	//fonction qui doit etre redéfini dans la classe enfant

}



void cgWindow::WindowID(int newWindowID) { if ( newWindowID >= 0 ) m_windowID = newWindowID; }

int cgWindow::WindowID(void) { return m_windowID; }



int cgWindow::Left() { return m_left; }

int cgWindow::Top() { return m_top; }

int cgWindow::Width() { return m_width; }

int cgWindow::Height() { return m_height; }

char* cgWindow::Title() { return m_titre; }

unsigned int cgWindow::Style() { return m_style; }



void cgWindow::ChangeSize(int w, int h)

{

	m_width = w;

	m_height = h;

}

