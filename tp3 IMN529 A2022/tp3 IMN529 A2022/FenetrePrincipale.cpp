//*******************************************************************
//* Noyau Graphique 3d (n3d) utilisé dans les cours d'infographie   * 
//* à l'Université de Sherbrooke au DMI.                            *
//*                                                                 *
//* Personnes ayant participées à n3d                               *
//*         Richard Egli                                            *
//*         Normand Brière                                          *
//*         Jean-Francois Blier                                     *
//*         Eric Beaudry                                            *
//*                                                                 *
//* Vous pouvons utiliser le noyau pour des fins personnelles       *
//* ou pour les cours d'infographies au DI UdeS. Pour toutes autres *
//* utilisations, SVP contactez Richard Egli,                       *
//* Richard.Egli@USherbrooke.ca                                     *
//* copyright 2019                                                  *
//*																	*
//*******************************************************************
//*																	*
//* Programme: FenetrePrincipale.cpp								*
//*                                                                 *
//*******************************************************************
//*																	*
//* Description:													*
//*		Fenêtre faisant l'affichage de la scène 3D.					*
//*																	*
//*******************************************************************

#include "fenetreprincipale.h"
#include "main.h"
#include "rayons.h"					//Trace de rayons
#include "radiosite.h"				//Calcul de radiosité

//static void FenetrePrincipale::OnMenuOption(int value);
void TracerRayons();

FenetrePrincipale::FenetrePrincipale()
	:	cgView(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE,
		10,10,
		512,512, "Noyau 3D")
{
	m_bAnimation = FAUX;
	m_nSceneActive = 0;
}

FenetrePrincipale::~FenetrePrincipale()
{
}

void FenetrePrincipale::InitNbScene(entier n)
{
	assert(n >= 0);
	m_nNbScene = n;
	m_pScenes = new SceneCamera[n];
}

SceneCamera* FenetrePrincipale::Scene(entier i)
{
	assert(i >= 0 && i < m_nNbScene);
	return &(m_pScenes[i]);
}

SceneCamera* FenetrePrincipale::Scene()
{
	assert(m_nSceneActive >= 0 && m_nSceneActive < m_nNbScene);
	return &(m_pScenes[m_nSceneActive]);
}

void FenetrePrincipale::InitWindow()
{
	//-------------------------------------------
	//Creation des menus de la fenetre principale
	//-------------------------------------------
	//Menu principal
	mainMenu = glutCreateMenu(OnMenuOption);
	glutAddMenuEntry("Camera...", 1);
	glutAddMenuEntry("Settings...", 2);
	glutAddMenuEntry("Lumieres...", 3);
	if ( bDesignateurActif )
		glutAddMenuEntry("Designateur...", 4);
	if ( bTransformateurActif )
		glutAddMenuEntry("Transformation...", 5);
	if ( Animation() )
		glutAddMenuEntry("Animation...", 6);
	if ( bTracerRayons ){
		glutAddMenuEntry("Trace de rayons", 7);
	}
	if(bCalculRadiosite){
	   glutAddMenuEntry("Radiosité (Gauss-Seidel)", 11);
	   glutAddMenuEntry("Radiosité (Propagation)", 12);
	}
	glutAddMenuEntry("Quitter",27);

	//Attache le menu sur bouton droit de la souris
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//-------------------------------------------
	//Setup des fonctionalite d'OpenGL
	//-------------------------------------------
	Display()->InitDisplay();
}

void FenetrePrincipale::Animate(booleen v)
{
	if ( v )
		pApplication->EnableTimer();
	else
		pApplication->DisableTimer();
}

void FenetrePrincipale::OnMenuOption(int value)
{
	switch(value)
	{
	case 1:		//Camera
		pFenetreCamera->ShowWindow();
		break;
	case 2:		//Settings
		pFenetreSetting->ShowWindow();
		break;
	case 3:		//Lumiere
		pFenetreLumiere->ShowWindow();
		break;
	case 4:		//Designateur
		pFenetreDesignateur->ShowWindow();
		break;
	case 5:		//Transformation
		pFenetreTransformation->ShowWindow();
		break;
	case 6:		//Animation
		pFenetreAnimation->ShowWindow();
		break;
	case 7:		//Trace de rayons
		TracerRayons();
		break;
	case 11:    //Calcul Radiosite par Gauss Seidel
	      CalculRadiosite_GS(pFenAff3D->Scene()->Scene());
	      break;
	case 12:
	      CalculRadiositePropagation(pFenAff3D->Scene()->Scene());
	      break;
	case 27:	//Quitter
		pApplication->StopApplication();
		break;
	}
}

