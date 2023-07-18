//*******************************************************************

//*																	*

//* Programme: chaine.cpp											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation des chaines de caractères						*

//*																	*

//*******************************************************************


#include "chaine.h"

chaine::chaine()
{
	i = 0;
}

chaine::chaine(char *c)
{
	i = 0;
	while (*c != '\0') s[i++] = *c++;
}

booleen	chaine::operator==(chaine &c)
{
	if (i != c.i) return FAUX;

	short	j = 0;

	while (s[j] == c.s[j] && j<i) j++;

	return j == i;
}

char	*chaine::C()
{
	s[i] = '\0';
	return s;
}

