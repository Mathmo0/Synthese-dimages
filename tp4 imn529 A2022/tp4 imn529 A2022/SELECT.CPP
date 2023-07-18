#include "select.h"
#include "utilreel.h"
#include "eps.h"
#include "objets.h"
#include "global.h"

static	booleen	Atome_Inter(Objet* o, const Attributs& a, const point& p, const vecteur& v, reel* k, Ensemble* &o2)
{
	booleen	inter;

	Transformation t = a.transformation();

	switch (o->type()) {
		case unSegment : inter = Segment_Inter((Segment &)*o, t, p,v, k); break;
		case unPoint : inter = Point_Inter((Point &)*o, t, p,v, k); break;
		default : inter = o->inter(t.inverse(p),t.inverse(v), k); break;
	}
	if (inter) {
		o2 = new Ensemble;
		o2->ajoute(o,ATTR);
	}
	return inter;
}


static	booleen	Select_Objet (Objet* o, const Attributs& a, const point& p, const vecteur& v, reel *k, Ensemble* &o2)
{
	if (profondeur==0) return FAUX;
	if (hidetoselect && (a*o->attributs()).hide()) return FAUX;

	if (o->type() == unEnsemble) 
	{
       	if (volumeenglobant && !o->volume().inter(a.transformation().inverse(p),a.transformation().inverse(v),k)) 
			return FAUX;

		Ensemble *temp;
		entier	i,j;
		reel	k2;
		Attributs a2 = a * o->attributs();
		booleen	inter=FAUX;

		for (i=1; i<=((Ensemble*)o)->composantes (); i+=1) 
		{
			k2 = *k;
			profondeur -= 1;
			if (Select_Objet (((Ensemble*)o)->composante (i), a2, p,v, &k2, temp)) {
				if (temp->type() == unPoint && !(inter && o2->type() == unPoint)) k2 -= epselect; // ???
				if (pp(k2, *k)) 
				{
					if (inter) 
						o2->detruire();
					o2 = new Ensemble;
                	o2->ajoute(o,ATTR);
				    for (j=1; j<=temp->composantes (); j+=1) 
                		o2->ajoute(((Ensemble*)temp->composante (j))->composante(1), o->attributs() * temp->composante(j)->attributs());
					temp->detruire();
					*k = k2;
					inter = VRAI;
				} 
				else 
					delete temp;
			}
			profondeur += 1;
		}
		return inter;
	} 
	else 
		return Atome_Inter(o, a, p,v, k, o2);
}

booleen	Select_Objet (Objet* o, const point& p, const vecteur& v, reel *k, Ensemble* &o2)
{
	*k = INFINI;
	return Select_Objet (o, ATTR, p,v,k, o2);
}


static	booleen	Polygone_Composante(Polygone& o, const Transformation& t, const point& p, const vecteur& v, reel* k, Objet* &c)
{
        if (volumeenglobant && !o.volume().inter(t.inverse(p),t.inverse(v),k)) return(FAUX);
	point	pt;
	entier i;

	for (i=1; i<=o.sommets(); i+=1) {
		pt = o.sommet(i);
		if (Select_Point(t.transforme(pt),p,v,k)) {
			c = new Point(t.transforme(pt));
			return VRAI;
		}
	}

	point	p1,p2;

	for (i=1; i<=o.sommets(); i+=1) {
		p1 = o.sommet(i);
		if (i==o.sommets()) p2 = o.sommet(1);
		else p2 = o.sommet(i+1);
		if (Select_Segment(t.transforme(p1),t.transforme(p2),p,v,k)) {
			c = new Segment(t.transforme(p1),t.transforme(p2));
			return VRAI;
		}
	}

	if (o.inter(t.inverse(p),t.inverse(v), k)) 
	{
		c = new Plan(t.transforme(o.mplan()));
		return VRAI;
	}

	return FAUX;
}

static	booleen	Sphere_Composante(Sphere& o, const Transformation& t, const point& p, const vecteur& v, reel* k, Objet* &c)
{
	if (o.inter(t.inverse(p),t.inverse(v), k)) {
		c = new Point((t * o.attributs().transformation()).transforme(O));
		return VRAI;
	}
	return FAUX;
}

static	booleen	Plan_Composante(Plan& o, const Transformation& t, const point& p, const vecteur& v, reel* k, Objet* &c)
{
	if (o.inter(t.inverse(p),t.inverse(v), k)) {
		c = new Plan(t.transforme(o.mplan()));
		return VRAI;
	}
	return FAUX;
}

static	booleen	Segment_Composante(const Segment& o, const Transformation& t, const point& p, const vecteur& v, reel* k, Objet* &c)
{
	if (Select_Point(t.transforme(o.p1()), p,v,k)) {
		c = new Point(t.transforme(o.p1()));
		return VRAI;
	}
	if (Select_Point(t.transforme(o.p2()), p,v,k)) {
		c = new Point(t.transforme(o.p2()));
		return VRAI;
	}
	if (Select_Segment(t.transforme(o.p1()),t.transforme(o.p2()), p,v,k)) {
		c = new Segment(t.transforme(o.p1()),t.transforme(o.p2()));
		return VRAI;
	}
	return FAUX;
}

