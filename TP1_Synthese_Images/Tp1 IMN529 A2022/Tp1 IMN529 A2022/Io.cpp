
#include <iostream>
#include <cstdlib>
#include "io.h"
#include "geo.h"
#include "erreur.h"
#include "utilalg.h"
#include "util.h"
#include "objets.h"
#include "alg.h"
#include "fichier.h"
#include "chaine.h"
#include "attr.h"
#include "transfo.h"
#include "camera.h"

using namespace std;

const	int	NB_TT=20;
booleen	arbre = VRAI;

chaine	vnt[NB_TT] = { "ID", "TR", "HO", "RT", "CZ", "AV", "MA", "GD", "CD", "TD", "CS", "TS", "CA", "TA", "CR", "CT", "CO", "CE", "HD", "LK", };

#define	NB_TO	13

static	chaine	vno[NB_TO] = { "FI", "OC", "PT", "SG", "TI", "PG", "SP", "CL", "PL", "DR", "VO", "FR", "LN", };
Type	vto[NB_TO] = {unIndefini, unEnsemble, unPoint, unSegment, unTriangle, unPolygone, uneSphere, unCylindre, unPlan, uneDroite, unVolume, unFractal, unVide, };

static	entier	NbObjets = 0;
static	Objet	*Objets[1000];
static	entier	Numeros[1000];



void	Lire_Sorte (Fichier &f, Type *s)
{
	chaine	c;
	entier	i;

	if ( !f.mchaine(c) )
	{
		printf("Chaine attendue\n");
		exit(1);
	}

	for (i=0; i<NB_TT; i+=1) {
		if (c == vnt[i]) {
			*s = (Type)i; return;
		}
	}
	Erreur(8,c.C());
}

void	Lire_vecteur(Fichier &f, vecteur *v)
{
	double v1,v2,v3;
	if ( !f.mreel(v1) )
	{
		printf("Reel attendu\n");
		exit(1);
	}
	if ( !f.mreel(v2) )
	{
		printf("Reel attendu\n");
		exit(1);
	}
	if ( !f.mreel(v3) )
	{
		printf("Reel attendu\n");
		exit(1);
	}

	*v = vecteur (v1,v2,v3);
}

void	Lire_point(Fichier &f, point *p)
{
	double v1,v2,v3;
	if ( !f.mreel(v1) )
	{
		printf("Reel attendu\n");
		exit(1);
	}
	if ( !f.mreel(v2) )
	{
		printf("Reel attendu\n");
		exit(1);
	}
	if ( !f.mreel(v3) )
	{
		printf("Reel attendu\n");
		exit(1);
	}

	*p = point (v1,v2,v3);
}

void	Lire_Sommet(Fichier &f, point* &p)
{
	double v1,v2,v3;
	if ( !f.mreel(v1) )
	{
		printf("Reel attendu\n");
		exit(1);
	}
	if ( !f.mreel(v2) )
	{
		printf("Reel attendu\n");
		exit(1);
	}
	if ( !f.mreel(v3) )
	{
		printf("Reel attendu\n");
		exit(1);
	}

	p = new point (v1,v2,v3);
}

void	Lire_Identite (Fichier &, Transformation *t)
{
	*t = N;
}

void	Lire_Translation (Fichier &f, Transformation *t)
{
	vecteur	v;

	Lire_vecteur(f, &v);
	*t = Deplacement(v);
}

void	Lire_Homothetie (Fichier &f, Transformation *t)
{
	point	p;
	vecteur	v;
	reel	r;

	Lire_point(f, &p);
	Lire_vecteur(f, &v);
	if ( !f.mreel(r) )
	{
		printf("Reel attendu\n");
		exit(1);
	}

	*t = Homothetie(p,v,r);
}

