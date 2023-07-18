//*******************************************************************
//*																	*
//* Programme: cgChoiceBox.cpp										*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Implantation de choice box. Les choices bos permettent	 	*
//*		d'afficher plusieurs sélections qui sont des chaines de 	*
//*		caractères. On peut changer la sélection courante en		*
//*		pressant sur la flèche haut ou la flèche bas.				*
//*																	*
//*******************************************************************


#include "cgChoiceBox.h"

#include "cgcString.h"



cgChoiceBox::cgChoiceBox(int left, int top, unsigned len, cgcTableau<cgcString> t, int value)

	: cgControl(left,top,(len+3+1)*8,30)

{

	//+1 pour len est pour les chiffres negatifs



	x = left;

	y = top;

	h = HAUT_SPIN;		

	w = (len+3)*8;	

	

	m_nLen = len+1;

	SetValue(value);

	m_element = t;



	m_nSelection = SPINNER_NONE;

}



cgChoiceBox::~cgChoiceBox()

{

}



int cgChoiceBox::GetValue()

{

	return m_nValeur;

}



void cgChoiceBox::SetValue(int value)

{

	if ( value >= m_element.Len() ) 

		value = m_element.Len()-1;

	if ( value < 0 ) 

		value = 0;



	m_nValeur = value;

}



void cgChoiceBox::OnDraw()

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

	cgcString str(m_element[m_nValeur]);

	cgTexte(nx+2,y+15,str);

}



booleen cgChoiceBox::OnMouseDown(int button, int posX, int posY)

{

	//Si le click n'est pas sur le spinner alors on ne fait rien

	if ( posX-x > LAR_SPIN ) return FAUX;



	//Indique que l'objet est selectionne

	cgControl::OnMouseDown(button,posX,posY);



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



booleen cgChoiceBox::OnMouseUp(int button, int posX, int posY)

{

	m_nSelection = SPINNER_NONE;

	cgControl::OnMouseUp(button,posX,posY);

	return VRAI;

}

