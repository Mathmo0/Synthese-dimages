
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "util.h"
#include "utilalg.h"
#include "ensemble.h"
#include "polygone.h"
#include "segment.h"
#include "alg.h"

#include "definition.h"
#include "attr.h"
#include "global.h"

using namespace std;

reel seedri=0.328948;

static  void    Concatene(Ensemble* la2, const Attributs& a, Ensemble *la)
{
	//for (entier i=1; i<=la2->composantes(); i+=1) {
		//la->ajoute(la2->composante(i)->fils(), a * la2->composante(i)->attributs());
	//}
}

void    Couture(Objet* o, Ensemble* &la)
{
	//la = new Ensemble();
	//if (o->type() == unEnsemble) { // && o.nbparents() == 1
		//Ensemble *la2;
		//for (entier i=1; i<=((Ensemble*)o)->composantes(); i+=1) {
			//Couture (((Ensemble*)o)->composante(i), la2);
			//Concatene (la2, o->attributs(), la);
			//delete la2;
		//}
	//} else {
		//if (o->type() != unIndefini) la->ajoute (o);
	//}
}


vecteur	Reflechi(const vecteur& i, const vecteur& n)
{
	return(i - 2.0*n*(i*n));
}

vecteur	Transmis(const vecteur& i, const vecteur& n)
{
	return(i);
}

reel	Uniforme(const reel& a, const reel& b)
{	seedri=(seedri+3.141592654);
	seedri = seedri*seedri*seedri;
	seedri=seedri-int(seedri);
//	printf("seed= %f \n",seedri);
	return(seedri*(b-a) + a);
}

reel    Uniforme(const reel& s)
{
        long    *p = (long *) &s;

//        srand48(*p);
//        return drand48();

		return 0.0;
}

point	Centre(const Polygone& o)
{
	vecteur	m(0.0,0.0,0.0);
	point	p;
	entier	nb;

	for (entier i=1; i<=(nb=o.sommets()); i+=1) {
		p = o.sommet(i);
		m = m+vecteur(p.x(),p.y(),p.z());
	}
	m = m*(1.0/nb);
	return(point(m.x(),m.y(),m.z()));
}

static	void	printab(entier tabs)
{
	for (entier i=0; i<tabs; i+=1) {
		printf("  ");
	}
}

void	Print(Objet *o, char *n)
{
	printf(n);
	if (avecno) printf(" (n = %d)", o->numero());
	if (avecnb) printf(" (p = %d)", o->ensembles());
	printf("\n");
}

static	void	Print_Objet_Tabs(Objet* o, entier tabs)
{
	entier	i/*,j,k*/;
	Segment *sss = (Segment *) o;

	printab(tabs);
	switch (o->type()) 

	{
		case unEnsemble : 

			Print(o, "OC");
			

			for (i=1; i<=((Ensemble *)o)->composantes(); i+=1) 

				Print_Objet_Tabs (((Ensemble*)o)->composante(i), tabs+1);


			break;
		case unPoint : Print(o, "Point"); break;
		case unSegment : Print(o, "Segment"); 
			cout << (float) (sss->p1().x()) << " " << (float) (sss->p2().x()) << endl;
			break;
		case unPolygone : Print(o, "Polygone"); break;
		case uneSphere : Print(o, "Sphere"); break;
		case unCylindre : Print(o, "Cylindre"); break;
		case unPlan : Print(o, "Plan"); break;
		case uneDroite : Print(o, "Droite"); break;
		case unVolume : Print(o, "Volume"); break;
		case unVide : Print(o, "Vide"); break;
		default : Print(o, "Indefini"); break;
	}

	if (!avecmat) 

		return;


//Affichage de la matrice

/*	for (i=1; i<=3; i+=1) {
		printab(tabs);
		for (j=1; j<=4; j+=1) {
			printf("%f ", o->attributs().transformation().M().e(i,j));
		}
		printf("\n");
	}

*/
	printf("\n");
}

void	Print_Objet(Objet* o)
{
	printf("\n");
	Print_Objet_Tabs(o,0);
}


matrice	printmul(matrice* m1, matrice* m2)
{
	return *m1 * *m2;
}

