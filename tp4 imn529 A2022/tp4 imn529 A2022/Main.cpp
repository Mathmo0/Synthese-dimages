//*******************************************************************
//*																	*
//* Programme: main.cpp												*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Programme principal pour le noyau 3D.						*
//*																	*
//*******************************************************************

#include <stdlib.h>					//exit()
#include "Parser.h"					//Transcriveur des .scn et .vsn
#include "cgApplication.h"
#include "FenetrePrincipale.h"
#include "FenetreCamera.h"
#include "FenetreSetting.h"
#include "FenetreDesignateur.h"
#include "FenetreTransformation.h"
#include "FenetreLumiere.h"
#include "FenetreAnimation.h"
#include "Definition.h"
#include "fichier.h"

//-------------------------------------------------------------------
//Definition des fonctions globales
//-------------------------------------------------------------------
cgApplication* pApplication;
FenetrePrincipale* pFenAff3D;
FenetreCamera* pFenetreCamera;
FenetreSetting* pFenetreSetting;
FenetreDesignateur* pFenetreDesignateur;
FenetreTransformation* pFenetreTransformation;
FenetreLumiere* pFenetreLumiere;
FenetreAnimation* pFenetreAnimation;

//----------------------------------------
//Charge une scene
//----------------------------------------
void LoadScene(char nomFichier[], int no_slide)
{
	char source[100];
	char cible[100];
	sprintf_s(source, 100, "%s.scn", nomFichier);
	sprintf_s(cible, 100, "scene.scn");
	Parser(source,cible);
	sprintf_s(source, 100, "%s.vsn", nomFichier);
	sprintf_s(cible,100, "scene.vsn");
	Parser(source,cible);

	if ( !pFenAff3D->Scene(no_slide)->LoadScene("scene") )
	{
		printf("Fichier '%s.scn' ou '%s.vsn' inexistants ou corrompus\n",nomFichier,nomFichier);
		exit(1);
	}
}

//----------------------------------------------------
//Charge les scenes dans le cas ou il y en a plusieurs
//----------------------------------------------------
void LoadScenes(int argc, char *argv[])
{
	if ( argc > 2 )
	{
		//Check les flags pouvant survenir sur la ligne de commandes
		for(int i=2; i < argc; i++)
		{
			if ( strcmp(argv[i],"/a") == 0 )
				pFenAff3D->Animation(VRAI);
		}

		//Si on est en mode animation, on regarde combien de slide on a.
		if ( pFenAff3D->Animation() )
		{
			char fichier[256];
			booleen existe;
			entier nbSlide = 0;
			do
			{
				sprintf_s(fichier,256,"%s%03d.scn",argv[1],nbSlide+1);
				if ( (existe = FichierExistant(fichier)) )
					nbSlide++;
			}
			while (existe);

			if ( nbSlide ==  0 )
			{
				printf("Fichiers '%sxxx.scn' ou '%sxxx.vsn' inexistants ou corrompus en mode animation\n",argv[1],argv[1]);
				exit(1);
			}

			pFenAff3D->InitNbScene(nbSlide);
			for(int i = 0; i < nbSlide; i++)
			{
				sprintf_s(fichier,256,"%s%03d",argv[1],i+1);
				LoadScene(fichier,i);
			}
		}
	}
	else
	{
		pFenAff3D->InitNbScene(1);
		LoadScene(argv[1],0);
	}
}

//-------------------------------------------------------------------
//
//	Programme principal (main)
//
//-------------------------------------------------------------------
void main( int argc, char *argv[] )
{
	//Test pour voir si un fichier a été passé en paramètre
	if ( argc < 2 )
	{
		printf("Vous devez nous indiquer le nom du fichier contenant la description de la scène et de la vue");
		exit(1);
	}

	//Création de l'application
	//-------------------------
	pApplication = new cgApplication();

	//Création de la fenetre principale et lecture des scenes
	pFenAff3D = new FenetrePrincipale();
	LoadScenes(argc, argv);
	pApplication->AddWindow(pFenAff3D);
	pApplication->CreateTimer(pFenAff3D->WindowID(), 300);

	//Creation de la fenetre caméra
	pFenetreCamera = new FenetreCamera(pFenAff3D);
	pApplication->AddWindow(pFenetreCamera);
	pFenetreCamera->HideWindow();

	//Creation de la fenetre setting
	pFenetreSetting = new FenetreSetting(pFenAff3D);
	pApplication->AddWindow(pFenetreSetting);
	pFenetreSetting->HideWindow();

	//Creation de la fenetre selection
	pFenetreDesignateur = new FenetreDesignateur(pFenAff3D);
	pApplication->AddWindow(pFenetreDesignateur);
	pFenetreDesignateur->HideWindow();

	//Creation de la fenetre transformation
	pFenetreTransformation = new FenetreTransformation(pFenAff3D);
	pApplication->AddWindow(pFenetreTransformation);
	pFenetreTransformation->HideWindow();

	//Creation de la fenetre lumiere
	pFenetreLumiere = new FenetreLumiere(pFenAff3D);
	pApplication->AddWindow(pFenetreLumiere);
	pFenetreLumiere->HideWindow();

	//Creation de la fenetre animation
	pFenetreAnimation = new FenetreAnimation(pFenAff3D);
	pApplication->AddWindow(pFenetreAnimation);
	pFenetreAnimation->HideWindow();

	//Exécute l'application
	//---------------------
	pApplication->StartApplication();
}