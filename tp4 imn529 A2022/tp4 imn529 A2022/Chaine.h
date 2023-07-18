//*******************************************************************

//*																	*

//* Programme: chaine.h												*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Définition des chaines de caractères						*

//*																	*

//*******************************************************************


#ifndef _CHAINE
#define _CHAINE

#include "definition.h"

class	chaine 

{
	char	s[100];
	short	i;


public:
	chaine();
	chaine(char *);

	char *	C();

	booleen	operator==(chaine &);
};

#endif

