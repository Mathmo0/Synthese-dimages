#ifndef _DESIGNATEUR

#define _DESIGNATEUR



#include "Definition.h"
#include "alg.h"
#include "ensemble.h"
#include "point.h"
#include "Camera.h"
#include "Objet.h"


class Designateur
{
protected:
	booleen	m_bOkSelection;
	entier  m_iPath;		//Numéro de la sélection courante dans m_Path
	point	m_pS;			//Origine de l'axe de la sélection
	vecteur	m_vS;			//Direction de l'axes de la sélection
	reel	m_kS;			//Point d'intersection de la sélection = m_pS + m_kS*m_vS


	Ensemble* m_Path;		//Les sélections possibles
	Objet* m_Selection;		//Selection courante dans la scène

	Attributs m_a0;			//Attributs de la sélection

	booleen	m_bOkComposante;
	Objet* m_Composante;	//Composante courante dans la scène
	point	pC;
	vecteur	vC;
	reel	kC;

public:

	Designateur();
	~Designateur();


	Ensemble* Path() { return m_Path; }
	Objet* Selection() { return m_Selection; }
	Objet* Composante() { return m_Composante; }


	booleen OkComposante() { return m_bOkComposante; }
	booleen OkSelection() { return m_bOkSelection; }


	//Affiche la sélection courante
	void MontreSelection();


	//Methodes pour la selection et la gestion des selections
	void Select(double x, double y, const Camera& camera, Objet* scene);
	void DownSelect();
	void UpSelect();
	void Z_Select(Objet* scene);
	void mZ_Select(Objet* scene);

	//Methodes pour la selection et la gestion des composantes
//	void OkSelect();
	void SelectComposante(double x, double y, const Camera& camera, Objet* scene);
	void Z_SelectComposante(Objet* scene);
	void mZ_SelectComposante(Objet* scene);


	void ShowComposante();
	void ShowSelection();
	void UnSelectSelection();
	void UnSelectComposante();


	//Methodes pour la modification de la selection
	void OkTransformation();
	void Translation(reel ktrans);
	void Homothetie(reel xhomo);
	void Rotation(reel teta);

protected:
	void ShowObjet(const Objet &o);
	void patchecomposante();


	void AppliqueASelection(Transformation t);


	void OkComposante(booleen v) { m_bOkComposante = v; }
	void OkSelection(booleen v) { m_bOkSelection = v; }

};

#endif