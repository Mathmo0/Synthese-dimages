//*******************************************************************
//*																	*
//* Programme: cgButton.cpp											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Implantation des bouttons graphiques.					 	*
//*																	*
//*******************************************************************


#include "cgButton.h"


cgButton::cgButton(int left, int top, int width, int height, cgcString title)
	: cgControl(left,top,width,height)
{
	x = left;
	y = top;
	w = width;
	h = height;

	m_titre = title;
}

cgButton::~cgButton()
{
}

cgcString cgButton::GetCaption()
{
	return m_titre;
}

void cgButton::SetCaption(cgcString titre)
{
	m_titre = titre;
}

void cgButton::OnDraw()
{
	//Rempli le fond
	glColor3f(0.75,0.75,0.75);
	glRecti(x,y,x+w,y+h);

	//Dessin du contour du bouton
	if ( Select() )
		glColor3f(0,0,0);
	else
		glColor3f(1,1,1);

	glBegin(GL_LINES);
		glVertex2f(x,y);
		glVertex2f(x,y+h);

		glVertex2f(x,y);
		glVertex2f(x+w,y);
	glEnd();
  
	if ( Select() )
		glColor3f(1,1,1);
	else
		glColor3f(0,0,0);
	glBegin(GL_LINES);
		glVertex2f(x,y+h);
		glVertex2f(x+w,y+h);

		glVertex2f(x+w,y+h);
		glVertex2f(x+w,y);
	glEnd();

	//Affichage du titre du bouton
	glColor3f(0,0,0);
	int len = m_titre.Len();
	float posX = ((w - (len*8))/2) + x;
	float posY = ((h - 13)/2) + y + 10;
	if ( posX <= x || posY <= y ) 
		return;
	cgTexte(posX,posY,m_titre);
}

booleen cgButton::OnMouseMove(int x, int y) 
{
	if ( Select() )
	{
		if ( !Intersecte(x,y) )
			Select(FAUX);
	}
	else
	{
		if ( Intersecte(x,y) )
			Select(VRAI);
	}

	return FAUX;
}
