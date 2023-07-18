//*******************************************************************
//*																	*
//* Programme: cgSpinner.cpp										*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Implantation de roulettes permettant d'incrémenter ou de	*
//*		décrémenter une valeur numérique.							*
//*																	*
//*******************************************************************



#include "cgSpinner.h"

#include <cmath>			//pow

#include <assert.h>			//assert



//+1 pour len est pour les chiffres negatifs

cgSpinner::cgSpinner(int left, int top, unsigned len, int min, int max, int step, int value)

	: cgControl(left,top,(len+3+1)*8,30)

{

	assert(min <= max);



	x = left;

	y = top;

	h = HAUT_SPIN;		

	w = (len+3)*8;	

	

	m_nLen = len+1;

	m_nMin = min;

	m_nMax = max;

	m_nStep = step;



	m_nSelection = SPINNER_NONE;

	m_nPosCurseur = 1;



	SetValue(value);

}



cgSpinner::~cgSpinner()

{

}



int cgSpinner::GetValue()

{

	int v = 0;



	for(int i = 1; i < m_nLen; i++)

		v += pow(10.0,m_nLen-i-1)*(m_Valeur[i]-48);

	

	if ( m_Valeur[0] == '-' ) v = v * -1;



	return v;

}



void cgSpinner::SetValue(int value)

{

	//Test la valeur avant de l'affecter

	if ( value < m_nMin ) value = m_nMin;

	if ( value > m_nMax ) value = m_nMax;



	int c = value;

	if ( abs(c) > (pow(10.0,m_nLen-1)-1) )

	{

		if ( c < 0 )

			c = -(pow(10.0,m_nLen-1)-1);

		else

			c = pow(10.0,m_nLen-1)-1;

	}



	if ( c < 0 ) m_Valeur[0] = '-'; else m_Valeur[0] = ' ';

	c = abs(c);



	for(int i = 1; i < m_nLen; i++)

	{

		int v = (int) c / pow(10.0,m_nLen-i-1);

		m_Valeur[i] = v+48;



		c -= v*pow(10.0,m_nLen-i-1);	//Soustrait pour l'enlever

	}

}



void cgSpinner::OnDraw()

