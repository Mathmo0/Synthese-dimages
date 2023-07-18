#ifndef _SCENECAMERA
#define _SCENECAMERA

#include "definition.h"
#include "attr.h"
#include "designateur.h"
#include "ensemble.h"
#include "couleur.h"
#include "camera.h"

typedef Designateur  SDesignateur;

class SceneCamera
{
protected:
	Camera	m_Camera;			//Camera de la scene
	SDesignateur	m_Designateur;	//Représente le désignateur de la scène

	Ensemble* m_pscene;			//Contenu du .scn
	Ensemble* m_pScene;			//Contient m_pscene

public:
	SceneCamera();
	SceneCamera(const SceneCamera& s);
	~SceneCamera();

	void operator=(const SceneCamera& s);

	//Operations sur la SsceneCamera
	Ensemble* Scene() { return m_pScene; }
	const Camera& GetCamera() { return m_Camera; }
	Camera* GetpCamera() { return &m_Camera; }
	SDesignateur* Designateur() { return &m_Designateur; }

	//Affichage de la scene
	void DrawScene();

	//Lecture et ecriture de la SceneCamera
	booleen LoadScene(char* fichier);
	booleen LireVSN(char fichier[]);
	booleen LireSCN(char fichier[]);

	booleen EcrireScene(char fichier[]);
	booleen EcrireVSN(char fichier[]);
};

#endif

