//*******************************************************************
//*																	*
//* Programme: cgSlider.h											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Implantation de slider permettant de choisir une valeur		*
//*		entière.													*
//*																	*
//*******************************************************************

#include "cgSlider.h"
#include <assert.h>			//assert

#define HEIGHT 30

//+1 pour len est pour les chiffres negatifs
cgSlider::cgSlider(int left, int top, int width, double min, double max, int interespacement, double step, double value)
	: cgControl(left,top,width,HEIGHT)
{
	assert(min <= max);

	x = left;
	y = top;
	w = width;
	h = HEIGHT;

	m_nInterEspacement = interespacement;

	m_nStep = step;
	m_nMin = min;
	m_nMax = max;
	SetValue(value);

	m_nRatio = (m_nMax - m_nMin) / w;
}

cgSlider::~cgSlider()
{
}

double cgSlider::GetValue()
{
	return m_nValeur;
}

void cgSlider::SetValue(double value)
{
	//Test la valeur avant de l'affecter
	if ( value < m_nMin )
		value = m_nMin;
	if ( value > m_nMax )
		value = m_nMax;

	m_nValeur = value;
}

void cgSlider::OnDraw()
{
	//Remplit le fond en gris
	//-------------------------------
	glColor3f(0.75,0.75,0.75);
	glRecti(x,y,x+w+1,y+h);

	//Dessin de la ligne horizontale
	//-------------------------------
	glBegin(GL_LINES);
		//Lignes
		glColor3f(0.5,0.5,0.5);
		glVertex2f(x,y+3);
		glVertex2f(x+w,y+3);

		glColor3f(0.0,0.0,0.0);
		glVertex2f(x,y+4);
		glVertex2f(x+w,y+4);

		glColor3f((float)0.85,(float)0.85,(float)0.85);
		glVertex2f(x,y+5);
		glVertex2f(x+w,y+5);

		glColor3f(1.0,1.0,1.0);
		glVertex2f(x,y+6);
		glVertex2f(x+w,y+6);

		//coin gauche
		glColor3f(0.5,0.5,0.5);
		glVertex2f(x,y+3);
		glVertex2f(x,y+6);

		//coin droit
		glColor3f((float)0.85,(float)0.85,(float)0.85);
		glVertex2f(x+w-1,y+4);
		glVertex2f(x+w-1,y+5);

		glColor3f(1.0,1.0,1.0);
		glVertex2f(x+w,y+3);
		glVertex2f(x+w,y+7);
	glEnd();

	//Dessin des lignes verticales
	//-------------------------------
	int NB_LIGNES = w / m_nInterEspacement;
	int val = m_nMin;
	int renduX = x;

	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);
	for(int i = 0; i <= NB_LIGNES; i++)
	{
		//Affichage de la ligne veticale
		glVertex2f(renduX,y+20);
		glVertex2f(renduX,y+25);

		renduX += m_nInterEspacement;
	}
	glEnd();

	//Affichage du pointeur du slider
	//-------------------------------
	double ratio = ((float)m_nValeur) / m_nMax;
	int posx = (ratio * w) + x - 5;
	int posy = m_nTop;

	glColor3f(0.75,0.75,0.75);
	glRecti(posx,posy,posx+11,posy+21);

	glBegin(GL_LINES);
		glColor3f(1.0,1.0,1.0);
		glVertex2f(posx,posy);
		glVertex2f(posx+10,posy);
		glVertex2f(posx,posy);
		glVertex2f(posx,posy+16);
		glVertex2f(posx+1,posy+16);
		glVertex2f(posx+5,posy+20);

		glColor3f(0.0,0.0,0.0);
		glVertex2f(posx+10,posy);
		glVertex2f(posx+10,posy+15);
		glVertex2f(posx+10,posy+15);
		glVertex2f(posx+5,posy+20);

		glColor3f(0.5,0.5,0.5);
		glVertex2f(posx+9,posy+1);
		glVertex2f(posx+9,posy+15);
		glVertex2f(posx+9,posy+15);
		glVertex2f(posx+5,posy+19);

		glColor3f((float)0.85,(float)0.85,(float)0.85);
		glVertex2f(posx+1,posy+1);
		glVertex2f(posx+9,posy+1);
		glVertex2f(posx+1,posy+1);
		glVertex2f(posx+1,posy+16);
		glVertex2f(posx+2,posy+16);
		glVertex2f(posx+5,posy+19);
	glEnd();

	if ( Focus() )
	{
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1,0xDB6D);

		glColor3f(0.0, 0.0, 0.0);
		cgRectangle(posx-1,posy-1,posx+11,posy+20);

		glDisable(GL_LINE_STIPPLE);
	}
}

booleen cgSlider::OnMouseDown(int button, int posX, int posY)
{
	int val = posX - x;
	double ratio = ((float)val)/w;
	SetValue((ratio*(m_nMax-m_nMin)) + m_nMin);

	return VRAI;
}

booleen cgSlider::OnMouseMove(int posX, int posY)
{
	int val = posX - x;

	if ( val < 0 )
		SetValue(m_nMin);
	else if ( val > w )
		SetValue(m_nMax);
	else
	{
		double ratio = ((float)val)/w;
		SetValue((ratio*(m_nMax-m_nMin)) + m_nMin);
	}

	return VRAI;
}

booleen cgSlider::OnSpecialKeyPress(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if ( GetValue()-m_nRatio >= m_nMin )
		{
			SetValue(GetValue()-m_nRatio);
			return VRAI;
		}
		return FAUX;
		break;
	case GLUT_KEY_RIGHT:
		if ( GetValue()+m_nRatio <= m_nMax )
		{
			SetValue(GetValue()+m_nRatio);
			return VRAI;
		}
		return FAUX;
		break;
	}

	return FAUX;
}
