//*******************************************************************

//*																	*

//* Programme: canon.cpp											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation des transformations canoniques.				*

//*																	*

//*******************************************************************


#include "canon.h"
#include "mat.h"
#include "utilalg.h"
#include "erreur.h"

#ifdef INLINE
inline
#endif
Transformation	Translation (const vecteur& v)
/* Retourne la transformation lineaire d'une translation selon v. */
{
	return Transformation(Mat_Translation (v.x(),v.y(),v.z()), Mat_Translation (-v.x(),-v.y(),-v.z()));
}


#ifdef INLINE
inline
#endif
Transformation	Homo_X (const reel& s)
/* Retourne la transformation lineaire d'un changement d'echelle selon l'axe X. */
{
	return Transformation(Mat_Homo_X (s), Mat_Homo_X (1.0/s));
}

#ifdef INLINE
inline
#endif
Transformation	Homo_Y (const reel& s)
/* Retourne la transformation lineaire d'un changement d'echelle selon l'axe Y. */
{
	return Transformation(Mat_Homo_Y (s), Mat_Homo_Y (1.0/s));
}

#ifdef INLINE
inline
#endif
Transformation	Homo_Z (const reel& s)
/* Retourne la transformation lineaire d'un changement d'echelle selon l'axe Z. */
{
	return Transformation(Mat_Homo_Z (s), Mat_Homo_Z (1.0/s));
}

#ifdef INLINE
inline
#endif
Transformation	Rot_X (const reel& a)
/* Retourne la transformation lineaire d'une rotation de a degres autour de l'axe X. */
{
	return Transformation(Mat_Rot_X (a), Mat_Rot_X (-a));
}


#ifdef INLINE
inline
#endif
Transformation	Rot_Y (const reel& a)
/* Retourne la transformation lineaire d'une rotation de a degres autour de l'axe Y. */
{
	return Transformation(Mat_Rot_Y (a), Mat_Rot_Y (-a));
}


#ifdef INLINE
inline
#endif
Transformation	Rot_Z (const reel& a)
/* Retourne la transformation lineaire d'une rotation de a degres autour de l'axe Z. */
{
	return Transformation(Mat_Rot_Z (a), Mat_Rot_Z (-a));
}


#ifdef INLINE
inline
#endif
Transformation	Cis_X (const vecteur& w)
/* Retourne la transformation lineaire d'un cisaillement selon l'axe X. */
{
	return Transformation(Mat_Cis_X (w.x(),w.y(),w.z()), Mat_Cis_X (-w.x()/(1.0+w.x()),-w.y()/(1.0+w.x()),-w.z()/(1.0+w.x())));
}

#ifdef INLINE
inline
#endif
Transformation	Cis_Y (const vecteur& w)
/* Retourne la transformation lineaire d'un cisaillement selon l'axe Y. */
{
	return Transformation(Mat_Cis_Y (w.x(),w.y(),w.z()), Mat_Cis_Y (-w.x()/(1.0+w.y()),-w.y()/(1.0+w.y()),-w.z()/(1.0+w.y())));
}

#ifdef INLINE
inline
#endif
Transformation	Cis_Z (const vecteur& w)
/* Retourne la transformation lineaire d'un cisaillement selon l'axe Z. */
{
	return Transformation(Mat_Cis_Z (w.x(),w.y(),w.z()), Mat_Cis_Z (-w.x()/(1.0+w.z()),-w.y()/(1.0+w.z()),-w.z()/(1.0+w.z())));
}


#ifdef INLINE
inline
#endif
Transformation	Rot_sincos(const vecteur& v, const reel& s, const reel& c)
/* Retourne la transformation lineaire d'une rotation de a degres autour
   d'un vecteur v (horaire vu dans la direction de v) etant donnes le
   cosinus et le sinus de l'angle de rotation. */
{
	return Transformation(Mat_Rotsincos (v,s,c), Mat_Rotsincos (v,-s,c));	
}


Transformation	Base_Ortho (const vecteur& v1, const vecteur& v2, const vecteur& v3)
/* Retourne la transformation lineaire effectuant un changement de base
de la base canonique a la base orthogonale [v1,v2,v3]. */
{
	matrice mi = Mat_Change_Base (v1,v2,v3);
	matrice	m = mi;
	m.transpose();
	return Transformation(m,mi);
}

Transformation	Base (const vecteur& v1, const vecteur& v2, const vecteur& v3)
/* Retourne la transformation lineaire effectuant un changement de base
de la base canonique a la base vectoriel [v1,v2,v3]. */
{
	matrice mi = Mat_Change_Base (v1,v2,v3);
	matrice	m;
	if (!mi.inverse(&m)) Erreur(1, "");
	return Transformation(m,mi);
}

Transformation	Repere_Ortho (const point& o, const vecteur& v1, const vecteur& v2, const vecteur& v3)
/* Retourne la transformation lineaire effectuant un changement de repere
du repere canonique au repere orthogonal [o,v1,v2,v3]. */
{
	return Base_Ortho (v1,v2,v3) * Translation (O-o);
}

Transformation	Repere (const point& o, const vecteur& v1, const vecteur& v2, const vecteur& v3)
/* Retourne la transformation lineaire effectuant un changement de repere
du repere canonique au repere [o,v1,v2,v3]. */
{
	return Base (v1,v2,v3) * Translation (O-o);
}

