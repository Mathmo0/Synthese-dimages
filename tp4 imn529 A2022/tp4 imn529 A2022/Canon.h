//*******************************************************************

//*																	*

//* Programme: canon.h												*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Définition des transformations canoniques.					*

//*																	*

//*******************************************************************


#include "alg.h"

#include "definition.h"	

#include "transfo.h"

/* TRANSFORMATIONS LINEAIRES CANONIQUES */

Transformation	Translation (const vecteur& v);
/* Retourne la transformation lineaire d'une translation selon v. */

Transformation	Homo_X (const reel& s);
/* Retourne la transformation lineaire d'un changement d'echelle selon l'axe X. */
Transformation	Homo_Y (const reel& s);
/* Retourne la transformation lineaire d'un changement d'echelle selon l'axe Y. */
Transformation	Homo_Z (const reel& s);
/* Retourne la transformation lineaire d'un changement d'echelle selon l'axe Z. */

Transformation	Rot_X (const reel& a);
/* Retourne la transformation lineaire d'une rotation de a radians autour de l'axe X. */
Transformation	Rot_Y (const reel& a);
/* Retourne la transformation lineaire d'une rotation de a radians autour de l'axe Y. */
Transformation	Rot_Z (const reel& a);
/* Retourne la transformation lineaire d'une rotation de a radians autour de l'axe Z. */

Transformation	Cis_X (const vecteur& w);
/* Retourne la transformation lineaire d'un cisaillement selon l'axe X. */
Transformation	Cis_Y (const vecteur& w);
/* Retourne la transformation lineaire d'un cisaillement selon l'axe Y. */
Transformation	Cis_Z (const vecteur& w);
/* Retourne la transformation lineaire d'un cisaillement selon l'axe Z. */

Transformation	Rot_sincos(const vecteur& v, const reel& s, const reel& c);
/* Retourne la transformation lineaire d'une rotation de a radians autour
   d'un vecteur v (horaire vu dans la direction de v) etant donnes le
   cosinus et le sinus de l'angle de rotation. */

Transformation	Base_Ortho (const vecteur& v1, const vecteur& v2, const vecteur& v3);
/* Retourne la transformation lineaire effectuant un changement de base
   de la base canonique a la base orthogonale [v1,v2,v3]. */

Transformation	Base (const vecteur& v1, const vecteur& v2, const vecteur& v3);
/* Retourne la transformation lineaire effectuant un changement de base
   de la base canonique a la base vectoriel [v1,v2,v3]. */

Transformation	Repere_Ortho (const point& o, const vecteur& v1, const vecteur& v2, const vecteur& v3);
/* Retourne la transformation lineaire effectuant un changement de repere
   du repere canonique au repere orthogonal [o,v1,v2,v3]. */

Transformation	Repere (const point& o, const vecteur& v1, const vecteur& v2, const vecteur& v3);
/* Retourne la transformation lineaire effectuant un changement de repere
   du repere canonique au repere [o,v1,v2,v3]. */
