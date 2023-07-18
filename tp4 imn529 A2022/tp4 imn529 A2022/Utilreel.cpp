//*******************************************************************

//*																	*

//* Programme: utilreel.cpp											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation de fonctions de comparaison pour les reel		*

//*		a une petite valeur pres(EPSILONE)							*

//*																	*

//*******************************************************************


#include "utilreel.h"

booleen pg(const reel&b, const reel&a)
{
	return(b - a > EPS);
}

booleen pp(const reel&b, const reel&a)
{
	return(b - a < -EPS);
}

booleen pge(const reel&b, const reel&a)
{
	return(b - a >= -EPS);
}

booleen ppe(const reel&b, const reel&a)
{
	return(b - a <= EPS);
}

booleen eg(const reel&b, const reel&a)
{
	return(pge(b,a)&&ppe(b,a));
}

booleen neg(const reel&b, const reel&a)
{
	return( pg(b,a) || pp(b,a) );
}


