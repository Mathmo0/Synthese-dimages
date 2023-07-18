//*******************************************************************

//*																	*

//* Programme: mat.cpp												*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation des matrices des transformations.				*

//*																	*

//*******************************************************************


#include "mat.h"
#include <cmath>

/* MATRICES DE TRANSFORMATION */

matrice	Mat_Translation (const reel& dx, const reel& dy, const reel& dz)
/* Retourne la matrice de transformation d'une translation selon v. */
{
	matrice	m = I;
	m.e(1, 4) = dx;
	m.e(2, 4) = dy;
	m.e(3, 4) = dz;
	return m;
}

matrice	Mat_Homo_X (const reel& s)
/* Retourne la matrice de transformation d'un changement d'echelle selon l'axe X. */
{
	matrice	m = I;
	m.e(1, 1) = s;
	return m;
}

matrice	Mat_Homo_Y (const reel& s)
/* Retourne la matrice de transformation d'un changement d'echelle selon l'axe Y. */
{
	matrice	m = I;
	m.e(2, 2) = s;
	return m;
}

matrice	Mat_Homo_Z (const reel& s)
/* Retourne la matrice de transformation d'un changement d'echelle selon l'axe Z. */
{
	matrice	m = I;
	m.e(3, 3) = s;
	return m;
}

matrice	Mat_Rot_X (const reel& a)
/* Retourne la matrice de transformation d'une rotation de a degres autour de l'axe X. */
{
	matrice	m = I;
	m.e(2, 2) = cos(a);
	m.e(2, 3) = -sin(a);
	m.e(3, 2) = -m.e(2, 3);
	m.e(3, 3) = m.e(2, 2);
	return m;
}

matrice	Mat_Rot_Y (const reel& a)
/* Retourne la matrice de transformation d'une rotation de a degres autour de l'axe Y. */
{
	matrice	m = I;
	m.e(1, 1) = cos(a);
	m.e(1, 3) = sin(a);
	m.e(3, 1) = -m.e(1, 3);
	m.e(3, 3) = m.e(1, 1);
	return m;
}

matrice	Mat_Rot_Z (const reel& a)
/* Retourne la matrice de transformation d'une rotation de a degres autour de l'axe Z. */
{
	matrice	m = I;
	m.e(1, 1) = cos(a);
	m.e(1, 2) = -sin(a);
	m.e(2, 1) = -m.e(1, 2);
	m.e(2, 2) = m.e(1, 1);
	return m;
}


matrice	Mat_Cis_X (const reel& w1, const reel& w2, const reel& w3)
/* Retourne la matrice de transformation d'un cisaillement selon l'axe X. */
{
	matrice	m = I;
	m.e(1, 1) = 1.0+w1;
	m.e(2, 1) = w2;
	m.e(3, 1) = w3;
	return m;
}

matrice	Mat_Cis_Y (const reel& w1, const reel& w2, const reel& w3)
/* Retourne la matrice de transformation d'un cisaillement selon l'axe Y. */
{
	matrice	m = I;
	m.e(1, 2) = w1;
	m.e(2, 2) = 1.0+w2;
	m.e(3, 2) = w3;
	return m;
}

matrice	Mat_Cis_Z (const reel& w1, const reel& w2, const reel& w3)
/* Retourne la matrice de transformation d'un cisaillement selon l'axe Z. */
{
	matrice	m = I;
	m.e(1, 3) = w1;
	m.e(2, 3) = w2;
	m.e(3, 3) = 1.0+w3;
	return m;
}

matrice	Mat_Change_Base (const vecteur& v1, const vecteur& v2, const vecteur& v3)
/* Retourne la matrice de transformation effectuant un changement de base
   de la base vectoriel (v1,v2,v3) a la base canonique. */
{
	matrice	m;
	m.e(1, 1) = v1.x(); m.e(1, 2) = v2.x(); m.e(1, 3) = v3.x(); m.e(1, 4) = 0.0;
	m.e(2, 1) = v1.y(); m.e(2, 2) = v2.y(); m.e(2, 3) = v3.y(); m.e(2, 4) = 0.0;
	m.e(3, 1) = v1.z(); m.e(3, 2) = v2.z(); m.e(3, 3) = v3.z(); m.e(3, 4) = 0.0;
	return m;
}

matrice	Mat_Rotsincos (const vecteur& v, const reel& sina, const reel& cosa)           
/* Retourne la matrice de transformation d'une rotation de a degres autour
   d'un vecteur v (horaire vu dans la direction de v) etant donnes le
   cosinus et le sinus de l'angle de rotation. */
{
	reel	vx,vy,vz;

	v.unitaire().composantes (&vx,&vy,&vz);
	matrice	m = I;
	m.e(1, 1) = cosa*(1.0-vx*vx) + vx*vx;
	m.e(1, 2) = (1.0-cosa)*vx*vy - sina*vz;
	m.e(1, 3) = (1.0-cosa)*vx*vz + sina*vy;
	m.e(2, 1) = (1.0-cosa)*vx*vy + sina*vz;
	m.e(2, 2) = cosa*(1.0-vy*vy) + vy*vy;
	m.e(2, 3) = (1.0-cosa)*vy*vz - sina*vx;
	m.e(3, 1) = (1.0-cosa)*vx*vz - sina*vy;
	m.e(3, 2) = (1.0-cosa)*vy*vz + sina*vx;
	m.e(3, 3) = cosa*(1.0-vz*vz) + vz*vz;
	return m;
}

matrice	Mat_Symetrie (const plan& p)
/* Retourne la matrice de transformation d'une symetrie selon un plan p. */
{
	reel	a,b,c,d;

	matrice	m = I;
	/* pt' := pt - (2*p*pt)/(N*N) * N */
	p.abcd (&a,&b,&c,&d);
	m.e(1, 1) = 1.0-2.0*a*a; m.e(1, 2) = -2.0*a*b; m.e(1, 3) = -2.0*a*c; m.e(1, 4) = -2.0*a*d;
	m.e(2, 1) = -2.0*b*a; m.e(2, 2) = 1.0-2.0*b*b; m.e(2, 3) = -2.0*b*c; m.e(2, 4) = -2.0*b*d;
	m.e(3, 1) = -2.0*c*a; m.e(3, 2) = -2.0*c*b; m.e(3, 3) = 1.0-2.0*c*c; m.e(3, 4) = -2.0*c*d;
	return m;
}

