//*******************************************************************

//*																	*

//* Programme: cgForm.h												*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		cgForm est dérivée de cgWindow. Elle permet de faire des	*

//*		feuilles où l'on place des contrôles graphiques(Boutton, 	*

//*		Case à cocher, ...) pour ainsi intéragir avec l'usager.		*

//*																	*

//*		L'affichage se fait en 2D.									*

//*																	*

//*******************************************************************



#ifndef _cgFORM

#define _cgFORM



#include "cgWindow.h"

#include "cgControl.h"



class cgForm : public cgWindow

{

protected:

	cgControl* m_pControle[50];

	int m_nNbControle;



	//Controle qui est selectionne

	booleen m_bControleSelectionne;

	CONTROL_ID m_nControleSelectionne;

	//Controle qui a le focus

	booleen m_bFocus;

	CONTROL_ID m_CtrlFocus;



public:

	cgForm(	unsigned int style,

			int setInitPositionX, int setInitPositionY,

			int setWidth, int setHeight,

			char * title);

	~cgForm();



	void InitWindow();



	//Gestion des controles

	CONTROL_ID AddControl(cgControl* c);



	//Gestion des messages

	virtual void OnDraw();

	virtual void OnChangeSize(int w, int h);   

	virtual void CallBackVisibilityFunc(int visible) {}

	virtual void OnTimer() {}

	virtual void OnKeyPress(unsigned char key, int x, int y);

	virtual void OnSpecialKeyPress(int key, int x, int y);   

	virtual void OnMouseClick(int button, int state, int x, int y);

	virtual void OnMouseMoveWithButton(int x, int y);

	virtual void OnMouseMove(int x, int y);



	//Fonction appeles lors de recpetion des messages

	virtual void OnChange(CONTROL_ID ID) {}

};



#endif

