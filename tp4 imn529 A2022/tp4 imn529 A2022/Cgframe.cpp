//*******************************************************************

//*																	*

//* Programme: cgFrame.cpp											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation de frames(lignes contour) permettant  de		*

//*		regrouper certains contrôles ensembles.					 	*

//*																	*

//*******************************************************************



#include "cgFrame.h"



cgFrame::cgFrame(int left, int top, int width, int height, cgcString titre, booleen transparent)

	: cgControl(left,top,width,height)

{

	x = left;

	y = top;

	h = height;

	w = width;

	

	m_titre = titre;



	Transparent(transparent);

}



cgFrame::~cgFrame()

{

}



cgcString cgFrame::GetCaption()

{

	return m_titre;

}



void cgFrame::SetCaption(cgcString texte)

{

	m_titre = texte;

}



void cgFrame::OnDraw()

{

	//Rempli le fond si le fond n'est pas transparent

	if ( !Transparent() )

	{

		glColor3f(0.75,0.75,0.75);

		glRecti(x,y,x+w,y+h);

	}



	glColor3f(0.5,0.5,0.5);

	glBegin(GL_LINES);

		glVertex2f(x,y);

		glVertex2f(x,y+h);



		glVertex2f(x,y);

		glVertex2f(x+w,y);



		glVertex2f(x+w,y);

		glVertex2f(x+w,y+h);



		glVertex2f(x,y+h);

		glVertex2f(x+w,y+h);

	glEnd();



	glColor3f(1,1,1);

	glBegin(GL_LINES);

		glVertex2f(x+1,y+1);

		glVertex2f(x+1,y+h+1);



		glVertex2f(x+1,y+1);

		glVertex2f(x+w-1,y+1);



		glVertex2f(x+w+1,y+1);

		glVertex2f(x+w+1,y+h+1);



		glVertex2f(x+1,y+h+1);

		glVertex2f(x+w+1,y+h+1);

	glEnd();



	//Affichage du titre du frame

	int len = m_titre.Len();

	glColor3f(0.75,0.75,0.75);

	glRectf(x+5,y-6,x+5+(len*8),y+6);

	glColor3f(0,0,0);

	cgTexte(x+9,y+3,m_titre);

}

