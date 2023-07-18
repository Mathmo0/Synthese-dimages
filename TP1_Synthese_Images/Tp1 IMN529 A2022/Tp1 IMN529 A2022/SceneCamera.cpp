#include "SceneCamera.h"
#include "scene.h"
#include "fichier.h"
#include "io.h"
#include "string.h"

SceneCamera::SceneCamera() 
{
}

SceneCamera::~SceneCamera()
{
}

SceneCamera::SceneCamera(const SceneCamera& s)
{
	m_Camera = s.m_Camera;
	m_Designateur = s.m_Designateur;

	m_pscene = (Ensemble*)s.m_pscene->copie();
	m_pScene = (Ensemble*)s.m_pscene->copie();
}

void SceneCamera::operator=(const SceneCamera& s)
{
	m_Camera = s.m_Camera;
	m_Designateur = s.m_Designateur;

	m_pscene = (Ensemble*)s.m_pscene->copie();
	m_pScene = (Ensemble*)s.m_pscene->copie();
}

void SceneCamera::DrawScene()
{
	Affiche_Scene(*Scene(),ATTR);
}

booleen SceneCamera::LoadScene(char* fichier)
{
	m_pscene = new Ensemble();
	m_pScene = new Ensemble();
	m_pScene->ajoute(m_pscene);

	if ( !LireSCN(fichier) ) return FAUX;
	if ( !LireVSN(fichier) ) return FAUX;

	return VRAI;
}

booleen SceneCamera::LireVSN(char fichier[])
{
	Fichier f;
	char s[256];

	sprintf_s(s, 256, "%s.vsn", fichier);
	if ( !f.Open(s, "r") ) return FAUX;

	printf("Lecture du .vsn en cours...\n");

	point	pt;
	vecteur	v;
	Lire_point(f, &pt);
	m_Camera.PR (pt);
	printf("  PR <%f,%f,%f>\n",pt.x(),pt.y(),pt.z());
	Lire_vecteur(f, &v);
	m_Camera.VN (v);
	printf("  VN <%f,%f,%f>\n",v.x(),v.y(),v.z());
	Lire_vecteur(f, &v);
	m_Camera.VH (v);
	printf("  VH <%f,%f,%f>\n",v.x(),v.y(),v.z());

	reel r;
	if ( !f.mreel(r) ) { printf("Reel attendu\n"); exit(1); }
	m_Camera.DO (r);
	printf("  do %f\n",r);
	if ( !f.mreel(r) ) { printf("Reel attendu\n"); exit(1); }
	m_Camera.DV (r);
	printf("  dv %f\n",r);
	if ( m_Camera.DV() < m_Camera.DO() ) 
	{
		printf("DV est plus petit que DO. Il faut que DV soit plus grand que DO\n");
		exit(1);
	}

	double v1,v2,v3,v4;
	if ( !f.mreel(v1) ) { printf("Reel attendu\n"); exit(1); }
	if ( !f.mreel(v2) ) { printf("Reel attendu\n"); exit(1); }
	if ( !f.mreel(v3) )	{ printf("Reel attendu\n"); exit(1); }
	if ( !f.mreel(v4) )	{ printf("Reel attendu\n"); exit(1); }
	printf("  FENETRE: %f,%f,  %f,%f\n",v1,v2,v3,v4);
	m_Camera.fenetre(v1,v2,v3,v4);

	if ( !f.mreel(v1) ) { printf("Reel attendu\n"); exit(1); }
	if ( !f.mreel(v2) ) { printf("Reel attendu\n"); exit(1); }
	if ( !f.mreel(v3) ) { printf("Reel attendu\n"); exit(1); }
	if ( !f.mreel(v4) ) { printf("Reel attendu\n"); exit(1); }
	m_Camera.cloture (v1,v2,v3,v4);
	printf("  CLOTURE: %f,%f,  %f,%f\n",v1,v2,v3,v4);

	if ( !f.mreel(r) ) { printf("Reel attendu\n"); exit(1); }
	m_Camera.DH (r);
	printf("  dh %f\n",r);
	if ( !f.mreel(r) && !f.fin() ) { printf("Reel attendu\n"); exit(1); }
	m_Camera.DY (r);
	printf("  dy %f\n",r);

	m_Camera.perspective(VRAI);

	//Lecture des lumieres
	entier nbLum = 0;
	while ( !f.fin() && nbLum < 8)
	{
		//Lecture de la position de la source
		double v1,v2,v3;
		if ( !f.mreel(v1) )
		{
			if ( !f.fin() ) { printf("Reel attendu\n"); exit(1); } else break;
		}
		if ( !f.mreel(v2) ) { printf("Reel attendu\n"); exit(1); }
		if ( !f.mreel(v3) ) { printf("Reel attendu\n"); exit(1); }

		pt = point (v1,v2,v3);
		printf("  \nLumiere %d\n",nbLum+1);
		printf("  POS <%f,%f,%f>\n",v1,v2,v3);

		//Lecture de la couleur diffuse de la source
		reel rd,gd,bd;
		if ( !f.mreel(rd) ) { printf("Reel attendu\n"); exit(1); }
		if ( !f.mreel(gd) ) { printf("Reel attendu\n"); exit(1); }
		if ( !f.mreel(bd) ) { printf("Reel attendu\n"); exit(1); }
		printf("  Couleur diffuse <%f,%f,%f>\n",rd,gd,bd);

		//Lecture de la couleur ambiante de la source
		reel ra,ga,ba;
		if ( !f.mreel(ra) ) { printf("Reel attendu\n"); exit(1); }
		if ( !f.mreel(ga) ) { printf("Reel attendu\n"); exit(1); }
		if ( !f.mreel(ba) ) { printf("Reel attendu\n"); exit(1); }
		printf("  Couleur ambiante <%f,%f,%f>\n",ra,ga,ba);

		Lumiere lum(pt, ra,ga,ba, rd,gd,bd);
		m_Camera.AddLumiere(lum);

		nbLum++;
	}

	f.Close();

	printf("Lecture du .vsn terminee\n");
	reel	d0 = m_Camera.DO ();
	reel	dv = m_Camera.DV ();
	reel    hmin = m_Camera.Hmin ();
	reel    hmax = m_Camera.Hmax ();
//	m_Camera.Pas(0);

	return VRAI;
}

