//*******************************************************************

//*																	*

//* Programme: objet.cpp											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation de la classe Objet. Classe générale pour		*

//*		pouvoir définir les propriétés globales à tous les objets	*

//*		graphiques.													*

//*																	*

//*******************************************************************


#include "objet.h"


#include "definition.h"

#include "ensemble.h"
#include "utilalg.h"
#include "erreur.h"

entier	Objet::NbObjet=0;
entier	Objet::NUMERO=0;

Objet::Objet ()
{
	num = NUMERO++;
	s = unIndefini;
	NbObjet += 1;
	//vol = new Infini;
	defvol = FAUX;
	attr = new Attributs;
	nbens = 0;
	lens = 0;
}

Objet::~Objet ()
{
	NbObjet -= 1;
	if (defvol) delete vol;
	defvol = FAUX;
	delete attr;
}

entier	Objet::numero () const
{
	return num;
}

entier	Objet::ensembles () const
{
	return nbens;
}

Ensemble* Objet::ensemble (entier i) const
{
	return lens[i-1].e;
}

void	Objet::ensemble (Ensemble *e, entier i)
{
	if (nbens==0) 

	{
		lens = new LEnsembles;
	} 

	else 

	{
		LEnsembles	*temp = new LEnsembles[nbens+1];
		for (entier j=0; j<nbens; j+=1)
			temp[j] = lens[j];

		delete lens;
		lens = temp;
	}

	lens[nbens].e = e;
	lens[nbens].i = i-1;

	nbens += 1;
}

void    Objet::detruire (entier i)
{
	if (i < 0 || i > nbens) Erreur(10, "");

	LEnsembles *temp;

	if (nbens > 1) 

		temp = new LEnsembles[nbens-1];
	else 

		temp = 0;

	entier j;
	for (j=0; j<i-1; j+=1) 

		temp[j] = lens[j];
	for (j=i; j<nbens; j+=1) 

	{
		temp[j-1] = lens[j];
		temp[j-1].e->lcomp[lens[j].i].i = j-1;
	}
	delete lens;
	lens = temp;

	//if (nbens == 0) return; // ok, pour graphe cyclique

	if (--nbens == 0) 

		delete this;
}

void    Objet::detruire ()
{
	if (nbens == 0) delete this;

	while (ensembles() > 0) 

	{
		lens[0].e->detache(lens[0].i+1);
		detruire(1);
	}
}

//const	Englobant&	Objet::volume ()
//{
	//if (defvol) return *vol;
	//else { // erreur ?
		//vol = new Infini();
		//defvol = VRAI;
		//return *vol;
	//}
//}

void	Objet::Touche ()
{
	//num = NUMERO++;
	if (defvol) delete vol;


	defvol = FAUX;
	for (entier j=0; j<nbens; j+=1) 

		lens[j].e->Touche();
}

Type	Objet::type () const
{
	return s;
}

void	Objet::attributs (const Attributs& a)
{
	*attr = a * *attr;
	//if (defvol) vol->transformation(a.transformation());
	this->Touche();
}

const Attributs& Objet::attributs () const
{
	return *attr;
}

void	Objet::attributs (Attributs* a)
{
	*attr = *a;
	this->Touche();
}

booleen	Objet::inter(const point& p, const vecteur& v, reel* k)
{
	return FAUX;
}

vecteur	Objet::gradient(const point&p)
{
	return(O-O);
}

point	Objet::unpoint()
{
	return(O);
}

void	Objet::reset()
{
}

entier	Objet::composantes () const
{
	return(0);
}

Objet*	Objet::composante (entier i) const
{
	Erreur(11, ""); /* composante inexistante */
	return(0);
}
