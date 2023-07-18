//*******************************************************************

//*																	*

//* Programme: camera.cpp											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation de la caméra. Permet de définir la pyramide	*

//*		et permet de déplacer la caméra dans la scène.				*

//*																	*

//*******************************************************************



#include "camera.h"
#include "geo.h"
#include "utilalg.h"
#include <assert.h>

#include <cmath>

#include "cstdio"

#ifdef INLINE

inline

#endif

Camera::Camera()

{

	PR(point(0.0,0.0,0.0)); 

	VN(vecteur(0.0,0.0,1.0));

	VH(vecteur(0.0,1.0,0.0));

	DV(0.0);

	DO(-1.0);

	DH(-1.0);

	DY(100.0);

	fenetre(-1.0,1.0,-1.0,1.0);

	cloture(0.0,1.0,0.0,1.0);



	lockvh=VRAI;

	prmode=VRAI;

	Step(0);

	Pas(0);



	LumiereActiveScene(VRAI);

	m_bAvecLumiere = FAUX;

	m_nNbLumiere = 0;

}



Camera::Camera(const Camera& c)

{

	pr = c.pr;

	vn = c.vn;

	vh = c.vh;



	pmin = c.pmin;

	pmax = c.pmax;

	hmin = c.hmin;

	hmax = c.hmax;

	xmin = c.xmin;

	xmax = c.xmax;

	ymin = c.ymin;

	ymax = c.ymax;



	dv = c.dv;

	d0 = c.d0;

	dy = c.dy;

	dh = c.dh;



	persp = c.persp;

	step = c.step;



	lockvh = c.lockvh;

	prmode = c.prmode;

	t = c.t;



	m_bLumiereActiveScene = c.m_bLumiereActiveScene;

	m_bAvecLumiere = c.m_bAvecLumiere;

	m_nNbLumiere = c.m_nNbLumiere;

	for(int i = 0; i < m_nNbLumiere; i++)

		m_Lumiere[i] = c.m_Lumiere[i];

}



void Camera::operator=(const Camera& c)

{

	pr = c.pr;

	vn = c.vn;

	vh = c.vh;



	pmin = c.pmin;

	pmax = c.pmax;

	hmin = c.hmin;

	hmax = c.hmax;

	xmin = c.xmin;

	xmax = c.xmax;

	ymin = c.ymin;

	ymax = c.ymax;



	dv = c.dv;

	d0 = c.d0;

	dy = c.dy;

	dh = c.dh;



	persp = c.persp;

	step = c.step;



	lockvh = c.lockvh;

	prmode = c.prmode;

	t = c.t;



	m_bLumiereActiveScene = c.m_bLumiereActiveScene;

	m_bAvecLumiere = c.m_bAvecLumiere;

	m_nNbLumiere = c.m_nNbLumiere;

	for(int i = 0; i < m_nNbLumiere; i++)

		m_Lumiere[i] = c.m_Lumiere[i];

}



#ifdef INLINE

inline

#endif

const	point&	Camera::PR () const { return(pr); }

#ifdef INLINE

inline

#endif

point	Camera::PO () const { return(pr+(d0*vn)); }



#ifdef INLINE

inline

#endif

const	vecteur&	Camera::VN () const { return(vn); }

#ifdef INLINE

inline

#endif

const	vecteur&	Camera::VH () const { return(vh); }



#ifdef INLINE

inline

#endif

const	reel&	Camera::DV () const { return(dv); }

#ifdef INLINE

inline

#endif

const	reel&	Camera::DO () const { return(d0); }

#ifdef INLINE

inline

#endif

const	reel&	Camera::DH () const { return(dh); }

#ifdef INLINE

inline

#endif

const	reel&	Camera::DY () const { return(dy); }



#ifdef INLINE

inline

#endif

const	reel&	Camera::Pmin () const { return(pmin); }

#ifdef INLINE

inline

#endif

const	reel&	Camera::Pmax () const { return(pmax); }

#ifdef INLINE

inline

#endif

const	reel&	Camera::Hmin () const { return(hmin); }

#ifdef INLINE

inline

#endif

const	reel&	Camera::Hmax () const { return(hmax); }



#ifdef INLINE

inline

#endif

const	reel&	Camera::Xmin () const { return(xmin); }

#ifdef INLINE

inline

#endif

const	reel&	Camera::Xmax () const { return(xmax); }

#ifdef INLINE

inline

#endif

const	reel&	Camera::Ymin () const { return(ymin); }

#ifdef INLINE

inline

#endif

const	reel&	Camera::Ymax () const { return(ymax); }



#ifdef INLINE

inline

#endif

void	Camera::PR (const point& p) { pr=p; }

#ifdef INLINE

inline

#endif

