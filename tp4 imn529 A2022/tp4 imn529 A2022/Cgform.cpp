//*******************************************************************

//*																	*

//* Programme: cgForm.cpp											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		cgForm est dérivée de cgWindow. Elle permet de faire des	*

//*		feuilles où l'on place des contrôles graphiques(Boutton, 	*

//*		Case à cocher, ...) pour ainsi intéragir avec l'usager.		*

//*																	*

//*		L'affichage se fait en 2D.									*

//*																	*

//*******************************************************************



#include "cgForm.h"



cgForm::cgForm(	unsigned int style,

				int left, int top,

				int width, int height,

				char * title) 

	: cgWindow(style,left,top,width,height, title)

{

	m_nNbControle = 0;

	m_bControleSelectionne = FAUX;



	m_bFocus = FAUX;

}



cgForm::~cgForm()

{

	//Detruit les controles

	for(int i = 0; i < m_nNbControle; i++)

		delete m_pControle[i];



	DestroyWindow();		//Detruit la fenetre

}



void cgForm::InitWindow()

{

}



CONTROL_ID cgForm::AddControl(cgControl* c)

{

	CONTROL_ID id = -1;



	if ( m_nNbControle < 50 )

	{

		id = m_nNbControle;

		m_pControle[id] = c;

		m_nNbControle++;

	}



	return id;

}



void cgForm::OnDraw()

{

	//On efface la fenetre

	glClearColor(0.75,0.75,0.75,0.0);

	glClear(GL_COLOR_BUFFER_BIT);



	//Affiche tous les controles

	for(int i = 0; i < m_nNbControle; i++)

	{

		if ( m_pControle[i]->Visible() )

			m_pControle[i]->OnDraw();

	}



	//Echange les buffers et affiche le tout

	glutSwapBuffers();

	glFlush();

}



void  cgForm::OnChangeSize(int w, int h)

{

	//Remet la dimension de la fenetre a celle qui doit etre d'apres l'initialisation

	glutReshapeWindow( Width(),Height() );



	//Set le viewport

	glViewport(0, 0, w, h);



	//Indique la facon dont on effectue le dessinage

	glLoadIdentity();

	glOrtho(0,w,h,0,1,-1);

}



void cgForm::OnKeyPress(unsigned char key, int x, int y)

{

	if ( m_bFocus )

	{

		if ( m_pControle[m_CtrlFocus]->OnKeyPress(key,x,y) )

		{

			Redraw();

			OnChange(m_nControleSelectionne);

		}

	}

}



void cgForm::OnSpecialKeyPress(int key, int x, int y)

{

	if ( m_bFocus )

	{

		if ( m_pControle[m_CtrlFocus]->OnSpecialKeyPress(key,x,y) )

		{

			Redraw();

			OnChange(m_nControleSelectionne);

		}

	}

}   



void cgForm::OnMouseClick(int button, int state, int x, int y)

{

	if ( state == GLUT_UP  )

	{

		if ( m_bControleSelectionne )

		{

			m_bControleSelectionne = FAUX;

			//Deselectionne le controle selectionne

			if ( m_pControle[m_nControleSelectionne]->OnMouseUp(button,x,y) )

				Redraw();



			//Si c'est le meme controle qui a ete selectionne, alors

			//c'est que c'est un click sur le controle

			if ( m_pControle[m_nControleSelectionne]->Intersecte(x,y) )

				OnChange(m_nControleSelectionne);

		}

	}

	else

	{

		for(int i = m_nNbControle-1; i >= 0; i--)

		{

			if ( m_pControle[i]->Intersecte(x,y) )

			{

				//Indique qu'il y a maintenant un controle de selectionne

				m_bControleSelectionne = VRAI;

				m_nControleSelectionne = i;



				if ( m_bFocus )

					m_pControle[m_CtrlFocus]->Focus(FAUX);



				m_CtrlFocus = i;

				m_bFocus = VRAI;

				m_pControle[m_CtrlFocus]->Focus(m_bFocus);



				//Change l'état du controle et le redessine

				if ( m_pControle[i]->OnMouseDown(button,x,y) )

					Redraw();



				return;

			}

		}



		//Comme aucun controle n'a ete selectionne, on enleve le focus

		//au controle ayant le focus s'il y en a un.

		if ( m_bFocus )

		{

			m_pControle[m_CtrlFocus]->Focus(FAUX);

			Redraw();

			m_bFocus = FAUX;

		}

	}

}



void cgForm::OnMouseMove(int x, int y)

{

	//On ne fait rien lorsque la souris bouge sans un bouton enfonce

}



void cgForm::OnMouseMoveWithButton(int x, int y)

{

	//Gere le fait qu'un controle est selectionne mais qu'on peut ne

	//plus se trouver dessus. Losqu'on retourne dessus, on le reaffiche

	if ( m_bControleSelectionne )

	{

		if ( m_pControle[m_nControleSelectionne]->OnMouseMove(x,y) )

			OnChange(m_nControleSelectionne);

		Redraw();

	}

}

