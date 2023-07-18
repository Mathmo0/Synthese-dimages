#pragma warning(disable : 4996)

#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>

void Translate(FILE* fs, FILE* fc)
{
	FILE* f2;
	char	c,s[100];

	c = getc (fs);
	while ( !feof(fs) ) 
	{
		switch (c) 
		{
		case '\\': 
			fscanf_s (fs,"%s",s, sizeof(s));
			f2 = fopen (s,"r");
			if (f2 == NULL) 
			{
				printf("Le fichier '%s' n'existe pas\n",s);
				exit(1);
			}
			Translate(f2,fc);
			fclose (f2);
			break;
		case '{':
			do 
			{
				c = getc (fs);
				if ( feof(fs) ) 
				{
					printf("Fin de fichier rencontrer avant la fin attendue\n");
					exit(1);
				}
			} while (c != '}');
			break;
		default : 
			putc(c,fc);
			break;
		}
		
		c = getc (fs);
	}
}

void Parser(char source[], char cible[])
{
	//Ouverture du fichier source en lecture
	FILE* fs;
	fs = fopen(source,"r");
	if ( fs == NULL )
	{
		printf("Le fichier '%s' n'existe pas\n",source);
		exit(1);
	}

	//Ouverture du fichier cible en ecriture
	FILE* fc;
	fc = fopen(cible,"w");
	if ( fc == NULL )
	{
		printf("Impossible de creer le fichier temporaire '%s'\n",cible);
		exit(1);
	}

	//Parse le fichier
	Translate(fs,fc);

	fclose(fs);
	fclose(fc);
}