static	booleen	Cylindre_Composante(Cylindre& o, const Transformation& t, const point& p, const vecteur& v, reel* k, Objet* &c)
{
	if (o.inter(t.inverse(p),t.inverse(v), k)) {
		c = new Segment((t * o.attributs().transformation()).transforme(O), (t * o.attributs().transformation()).transforme(point(1.0,0.0,0.0)));
		Objet	*c2;
		if (Segment_Composante((Segment&)*c, N,p,v, k, c2)) {
			delete c;
			c = c2;
		}
		return VRAI;
	}
	return FAUX;
}

static	booleen	Point_Composante(const Point& o, const Transformation& t, const point& p, const vecteur& v, reel* k, Objet* &c)
{
	if (Select_Point(t.transforme(o.pt()), p,v,k)) {
		c = new Point(t.transforme(o.pt()));
		return VRAI;
	}
	return FAUX;
}

static	booleen	Volume_Composante(const Volume& o, const Transformation& t, const point& p, const vecteur& v, reel* k, Objet* &c)
{
	Triangle tri;
	PointVol p1,p2,p3;
	entier i;

	for (i=1; i<=o.Nb_Triangle(); i+=1) {
		tri = o.Ieme_Triangle (i);
		Pts_Triangle (tri, &p1,&p2,&p3);

		if (Select_Point(t.transforme(*p1), p,v,k)) {
			c = new Point(t.transforme(*p1));
			return VRAI;
		}
		if (Select_Point(t.transforme(*p2), p,v,k)) {
			c = new Point(t.transforme(*p2));
			return VRAI;
		}
		if (Select_Point(t.transforme(*p3), p,v,k)) {
			c = new Point(t.transforme(*p3));
			return VRAI;
		}
	}
	for (i=1; i<=o.Nb_Triangle(); i+=1) {
		tri = o.Ieme_Triangle (i);
		Pts_Triangle (tri, &p1,&p2,&p3);

		if (Select_Segment(t.transforme(*p1),t.transforme(*p2), p,v,k)) {
			c = new Segment(t.transforme(*p1),t.transforme(*p2));
			return VRAI;
		}
		if (Select_Segment(t.transforme(*p2),t.transforme(*p3), p,v,k)) {
			c = new Segment(t.transforme(*p2),t.transforme(*p3));
			return VRAI;
		}
		if (Select_Segment(t.transforme(*p3),t.transforme(*p1), p,v,k)) {
			c = new Segment(t.transforme(*p3),t.transforme(*p1));
			return VRAI;
		}
	}
	// ... triangles...
	return FAUX;
}

static	booleen	Atome_Composante(const Objet& o, const Transformation& t, const point& p, const vecteur& v, reel* k, Objet* &c)
{
	switch (o.type()) {
		case unPolygone : return Polygone_Composante((Polygone &)o, t, p,v, k, c);
		case uneSphere : return Sphere_Composante((Sphere &)o, t, p,v, k, c);
		case unCylindre : return Cylindre_Composante((Cylindre &)o, t, p,v, k, c);
		case unPlan : return Plan_Composante((Plan &)o, t, p,v, k, c);
		case unSegment : return Segment_Composante((Segment &)o, t, p,v, k, c);
		case unPoint : return Point_Composante((Point &)o, t, p,v, k, c);
		case unVolume : return Volume_Composante((Volume &)o, t, p,v, k, c);
		default : return FAUX;
	}
}

static	booleen	Select_Composante(const Objet& o, const Transformation& t, const point& p, const vecteur& v, reel *k, Objet* &o2, entier n)
{
	if (n==0) return FAUX;

	if (hidetoselect && o.attributs().hide()) return FAUX;

	if (o.type() == unEnsemble) 
	{
		Objet	*temp;
		entier	i;
		reel	k2;
		Transformation t2 = t * o.attributs().transformation();
		booleen	inter=FAUX;

		*k = INFINI;
		for (i=1; i<=((Ensemble&)o).composantes (); i+=1) {
			k2 = *k;
			if (Select_Composante (*((Ensemble&)o).composante (i), t2, p,v, &k2, temp, n-1)) {
				if (temp->type() == unPoint && !(inter && o2->type() == unPoint)) 
					k2 -= epselect;
				if (pp(k2, *k)) 
				{
					if (inter) delete o2;
					o2 = temp;
					//o2->attributs(o.attributs() * ((Ensemble&)o).attributs(i));
					*k = k2;
					inter = VRAI;
				} else delete temp;
			}
		}
		//if (inter) o2->attributs(o.attributs());
		return inter;
	} else return Atome_Composante(o, t, p,v, k, o2);
}

booleen	Select_Composante(const Objet& o, const point& p, const vecteur& v, reel *k, Objet* &o2)
{
	return Select_Composante(o, N, p,v.unitaire(),k, o2, profondeur);
}

