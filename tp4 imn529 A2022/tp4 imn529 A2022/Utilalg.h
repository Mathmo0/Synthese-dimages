    //*******************************************************************

//*																	*

//* Programme: utilreel.h											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Définition d'opérateurs utilitaires algébriques				*

//*																	*

//*******************************************************************



#include "alg.h"


booleen	operator==(const vecteur &v, const vecteur &u);

booleen operator==(const point &p, const point &q);

reel	operator*(const vecteur &v, const vecteur &u);
/* produit scalaire x = v1 * v2 */

vecteur	operator^(const vecteur &v, const vecteur &u);
/* produit vectoriel v = v1 X v2 */

vecteur	operator*(const vecteur &v, const reel &k);
/* produit par un scalaire v2 = v1 * k */

vecteur	operator*(const reel &k, const vecteur &v);
/* produit par un scalaire v2 = k * v1 */

vecteur	operator+(const vecteur &v, const vecteur &u);

point	operator+(const point &p, const vecteur &u);

point	operator-(const point &p, const vecteur &u);

point	operator+(const vecteur &u, const point &p);

vecteur	operator-(const vecteur &v);

vecteur	operator-(const vecteur &v, const vecteur &u);

vecteur	operator-(const point &p, const point &q);


point   operator*(const point& p, const droite& d);
 
vecteur	operator-(const point& p, const droite& d);
 
point   operator*(const point& pt, const plan& pl);
 
vecteur	operator-(const point& pt, const plan& pl);
 
point   operator*(const droite& d1, const droite& d2);
/* le point appartient a d2 */
 
vecteur	operator-(const droite& d1, const droite& d2) ;
 
point	operator*(const droite& d, const plan& p);
 
vecteur	operator-(const droite& d, const plan& p);
 
droite  operator*(const plan& p1, const plan& p2);
 
vecteur	operator-(const plan& p1, const plan& p2);
 
