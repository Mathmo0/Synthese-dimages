//*******************************************************************

//*																	*

//* Programme: definitino.h											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Programme principal pour le noyau 3D.						*

//*																	*

//*******************************************************************



//-------------------------------------------------------------------

//Definition des booleens, VRAI et FAUX

//-------------------------------------------------------------------

#ifndef _BOOLEEN

#define _BOOLEEN

	typedef	int	booleen;



	extern const booleen FAUX;

	extern const booleen VRAI;

#endif



//-------------------------------------------------------------------

//Definition des entiers

//-------------------------------------------------------------------

#ifndef _ENTIER

#define _ENTIER

	typedef	int	entier;

#endif



//-------------------------------------------------------------------

//Definition des reels

//-------------------------------------------------------------------

#ifndef _REEL

#define _REEL

	typedef	double reel;



	extern const reel EPS;

	extern const reel INFINI;

#endif





//-------------------------------------------------------------------

//Definition des trinary

//-------------------------------------------------------------------

#ifndef _TRINARY

#define _TRINARY

	typedef	int	trinary;



	extern const trinary AUCUN;

#endif



//-------------------------------------------------------------------

//Definition de PI

//-------------------------------------------------------------------

#undef	PI

#define	PI	3.14159265359





#ifndef _TYPE_SELECTION

#define _TYPE_SELECTION



typedef int TYPE_SELECTION;

#define AUCUNE_SELECTION		0

#define OBJET_SELECTION			1

#define COMPOSANTE_SELECTION	2



#endif