void	Camera::PO (const point& p) { pr=p-d0*vn; }



#ifdef INLINE

inline

#endif

void	Camera::VN (const vecteur& v) { vn=v; vn.normalise(); }

#ifdef INLINE

inline

#endif

void	Camera::VH (const vecteur& v) { vh=v; }



#ifdef INLINE

inline

#endif

void	Camera::DV (const reel& d) { dv=d; }

#ifdef INLINE

inline

#endif

void	Camera::DO (const reel& d) { d0=d; }

#ifdef INLINE

inline

#endif

void	Camera::DH (const reel& d) { dh=d; }

#ifdef INLINE

inline

#endif

void	Camera::DY (const reel& d) { dy=d; }



#ifdef INLINE

inline

#endif

void	Camera::Pmin (const reel& d) { pmin=d; }

#ifdef INLINE

inline

#endif

void	Camera::Pmax (const reel& d) { pmax=d; }

#ifdef INLINE

inline

#endif

void	Camera::Hmin (const reel& d) { hmin=d; }

#ifdef INLINE

inline

#endif

void	Camera::Hmax (const reel& d) { hmax=d; }



#ifdef INLINE

inline

#endif

void	Camera::Xmin (const reel& d) { xmin=d; }

#ifdef INLINE

inline

#endif

void	Camera::Xmax (const reel& d) { xmax=d; }

#ifdef INLINE

inline

#endif

void	Camera::Ymin (const reel& d) { ymin=d; }

#ifdef INLINE

inline

#endif

void	Camera::Ymax (const reel& d) { ymax=d; }



#ifdef INLINE

inline

#endif

void	Camera::fenetre (const reel& d1, const reel& d2, const reel& d3, const reel& d4) 

{ 

	pmin=d1; 

	pmax=d2; 

	hmin=d3; 

	hmax=d4; 

}

#ifdef INLINE

inline

#endif

void	Camera::cloture (const reel& d1, const reel& d2, const reel& d3, const reel& d4) { xmin=d1; xmax=d2; ymin=d3; ymax=d4; }



void	Camera::perspective (booleen b) { persp=b; }

booleen	Camera::perspective () const { return persp; }



void Camera::LockVH(int v)
{
	lockvh = v;
}


void Camera::Step (const reel& s)
{
	step = s;
}

void Camera::Down()
{
	point	pr;
	vecteur	vn,vh,vd;

	pr = PR();
	vn = VN();
	vh = VH();
	vd = (vn^vh).unitaire();

	if ( !prmode ) 

	{
		t = Rotation (PO(),vd,ANGLE);
		PR(t.transforme(pr));
	} 

	else

		t = Rotation (pr,vd,ANGLE);

	VN(t.transforme(vn));
	if (!lockvh) 

		VH(t.transforme(vh));
}

void Camera::Up()
{
	point	pr;
	vecteur	vn,vh,vd;

	pr = PR();
	vn = VN();
	vh = VH();
	vd = (vn^vh).unitaire();

	if (!prmode) 

	{
		t = Rotation (PO(),vd,-ANGLE);
		PR(t.transforme(pr));
	} 

	else 

		t = Rotation (pr,vd,-ANGLE);

	VN(t.transforme(vn));
	if (!lockvh) 

		VH(t.transforme(vh));
}

void Camera::Left()

{

	point	pr;

	vecteur	vn,vh,vd;



	pr = PR();

	vn = VN();

	vh = VH();



	if (!prmode) 

	{

		t = Rotation (PO(),vh,-ANGLE);

		PR(t.transforme(pr));

	} 

	else 

		t = Rotation (pr,vh,-ANGLE);



	VN(t.transforme(vn));

}



void Camera::Right()

{

	point	pr;

	vecteur	vn,vh,vd;



	pr = PR();

	vn = VN();

	vh = VH();



	if (!prmode) 

	{

		t = Rotation (PO(),vh,ANGLE);

		PR(t.transforme(pr));

	} 

	else 

		t = Rotation (pr,vh,ANGLE);



	VN(t.transforme(vn));

}



void Camera::AntiHoraire()
{
	if (!lockvh) {
		point	pr;
		vecteur	vn,vh,vd;

		pr = PR ();
		vn = VN ();
		vh = VH ();

		t = Rotation (pr,vn,ANGLE);

		VH(t.transforme(vh));
	}
}

void Camera::Horaire()
{
	if (!lockvh) {
		point	pr;
		vecteur	vn,vh,vd;

		pr = PR ();
		vn = VN ();
		vh = VH ();

		t = Rotation (pr,vn,-ANGLE);

		VH(t.transforme(vh));
	}
}

