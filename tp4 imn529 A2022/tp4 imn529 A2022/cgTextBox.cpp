//*******************************************************************

//*																	*

//* Programme: cgTextBox.cpp										*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation des régions d'éditions. Les régions d'éditions	*

//*		permettent d'entrer du texte via le clavier.				*

//*																	*

//*******************************************************************



#include "cgTextBox.h"



cgTextBox::cgTextBox(int left, int top, int len, cgcString texte, booleen transparent)

	: cgControl(left,top,len*8+10,20)

{

	m_nPosCurseur = 0;

	m_nLenMax = len;

	m_texte = texte;

	

	Transparent(transparent);

}



cgTextBox::~cgTextBox()

{

}



cgcString cgTextBox::GetText()

{

	return m_texte;

}



void cgTextBox::SetText(cgcString texte)

{

	m_texte = texte;

}



void cgTextBox::OnDraw()

{

	int x = m_nLeft;

	int y = m_nTop;

	int w = m_nWidth;

	int h = m_nHeight;



	//Remplit le fond

	glColor3f(1.0,1.0,1.0);

	glRecti(x,y,x+w,y+h);



	//Cadre autour du texte

	glColor3f((float)0.35,(float)0.35,(float)0.35);

	glBegin(GL_LINE_LOOP);

		glVertex2f(x,y);

		glVertex2f(x,y+h);



		glVertex2f(x  ,y);

		glVertex2f(x+w,y);

	glEnd();	



	glColor3f(0,0,0);

	glBegin(GL_LINE_LOOP);

		glVertex2f(x+1,y+1);

		glVertex2f(x+1,y+h);



		glVertex2f(x+1,y+1);

		glVertex2f(x+w,y+1);

	glEnd();	



	glColor3f((float)0.8,(float)0.8,(float)0.8);

	glBegin(GL_LINE_LOOP);

		glVertex2f(x+1,y+h-1);

		glVertex2f(x+w,y+h-1);



		glVertex2f(x+w-1,y+1);

		glVertex2f(x+w-1,y+h);

	glEnd();	



	glColor3f(1.0,1.0,1.0);

	glBegin(GL_LINE_LOOP);

		glVertex2f(x  ,y+h);

		glVertex2f(x+w,y+h);



		glVertex2f(x+w,y);

		glVertex2f(x+w,y+h);

	glEnd();	



	//Affichage du texte

	glColor3f(0,0,0);

	cgTexte(x+5,y+15,m_texte);



	//Affichage du curseur

	if ( Focus() )

	{

		int posx = x + (m_nPosCurseur*8) + 3;

		glColor3f(0,0,0);

		glBegin(GL_LINE_LOOP);

			glVertex2f(posx,y+2);

			glVertex2f(posx,y+h-2);

			glVertex2f(posx+1,y+2);

			glVertex2f(posx+1,y+h-2);

		glEnd();	

	}

}



booleen cgTextBox::OnMouseDown(int button, int x, int y)

{

	cgControl::OnMouseDown(button,x,y);



	if ( button == GLUT_LEFT_BUTTON )

	{

		if ( x > m_nLeft && x < m_nLeft+m_nWidth )

		{

			int posx = x - m_nLeft / 8;

			m_nPosCurseur = posx;

			return VRAI;

		}

	}



	return FAUX;

}



booleen cgTextBox::OnSpecialKeyPress(int key, int x, int y)

{

	switch (key)

	{

	case GLUT_KEY_LEFT:

		if ( m_nPosCurseur > 0 )

		{

			m_nPosCurseur--;

			return VRAI;

		}

		break;

	case GLUT_KEY_RIGHT:

		if ( m_nPosCurseur < m_nLenMax && m_nPosCurseur < m_texte.Len() )

		{

			m_nPosCurseur++;

			return VRAI;

		}

		break;

	case GLUT_KEY_HOME:

		m_nPosCurseur = 0;

		return VRAI;

		break;

	case GLUT_KEY_END:

		m_nPosCurseur = m_texte.Len();

		return VRAI;

		break;

	}



	return FAUX;

}



booleen cgTextBox::OnKeyPress(unsigned char key, int x, int y)

{

	cgcString s;

	int i = 0;



	switch (key)

	{

	case 8:	//BACKSPACE

		if ( m_nPosCurseur > 0 )

		{

			for(; i < m_nPosCurseur-1; i++)

				s += m_texte[i];

			for(i = m_nPosCurseur; i < m_texte.Len(); i++)

				s += m_texte[i];

			m_texte = s;

			m_nPosCurseur--;



			return VRAI;

		}

		break;

	default:

		if ( m_nPosCurseur < m_nLenMax )

		{

			m_texte[m_nPosCurseur] = key;

			m_nPosCurseur++;



			return VRAI;

		}

	}



	return FAUX;

}

