
#include "particule.h"
#include "englobe.h"

Particule::Particule ()
{
	s = uneParticule;
}

Particule::Particule (point *pp)
{
	s = uneParticule;
	p = pp;
}

point	*Particule::pt () const
{
	return p;
}

void	Particule::attributs (const Attributs& a)
{
	Objet::attributs(a);
	//*p = (attr.transformation().inverse() * a.transformation() * attr.transformation()).transforme(*p);
}

Objet*	Particule::copie () const
{
	Particule *o = new Particule;

	*o = *this;
	if (this->defvol) o->vol = this->vol->copie();
	return(o);
}

const	Englobant&    Particule::volume() const
{
	if (!defvol) {
        	((Objet*)this)->vol = new VolVide();
        	((Objet*)this)->defvol = VRAI;
	}
        return *vol;
}
 