void Camera::Front()
{

//	reel s = pow(2,step);

	reel s = step;


	if (prmode) 

	{
		DO(DO () + s);
		DV(DV () + s);
		DH(DH () + s);
		DY(DY () + s);
	} 

	else 

		PR(PR () + s*VN());
}

void Camera::Back()
{
//	reel s = pow(2,step);

	reel s = step;



	if (prmode) 

	{
		DO(DO () - s);
		DV(DV () - s);
		DH(DH () - s);
		DY(DY () - s);
	} 

	else 

		PR(PR () - s*VN());
}


void Camera::Pas(int v)
{

	step = pow(2.0,v);
}

void Camera::DOplus()
{
	if ((DO()+ step + 0.001) < DV()) 

	{
		DO(DO () + step);
	}
}

void Camera::DOmoins()
{
	DO(DO () - step);

}

void Camera::DVmoins()
{
	if ((DV() - step - 0.001) > DO()) 

	{
		DV(DV () - step);
	}
}

void Camera::DVplus()
{
	DV(DV () + step);

}

void Camera::PRmode(int v)
{
	prmode = v;
}


void Camera::FenetreMul2()

{

	reel	x = (Pmax()+Pmin())/2;

	reel	y = (Hmax()+Hmin())/2;

	reel	dx = (Pmax()-Pmin())/2;

	reel	dy = (Hmax()-Hmin())/2;



	fenetre(x-2*dx, x+2*dx, y-2*dy, y+2*dy);

}



void Camera::FenetreDiv2()

{

	reel	x = (Pmax()+Pmin())/2;

	reel	y = (Hmax()+Hmin())/2;

	reel	dx = (Pmax()-Pmin())/2;

	reel	dy = (Hmax()-Hmin())/2;



	fenetre(x-dx/2, x+dx/2, y-dy/2, y+dy/2);

}



//--------------------

//Gestion des lumières

//--------------------

void Camera::AddLumiere( Lumiere* lum )

{

	if ( m_nNbLumiere < NB_MAX_LUMIERE )

	{

		m_Lumiere[m_nNbLumiere] = lum;

		m_nNbLumiere++;



		m_bAvecLumiere = VRAI;

	}

}



const Lumiere* Camera::GetLumiere(entier i) const

{
	assert(i >= 0);

	assert(i < m_nNbLumiere);



	return m_Lumiere[i];
}



const entier& Camera::NbLumiere() const

{

	return m_nNbLumiere;

}



const booleen& Camera::AvecLumiere() const

{

	return m_bAvecLumiere;

}



const booleen& Camera::LumiereActiveScene() const

{

	return m_bLumiereActiveScene;

}



void Camera::LumiereActiveScene(const booleen& v)

{

	m_bLumiereActiveScene = v;

}



const booleen& Camera::LumiereActive(const int& i) const

{

	assert(i >= 0);

	assert(i < m_nNbLumiere);



	return m_Lumiere[i]->Active();

}



void Camera::ActiverLumiere(const int& i, const booleen& v)

{

	assert(i >= 0);

	assert(i < m_nNbLumiere);



	m_Lumiere[i]->Active(v);

	if ( v )

	{

		if ( !m_bAvecLumiere ) m_bAvecLumiere = VRAI;

	}

	else

	{

		//Check pour voir s'il y a une lumiere d'allumee

		m_bAvecLumiere = FAUX;

		for(int j = 0 ; j < m_nNbLumiere; j++)

		{

			if ( m_Lumiere[j]->Active() )

			{

				m_bAvecLumiere = VRAI;

				break;

			}

		}

	}

}



//*********** Modifier >>>>>>>>>>>
const Couleur& Camera::IntensiteAmbiante(const int& i) const

{

	assert(i >= 0);

	assert(i < m_nNbLumiere);



	return m_Lumiere[i]->IntensiteAmbiante();

}



const Couleur& Camera::Intensite(const int& i) const

{

	assert(i >= 0);

	assert(i < m_nNbLumiere);



	return m_Lumiere[i]->Intensite();

}



void Camera::IntensiteAmbiante(const int& i, Couleur c)

{

	assert(i >= 0);

	assert(i < m_nNbLumiere);



	m_Lumiere[i]->IntensiteAmbiante(c);

}



void Camera::Intensite(const int& i, Couleur c)

{

	assert(i >= 0);

	assert(i < m_nNbLumiere);



	m_Lumiere[i]->Intensite(c);

}
//<<<<<<<<<<< Modifier ***********



const point& Camera::Position(const int& i) const

{

	assert(i >= 0);

	assert(i < m_nNbLumiere);



	return m_Lumiere[i]->Position();

}



void Camera::Position(const int& i, const point& p)

{

	assert(i >= 0);

	assert(i < m_nNbLumiere);



	m_Lumiere[i]->Position(p);

}