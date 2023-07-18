#ifndef _SCENECAMERA

#define _SCENECAMERA



#include "Definition.h"

#include "Attr.h"

#include "Designateur.h"

#include "Ensemble.h"

#include "Couleur.h"

#include "Camera.h"



class SceneCamera

{

protected:

	Camera	m_Camera;			//Camera de la scene

	Designateur	m_Designateur;	//Représente le désignateur de la scène



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

	Designateur* Designateur() { return &m_Designateur; }



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

