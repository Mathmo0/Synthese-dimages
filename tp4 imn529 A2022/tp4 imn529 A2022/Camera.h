// *******************************************************************

// *                                                                 *

// * Programme: camera.h                                             *

// *                                                                 *

// *******************************************************************

// *                                                                 *

// * Description:                                                    *

// *  Implantation de la caméra. Permet de définir le volume de      *

// *  vision de l'usager (déplacer la camera)                        *                                             *

// *                                                                 *

// *******************************************************************



#ifndef _CAMERA

#define _CAMERA



#include "definition.h"

#include "transfo.h"

#include "lumiere.h"		//Lumiere

#include "spotlight.h"


#define	ANGLE	0.104719755

#define NB_MAX_LUMIERE		8



class Camera 

{

private:

	point	pr;

	vecteur	vn,vh;

	reel	pmin,pmax,hmin,hmax;

	reel	xmin,xmax,ymin,ymax;

	reel	dv,d0,dy,dh;



	booleen	persp;

	reel	step;

	booleen	lockvh;

	booleen	prmode;

	Transformation t;



	booleen m_bLumiereActiveScene;	//Indique si on met les lumieres dans la scene

	booleen	m_bAvecLumiere;			//Indique si au moins un 1 lumiere est active

	entier	m_nNbLumiere;			//Nombre de lumieres


	Lumiere *m_Lumiere[8];		    //On peut avoir jusqu'a 8 lumieres



public:

	Camera();

	~Camera() {}



	Camera(const Camera& c);

	void operator=(const Camera& c);



public:		//Disposition de la caméra

	const	point&	PR() const;

	void	PR(const point&);



	point	PO() const;

	void	PO(const point&);



	const	vecteur&	VN() const;

	void	VN(const vecteur&);



	const	vecteur&	VH() const;

	void	VH(const vecteur&);



	const	reel&	DV() const;

	void	DV(const reel&);



	const	reel&	DO() const;

	void	DO(const reel&);



	const	reel&	DH() const;

	void	DH(const reel&);



	const	reel&	DY() const;

	void	DY(const reel&);



	void	perspective(booleen);

	booleen	perspective() const;



	const	reel&	Xmin() const;

	void	Xmin(const reel&);



	const	reel&	Xmax() const;

	void	Xmax(const reel&);



	const	reel&	Ymin() const;

	void	Ymin(const reel&);



	const	reel&	Ymax() const;

	void	Ymax(const reel&);



	void	fenetre(const reel&, const reel&, const reel&, const reel&);



	const	reel&	Pmin() const;

	void	Pmin(const reel&);



	const	reel&	Pmax() const;

	void	Pmax(const reel&);



	const	reel&	Hmin() const;

	void	Hmin(const reel&);



	const	reel&	Hmax() const;

	void	Hmax(const reel&);



	void	cloture(const reel&, const reel&, const reel&, const reel&);



public:		//Déplacement de la caméra

	void	Step(const reel&);	

	void	LockVH(int);		

	void	Down();				

	void	Up();				

	void	Left();				

	void	Right();			

	void	AntiHoraire();		

	void	Horaire();			

	void	Front();			

	void	Back();				

	void	Pas(int);			

	void	DOplus();			

	void	DOmoins();			

	void	DVplus();			

	void	DVmoins();			

	void	PRmode(int);		



	int GetVHFixe() { return lockvh; }

	int GetPRFixe() { return prmode; }

	double GetPas() { return step; }



	void FenetreMul2();

	void FenetreDiv2();



public:	//Lumières

	//Ajout et acces aux lumieres

	void AddLumiere( Lumiere* lum );

	const Lumiere* GetLumiere(entier i) const;



	//Retourne le nombre de lumieres (0 - 8)

	const entier& NbLumiere() const;

	//Retourne VRAI s'il y a au moins une lumiere qui est active

	const booleen& AvecLumiere() const;



	//Retourne VRAI si les lumieres de la scenes sont actives. On peut les desactiver ou

	//les activer tous en meme temps.

	const booleen& LumiereActiveScene() const;

	void LumiereActiveScene(const booleen& v);



	//Permet d'activer ou desactiver une lumiere precise de la scene

	const booleen& LumiereActive(const int& i) const;

	void ActiverLumiere(const int& i, const booleen& v);



	//Permet de modifier et d'obtenir les couleurs ambiantes et diffuses d'une lumiere


//*********** à Modifier >>>>>>>>>>>
	const Couleur& IntensiteAmbiante(const int& i) const;

	const Couleur& Intensite(const int& i) const;

	void IntensiteAmbiante(const int& i, Couleur c);

	void Intensite(const int& i, Couleur c);
//<<<<<<<<<<< Modifier ***********



	//Permet d'obtenir et modifier la position d'une lumiere

	const point& Position(const int& i) const;

	void Position(const int& i, const point& p);

};



#endif






