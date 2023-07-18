//*******************************************************************

//*																	*

//* Programme: mat.h												*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Définition des matrices des transformations.				*

//*																	*

//*******************************************************************



#include "definition.h"
#include "alg.h"

matrice	Mat_Translation (const reel& dx, const reel& dy, const reel& dz);
matrice	Mat_Homo_X (const reel& s);
matrice	Mat_Homo_Y (const reel& s);
matrice	Mat_Homo_Z (const reel& s);
matrice	Mat_Rot_X (const reel& a);
matrice	Mat_Rot_Y (const reel& a);
matrice	Mat_Rot_Z (const reel& a);
matrice	Mat_Cis_X (const reel& w1, const reel& w2, const reel& w3);
matrice	Mat_Cis_Y (const reel& w1, const reel& w2, const reel& w3);
matrice	Mat_Cis_Z (const reel& w1, const reel& w2, const reel& w3);
matrice	Mat_Change_Base (const vecteur& v1, const vecteur& v2, const vecteur& v3);
/* Retourne la matrice de transformation effectuant un changement de base
   de la base canonique a la base vectoriel [v1,v2,v3]. */
matrice	Mat_Rotsincos (const vecteur& v, const reel& sina, const reel& cosa);
matrice	Mat_Symetrie (const plan& p);