void	Lire_Rotation (Fichier &f, Transformation *t)
{
	point	p;
	vecteur	v;
	reel	r;

	Lire_point(f, &p);
	Lire_vecteur(f, &v);
	if ( !f.mreel(r) )
	{
		printf("Reel attendu\n");
		exit(1);
	}

	*t = Rotation(p,v,r);
}

void	Lire_Alignement (Fichier &f, Transformation *t)
{
	vecteur	v1,v2;

	Lire_vecteur(f, &v1);
	Lire_vecteur(f, &v2);
	*t = Alignement(v1,v2);
}

void	Lire_Cisaillement (Fichier &f, Transformation *t)
{
	point	p;
	vecteur	v;
	vecteur	w;

	Lire_point(f, &p);
	Lire_vecteur(f, &v);
	Lire_vecteur(f, &w);
	*t = Cisaillement(p,v,w);
}

void	Lire_Matrice (Fichier &f, Transformation *t)
{
	matrice	m,mi;

	reel r;
	entier	i,j;

	for (i=1; i<=3; i+=1) 
	{
		for (j=1; j<=4; j+=1) 
			if ( !f.mreel(r) )
			{
				printf("Reel attendu\n");
				exit(1);
			}
			m.e(i,j) = r;
	}
	for (i=1; i<=3; i+=1) 
	{
		for (j=1; j<=4; j+=1) 
			if ( !f.mreel(r) )
			{
				printf("Reel attendu\n");
				exit(1);
			}
			mi.e(i,j) = r;
	}
	*t = Transformation(m,mi);
}

Couleur Lire_Couleur(Fichier &f)
{
	reel r,g,b;
	if ( !f.mreel(r) )
	{
		printf("Reel attendu\n");
		exit(1);
	}
	if ( !f.mreel(g) )
	{
		printf("Reel attendu\n");
		exit(1);
	}
	if ( !f.mreel(b) )
	{
		printf("Reel attendu\n");
		exit(1);
	}

	return Couleur(r,g,b);
}

void	Lire_Attributs (Fichier &f, Attributs *a0)
{
	Type	sorte;
	Attributs a;
	Transformation t;

	*a0 = ATTR;
	for (;;) 
	{
		a = ATTR;
		Lire_Sorte (f, &sorte);
		switch (sorte) 
		{
			case 0 : break;
			case 1 : Lire_Translation(f, &t); a.transformation(t); break;
			case 2 : Lire_Homothetie(f, &t); a.transformation(t); break;
			case 3 : Lire_Rotation(f, &t); a.transformation(t); break;
			case 4 : Lire_Cisaillement(f, &t); a.transformation(t); break;
			case 5 : Lire_Alignement(f, &t); a.transformation(t); break;
			case 6 : Lire_Matrice(f, &t); a.transformation(t); break;
			case 7 : 
				reel r;
				if ( !f.mreel(r) )
				{
					printf("Reel attendu\n");
					exit(1);
				}
				a.diffus(Couleur(r)); break;
			case 8 : 
				a.diffus(Lire_Couleur(f)); break;
			case 9 : 
				a.t_diffus(Lire_Couleur(f)); break;
			case 10 : 
				a.speculaire(Lire_Couleur(f)); break;
			case 11 : 
				a.t_speculaire(Lire_Couleur(f)); break;
			case 12 : 
				a.ambiant(Lire_Couleur(f)); break;
			case 13 : 
				a.t_ambiant(Lire_Couleur(f)); break;
			case 14 : 
				a.reflechi(Lire_Couleur(f)); break;
			case 15 : 
				a.transmis(Lire_Couleur(f)); break;
			case 16 : 
				a.ombre(Lire_Couleur(f)); break;
			case 17 : 
				a.emis(Lire_Couleur(f)); break;
			case 18 : 
				a.hide(VRAI); break;
			case 19 : 
				a.lock(VRAI); break;
		}

		if (sorte==0) 
			break;
		*a0 = a * *a0;
	}
}

Objet*	Lire_Point (Fichier &f)
{
	point	p;

	Lire_point(f, &p);
	return new Point (p);
}