{

	//Remplit le fond en gris

	glColor3f(0.75,0.75,0.75);

	glRecti(x,y,x+w,y+h);



	if ( m_nSelection != SPINNER_NONE )

	{

		glColor3f(0.5,0.5,0.5);

		if ( m_nSelection == SPINNER_UP )

		{

			glRecti(x,y,x+LAR_SPIN,y+(HAUT_SPIN/2));

		}

		else

		{

			glRecti(x,y+(HAUT_SPIN/2),x+LAR_SPIN,y+HAUT_SPIN);

		}

	}



	//Dessin du cadre

	glColor3f(1,1,1);

	glBegin(GL_LINES);

		glVertex2f(x,y);

		glVertex2f(x+LAR_SPIN,y);



		glVertex2f(x,y);

		glVertex2f(x,y+HAUT_SPIN);

	glEnd();



	glColor3f(0,0,0);

	glBegin(GL_LINES);

		glVertex2f(x+LAR_SPIN,y);

		glVertex2f(x+LAR_SPIN,y+HAUT_SPIN);



		glVertex2f(x,y+HAUT_SPIN);

		glVertex2f(x+LAR_SPIN,y+HAUT_SPIN);

	glEnd();



	//Dessin de la barre horizontal

	glColor3f(0,0,0);

	glBegin(GL_LINES);

		glVertex2f(x,y+(HAUT_SPIN/2)-1);

		glVertex2f(x+LAR_SPIN,y+(HAUT_SPIN/2)-1);

	glEnd();



	glColor3f(0.75,0.75,0.75);

	glBegin(GL_LINES);

		glVertex2f(x,y+(HAUT_SPIN/2));

		glVertex2f(x+LAR_SPIN,y+(HAUT_SPIN/2));

	glEnd();



	glColor3f(1,1,1);

	glBegin(GL_LINES);

		glVertex2f(x,y+(HAUT_SPIN/2)+1);

		glVertex2f(x+LAR_SPIN,y+(HAUT_SPIN/2)+1);

	glEnd();



	//Dessin des spins

	glColor3f(0,0,0);

	glBegin(GL_POLYGON);

		glVertex2f(x+(LAR_SPIN/2),y+2);

		glVertex2f(x+(LAR_SPIN/2)+4,y+6);



		glVertex2f(x+(LAR_SPIN/2),y+2);

		glVertex2f(x+4,y+6);



		glVertex2f(x+4,y+6);

		glVertex2f(x+(LAR_SPIN/2)+4,y+6);

	glEnd();



	glBegin(GL_POLYGON);

		glVertex2f(x+4,y+(HAUT_SPIN/2)+3);

		glVertex2f(x+(LAR_SPIN/2)+4,y+(HAUT_SPIN/2)+3);



		glVertex2f(x+(LAR_SPIN/2)+4,y+(HAUT_SPIN/2)+3);

		glVertex2f(x+(LAR_SPIN/2),y+(HAUT_SPIN/2)+7);



		glVertex2f(x+(LAR_SPIN/2),y+(HAUT_SPIN/2)+7);

		glVertex2f(x+4,y+(HAUT_SPIN/2)+3);

	glEnd();



	//Affichage de la valeur

	glColor3f(0.5,0.5,0.5);

	int nx = x+LAR_SPIN+2;

	cgRectangle(nx,y,nx+((m_nLen+1)*8),y+HAUT_SPIN);



	glColor3f(0,0,0);

	cgTexte(nx+2,y+15,m_Valeur,m_nLen);



	//Affichage du curseur s'il a le focus

	if ( Focus() )

	{

		int px = x+LAR_SPIN+ 3 + (m_nPosCurseur)*8;



		glColor3f(1,1,1);

		glBegin(GL_LINES);

			glVertex2f(px,y+HAUT_SPIN-3);

			glVertex2f(px+8,y+HAUT_SPIN-3);

		glEnd();

	}

}



booleen cgSpinner::OnMouseDown(int button, int posX, int posY)

{

	if ( posX-x > LAR_SPIN ) return FAUX;



	cgControl::OnMouseUp(button,posX,posY);



	int NewY = posY - y;

	if ( NewY > LAR_SPIN/2 )

	{

		m_nSelection = SPINNER_DOWN;

		SetValue(GetValue()-1);

	}

	else

	{

 		m_nSelection = SPINNER_UP;

		SetValue(GetValue()+1);

	}



	return VRAI;

}



booleen cgSpinner::OnMouseUp(int button, int posX, int posY)

{

	m_nSelection = SPINNER_NONE;

	cgControl::OnMouseUp(button,posX,posY);

	return VRAI;

}



booleen cgSpinner::OnKeyPress(unsigned char key, int x, int y)

{

	switch( key)

	{

	case '1':

	case '2':

	case '3':

	case '4':

	case '5':

	case '6':

	case '7':

	case '8':

	case '9':

	case '0':

		if ( m_nPosCurseur < m_nLen )

		{

			m_Valeur[m_nPosCurseur] = key;

			SetValue(GetValue());	//Test les minimum



			m_nPosCurseur++;

			if ( m_nPosCurseur == m_nLen )

				m_nPosCurseur--;



			return VRAI;

		}

		break;

	}



	return FAUX;

}



booleen cgSpinner::OnSpecialKeyPress(int key, int x, int y)

{

	switch (key)

	{

	case GLUT_KEY_LEFT:

		if ( m_nPosCurseur > 1 )

		{

			m_nPosCurseur--;

			return VRAI;

		}

		break;

	case GLUT_KEY_RIGHT:

		if ( m_nPosCurseur < m_nLen-1 )

		{

			m_nPosCurseur++;

			return VRAI;

		}

		break;

	}



	return FAUX;

}

