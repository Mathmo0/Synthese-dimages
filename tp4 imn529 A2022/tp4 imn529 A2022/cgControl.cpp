//*******************************************************************
//*																	*
//* Programme: cgControl.cpp										*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		cgControl est une classe abstraite qui sert pour la			*
//*		définition de contrôles graphiques de haut niveau.		 	*
//*																	*
//*******************************************************************


#include "cgControl.h"

#include "definition.h"

#include <cmath>



cgControl::cgControl(int left, int top, int width, int height)

{

	m_nLeft = left;		//Set l'aire englobant du controle

	m_nTop = top;

	m_nWidth = width;

	m_nHeight = height;



	m_bVisible = VRAI;		//Rend le controle visible

	m_bSelectionne = FAUX;	//Indique au controle qu'il n'est pas selectionne par la souris

	m_bFocus = FAUX;		//Indique que le controle n'a pas le focus

}



cgControl::~cgControl()

{

}



booleen cgControl::Intersecte(int x, int y)

{

	return ( x > m_nLeft && x < m_nLeft+m_nWidth &&

		     y > m_nTop && y < m_nTop+m_nHeight );

}



booleen cgControl::OnMouseDown(int button, int x, int y) 

{

	Select(VRAI);

	return VRAI;

}



booleen cgControl::OnMouseUp(int button, int x, int y)

{

	Select(FAUX);

	if ( Intersecte(x,y) )

		return VRAI;



	return FAUX;

}



booleen cgControl::OnMouseMove(int x, int y) 

{

	if ( Select() )

	{

		if ( !Intersecte(x,y) )

		{

			Select(FAUX);

			return VRAI;

		}

	}

	else

	{

		if ( Intersecte(x,y) )

		{

			Select(VRAI);

			return VRAI;

		}

	}



	return FAUX;

}



//-----------------------------------------------------------

//Fonctions generales pour aider dans le dessin des controles

//-----------------------------------------------------------



void cgControl::cgRectangle(int x1, int y1, int x2, int y2)

{

	glBegin(GL_LINE_LOOP);

		glVertex2f(x1,y1);

		glVertex2f(x2,y1);

		glVertex2f(x2,y2);

		glVertex2f(x1,y2);

	glEnd();

}



void cgControl::cgRectangleFill(int x1, int y1, int x2, int y2)

{

	glBegin(GL_POLYGON);

		glVertex2f(x1,y1);

		glVertex2f(x2,y1);

		glVertex2f(x2,y2);

		glVertex2f(x1,y2);

	glEnd();

}



void cgControl::cgCircle(int x, int y, int r, int nb_division)

{

	double deux_pi = 2.0*PI;

	double pas = (double)(PI / nb_division);



	double a,b;



	glBegin(GL_LINE_LOOP);

	for(double angle = 0; angle < deux_pi; angle += pas)

	{

		a = (r*sin(angle)) + x;

		b = (r*cos(angle)) + y;



		glVertex2f(a,b);

	}

	glEnd();

}



void cgControl::cgCircleFilled(int x, int y, int r, int nb_division)

{

	for(int i = r; i >= 0; i--)

		cgCircle(x,y,i,nb_division);

}



void cgControl::cgTexte(int x, int y, cgcString texte, int longueur)

{

	if ( longueur == -1 )

		longueur = texte.Len();



	glColor3f(0,0,0);

	glRasterPos2f(x, y);



	for (int i = 0; i < longueur; i++) 

		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, texte[i]);

}

