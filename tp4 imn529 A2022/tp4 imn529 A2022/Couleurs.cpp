//*******************************************************************

//*																	*

//* Programme: couleurs.cpp											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation des couleurs.									*

//*			Diffus, Spéculaire, Ambien, Réfléchi, Transmis, Ombre	*

//*			Emis.													*

//*																	*

//*******************************************************************



#include "couleurs.h"


#ifdef INLINE
inline
#endif
Couleurs::Couleurs ()
{
}

#ifdef INLINE
inline
#endif
const	Couleur&	Couleurs::diffus () const
{
	return(cd);
}

#ifdef INLINE
inline
#endif
void	Couleurs::diffus (const Couleur& c)
{
	cd = c;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Couleurs::speculaire () const
{
	return(cs);
}

#ifdef INLINE
inline
#endif
void	Couleurs::speculaire (const Couleur& c)
{
	cs = c;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Couleurs::t_diffus () const
{
	return(td);
}

#ifdef INLINE
inline
#endif
void	Couleurs::t_diffus (const Couleur& c)
{
	td = c;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Couleurs::t_speculaire () const
{
	return(ts);
}

#ifdef INLINE
inline
#endif
void	Couleurs::t_speculaire (const Couleur& c)
{
	ts = c;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Couleurs::reflechi () const
{
	return(cr);
}

#ifdef INLINE
inline
#endif
void	Couleurs::reflechi (const Couleur& c)
{
	cr = c;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Couleurs::transmis () const
{
	return(ct);
}

#ifdef INLINE
inline
#endif
void	Couleurs::transmis (const Couleur& c)
{
	ct = c;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Couleurs::ombre () const
{
	return(co);
}

#ifdef INLINE
inline
#endif
void	Couleurs::ombre (const Couleur& c)
{
	co = c;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Couleurs::emis () const
{
	return(ce);
}

#ifdef INLINE
inline
#endif
void	Couleurs::emis (const Couleur& c)
{
	ce = c;
}

#ifdef INLINE
inline
#endif
const	Couleur&	Couleurs::ambiant () const
{
	return(ca);
}

#ifdef INLINE
inline
#endif
const	Couleur&	Couleurs::t_ambiant () const
{
	return(ta);
}

#ifdef INLINE
inline
#endif
void	Couleurs::ambiant (const Couleur& c)
{
	ca = c;
}

#ifdef INLINE
inline
#endif
void	Couleurs::t_ambiant (const Couleur& c)
{
	ta = c;
}

