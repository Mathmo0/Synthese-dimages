//*******************************************************************
//*																	*
//* Programme: fichier.h											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Implantation de la classe Fichier. Gestion de la lecture et	*
//*		l'écriture des fichiers sur disque.							*
//*																	*
//*******************************************************************
#pragma warning(disable : 4996)
#include "fichier.h"

//----------------------------------------
//Test l'existance d'un fichier sur disque
//----------------------------------------
booleen FichierExistant(char nom[])
{
	FILE* fp;
	if ( (fp = fopen(nom,"r")) == NULL )
		return FAUX;

	fclose(fp);
	return VRAI;
}

//*******************************************************************
//Fonctions pour l'ouverture du fichier
//*******************************************************************
booleen	Fichier::Open(char *n, char *p)
{
	f = fopen(n,p);
	neuf = VRAI;
	return f != NULL;
}

//*******************************************************************
//Fonctions pour la fermeture du fichier
//*******************************************************************
void	Fichier::Close()
{
	fclose(f);
}

//*******************************************************************
//Fonctions pour la lecture dans le fichier
//*******************************************************************
booleen	Fichier::carac(char& c)
{
	neuf = FAUX;
	c = getc(f);

	return VRAI;
}

booleen	Fichier::mentier(entier& ent)
{
	neuf = FAUX;

	int rep = fscanf(f, "%d", &ent);
	if ( rep == EOF || !rep )
		return FAUX;

	return VRAI;
}

booleen	Fichier::mreel(reel& r)
{
	neuf = FAUX;


	int rep = fscanf(f, "%lf", &r);
	if ( rep == EOF || !rep )
		return FAUX;

	return VRAI;
}

booleen	Fichier::mchaine(chaine& c)
{
	neuf = FAUX;
	char	s[100];
	int rep = fscanf(f, "%s", s);
	c = s;

	if ( rep == EOF || !rep )
		return FAUX;

	return VRAI;
}

//*******************************************************************
//Fonctions pour l'écriture dans le fichier
//*******************************************************************
void	Fichier::Wcarac(char c)
{
	neuf = FAUX;
	fputc(c, f);
}

void	Fichier::Wentier(entier i)
{
	neuf = FAUX;
	fprintf(f, "%d", i);
}

void	Fichier::Wreel(reel r)
{
	neuf = FAUX;
	long pe = long(r+0.5);
	reel dx = pe - r;
	if (dx<EPS && dx>-EPS) r = pe;
	fprintf(f, "%.30lg", double(r));
}

void	Fichier::Wchaine(chaine s)
{
	neuf = FAUX;
	fprintf(f, "%s", s.C());
}

//*******************************************************************
//Fonctions pour l'interrogation de l'etat du pointeur dans le fichier
//*******************************************************************
booleen	Fichier::debut()
{
	return neuf;
}

booleen	Fichier::fin()
{
	return feof(f);
}
