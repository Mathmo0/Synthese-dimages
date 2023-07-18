#include "designateur.h"
#include "util.h"
#include "canon.h"
#include "scene.h"
#include "select.h"
#include "vision.h"
#include "geo.h"
#include "utilalg.h"
#include "utilreel.h"
#include "objets.h"
#include "Ensemble.h"

#define LinkDesignateur					
#define LinkTransformateur	

Designateur::Designateur()
{
	OkSelection(FAUX);
	m_Path = new Ensemble;
	m_Selection = new Ensemble;
	m_kS = 0.0;

	OkComposante(FAUX);
	pC = point(0.0,0.0,0.0);
	vC = vecteur(0.0,0.0,0.0);
	kC = 0.0;
}

Designateur::~Designateur()
{
}

//------------------------------------------------------------------
//
// Methodes pour la selection et la gestion des selections
//
//------------------------------------------------------------------
void Designateur::MontreSelection()
{
	if ( OkSelection() ) 
	{
		Attributs	a1;
		a1 = m_a0; 
		a1.highlight(VRAI);
		Affiche_Scene(*m_Selection,a1);
	}
}

#ifdef LinkDesignateur
void Designateur::Select(double x, double y, const Camera& camera, Objet* scene)
{
	Transformation t = Vision_Normee(camera);

	if (camera.perspective()) 
	{
		m_pS = t.inverse(O);
		m_vS = t.inverse(vecteur((reel)x,(reel)y,1.0));
	} 
	else 
	{
		m_pS = t.inverse(point((reel)x,(reel)y,0.0));
		m_vS = t.inverse(Z);
	}

	m_a0 = ATTR; // reset attributs de la selection
	if ( OkSelection() ) delete m_Selection;

	m_bOkSelection = Select_Objet(scene, m_pS, m_vS, &m_kS, m_Path);

	if ( OkSelection() ) 
	{
		m_iPath = m_Path->composantes();
		m_Selection = m_Path->composante(m_iPath);
	}
}

void Designateur::Z_Select(Objet* scene)
{
	if ( OkSelection() ) 
	{
		reel	k1;

		if (Select_Objet(scene, m_pS+m_vS*m_kS,m_vS, &k1, m_Path)) 
		{
			m_kS += k1;

			m_a0 = ATTR;  // reset attributs de la selection
			m_iPath = m_Path->composantes();

   			delete m_Selection;
			m_Selection = m_Path->composante(m_iPath);
		}
	}
}

void Designateur::mZ_Select(Objet* scene)
{
	if ( OkSelection() ) 
	{
		reel	k1;

		if (Select_Objet(scene, m_pS+m_vS*m_kS,-m_vS, &k1, m_Path)) 
		{
			m_kS -= k1;

			m_a0 = ATTR; // reset attributs de la selection
			m_iPath = m_Path->composantes();

   			delete m_Selection;
			m_Selection = m_Path->composante(m_iPath);
		}
	}
}

void Designateur::DownSelect()
{
	if ( OkSelection() ) 
	{
		if ( m_iPath < m_Path->composantes() ) 
		{
			m_iPath += 1;
			m_Selection = m_Path->composante(m_iPath);
		}
	}
}

void Designateur::UpSelect()
{
	if ( OkSelection() ) 
	{
		if ( m_iPath > 2 ) 
		{
			m_iPath -= 1;
			m_Selection = m_Path->composante(m_iPath);
		}
	}
}
#endif

//------------------------------------------------------------------
//
// Methodes pour la selection et la gestion des composantes
//
//------------------------------------------------------------------
/*void Designateur::OkSelect()
{
	if ( OkComposante() ) 
	{
		Attributs at = m_Selection->attributs();
		m_Selection->composante(1)->attributs(at);
		m_Selection = new Ensemble;
		m_Composante = new Vide;
	}	
}
*/

void Designateur::SelectComposante(double x, double y, const Camera& camera, Objet* scene)
{
	Transformation t = Vision_Normee(camera);
	if (camera.perspective()) 
	{
		pC = t.inverse(O);
		vC = t.inverse(vecteur((reel)x,(reel)y,1.0));
	} 
	else 
	{
		pC = t.inverse(point((reel)x,(reel)y,0.0));
		vC = t.inverse(Z);
	}

	if ( OkComposante() )
		delete m_Composante;

	vC.normalise();

	m_bOkComposante = Select_Composante(*scene, pC,vC, &kC, m_Composante);

}

void Designateur::Z_SelectComposante(Objet* scene)
{
	if ( OkComposante() ) 
	{
		reel	k1;
		Objet	*objavant = m_Composante;
		point	p = pC+vC*kC;

		m_bOkComposante = Select_Composante(*scene, p,vC, &k1, m_Composante);
		if ( m_bOkComposante ) 
		{
			kC += k1;


			delete objavant;
		} 
		else 
			OkComposante(VRAI);
	}
}

void Designateur::mZ_SelectComposante(Objet* scene)
{
	if ( OkComposante() ) 
	{
		reel	k1;
		Objet	*objavant = m_Composante;
		point	p = pC+vC*kC;
		vecteur	v = vC * -1.0;

		m_bOkComposante = Select_Composante(*scene, p,v, &k1, m_Composante);
		if ( OkComposante() && pg(kC-k1, 0.0)) 
		{
			kC -= k1;

			delete objavant;
		} 
		else 
			OkComposante(VRAI);
	}
}

void Designateur::UnSelectComposante()
{
	if ( OkComposante() ) 
	{
		delete m_Composante;
		OkComposante(FAUX);
	}
}

void Designateur::UnSelectSelection()
{
	delete m_Path;
	m_Path = NULL;
}

void Designateur::ShowObjet(const Objet &o)
{
	Affiche_Scene(o, Attributs(VRAI));
}

void Designateur::ShowComposante()
{
	Attributs	a1;
	a1.highlight(COMPOSANTE_SELECTION);

	if ( OkComposante() ) 
		Affiche_Scene(*m_Composante, a1);
}

void Designateur::ShowSelection()
{
	Attributs	a1;

	a1.highlight(OBJET_SELECTION);
	Affiche_Scene(*m_Selection,a1);
}

//-------------------------------
//
//Methodes pour le transformateur
//
//-------------------------------
#ifdef LinkTransformateur

#endif