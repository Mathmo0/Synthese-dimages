
#include "polygone.h"
#include "geo.h"
#include "erreur.h"
#include "utilreel.h"
#include "utilalg.h"
#include "definition.h"

#include "alg.h"
#include "attr.h"
#include "transfo.h"
#include "englobe.h"

Polygone::Polygone ()
{
	s = unPolygone;
	nb = 0;
	liste = 0;
	defpl = FAUX;
	defconvex = FAUX;
}

void	Polygone::ajoute (entier i, const point& s)
{
	entier	n,j;
	struct _elem	*temp;

	n = nb++;
	if (i < 0 || i > n) Erreur(12, "");
	if (n == 0) {
		liste = new _elem;
	} else {
		temp = new struct _elem[n+1];
		for (j=0; j<n; j+=1) {
			temp[j] = liste[j];
		}
		delete liste;
		liste = temp;
	}
	for (j=n; j>i; j-=1) {
		liste[j] = liste[j-1];
	}
	liste[i].pt = s;
	liste[i].defpl = FAUX;
	liste[i].defconvexe = FAUX;
	defconvex = FAUX;
	this->Touche();
}

void	Polygone::ajoute (const point& s)
{
	ajoute (nb, s);
}

entier	Polygone::sommets () const
{
	return(nb);
}

const	point&	Polygone::sommet (entier i) const
{
	if (i<1 || i>nb) 
        Erreur(13, "");
	return(liste[i-1].pt);
}

void	Polygone::sommet (entier i, point* &pp)
{
	if (i<1 || i>nb) Erreur(13, "");
	pp = &liste[i-1].pt;
}

const	plan&	Polygone::mplan (entier i) const
{
	if (i<1 || i>nb) Erreur(13, "");

	if (!this->liste[i-1].defpl) {
		point	p1 = this->sommet(i);
		point	p2;
		if (i==this->sommets()) p2 = this->sommet(1);
		else p2 = this->sommet(i+1);
		vecteur	vn = this->mplan().normale();
		vecteur	n1 = vn^(p2-p1);
		((Polygone*)this)->liste[i-1].pl = plan(p1,n1);
		((Polygone*)this)->liste[i-1].defpl = VRAI;
	}
	return(liste[i-1].pl);
}

booleen	Polygone::convexe (entier i)
{
	if (i<1 || i>nb) Erreur(13, "");

	if (!this->liste[i-1].defconvexe) {
		vecteur	n1;
		if (i==1) n1 = this->mplan(this->sommets()).normale();
		else n1 = this->mplan(i-1).normale();
		vecteur	n2 = this->mplan(i).normale();
		liste[i-1].convexe = pp(this->mplan().normale() * (n1^n2), 0.0);
		liste[i-1].defconvexe = VRAI;
	}
	return(liste[i-1].convexe);
}

booleen	Polygone::convexe ()
{
	if (!this->defconvex) {
		booleen	conv=VRAI,conc=VRAI;
		for (entier i=1; i<=this->sommets(); i+=1) {
			conv &= this->convexe(i);
			conc &= !this->convexe(i);
		}
		convex = conv || conc;
		defconvex = VRAI;
	}
	return (convex);
}

const	plan&	Polygone::mplan () const
{
	if (!defpl) {
		((Polygone*)this)->pl = plan(this->sommet(1), this->sommet(2), this->sommet(3));
		((Polygone*)this)->defpl = VRAI;
	}
	return(pl);
}

void	Polygone::attributs (const Attributs& a)
{
	Attributs	b = a;

	b.transformation (N);

	Objet::attributs (b);
	for (entier i=0; i<nb; i+=1) {
		liste[i].pt = a.transformation().transforme(liste[i].pt);
		liste[i].defpl = FAUX;
	}
	if (defpl) pl = a.transformation().transforme(pl);
	Touche();
}

void	Polygone::attributs (Attributs* a)
{
	Attributs	b = *a;

	b.transformation (N);

	Objet::attributs (&b);
	for (entier i=0; i<nb; i+=1) {
		liste[i].pt = a->transformation().transforme(liste[i].pt);
		liste[i].defpl = FAUX;
	}
	if (defpl) pl = a->transformation().transforme(pl);
	Touche();
}