Objet*	Lire_Segment (Fichier &f)
{
	point	p1,p2;

	Lire_point(f, &p1);
	Lire_point(f, &p2);
	return new Segment (p1,p2);
}

Objet*	Lire_Plan (Fichier &f)
{
	reel v1,v2,v3,v4;

	if ( !f.mreel(v1) )
	{
		printf("Reel attendu\n");
		exit(1);
	}
	if ( !f.mreel(v2) )
	{
		printf("Reel attendu\n");
		exit(1);
	}
	if ( !f.mreel(v3) )
	{
		printf("Reel attendu\n");
		exit(1);
	}
	if ( !f.mreel(v4) )
	{
		printf("Reel attendu\n");
		exit(1);
	}

	return new Plan(plan(v1,v2,v3,v4));
}

Objet*	Lire_Sphere (Fichier &)
{
	return new Sphere;
}

Objet*	Lire_Cylindre (Fichier &f)
{
	return new Cylindre;
}

Objet*	Lire_Triangle (Fichier &f)
{
	point p0,p;

	Polygone *o = new Polygone ();
	Lire_point(f, &p);
	o->ajoute(p);
	Lire_point(f,&p);
	o->ajoute(p);
	Lire_point(f,&p);
	o->ajoute(p);

	return o;
}

Objet*	Lire_Polygone (Fichier &f)
{
	point	p0,p;
	booleen	fini;

	Polygone *o = new Polygone ();

	Lire_point(f, &p0);
	o->ajoute (p0);
	do {
		Lire_point(f, &p);
		if ( !(fini = (p0==p)) ) 
			o->ajoute (p);
	} while (!fini);

	return o;
}

Objet*	Lire_Fractal (Fichier &f)
{
	point	p1,p2,p3;
	int nivsub;
	reel h1, h2;
	if ( !f.mentier(nivsub) )
	{
		printf("Entier attendu, niveau de subdivision fractal\n");
		exit(1);
	}

	if ( !f.mreel(h1) )
	{
		printf("Reel attendu, hauteur inf fractal\n");
		exit(1);
	}

	if ( !f.mreel(h2) )
	{
		printf("Reel attendu, hauteur sup fractal\n");
		exit(1);
	}

	Lire_point(f, &p1);
	Lire_point(f, &p2);
	Lire_point(f, &p3);

	Fractal *o = new Fractal (p1,p2,p3, nivsub, h1, h2);

	return o;
}


Objet*	Lire_Lien(Fichier &f)
{
	entier n;
	if ( !f.mentier(n) )
	{
		printf("Entier attendu\n");
		exit(1);
	}

	for (entier i=0; i<NbObjets; i+=1) {
		if (n == Numeros[i]) {
			return Objets[i];
		}
	}
	Erreur(0, "");
	return 0;
}

void	Lire_PointVol(Fichier &f, PointVol *p)
{
	reel v1,v2,v3;

	if ( !f.mreel(v1) )
	{
		printf("Reel attendu\n");
		exit(1);
	}
	if ( !f.mreel(v2) )
	{
		printf("Reel attendu\n");
		exit(1);
	}
	if ( !f.mreel(v3) )
	{
		printf("Reel attendu\n");
		exit(1);
	}

	Creer_PointVol ( v1,v2,v3, p);
}

