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
	chaine(const char *);

	char *	C();

	booleen	operator==(const chaine &) const;
};

#endif