booleen SceneCamera::LireSCN(char fichier[])
{
	char s[256];
	Fichier f;

	sprintf_s(s, 256, "%s.scn", fichier);
	if (!f.Open(s, "r")) return FAUX;

	printf("Lecture du .scn en cours...\n");
	Objet	*o = Objet::Lecture(f);
	printf("Lecture du .scn termine\n\n");

	f.Close();

	if (o->type() != unEnsemble) 
	{
		m_pscene = new Ensemble;
		m_pscene->ajoute(o,ATTR);
	} 
	else 
		m_pscene = (Ensemble *)o;

	m_pScene->enleve(1); // scene
	m_pScene->ajoute(m_pscene);

	return VRAI;
}

booleen SceneCamera::EcrireScene(char fichier[])
{
	//Ecriture du SCN
	Fichier	f;
	char s[256];
	sprintf_s(s, 256, "%s.scn", fichier);
	if (!f.Open(s, "w")) 
		return FAUX;
	m_pscene->Ecrire(&f);
	f.Close();

	//Ecriture du VSN
	if ( !EcrireVSN(fichier) ) 
		return FAUX;

	return VRAI;
}

booleen SceneCamera::EcrireVSN(char fichier[])
{
	Fichier f;
	char s[256];
	sprintf_s(s, 256, "%s.scn", fichier);
	if (!f.Open(s, "w")) return FAUX;

	Ecrire_point(&f, m_Camera.PR());
	Ecrire_vecteur(&f, m_Camera.VN());
	Ecrire_vecteur(&f, m_Camera.VH());

	f.Wreel(m_Camera.DO()); f.Wchaine(" ");
	f.Wreel(m_Camera.DV()); f.Wchaine("\n");

	f.Wreel(m_Camera.Pmin()); f.Wchaine(" ");
	f.Wreel(m_Camera.Pmax()); f.Wchaine(" ");
	f.Wreel(m_Camera.Hmin()); f.Wchaine(" ");
	f.Wreel(m_Camera.Hmax()); f.Wchaine("\n");
	f.Wreel(m_Camera.Xmin()); f.Wchaine(" ");
	f.Wreel(m_Camera.Xmax()); f.Wchaine(" ");
	f.Wreel(m_Camera.Ymin()); f.Wchaine(" ");
	f.Wreel(m_Camera.Ymax()); f.Wchaine("\n");

	f.Wreel(m_Camera.DH()); f.Wchaine(" ");
	f.Wreel(m_Camera.DY()); f.Wchaine("\n");

	f.Close();

	return VRAI;
}
