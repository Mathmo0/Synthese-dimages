#include "cgRadioButton.h"



cgRadioButton::cgRadioButton(int left, int top,

							 entier n,

							 cgcString Tableau[], 

							 booleen horizontal,

							 entier valeur, 

							 booleen transparent)

							 : cgControl(left,top,0,0)

{

	SetSelection(valeur);

	m_bHorizontal = horizontal;

	

	Transparent(transparent); 



	int maxx = 0;

	int nx = 0;

	for(int i = 0; i < n ; i++)

	{

		m_Tableau[i] = Tableau[i];



		int len = (Tableau[i].Len()*8) + 22;

		nx += len;

		if ( len > maxx )

			maxx = len;

	}

	

	if ( horizontal )

	{

		m_nWidth = nx;

		m_nHeight = 15;

	}

	else

	{

		m_nWidth = maxx;

		m_nHeight = 15*n;

	}

}



cgRadioButton::~cgRadioButton()

{



}

	

booleen cgRadioButton::GetSelection()

{

	return m_nSelection;

}



void cgRadioButton::SetSelection(int value)

{

	m_nSelection = value;

}



void cgRadioButton::OnDraw()

{

	int x = m_nLeft+10;

	int y = m_nTop+10;

	int w = m_nWidth;

	int h = m_nHeight;



	if ( !Transparent() )

	{

		glColor3f(0.75,0.75,0.75);

		glRecti(x,y,x+w,y+h);

	}



	for(int i = 0; i < m_Tableau.Len(); i++)

	{

		//Dessine le rond

		glColor3f(0,0,0);

		cgCircle(x,y,6,36);



		//Affiche le texte

		cgTexte(x+10,y+3, m_Tableau[i]);



		//Si ces celui-ci qui est selectionne, on affiche un cercle plein

		if ( GetSelection() == i )

		{

			cgCircleFilled(x,y,3,36);



			if ( Focus() )

			{

				glEnable(GL_LINE_STIPPLE);

				glLineStipple(1,0xDB6D);

				glColor3f(0.0, 0.0, 0.0);

				int nx = m_Tableau[i].Len()*8+10;

				cgRectangle(x+9,y-7,x+nx,y+6);

				glDisable(GL_LINE_STIPPLE);

			}

		}



		//

		if ( m_bHorizontal )

			x += m_Tableau[i].Len()*8+22;

		else

			y += 15;

	}

}



booleen cgRadioButton::OnMouseUp(int button, int posX, int posY)

{

	if ( cgControl::OnMouseUp(button,posX,posY) )

	{

		if ( m_bHorizontal )

		{

			int nx;

			int posx = m_nLeft;

			for(int i = 0; i < m_Tableau.Len(); i++)

			{

				nx = (m_Tableau[i].Len()*8) + 22;

				

				if ( posX >= posx && posX <= posx+nx )

				{

					m_nSelection = i;

					return VRAI;

				}



				posx += nx;

			}

		}

		else

		{

			int sel = (posY - m_nTop) / 15;

			assert( sel >= 0 );



			int nx = (m_Tableau[sel].Len()*8) + 22;

			int a = posX - m_nLeft;

			if ( a < nx )

				m_nSelection = sel;

		}



		return VRAI;

	}



	return FAUX;

}



booleen cgRadioButton::OnSpecialKeyPress(int key, int x, int y)

{

	switch (key)

	{

	case GLUT_KEY_LEFT:

	case GLUT_KEY_UP:

		if ( m_nSelection > 0 )

		{

			m_nSelection--;

			return VRAI;

		}

		break;

	case GLUT_KEY_RIGHT:

	case GLUT_KEY_DOWN:

		if ( m_nSelection < m_Tableau.Len()-1 )

		{

			m_nSelection++;

			return VRAI;

		}

		break;

	}



	return FAUX;

}

