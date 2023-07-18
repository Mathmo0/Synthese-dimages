//*******************************************************************

//*																	*

//* Programme: cgFrame.h											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation de frames(lignes contour) permettant  de		*

//*		regrouper certains contrôles ensembles.					 	*

//*																	*

//*******************************************************************



#ifndef _cgFRAME

#define _cgFRAME



#include "cgControl.h"

#include "cgcString.h"



class cgFrame : public cgControl

{

protected:

	cgcString m_titre;



	int x,y, w,h;



public:

	cgFrame(int left, int top, int width, int height, cgcString titre, booleen transparent = FAUX);

	~cgFrame();



	cgcString GetCaption();

	void SetCaption(cgcString titre);



	//Messages qui peuvent être captés

	virtual void OnDraw();

};



#endif