Objet*	Lire_Volume (Fichier &f)
{
	PointVol pt[500];
	reel	w;
	entier	nb_pts,nb_tri,i,subdiv,memsubdiv;
	entier	nopt1,nopt2,nopt3;
	Triangle tri;
 
	Volume	*o = new Volume;

	if ( !f.mreel(w) )
	{
		printf("Reel attendu\n");
		exit(1);
	}
	o->Coefficient_Tension(w);

	if ( !f.mentier(subdiv) )
	{
		printf("Entier attendu\n");
		exit(1);
	}
	o->Niveau_de_Subdiv (subdiv);
 
	if ( !f.mentier(memsubdiv) )
	{
		printf("Entier attendu\n");
		exit(1);
	}
	o->Niveau_de_Subdiv_Mem (memsubdiv);
 
	if ( !f.mentier(nb_pts) )
	{
		printf("Entier attendu\n");
		exit(1);
	}
	for (i=1; i<=nb_pts; i+=1)
		Lire_PointVol(f,&(pt[i]));
 
	if ( !f.mentier(nb_tri) )
	{
		printf("Entier attendu\n");
		exit(1);
	}
	for (i=1; i<=nb_tri; i+=1) 
	{
		if ( !f.mentier(nopt1) )
		{
			printf("Entier attendu\n");
			exit(1);
		}
		if ( !f.mentier(nopt2) )
		{
			printf("Entier attendu\n");
			exit(1);
		}
		if ( !f.mentier(nopt3) )
		{
			printf("Entier attendu\n");
			exit(1);
		}
		Def_Triangle (pt[nopt1], pt[nopt2], pt[nopt3], &tri);
		o->Ajoute (tri);
	}
 
	if (!o->Organise()) 
		Erreur(20, "");

	return o;
}
 
void	Lire_Type(Fichier &f, Type *t)
{
	chaine	no;

	if ( !f.mchaine(no) )
	{
		printf("Chaine attendue\n");
		exit(1);
	}
	for (entier i=0; i<NB_TO; i+=1) 
	{
		if (no == vno[i]) 
		{
			*t = vto[i];
			if (*t != unVide && *t != unIndefini) 
			{
				entier n;
				if ( !f.mentier(n) )
				{
					printf("Entier attendu\n");
					exit(1);
				}

				Numeros[NbObjets] = n;
			}

			return;
		}
	}
	Erreur (7,no.C());
}

void	Lire_Type2(Fichier &f, Type *t)
{
	chaine	no;

	if ( !f.mchaine(no) )
	{
		printf("Chaine attendue\n");
		exit(1);
	}
	for (entier i=0; i<NB_TO; i+=1) 
	{
		if (no == vno[i]) 
		{
			*t = vto[i];
			return;
		}
	}
	Erreur (7,no.C());
}

Objet*	Lire_Ensemble (Fichier &f)
{
	booleen	Lire_Objet2 (Fichier &, Objet* &);
	Objet	*c;
	Attributs	a;

	Ensemble *o = new Ensemble;
	Objets[NbObjets++] = o;
	for (;;) 
	{
		if (Lire_Objet2 (f, c)) 
		{
			Lire_Attributs (f, &a);
			o->ajoute (c, a);
		} else return o;
	}
}

booleen	Lire_Objet2 (Fichier &f, Objet* &o)
{
	Type	t;

	Objet	*p;

	Lire_Type (f, &t);
	switch (t) 
	{
		case unEnsemble : p = Lire_Ensemble (f); break;
		case unPoint : p = Lire_Point (f); break;
		case unSegment : p = Lire_Segment (f); break;
		case unTriangle: p = Lire_Triangle (f); break;
		case unPolygone : p = Lire_Polygone (f); break;
		case uneSphere : p = Lire_Sphere (f); break;
		case unPlan : p = Lire_Plan (f); break;
		case unCylindre : p = Lire_Cylindre (f); break;
		case unVolume : p = Lire_Volume (f); break;
		case unFractal : p = Lire_Fractal (f); break;
		case unVide : o = Lire_Lien(f); break;
		case unIndefini : return FAUX; break;
	}
	if (t != unVide) 
	{
		Attributs	a;
		Lire_Attributs (f, &a);
		p->attributs(a);
		if (t != unEnsemble) Objets[NbObjets++] = p;
		o = p;
	}
	return VRAI;
}

