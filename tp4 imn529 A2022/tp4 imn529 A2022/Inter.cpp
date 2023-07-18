
#include "inter.h"
#include "utilalg.h"
#include "objet.h"
#include "ensemble.h"
#include "englobe.h"
#include "attr.h"
#include "couleur.h"
#include "couleurs.h"
#include "definition.h"

#include "global.h"


/*booleen	T_Objet_Inter (Objet& o, const Attributs& a, const point& p, const vecteur& v, reel k, Couleur* c, entier n)
{
	if (n==0) return FAUX;

	Attributs	a2 = a * o.attributs();
	if (hidetorender && a2.hide()) return FAUX;

	if (volumeenglobant && !o.volume().inter(p,v,&k)) return(FAUX);

	if (o.type() == unEnsemble) {
		Couleur c2;
		booleen	inter=FAUX;

		*c = BLANC;

		const	Transformation *t = &(o.attributs().transformation());
		point	p2 = t->inverse(p);
		vecteur	v2 = t->inverse(v);

		for (entier i=1; i<=((Ensemble&)o).composantes (); i+=1) {
			if (T_Objet_Inter (*((Ensemble&)o).composante (i), a2, p2,v2,k, &c2, n-1)) {
				inter = VRAI;
				if (c2 == NOIR) { *c = NOIR; break; }
				else *c = *c * c2;
			}
		}
		return(inter);
	} else {
		reel	k2 = k;
		booleen	inter = o.inter(p,v, &k2);
		if (inter) {
			*c = a2.ombre();
			if (*c == BLANC) return FAUX;
		}
		return inter;
	}
}
*/


/*
booleen	T_Objet_Inter (Objet& o, const point& p, const vecteur& v, const reel& k, Couleur* c)
{
	return T_Objet_Inter (o, ATTR, p,v,k, c, profondeur);
}
*/


booleen	Objet_Inter (Objet& o, const point& p, const vecteur& v, reel *k, vecteur *vn, Attributs* a, entier n)
{
	if (n==0) return FAUX;
	if (hidetorender && o.attributs().hide()) return FAUX;

	//k2 = *k;
	//if (!o.volume().inter(p,v, &k2)) return(FAUX);
	if (volumeenglobant && !o.volume().inter(p,v,k)) return(FAUX);

	if (o.type() == unEnsemble) 

	{
		vecteur	vn2;
		booleen	inter=FAUX;

		Attributs	a2;
		reel	k2;

		const	Transformation *t = &(o.attributs().transformation());
		point	p2 = t->inverse(p);
		vecteur	v2 = t->inverse(v);

		for (entier i=1; i<=((Ensemble&)o).composantes(); i+=1) 

		{
			k2 = *k;
			if (Objet_Inter (*((Ensemble&)o).composante(i), p2,v2, &k2, &vn2, &a2, n-1)) 

			{
				*a = o.attributs() * a2;
				*vn = vn2;
				*k = k2;
				inter = VRAI;
			}
		}
		return(inter);
	} 

	else 

	{
		reel	k2 = *k;
		booleen	inter = o.inter(p,v, &k2);
		if (inter) 

        {
			*k = k2;
			*a = o.attributs();
			*vn = o.gradient(p + *k*v);
		}
		return(inter);
	}
}

booleen	Objet_Inter (Objet& o, const point& p, const vecteur& v, reel *k, vecteur *vn, Couleurs* c)
{
	Attributs	a;
	reel	k2 = INFINI;

	if (Objet_Inter (o, p,v, &k2,vn,&a, profondeur)) 

	{
		if (!(hidetorender && a.hide())) 

		{
			*c = a.couleurs(); // p + k2*v ?
			*vn = a.transformation().transforme(plan(O,*vn)).normale();
			*k = k2;
			return VRAI;
		} 

		else 

			return FAUX;
	} 

	else 

		return FAUX;
}

