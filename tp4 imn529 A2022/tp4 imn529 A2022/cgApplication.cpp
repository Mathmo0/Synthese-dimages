//*******************************************************************
//*																	*
//* Programme: cgApplication.cpp									*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		cgApplication gère l'affichage des fenêtres ainsi que les	*
//*		messages(souris, clavier,...).								*
//*																	*
//*		Nous ajoutons des cgWindow(ou ses fils) dans cgApplication	*
//*		pour avoir plusieurs fenêtres.								*
//*																	*
//*******************************************************************

#include "cgApplication.h"
#include "glut.h"
                                                    
cgWindow * viewPorts[NB_MAX_FENETRE]; 

			int  cgApplication::TimerCall;	
unsigned	long cgApplication::TimerRendu;	
unsigned	long cgApplication::TimerWait;	

cgApplication::cgApplication()
{
	//Creation des paramètres de la ligne de commande bidon
	char * argv[1]; 
	argv[0] = "run";
	int argc = 1;

	// Initialisation de GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(300, 300);
}


cgApplication::~cgApplication()
{
}


void cgApplication::AddWindow(cgWindow* pWindow)
{
	//Cree une nouvelle fenetre et sauvegarde son numero d'identification
	glutInitDisplayMode(pWindow->Style());
	glutInitWindowSize(pWindow->Width(), pWindow->Height());
	glutInitWindowPosition(pWindow->Left(), pWindow->Top());

	int windowID = glutCreateWindow(pWindow->Title());
	pWindow->WindowID(windowID);
	viewPorts[windowID] = pWindow;


	//Attache les fonctions de gestion des messages a la nouvelle fenetre

	glutDisplayFunc(CallBackDisplayFunc);
	glutKeyboardFunc(CallBackKeyboardFunc);
	glutSpecialFunc(CallBackSpecialFunc);
	glutMouseFunc(CallBackMouseFunc);
	glutMotionFunc(CallBackMotionFunc);
	glutPassiveMotionFunc(CallBackPassiveMotionFunc);
	glutReshapeFunc(CallBackReshapeFunc); 
	glutVisibilityFunc(CallBackVisibilityFunc);

	glViewport(0, 0, pWindow->Width(), pWindow->Height()); 
	pWindow->InitWindow();
}


void cgApplication::StartApplication()
{
	glutMainLoop();
}


void cgApplication::StopApplication()
{
	exit(0);
}
 

//---------------------- 
//Gestion de l'affichage
//---------------------- 

void cgApplication::CallBackDisplayFunc()
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->OnDraw();
}

void cgApplication::CallBackReshapeFunc(int w, int h)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->OnChangeSize(w, h);
}

void cgApplication::CallBackVisibilityFunc(int visible)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackVisibilityFunc(visible);
}

//----------------
//Gestion du timer
//----------------
void cgApplication::CallBackIdleFunc()
{
	if ( TimerRendu++ >= TimerWait )
	{
		glutSetWindow(TimerCall);
		viewPorts[TimerCall]->OnTimer();
		TimerRendu = 0;
	}
}

void cgApplication::CreateTimer(int IDWindow, unsigned long wait)
{
	TimerCall = IDWindow;
	TimerRendu = 0;
	TimerWait = wait*100;
}

void cgApplication::ChangeWaitTimer(entier delai)
{
	cgApplication::TimerWait = delai*100;
}

entier cgApplication::GetWaitTimer()
{
	return cgApplication::TimerWait/100;
}

void cgApplication::DisableTimer()
{
	glutSetWindow(TimerCall);
	glutIdleFunc(0); 
}

void cgApplication::EnableTimer()
{
	glutSetWindow(TimerCall);
	glutIdleFunc(CallBackIdleFunc); 
}

//------------------ 
//Gestion du clavier
//------------------ 
void cgApplication::CallBackKeyboardFunc(unsigned char key, int x, int y)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->OnKeyPress(key, x, y);
}

void cgApplication::CallBackSpecialFunc(int key, int x, int y)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->OnSpecialKeyPress(key, x, y);
}   

//-------------------- 
//Gestion de la souris
//--------------------
void cgApplication::CallBackMouseFunc(int button, int state, int x, int y)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->OnMouseClick(button, state, x, y);
}

void cgApplication::CallBackMotionFunc(int x, int y)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->OnMouseMoveWithButton(x, y);
}

void cgApplication::CallBackPassiveMotionFunc(int x, int y)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->OnMouseMove(x, y);
}
