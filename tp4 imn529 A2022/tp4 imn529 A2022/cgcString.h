//*******************************************************************

//*																	*

//* Programme: cgcString.h											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		cgcString est une implémentation minimale des chaînes de	*

//*		caractères.													*

//*																	*

//*******************************************************************



#ifndef _CGCSTRING

#define _CGCSTRING



#include<assert.h>		//ASSERT()

#include<iostream>	//cout, cin, endl

#include<string.h>

using namespace std;

class cgcString

{

protected:

	char * ch;	   //Pointe vers les caracteres de la chaine

	unsigned int longueur;    //Retient le nombre de caracteres que contient la chaine



public:

	//Constructeur de chaine : Met la chaine a vide

	cgcString() { ch = NULL ; longueur = 0;}



	cgcString(char c[])

	{

		longueur = (unsigned int)strlen(c);

		ch = new char[longueur];

		assert(ch!=NULL);



		for(unsigned int i = 0 ; i < longueur ; i++)

			ch[i] = c[i];

	}



	//Copieur

	cgcString(const cgcString & c)

	{

		longueur = c.longueur;

		ch = new char[longueur];

		assert(ch!=NULL);



		for(unsigned int i = 0 ; i < longueur ; i++)

			ch[i] = c.ch[i];

	}



	//Destructeur de chaine

	~cgcString() { delete [] ch; ch = NULL; longueur = 0; }



	char* Get() { return ch; }



	//Assignation d'une chaine a une autre chaine

	void operator= (const cgcString & c )

	{

		longueur = c.longueur;



		if ( longueur == 0 )

		{

			delete [] ch;

			ch = NULL;

		}

		else

		{

			//Detruit la chaine dynamique avant d'en recreer une autre.

			delete [] ch;

			ch = new char[longueur];

			assert(ch!=NULL);

		}



		for(unsigned int i = 0 ; i < longueur ; i++ )

			ch[i] = c.ch[i];

	}



	//Assignation d'une chaine a une autre chaine

	void operator+= (const cgcString & c )

	{

		int l = c.longueur + longueur;



		if ( l == 0 )

		{

			delete [] ch;

			ch = NULL;

		}

		else

		{

			char* t = new char[l];

			assert(t!=NULL);



			unsigned int i = 0;

			for(; i < longueur; i++)

				t[i] = ch[i];

			for(unsigned int j = 0; j < c.longueur; j++)

				t[i+j] = c.ch[j];



			delete [] ch;

			ch = t;

			longueur = l;

		}

	}



	//Assignation d'une chaine a une autre chaine

	void operator+= (const char& c )

	{

		int l = longueur + 1;



		char* t = new char[l];

		assert(t!=NULL);



		unsigned int i = 0;

		for(; i < longueur; i++)

			t[i] = ch[i];

		t[i] = c;



		delete [] ch;

		ch = t;

		longueur = l;

	}



	//Iterateur

	char& operator[] (unsigned int n)

	{

		if (n+1 > longueur)

		{

			char * tmp = new char[n+1];

			assert(tmp!=NULL);



			//Recopie les anciens

			for(unsigned int i = 0 ; i < longueur ; i++)

				tmp[i] = ch[i];



			longueur = n+1;



			delete [] ch;

			ch = tmp;

		}



		return ch[n];

	}



	//Operateurs de comparaison

	int operator== (const cgcString &c)

	{

		if (longueur != c.longueur) return 0;



		//On regarde si chaque caractere est egale

		for(unsigned int i = 0 ; i < longueur ; i++)

		{

			if (ch[i]!=c.ch[i]) return 0;

		}

		return 1;

	}



	int operator!= (const cgcString &c) { return (!(operator==(c))); }



	int Len() { return longueur; }



	//Cout d'une chaine

	friend ostream& operator<< (ostream &sortie, cgcString & c)

	{

		for(unsigned int i=0; i < c.longueur ; i++)

			sortie << c.ch[i];



		return sortie;

	}

};



#endif