//*******************************************************************

//*																	*

//* Programme: cgApplication.h										*

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



#ifndef _cgAPPLICATION

#define _cgAPPLICATION



#include "cgWindow.h"

#include "definition.h"



//Nombre maximum de fenêtre pouvant être ouverte dans une application

#define NB_MAX_FENETRE 256 



class cgApplication

{

private:

	static void CallBackDisplayFunc(void);

	static void CallBackIdleFunc(void); 

	static void CallBackKeyboardFunc(unsigned char key, int x, int y);

	static void CallBackMotionFunc(int x, int y);

	static void CallBackMouseFunc(int button, int state, int x, int y);

	static void CallBackPassiveMotionFunc(int x, int y);

	static void CallBackReshapeFunc(int w, int h); 

	static void CallBackSpecialFunc(int key, int x, int y);   

	static void CallBackVisibilityFunc(int visible);



	//Gestion des timers

	static booleen TimerEnable;

	static int TimerCall;

	static unsigned long TimerRendu;	

	static unsigned long TimerWait;	



public:

 	cgApplication();

	~cgApplication();



	//Gestion des fenêtres de l'application

	void AddWindow(cgWindow* pWindow);



	//Gestion des timer

	void CreateTimer(int IDWindow, unsigned long wait);

	void DeleteTimer();



	void ChangeWaitTimer(entier delai);

	entier GetWaitTimer();

	void DisableTimer();

	void EnableTimer();



	//Gestion de l'exécution de l'application

	void StartApplication();

	void StopApplication();

};



#endif

