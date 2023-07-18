//*******************************************************************

//*																	*

//* Programme: ensemble.cpp											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation des ensembles.									*

//*																	*

//*******************************************************************


#include "ensemble.h"
#include "erreur.h"
#include "englobe.h"
#include "attr.h"
#include "global.h"


Ensemble::Ensemble ()
{
	s = unEnsemble;
	nbcomp = 0;
	lcomp = 0;
}


Ensemble::~Ensemble ()

{

	while ( this->composantes() > 0 ) 

		this->enleve(1);

}


void	Ensemble::ajoute (entier i, Objet* o, const Attributs& a)
{
	Ensemble *e = new Ensemble;
	e->attributs(a);
	e->ajoute(o);

	ajoute(i, e);
}

void	Ensemble::ajoute (entier i, Objet* o)
{
	if (i < 0 || i > nbcomp) Erreur(10, "");


	if (nbcomp==0) 

		lcomp = new LComposantes;
	else 

	{
		LComposantes *temp = new LComposantes[nbcomp+1];
		entier	j;
		for (j=0; j<i; j+=1) 

			temp[j] = lcomp[j];
		for (j=i; j<nbcomp; j+=1) 

		{
			temp[j+1] = lcomp[j];
			temp[j+1].c->lens[lcomp[j].i].i = j+1;
		}
		delete lcomp;
		lcomp = temp;
	}

	o->ensemble(this, i+1);

	lcomp[i].c = o;
	lcomp[i].i = o->ensembles()-1;

	nbcomp += 1;
	this->Touche();
}

void	Ensemble::ajoute (Objet* o)
{
	ajoute (nbcomp, o);
}

void	Ensemble::ajoute (Objet* o, const Attributs& a)
{
	ajoute (nbcomp, o, a);
}

// enleve le lien entre l'ensemble et la composante

void	Ensemble::detache (entier i)
{
	LComposantes *temp;

	if (nbcomp > 1) temp = new LComposantes[nbcomp-1];
	else temp = 0;

	entier	j;
	for (j=0; j<i-1; j+=1) 

		temp[j] = lcomp[j];


	for (j=i; j<nbcomp; j+=1) 

	{
		temp[j-1] = lcomp[j];
		temp[j-1].c->lens[lcomp[j].i].i = j-1;
	}
	delete lcomp;
	lcomp = temp;

	nbcomp -= 1;

	this->Touche();
}

// enleve le lien et detruit la composante

void	Ensemble::enleve (entier i)
{
	if (i < 0 || i > nbcomp) Erreur(10, "");

	lcomp[i-1].c->detruire(lcomp[i-1].i+1);

	detache(i);
}

void	Ensemble::enleve ()
{
	enleve(nbcomp);
}

void	Ensemble::remplace (entier i, Objet *o, const Attributs& a)
{
	lcomp[i-1].c->detruire(lcomp[i-1].i+1);

	Ensemble *e = new Ensemble;
	e->attributs(a);
	e->ajoute(o);

	e->ensemble(this, i);

	lcomp[i-1].c = e;
	lcomp[i-1].i = e->ensembles()-1;

	this->Touche();
}

void	Ensemble::remplace (Objet *o, const Attributs&a)
{
	remplace(nbcomp, o, a);
}

void	Ensemble::remplace (Objet *o)
{
	remplace(nbcomp, o);
}

void	Ensemble::remplace (entier i, Objet *o)
{
	lcomp[i-1].c->detruire(lcomp[i-1].i+1);

	o->ensemble(this, i);

	lcomp[i-1].c = o;
	lcomp[i-1].i = o->ensembles()-1;

	this->Touche();
}

entier	Ensemble::composantes () const
{
	return(nbcomp);
}

Objet*	Ensemble::composante (entier i) const
{
	if (i<1 || i>nbcomp) Erreur(11, "");
	return(lcomp[i-1].c);
}


Objet*	Ensemble::copie () const
{
	Ensemble *e = new Ensemble;

	for (entier i=0; i<nbcomp; i+=1)
		e->ajoute(this->lcomp[i].c->copie());


	Attributs *aaa = new Attributs;
	*aaa = *(this->attr);
	e->attr = aaa;
	e->defvol = this->defvol;
	if (this->defvol) e->vol = this->vol->copie();


	return(e);
}

booleen	Ensemble::inter(const point& p, const vecteur& v, reel* k)
{
	const	Transformation *t = &(this->attributs().transformation());

	point	p2 = t->inverse(p);
	vecteur	v2 = t->inverse(v);

	booleen	inter=FAUX;

	for (entier i=1; i<=this->composantes (); i+=1) 

	{
		if (this->composante(i)->inter(p2,v2, k)) { inter = VRAI; }
	}


	return (inter);
}

const	Englobant&    Ensemble::volume() const
{
	if (!defvol) 

	{
		((Objet*)this)->vol = new VolVide();

		if (profondeur == 0 || profondeur == 1) return *vol;

		booleen infini=FAUX;
 
		const Englobant *v2;
		Englobant *v3;//,*v4;

		for (entier i=1; i<=this->composantes(); i+=1) 

		{
			if (infini) break;

			profondeur -= 1;
			v2 = &this->composante(i)->volume();
			profondeur += 1;
			if (v2->infini()) 

			{
		       	infini = VRAI;
				delete vol;
				((Objet*)this)->vol = new Infini();
			} 

			else 

			{
				//v4 = v2->copie();
				//v4->transformation(this->composante(i)->attributs().transformation());
				Englobe(*vol,*v2, &v3);
				delete vol;
				//delete v4;
				((Objet*)this)->vol = v3;
			}
		}
		((Objet*)this)->vol->transformation(this->attributs().transformation());
		((Objet*)this)->defvol = VRAI;
	}


	return *vol;
}
 