Objet*	Polygone::copie () const
{	
	Polygone *p = new Polygone;

	for (entier i=1; i<=this->sommets(); i+=1) {
		p->ajoute(this->liste[i-1].pt);
	}
	*(p->attr) = *(this->attr);
	p->defvol = this->defvol;
	if (this->defvol) p->vol = this->vol->copie();
	return(p);
}

Polygone::~Polygone ()
{
	delete this->liste;
}


booleen	Polygone::inter(const point& p, const vecteur& v, reel* k)
{
	plan	pl = this->mplan ();
	point	pi;

	reel	k2;

	if ( !pl.inter(p,v, &pi, &k2) ) 

		return FAUX;
	if ( pge(k2, *k) ) 

		return FAUX;

	if (this->convexe()) 

	{
		booleen	f=VRAI,f2=VRAI;
		reel	d;

		for (entier i=1; i<=this->sommets(); i+=1) 

		{
			d = this->mplan(i).distance(pi);
			f &= pp(d, 0.0);
			f2 &= pg(d, 0.0);
			if (!f && !f2) return FAUX;
		}
		*k = k2;
		return VRAI;
	} 

	else 

	{
		point	p1,p2;

		booleen	a,b,f=FAUX;
		booleen	a2,b2,f2=FAUX;

		vecteur v2,n1,n2;

		reel d = this->mplan(1).distance(pi);
		a = pp(d, 0.0);
		a2 = pg(d, 0.0);

		for (entier i=1; i<=this->sommets(); i+=1) 

		{
			//d = this->mplan(i).distance(pi);
			//a = pp(d, 0.0);
			//a2 = pg(d, 0.0);

			if (i==this->sommets()) 

			{
				d = this->mplan(1).distance(pi);
				b = pp(d, 0.0);
				b2 = pg(d, 0.0);
				if (this->convexe(1)) {
					f ^= (!a && b);
					f2 ^= (!a2 && b2);
				} else {
					f ^= (a && !b);
					f2 ^= (a2 && !b2);
				}
			} 

			else 

			{
				d = this->mplan(i+1).distance(pi);
				b = pp(d, 0.0);
				b2 = pg(d, 0.0);
				if (this->convexe(i+1)) 

				{
					f ^= (!a && b);
					f2 ^= (!a2 && b2);
				} 

				else 

				{
					f ^= (a && !b);
					f2 ^= (a2 && !b2);
				}
			}
			a = b; a2 = b2;
		}


		if (!f || !f2) 

		{ 

			*k = k2; 

			return VRAI; 

		}
		else 

			return FAUX;
	}
}

vecteur	Polygone::gradient(const point&p)
{
	return(-this->mplan().normale());
}

point	Polygone::unpoint()
{
	return(sommet(1));
}

static	const	reel	eps=0.01;

const	Englobant&    Polygone::volume() const
{
	if (!defvol) {
        	Transformation  t = Alignement(this->mplan().normale(),Z) * Deplacement(O-this->sommet(1));
 
        	reel    xmin=INFINI,ymin=INFINI;
        	reel    xmax=-INFINI,ymax=-INFINI;
        	point   p;
 
        	for (entier i=1; i<=this->sommets(); i+=1) {
                	p = t.transforme(this->sommet(i));
                	if (p.x()<xmin) xmin = p.x();
                	if (p.y()<ymin) ymin = p.y();
                	if (p.x()>xmax) xmax = p.x();
                	if (p.y()>ymax) ymax = p.y();
        	}
 
        	if (!pg(xmax,xmin)) { xmin -= eps; xmax += eps; }
        	if (!pg(ymax,ymin)) { ymin -= eps; ymax += eps; }
 
        	reel    zmax = (xmax - xmin)*eps;
        	reel    zmin = -zmax;
 
        	((Objet*)this)->vol = new Carre(t.inverse() *
                        	Deplacement(point(xmin,ymin,0.0) - O) *
                        	Homothetie (O,X, xmax-xmin) *
                        	Homothetie (O,Y, ymax-ymin) *
                        	Homothetie (O,Z, zmax-zmin));
        	((Objet*)this)->defvol = VRAI;
	}
        return *vol;
}
 