Objet*	Lire_Branche (Fichier &f)
{
	booleen	Lire_Arbre (Fichier &, Objet* &);
	Objet	*c;
	
	Ensemble *o = new Ensemble;

	for (;;) 
	{
		if (!Lire_Arbre (f, c))  
			return o;
		
		o->ajoute(c);
	} 	
}

booleen	Lire_Arbre (Fichier &f, Objet* &o)
{
	Type	t;

	Objet	*p;

	Lire_Type2 (f, &t);
	switch (t) 
	{
		case unEnsemble : 
			p = Lire_Branche (f); break;
		case unPoint : 
			p = Lire_Point (f); break;
		case unSegment : 
			p = Lire_Segment (f); break;
		case unTriangle : 
			p = Lire_Triangle (f); break;
		case unPolygone : 
			p = Lire_Polygone (f); break;
		case uneSphere : 
			p = Lire_Sphere (f); break;
		case unPlan : 
			p = Lire_Plan (f); break;
		case unCylindre : 
			p = Lire_Cylindre (f); break;
		case unVolume : 
			p = Lire_Volume (f); break;
		case unFractal : 
			p = Lire_Fractal (f); break;
	  	case unVide : 
			o = Lire_Lien(f); break;
		case unIndefini : 
			return FAUX; break;
	}
	
	if (t != unVide) 
	{
		Attributs	a;
		Lire_Attributs (f, &a);
		p->attributs(a);
	//	Print_Objet (p);
	//	if (t != unEnsemble) Objets[NbObjets++] = p;
		o = p;
	}
	return VRAI;
}

Objet*	Objet::Lecture (Fichier &f)
{
	NbObjets = 0;
	Objet	*o;
	if (Lire_Arbre (f, o)) 
		return o;
	else 
		return 0;
}

void	Ecrire_vecteur(Fichier *f, vecteur v)
{
	f->Wreel(v.x()); f->Wchaine(" ");
	f->Wreel(v.y()); f->Wchaine(" ");
	f->Wreel(v.z()); f->Wchaine("\n");
}

void	Ecrire_point(Fichier *f, point p)
{
	f->Wreel(p.x()); f->Wchaine(" ");
	f->Wreel(p.y()); f->Wchaine(" ");
	f->Wreel(p.z()); f->Wchaine("\n");
}

void	Ecrire_Matrice (Fichier *f, Transformation t)
{
	matrice	m = t.M();
	matrice	mi = t.Mi();

	entier	i,j;

	for (i=1; i<=3; i+=1) 
	{
		for (j=1; j<=4; j+=1) 
		{
			f->Wreel(m.e(i,j));
			f->Wchaine(" ");
		}
		f->Wchaine("\n");
	}
	for (i=1; i<=3; i+=1) 
	{
		for (j=1; j<=4; j+=1) 
		{
			f->Wreel(mi.e(i,j));
			f->Wchaine(" ");
		}
		f->Wchaine("\n");
	}
}

void	Ecrire_Coefficient (Fichier *f, const Coefficient& c, char *s)
{
	if (c.defined()) 
	{
		f->Wchaine(s); f->Wchaine(" ");
		f->Wreel(c.couleur().rouge()); f->Wchaine(" ");
		f->Wreel(c.couleur().vert()); f->Wchaine(" ");
		f->Wreel(c.couleur().bleu()); f->Wchaine("\n");
	}
}

