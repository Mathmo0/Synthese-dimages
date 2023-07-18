
#include "parti.h"
#include "select.h"
#include "eps.h"
#include "utilreel.h"
#include "objets.h"

#include "definition.h"
#include "transfo.h"
#include "attr.h"
#include "englobe.h"
#include "global.h"


static	booleen	Polygone_Particule(Polygone& o, const Transformation& t, const point& p, const vecteur& v, reel* k, Particule* &c)
{
	point	*pt;

	for (entier i=1; i<=o.sommets(); i+=1) {
		o.sommet(i, pt);
		if (Select_Point(t.transforme(*pt),p,v,k)) {
			c = new Particule(pt);
			c->attributs(Attributs(t));
			return VRAI;
		}
	}

	return FAUX;
}


static	booleen	Segment_Particule(Segment& o, const Transformation& t, const point& p, const vecteur& v, reel* k, Particule* &c)
{
	point	*pt;

	o.p1(pt);
	if (Select_Point(t.transforme(*pt), p,v,k)) {
		c = new Particule(pt);
		c->attributs(Attributs(t));
		return VRAI;
	}
	o.p2(pt);
	if (Select_Point(t.transforme(*pt), p,v,k)) {
		c = new Particule(pt);
		c->attributs(Attributs(t));
		return VRAI;
	}
	return FAUX;
}

static	booleen	Point_Particule(Point& o, const Transformation& t, const point& p, const vecteur& v, reel* k, Particule* &c)
{
	point	*pt;

	o.pt(pt);
	if (Select_Point(t.transforme(*pt), p,v,k)) {
		c = new Particule(pt);
		c->attributs(Attributs(t));
		return VRAI;
	}
	return FAUX;
}

static	booleen	Volume_Particule(const Volume& o, const Transformation& t, const point& p, const vecteur& v, reel* k, Particule* &c)
{
	Triangle tri;
	PointVol p1,p2,p3;

	for (entier i=1; i<=o.Nb_Triangle(); i+=1) {
		tri = o.Ieme_Triangle (i);
		Pts_Triangle (tri, &p1,&p2,&p3);

		if (Select_Point(t.transforme(*p1), p,v,k)) {
			c = new Particule(p1);
			c->attributs(Attributs(t));
			return VRAI;
		}
		if (Select_Point(t.transforme(*p2), p,v,k)) {
			c = new Particule(p2);
			c->attributs(Attributs(t));
			return VRAI;
		}
		if (Select_Point(t.transforme(*p3), p,v,k)) {
			c = new Particule(p3);
			c->attributs(Attributs(t));
			return VRAI;
		}
	}
	return FAUX;
}

static	booleen	Atome_Particule(const Objet& o, const Transformation& t, const point& p, const vecteur& v, reel* k, Particule* &c)
{
	switch (o.type()) {
		case unPolygone : return Polygone_Particule((Polygone &)o, t, p,v, k, c);
		case unSegment : return Segment_Particule((Segment &)o, t, p,v, k, c);
		case unPoint : return Point_Particule((Point &)o, t, p,v, k, c);
		case unVolume : return Volume_Particule((Volume &)o, t, p,v, k, c);
		default : return FAUX;
	}
}


booleen	Select_Particule (Objet* o, const Transformation& t, const point& p, const vecteur& v, reel *k, Particule* &o2)
{
	if (hidetoselect && o->attributs().hide()) return FAUX;
        if (volumeenglobant && !o->volume().inter(t.inverse(p),t.inverse(v),k)) return(FAUX);

	booleen	inter=FAUX;

	if (o->type() == unEnsemble) {
		Particule *temp;
		reel	k2;
		Transformation t2 = t * o->attributs().transformation();

		*k = INFINI;
		for (entier i=1; i<=((Ensemble*)o)->composantes (); i+=1) {
			k2 = *k;
			if (Select_Particule (((Ensemble*)o)->composante (i), t2, p,v, &k2, temp)) {
                                if (temp->type() == unPoint && !(inter && o2->type() == unPoint)) k2 -= epselect;
				if (pp(k2, *k)) {
					if (inter) delete o2;
					o2 = temp;
					//o2->attributs(((Ensemble*)o)->attributs(i));
					*k = k2;
					inter = VRAI;
				} else delete temp;
			}
		}
	} else {
		inter = Atome_Particule(*o,t, p,v, k,o2);
	}
	return inter;
}

booleen	Select_Particule (Objet* o, const point& p, const vecteur& v, reel *k, Particule* &o2)
{
	return Select_Particule (o,N,p,v,k,o2);
}

