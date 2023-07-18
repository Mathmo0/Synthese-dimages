//*******************************************************************
//*																	*
//* Programme: cgCheckBox.cpp										*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Implantation des checks box.							 	*
//*																	*
//*******************************************************************



#include "cgCheckBox.h"



cgCheckBox::cgCheckBox(int left, int top, unsigned int len, cgcString texte, booleen value, booleen transparent)

	: cgControl(left,top,((len+2)*8)+LAR_CHECK+3,13)

{

	x = left;

	y = top;

	h = 13;					

	w = (len+2)*8;

	

	m_texte = texte;

	m_bValeur = value;

	Transparent(transparent);

}



cgCheckBox::~cgCheckBox()

{

}



cgcString cgCheckBox::GetCaption()

{

	return m_texte;

}



void cgCheckBox::SetCaption(cgcString texte)

{

	m_texte = texte;

}



booleen cgCheckBox::GetValue()

{

	return m_bValeur;

}



void cgCheckBox::SetValue(booleen value)

{

	m_bValeur = value;

}



void cgCheckBox::OnDraw()

{

	//Rempli le fond si le fond n'est pas transparent

	if ( !Transparent() )

	{

		glColor3f(0.75,0.75,0.75);

		glRecti(x,y,x+w,y+h);

	}



	//Dessin de la marque

	if ( Select() )

		glColor3f(0.5,0.5,0.5);

	else

		glColor3f(1,1,1);

	glRectf(x,y,x+LAR_CHECK,y+LAR_CHECK);



	//Gris fonce

	glColor3f(0.5,0.5,0.5);

	glBegin(GL_LINES);

		glVertex2f(x,y);

		glVertex2f(x+LAR_CHECK-1,y);



		glVertex2f(x,y);

		glVertex2f(x,y+LAR_CHECK-1);

	glEnd();

	

	//Blanc

	glColor3f(1,1,1);

	glBegin(GL_LINES);

		glVertex2f(x,y+LAR_CHECK);

		glVertex2f(x+LAR_CHECK,y+LAR_CHECK);



		glVertex2f(x+LAR_CHECK,y);

		glVertex2f(x+LAR_CHECK,y+LAR_CHECK);

	glEnd();



	//Noir

	glColor3f(0,0,0);

	glBegin(GL_LINES);

		glVertex2f(x+1,y+1);

		glVertex2f(x+1,y+LAR_CHECK-2);



		glVertex2f(x+1,y+1);

		glVertex2f(x+LAR_CHECK-2,y+1);

	glEnd();



	//Gris

	glColor3f(0.75,0.75,0.75);

	glBegin(GL_LINES);

		glVertex2f(x+LAR_CHECK-1,y+1);

		glVertex2f(x+LAR_CHECK-1,y+LAR_CHECK-1);



		glVertex2f(x+1,y+LAR_CHECK-1);

		glVertex2f(x+LAR_CHECK-1,y+LAR_CHECK-1);

	glEnd();



	//Affiche le check mark si valeur = VRAI

	if ( m_bValeur )

	{

		glColor3f(0,0,0);

		glBegin(GL_LINES);

			glVertex2f(x+4,y+6);

			glVertex2f(x+4,y+8);



			glVertex2f(x+5,y+7);

			glVertex2f(x+5,y+9);



			glVertex2f(x+5,y+9);

			glVertex2f(x+10,y+4);



			glVertex2f(x+6,y+9);

			glVertex2f(x+10,y+5);



			glVertex2f(x+6,y+10);

			glVertex2f(x+10,y+6);

		glEnd();

	}



	//Affichage du titre du bouton

	glColor3f(0,0,0);

	cgTexte(x+20,y+10,m_texte);

}



booleen cgCheckBox::OnMouseUp(int button, int posX, int posY)

{

	if ( cgControl::OnMouseUp(button,posX,posY) )

	{

		SetValue(!GetValue() );

		return VRAI;

	}



	return FAUX;

}

