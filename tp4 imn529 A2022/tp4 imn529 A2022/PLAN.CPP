
#include "plan.h"
#include "geo.h"
#include "utilreel.h"
#include "utilalg.h"
#include "transfo.h"
#include "definition.h"
#include "alg.h"
#include "attr.h"
#include "englobe.h"

Plan::Plan ()
{
	s = unPlan;
}

Plan::Plan (const plan& x)
{
	s = unPlan;
	p = x;
}

const	plan&	Plan::mplan () const
{
	return(p);
}

void	Plan::attributs (const Attributs& a)
{
	Attributs	b = a;

	b.transformation (N);

	Objet::attributs (b);
	p = a.transformation().transforme(p);
	Touche();
}

void	Plan::attributs (const Attributs* a)
{
	Attributs	b = *a;

	b.transformation (N);

	Objet::attributs (&b);
	p = a->transformation().transforme(p);
	Touche();
}

Transformation  Plan::Homothetie(const reel& scal) const
{
        return ::Homothetie(this->mplan().mpoint(), this->mplan().normale(), scal);
}

Transformation  Plan::HomothetieUnitaire(const reel&) const
{
	return N;
}

Transformation  Plan::Rotation(const reel&) const
{
	return N;
}

Transformation  Plan::Deplacement() const
{
	return N;
}

Transformation  Plan::DeplacementUnitaire(const reel& unite) const
{
        return ::Deplacement(this->mplan().normale() * unite);
}

Objet*	Plan::copie () const
{
	Plan	*o = new Plan;

	*o = *this;
	if (this->defvol) o->vol = this->vol->copie();
	return(o);
}

booleen	Plan::inter(const point& p, const vecteur& v, reel* k)
{
	point	pi;
	reel	k2;

	if (!this->mplan().inter(p,v, &pi, &k2)) return FAUX;
	if (pge(k2, *k)) return FAUX;

	*k = k2;
	return VRAI;
}

vecteur	Plan::gradient(const point&p)
{
	return(this->mplan().normale());
}
point	Plan::unpoint() 
{
	return(this->mplan().mpoint());
}

const   Englobant&    Plan::volume() const
{
        if (!defvol) {
                ((Objet*)this)->vol = new Infini();
                ((Objet*)this)->defvol = VRAI;
        }
	return *vol;
}

