
#include "vide.h"
#include "englobe.h"

Vide::Vide ()
{
	s = unVide;
}

void	Vide::attributs (const Attributs& a)
{
}

Objet*	Vide::copie () const
{
	Vide	*o = new Vide;

	o->attr = this->attr;
	o->defvol = this->defvol;
	if (this->defvol) o->vol = this->vol->copie();
	return(o);
}

const	Englobant&    Vide::volume() const
{
        if (!defvol) {
		((Objet*)this)->vol = new VolVide();
	        ((Objet*)this)->defvol = VRAI;
	}
        return *vol;
}

