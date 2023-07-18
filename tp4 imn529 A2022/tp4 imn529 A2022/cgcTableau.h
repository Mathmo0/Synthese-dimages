//*******************************************************************
//*																	*
//* Programme: cgcTableau.h											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		cgcTableau implémente la gestion dynamique d'un tableau.	*
//*		Il est templaté(permet de faire un tableau de n'importe		*
//*		quel type de données(simple ou composé).					*
//*																	*
//*******************************************************************


#ifndef _CGCTABLEAU
#define _CGCTABLEAU


#include <assert.h>


template <class TYPE> 
class cgcTableau
{
protected:
	TYPE * tab;		//Éléments du tableau
	int dim;		//Dimension du tableau


public:
	//Constructeur par défaut
	cgcTableau()
	{ 
		tab = NULL; 
		dim = 0;
	}


	//Constructeur prenant une dimension initiale
	cgcTableau(int i)
	{
		dim = i;
		tab = new TYPE[dim];
		assert(tab!=NULL);
	}


	//Copieur
	cgcTableau(const cgcTableau &t)
	{
		dim = t.dim;


		if(dim==0)
			tab = NULL;
		else
		{
			tab = new TYPE[dim];
			assert(tab!=NULL);
		}


		for(int i = 0 ; i < dim ; i++)
			tab[i] = t.tab[i];
	}


	//Destructeur
	~cgcTableau() {  delete [] tab; }


	//Affectateur
	void operator= (const cgcTableau & t)
	{
		if (t.dim==0)
		{
			delete [] tab;  //detruit l'ancien et remet le pointeur a rien
			tab=NULL;
		}

		else
		{
			if ( t.dim != dim )
			{
				delete [] tab;     	  //Detruit l'espace avant d'en allouer
				tab = new TYPE[t.dim];  //une autre d'une grandeur differente
				assert(tab!=NULL);
			}


			dim = t.dim;


			for(int i = 0 ; i < dim ; i++)
				tab[i] = t.tab[i];

		}

	}



	//Iterateur
	TYPE& operator[] (int n)
	{
		assert(n>=0);


		if (n+1 > dim)
		{
			TYPE * tmp = new TYPE[n+1];
			assert(tmp!=NULL);


			//Recopie les anciens
			for(int i = 0 ; i < dim ; i++)
				tmp[i] = tab[i];


			dim = n+1;


			delete [] tab;
			tab = tmp;
		}
		return tab[n];
	}


	//Retourne la dimension du tableau
	int Len() { return dim; }
};



#endif