void	Ecrire_Attributs (Fichier *f, Attributs a)
{
	if (a.deftransformation() && !a.transformation().neutre()) 
	{
		f->Wchaine("MA ");
		Ecrire_Matrice(f, a.transformation());
	}

	Coefficient *c;

	a.diffus(c);
	Ecrire_Coefficient (f, *c, "CD");
	a.t_diffus(c);
	Ecrire_Coefficient (f, *c, "TD");
	a.speculaire(c);
	Ecrire_Coefficient (f, *c, "CS");
	a.t_speculaire(c);
	Ecrire_Coefficient (f, *c, "TS");
	a.ambiant(c);
	Ecrire_Coefficient (f, *c, "CA");
	a.t_ambiant(c);
	Ecrire_Coefficient (f, *c, "TA");
	a.reflechi(c);
	Ecrire_Coefficient (f, *c, "CR");
	a.transmis(c);
	Ecrire_Coefficient (f, *c, "CT");
	a.ombre(c);
	Ecrire_Coefficient (f, *c, "CO");
	a.emis(c);
	Ecrire_Coefficient (f, *c, "CE");
	// ...
	if (a.hide()) 
		f->Wchaine("HD\n");

	if (a.lock())
		f->Wchaine("LK\n");

	f->Wchaine("ID\n");
}

void	Ecrire_Type(Fichier *f, Type t)
{
	switch (t) 
	{
		case unEnsemble : f->Wchaine("OC "); break;
		case unPoint : f->Wchaine("PT "); break;
		case unSegment : f->Wchaine("SG "); break;
		case unPolygone : f->Wchaine("PG "); break;
		case uneSphere : f->Wchaine("SP "); break;
		case unPlan : f->Wchaine("PL "); break;
		case unCylindre : f->Wchaine("CL "); break;
		case unVolume : f->Wchaine("VO "); break;
		case unVide : break;
	}
}

booleen	Deja_Ecrit(Fichier &f, Objet& o)
{
	if (f.debut()) 
		NbObjets = 0;
	if (arbre) 
		return FAUX; 

	for (entier i=0; i<NbObjets; i+=1) 
	{
		if (o.numero() == Numeros[i]) 
		{
			f.Wchaine("LN ");
			f.Wentier(o.numero());
			f.Wchaine("\n");
			return VRAI;
		}
	}
	Numeros[NbObjets] = o.numero();
	Objets[NbObjets++] = &o;
	return FAUX;
}

void	Point::Ecrire(Fichier *f)
{
	if (Deja_Ecrit(*f, *this)) return;

	f->Wchaine("PT ");
	
	if (!arbre) {f->Wentier(numero()); f->Wchaine("\n");}

	Ecrire_point(f, pt());

	Ecrire_Attributs (f, ((Objet *)this)->attributs());
}

void	Droite::Ecrire(Fichier *f) const
{
}

void	Objet::Ecrire(Fichier *f) const
{
}

void	Fractal::Ecrire(Fichier *f) const
{
}

void	Particule::Ecrire(Fichier *f) const
{
}

void	Segment::Ecrire (Fichier *f)
{
	if (Deja_Ecrit(*f, *this)) return;

	f->Wchaine("SG ");
	if (!arbre) { f->Wentier(numero()); f->Wchaine("\n");}

	Ecrire_point(f, p1());
	Ecrire_point(f, p2());

	Ecrire_Attributs (f, ((Objet *)this)->attributs());
}

void	Plan::Ecrire (Fichier *f)
{
	if (Deja_Ecrit(*f, *this)) return;

	f->Wchaine("PL ");
	if (!arbre) {f->Wentier(numero()); f->Wchaine("\n");}

	reel	a,b,c,d;
	this->mplan().abcd(&a,&b,&c,&d);
	f->Wreel(a); f->Wchaine(" ");
	f->Wreel(b); f->Wchaine(" ");
	f->Wreel(c); f->Wchaine(" ");
	f->Wreel(d); f->Wchaine("\n");

	Ecrire_Attributs (f, ((Objet *)this)->attributs());
}

void	Sphere::Ecrire (Fichier *f)
{
	if (Deja_Ecrit(*f, *this)) return;

	f->Wchaine("SP\n");
	if (!arbre) {f->Wentier(numero()); f->Wchaine("\n");}


	Ecrire_Attributs (f, attributs());
}

