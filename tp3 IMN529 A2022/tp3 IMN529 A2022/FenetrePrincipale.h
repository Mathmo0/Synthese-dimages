//*******************************************************************
//*																	*
//* Programme: FenetrePrincipale.h									*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Fen�tre faisant l'affichage de la sc�ne 3D.					*
//*																	*
//*******************************************************************

#ifndef _FENETREPRINCIPALE
#define _FENETREPRINCIPALE

#include "cgView.h"
#include "scenecamera.h"
#include "settings.h"
#include "displayopengl.h"

//Variables pour la gestion des TP
//--------------------------------
#define LinkSphere			
#define bDesignateurActif		VRAI
#define bTransformateurActif	VRAI
#define bTracerRayons			VRAI
#define bCalculRadiosite		VRAI

typedef Display SDisplay;

class FenetrePrincipale : public cgView
{
protected:
	booleen m_bAnimation;	//Indique si on est en mode animation

	entier m_nNbScene;		//Nombre de scenes
	entier m_nSceneActive;	//Indique la scene active
	SceneCamera* m_pScenes;	//Scenes de la fenetres

	SDisplay m_Display;		//Display faisant l'affichage des sc�nes

private:
	int mainMenu;
	int mainWindow;

public:
	FenetrePrincipale();
	~FenetrePrincipale();

	//Settings et display
	SDisplay* Display() { return &m_Display; }

	//Scenes
	SceneCamera* Scene(entier i);
	SceneCamera* Scene();
	void InitNbScene(entier n);
	entier NbScene() { return m_nNbScene; }
	entier SceneActive() { return m_nSceneActive; }
	void SceneActive(entier n) { m_nSceneActive = n; }

	//Animation
	void Animate(booleen v);
	void Animation(const booleen& v) { m_bAnimation = v; }
	booleen Animation() { return m_bAnimation; }

	//Initialise le mode d'OpenGL et load la scene
	virtual void InitWindow();

	//Fonction de gestion des messages
	virtual void OnDraw();
	virtual void OnChangeSize(int w, int h);
	virtual void OnMouseClick(int button, int state, int x, int y);
	virtual void OnSpecialKeyPress(int key, int x, int y);   
	virtual void OnTimer();

private:
	static void OnMenuOption(int value);
};

#endif
