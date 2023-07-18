//*******************************************************************

//*																	*

//* Programme: attr.cpp												*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation des attributs.									*

//*																	*

//*******************************************************************



#include "attr.h"



const Attributs	ATTR;


#ifdef INLINE
inline
#endif
Attributs::Attributs ()
{
	defin = defhl = deft = FAUX;
	h = AUCUN;
	l = AUCUN;
}

#ifdef INLINE
inline
#endif
Attributs::Attributs (const Couleur&c)
{
	defin = defhl = deft = FAUX;
	h = AUCUN;
	l = AUCUN;


	diffus(c);

	t_diffus(c);

	speculaire(c);

	t_speculaire(c);

	ambiant(c);

	t_ambiant(c);

	reflechi(c);

	transmis(c);

	ombre(c);

	emis(c);

}


#ifdef INLINE
inline
#endif
Attributs::Attributs (const booleen& c)
{
	defin = defhl = deft = FAUX;
	h = AUCUN;
	l = AUCUN;
	this->highlight(c);
}

#ifdef INLINE
inline
#endif
Attributs::Attributs (const Transformation& c)
{
	defin = defhl = deft = FAUX;
	h = AUCUN;
	l = AUCUN;
	this->transformation(c);
}

#ifdef INLINE
inline
#endif
Couleurs Attributs::couleurs() const
{
	Couleurs	c;

	c.diffus(cd.defined()?cd.couleur():NOIR);
	c.speculaire(cs.defined()?cs.couleur():NOIR);
	c.t_diffus(td.defined()?td.couleur():NOIR);
	c.t_speculaire(ts.defined()?ts.couleur():NOIR);
	c.ambiant(ca.defined()?ca.couleur():NOIR);
	c.t_ambiant(ta.defined()?ta.couleur():NOIR);
	c.reflechi(cr.defined()?cr.couleur():NOIR);
	c.transmis(ct.defined()?ct.couleur():NOIR);
	c.ombre(co.defined()?co.couleur():NOIR);
	c.emis(ce.defined()?ce.couleur():NOIR);

	return c;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Attributs::diffus () const
{
	return(cd.defined()?cd.couleur():NOIR);
}

#ifdef INLINE
inline
#endif
void	Attributs::diffus (const Couleur& c)
{
	cd = Coefficient(c);
}

#ifdef INLINE
inline
#endif
void	Attributs::diffus (const Coefficient& c)
{
	cd = c;
}

#ifdef INLINE
inline
#endif
void	Attributs::diffus (Coefficient* &c)
{
	c = &cd;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Attributs::speculaire () const
{
	return(cs.defined()?cs.couleur():NOIR);
}

#ifdef INLINE
inline
#endif
void	Attributs::speculaire (const Couleur& c)
{
	cs = Coefficient(c);
}

#ifdef INLINE
inline
#endif
void	Attributs::speculaire (const Coefficient& c)
{
	cs = c;
}

#ifdef INLINE
inline
#endif
void	Attributs::speculaire (Coefficient* &c)
{
	c = &cs;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Attributs::t_diffus () const
{
	return(td.defined()?td.couleur():NOIR);
}

#ifdef INLINE
inline
#endif
void	Attributs::t_diffus (const Couleur& c)
{
	td = Coefficient(c);
}

#ifdef INLINE
inline
#endif
void	Attributs::t_diffus (const Coefficient& c)
{
	td = c;
}

#ifdef INLINE
inline
#endif
void	Attributs::t_diffus (Coefficient* &c)
{
	c = &td;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Attributs::t_speculaire () const
{
	return(ts.defined()?ts.couleur():NOIR);
}

#ifdef INLINE
inline
#endif
void	Attributs::t_speculaire (const Couleur& c)
{
	ts = Coefficient(c);
}

#ifdef INLINE
inline
#endif
void	Attributs::t_speculaire (const Coefficient& c)
{
	ts = c;
}

#ifdef INLINE
inline
#endif
void	Attributs::t_speculaire (Coefficient* &c)
{
	c = &ts;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Attributs::reflechi () const
{
	return(cr.defined()?cr.couleur():NOIR);
}

#ifdef INLINE
inline
#endif
void	Attributs::reflechi (const Couleur& c)
{
	cr = Coefficient(c);
}

#ifdef INLINE
inline
#endif
void	Attributs::reflechi (const Coefficient& c)
{
	cr = c;
}

#ifdef INLINE
inline
#endif
void	Attributs::reflechi (Coefficient* &c)
{
	c = &cr;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Attributs::transmis () const
{
	return(ct.defined()?ct.couleur():NOIR);
}

#ifdef INLINE
inline
#endif
void	Attributs::transmis (const Couleur& c)
{
	ct = Coefficient(c);
}

#ifdef INLINE
inline
#endif
void	Attributs::transmis (const Coefficient& c)
{
	ct = c;
}

#ifdef INLINE
inline
#endif
void	Attributs::transmis (Coefficient* &c)
{
	c = &ct;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Attributs::ombre () const
{
	return(co.defined()?co.couleur():NOIR);
}

#ifdef INLINE
inline
#endif
void	Attributs::ombre (const Couleur& c)
{
	co = Coefficient(c);
}

#ifdef INLINE
inline
#endif
void	Attributs::ombre (const Coefficient& c)
{
	co = c;
}

#ifdef INLINE
inline
#endif
void	Attributs::ombre (Coefficient* &c)
{
	c = &co;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Attributs::emis () const
{
	return(ce.defined()?ce.couleur():NOIR);
}

#ifdef INLINE
inline
#endif
void	Attributs::emis (const Couleur& c)
{
	ce = Coefficient(c);
}

#ifdef INLINE
inline
#endif
void	Attributs::emis (const Coefficient& c)
{
	ce = c;
}

#ifdef INLINE
inline
#endif
void	Attributs::emis (Coefficient* &c)
{
	c = &ce;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Attributs::ambiant () const
{
	return(ca.defined()?ca.couleur():NOIR);
}

#ifdef INLINE
inline
#endif
void	Attributs::ambiant (const Couleur& c)
{
	ca = Coefficient(c);
}

#ifdef INLINE
inline
#endif
void	Attributs::ambiant (const Coefficient& c)
{
	ca = c;
}

#ifdef INLINE
inline
#endif
void	Attributs::ambiant (Coefficient* &c)
{
	c = &ca;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Attributs::t_ambiant () const
{
	return(ta.defined()?ta.couleur():NOIR);
}

#ifdef INLINE
inline
#endif
void	Attributs::t_ambiant (const Couleur& c)
{
	ta = Coefficient(c);
}

#ifdef INLINE
inline
#endif
void	Attributs::t_ambiant (const Coefficient& c)
{
	ta = c;
}

#ifdef INLINE
inline
#endif
void	Attributs::t_ambiant (Coefficient* &c)
{
	c = &ta;
}

#ifdef INLINE
inline
#endif
booleen	Attributs::hide () const
{
	return(h==VRAI);
}

#ifdef INLINE
inline
#endif
void	Attributs::hide (const trinary& h)
{
	Attributs::h = h;
}

#ifdef INLINE
inline
#endif
booleen	Attributs::lock () const
{
	return(l==VRAI);
}

#ifdef INLINE
inline
#endif
void	Attributs::lock (const trinary& l)
{
	Attributs::l = l;
}

#ifdef INLINE
inline
#endif
booleen	Attributs::highlight () const
{
	if (defhl) 

		return(hl);
	else 

		return(FAUX);
}

#ifdef INLINE
inline
#endif
void	Attributs::highlight (booleen nhl)
{
	hl = nhl;
	defhl = VRAI;
}


#ifdef INLINE
inline
#endif
booleen	Attributs::deftransformation () const
{
	return(deft);
}

#ifdef INLINE
inline
#endif
const	Transformation& Attributs::transformation() const
{
	if (deft) return(t);
	else return(N);
}

#ifdef INLINE
inline
#endif
void	Attributs::undeftransformation()
{
	deft = FAUX;
}

#ifdef INLINE
inline
#endif
void	Attributs::transformation(const Transformation& t)
{
	Attributs::t = t;
	deft = VRAI;
}

#ifdef INLINE
inline
#endif
Attributs	Attributs::operator*(const Attributs& a) const
{
	Attributs b;

	b.cd = this->cd * a.cd;
	b.td = this->td * a.td;
	b.cs = this->cs * a.cs;
	b.ts = this->ts * a.ts;
	b.ca = this->ca * a.ca;
	b.ta = this->ta * a.ta;
	b.cr = this->cr * a.cr;
	b.ct = this->ct * a.ct;
	b.co = this->co * a.co;
	b.ce = this->ce * a.ce;

	if (this->defhl) 

	{
		if (a.defhl) 

			b.hl = this->hl || a.hl; // undef hl ?
		else 

			b.hl = this->hl;
		b.defhl = VRAI;
	} 

	else 

	{
		if (a.defhl) 

		{
			b.hl = a.hl;
			b.defhl = VRAI;
		} 

		else 

			b.defhl = FAUX;
	}

	if (a.h == VRAI) 

	{
		b.h = VRAI;
	} 

	else 

	{
		if (a.h == FAUX) 

		{
			b.h = AUCUN;
		} 

		else 

		{
			b.h = this->h;
		}
	}

	if (a.l == VRAI) 

	{
		b.l = VRAI;
	} 

	else 

	{
		if (a.l == FAUX) 

		{
			b.l = AUCUN;
		} 

		else 

		{ // a.l == AUCUN
			b.l = this->l;
		}
	}

	if (this->deft) 

	{
		if (a.deft) 

			b.t = this->t * a.t;
		else 

			b.t = this->t;
		b.deft = VRAI;
	} 

	else 

	{
		if (a.deft) 

		{
			b.t = a.t;
			b.deft = VRAI;
		} 

		else 

			b.deft = FAUX;
	}

	return(b);
}

#ifdef INLINE
inline
#endif
Attributs	Attributs::inverse() const
{
	Attributs a;

	a = *this;
	if (this->deft) a.t = this->t.inverse();

	return(a);
}


#ifdef INLINE
inline
#endif
const Attributs& Attributs::operator = ( const Attributs& attr )
{
	defhl = attr.defhl;
    defin = attr.defin;
    deft = attr.deft;
	hl = attr.h;
	h = attr.h;

	l = attr.l;
	cd = attr.cd;
	td = attr.td;

	cs = attr.cs;

	ts = attr.ts;

	ca = attr.ca;

	ta = attr.ta;

	cr = attr.cr;

	ct = attr.ct;

	co = attr.co;

	ce = attr.ce;


	t = attr.t;

    return *this;
}