void FenetrePrincipale::OnMouseClick(int button, int state, int x, int y)
{
	if ( state == GLUT_UP && button == GLUT_LEFT )
	{
		TOUCHE_CONTROLE tc = GetControlKey();

		if ( tc & CTRL )
		{
			if ( bTransformateurActif )
			{
				//Sélection d'une composante
				double w = Width() / 2;
				double h = Height() / 2;
				double nx = (x - w) / w;
				double ny = (y - h) / h;

				Scene()->Designateur()->SelectComposante(-nx,-ny, Scene()->GetCamera(), Scene()->Scene());
				Redraw();
			}
		}
		else
		{
			if ( bDesignateurActif )
			{
				//Sélection d'un objet
				double w = Width() / 2;
				double h = Height() / 2;
				double nx = (x - w) / w;
				double ny = (y - h) / h;
				Scene()->Designateur()->Select(-nx,-ny, Scene()->GetCamera(), Scene()->Scene());
				Redraw();
			}
		}
	}
}

void FenetrePrincipale::OnDraw()
{
	//Set la camera et les lumieres
	Display()->SetupCamera(Scene()->GetpCamera());
	Display()->SetupLighting(Scene()->GetpCamera());

	//Affiche la scene
	Scene()->DrawScene();

	//Affiche la selection s'il y en a une
	Designateur* pDesignateur = Scene()->Designateur();
	if ( pDesignateur->OkSelection() || pDesignateur->OkComposante() ) 
	{
		//Change la grosseur de la selection
		int ancien = Display()->GrosseurTrait();

		//Affiche la selection d'un objet
		Display()->GrosseurTrait(ancien+3);
		pDesignateur->MontreSelection();
		Display()->GrosseurTrait(ancien+5);
		pDesignateur->ShowComposante();

		//Remet l'ancienne grosseur de ligne
		Display()->GrosseurTrait(ancien);
	}

	glutSwapBuffers();
	glFlush();
}

void FenetrePrincipale::OnChangeSize(int w, int h)
{
     const Camera& camera = m_pScenes->GetCamera();
//	if ( w < h ) h = w;
     if(w * (camera.Hmax() - camera.Hmin()) / (camera.Pmax()-camera.Pmin()) != h){
        h = (int) (w * (camera.Hmax() - camera.Hmin()) / (camera.Pmax()-camera.Pmin()));
        printf("Dimension de la fenetre :  w=%d   h=%d\n", w, h);
     }
	glutReshapeWindow( w, h );
	ChangeSize(w, h);

	Display()->OnChangeSize(w,h);
}

void FenetrePrincipale::OnSpecialKeyPress(int key, int x, int y)
{
	switch (key)
	{

	//Gestion de la camera
	case GLUT_KEY_LEFT:
		Scene()->GetpCamera()->Left();
		Redraw();
		return;
	case GLUT_KEY_RIGHT:
		Scene()->GetpCamera()->Right();
		Redraw();
		return;
	case GLUT_KEY_UP:
		Scene()->GetpCamera()->Up();
		Redraw();
		return;
	case GLUT_KEY_DOWN:
		Scene()->GetpCamera()->Down();
		Redraw();
		return;
	case GLUT_KEY_PAGE_UP:
		Scene()->GetpCamera()->Front();
		Redraw();
		return;
	case GLUT_KEY_PAGE_DOWN:
		Scene()->GetpCamera()->Back();
		Redraw();
		return;
	case GLUT_KEY_HOME:
		Scene()->GetpCamera()->FenetreMul2();
		Redraw();
		return;
	case GLUT_KEY_END:
		Scene()->GetpCamera()->FenetreDiv2();
		Redraw();
		return;

	//Gestion des settings
	case GLUT_KEY_F1:
		pFenetreSetting->ChangeGouraud();
		Redraw();
		return;
	case GLUT_KEY_F2:
		pFenetreSetting->ChangePolygoneRemplit();
		Redraw();
		return;
	case GLUT_KEY_F3:
		pFenetreSetting->ChangeContourPolygone();
		Redraw();
		return;
	case GLUT_KEY_F4:
		pFenetreSetting->ChangeCullFace();
		Redraw();
		return;

        case GLUT_KEY_F5:
                TracerRayons();
                return;

	//Gestion de l'animation
	case GLUT_KEY_F9:
		if ( Animation() )
		{
			SceneActive(SceneActive()-1);
			if ( SceneActive() < 0 ) SceneActive(m_nNbScene-1);
			pFenetreAnimation->ChangeSlide(SceneActive()+1);
			Redraw();
		}
		return;
	case GLUT_KEY_F10:
		if ( Animation() )
		{
			SceneActive(SceneActive()+1);
			if ( SceneActive() >= m_nNbScene ) SceneActive(0);
			pFenetreAnimation->ChangeSlide(SceneActive()+1);
			Redraw();
		}
		return;
	case GLUT_KEY_F11:
		if ( Animation() )
		{
			pFenetreAnimation->ChangeAnimate();
			Redraw();
		}
		return;
	}
}

void FenetrePrincipale::OnTimer()
{
	entier no = SceneActive()+1;
	if ( no >= NbScene() )
		no = 0;
	SceneActive(no);
	pFenetreAnimation->ChangeSlide(no+1);

	Redraw();
}

void TracerRayons()
{
  TraceRayons(pFenAff3D->Scene()->GetCamera(), pFenAff3D->Scene()->Scene(),
		pFenAff3D->Width(), pFenAff3D->Height(), "trace.ppm");

}