void	Cylindre::Ecrire (Fichier *f)
{
	if (Deja_Ecrit(*f, *this)) return;

	f->Wchaine("CL\n");
	if (!arbre) { f->Wentier(numero()); f->Wchaine("\n");}


	Ecrire_Attributs (f, attributs());
}

void	Polygone::Ecrire (Fichier *f)
{
	if (Deja_Ecrit(*f, *this)) return;

	f->Wchaine("PG ");
	if (!arbre) {f->Wentier(numero()); f->Wchaine("\n");}

	point	p0;
	for (entier i=1; i<=sommets(); i+=1) {
		if (i==1) p0 = sommet(1);
		if (i==1 || !(sommet(i)==p0)) Ecrire_point(f, sommet(i));
	}
	if (sommets()>0) Ecrire_point(f, sommet(1));

	Ecrire_Attributs (f, ((Objet *)this)->attributs());
}

void	Ecrire_PointVol(Fichier *f, PointVol p)
{
	f->Wreel(p->x()); f->Wchaine(" ");
	f->Wreel(p->y()); f->Wchaine(" ");
	f->Wreel(p->z()); f->Wchaine("\n");
}
 
void	Volume::Ecrire (Fichier *f)
{
	if (Deja_Ecrit(*f, *this)) return;

	f->Wchaine("VO ");
	if (!arbre) {f->Wentier(numero()); f->Wchaine("\n");}


	PointVol pts[500];
	entier	i,j,n=0;
 
	f->Wreel(Coefficient_Tension()); f->Wchaine(" ");
	f->Wentier(Niveau_de_Subdiv()); f->Wchaine(" ");
	f->Wentier(Niveau_de_Subdiv_Mem()); f->Wchaine(" ");
 
	Triangle tri;
	PointVol p1,p2,p3;

	for (i=1; i<=Nb_Triangle(); i+=1) 
	{
		tri = Ieme_Triangle (i);
		Pts_Triangle (tri, &p1,&p2,&p3);

		for (j=0; j<n; j+=1) if (p1 == pts[j]) break;
		if (j==n) pts[n++] = p1;

		for (j=0; j<n; j+=1) if (p2 == pts[j]) break;
		if (j==n) pts[n++] = p2;

		for (j=0; j<n; j+=1) if (p3 == pts[j]) break;
		if (j==n) pts[n++] = p3;
	}

	f->Wentier(n);
	f->Wchaine("\n");
	for (i=0; i<n; i+=1) 
		Ecrire_PointVol(f, pts[i]);
	
	f->Wentier(Nb_Triangle());
	f->Wchaine("\n");

	for (i=1; i<=Nb_Triangle(); i+=1) 
	{
		tri = Ieme_Triangle (i);
		Pts_Triangle (tri, &p1,&p2,&p3);

		for (j=0; j<n; j+=1) if (p1 == pts[j]) break;
		f->Wentier(j+1);
		f->Wchaine(" ");

		for (j=0; j<n; j+=1) if (p2 == pts[j]) break;
		f->Wentier(j+1);
		f->Wchaine(" ");

		for (j=0; j<n; j+=1) if (p3 == pts[j]) break;
		f->Wentier(j+1);
		f->Wchaine("\n");
	}

	Ecrire_Attributs (f, attributs());
}
 
void	Vide::Ecrire (Fichier *f) const
{
}

void	Ensemble::Ecrire (Fichier *f)
{
	if (composantes() == 0) return;

	if (Deja_Ecrit(*f, *this)) return;

	f->Wchaine("OC ");
	if (!arbre) {f->Wentier(numero());}
	 f->Wchaine("\n");

	for (entier i=1; i<=composantes(); i+=1) 
	{
		composante(i)->Ecrire(f);
		//if (composante(i)->type() != unVide && (composante(i)->type()!=unEnsemble || ((Ensemble*)composante(i))->composantes()!=0)) Ecrire_Attributs(f, attributs(i));
	}
	f->Wchaine("FI\n");

	Ecrire_Attributs (f, attributs());
}
