//*******************************************************************

//*																	*

//* Programme: erreur.cpp											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation des fonctions de gestion des erreurs.			*

//*																	*

//*******************************************************************


#include <cstdio>

#include <cstdlib>
#include "erreur.h"


//Declaration du tableau contenant les erreurs
static	char	*ERR[20] = 

{
			"Fichier %s inexistant.\r\n",
			"Type d'objet inconnu.\r\n",
			"Impossible de decouper un polygone.\r\n",
			"\n",
			"\n",
			"Affichage impossible (Debut_Graphique?).\r\n",
			"Type inconnu, %s.\r\n",
			"Transformation inconnue, %s.\r\n",
			"Memoire insuffisante.\r\n",
			"Indice de composante invalide.\r\n",
			"Composante inexistante.\r\n",
			"Indice de sommet invalide.\r\n",
			"Sommet inexistant.\r\n",
			"Transformation d'un objet indefini.\r\n",
			"Destruction d'un objet indefini.\r\n",
			"Fin de fichier dans un commentaire.\r\n",
			"Attribut de centre non defini.\r\n",
			"Attribut de couleur non defini.\r\n",
			"Impossible de decouper un objet.\r\n",
			"Volume.\r\n",
};


void _Erreur(const entier& n, char *s, int ligne, char *file)
{

	fprintf(stderr, "Erreur dans le module %s, ligne %d: ", file,ligne);

	fprintf(stderr, ERR[n-1], s);

//	exit(1);
}
