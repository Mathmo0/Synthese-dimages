//*******************************************************************

//*																	*

//* Programme: cgLabel.h											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation d'étiquettes. Les étiquettes sont simplement	*

//*		la représentation graphique de textes.						*

//*																	*

//*******************************************************************



#ifndef _cgLABEL

#define _cgLABEL



#include "cgControl.h"

#include "cgcString.h"



class cgLabel : public cgControl

{

protected:

	cgcString m_texte;



	int x,y, w,h;



public:

	cgLabel(int left, int top, cgcString texte, booleen transparent = FAUX);

	~cgLabel();



	cgcString GetCaption();

	void SetCaption(cgcString texte);



	//Messages qui peuvent être captés

	virtual void OnDraw();

};



#endif

