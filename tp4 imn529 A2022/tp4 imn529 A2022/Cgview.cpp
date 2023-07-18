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



#include "cgView.h"



cgView::cgView(	unsigned int style,

				int left, int top,

				int width, int height,

				char * title) 

	: cgWindow(style,left,top,width,height, title)

{

}



cgView::~cgView()

{

	DestroyWindow();

}

