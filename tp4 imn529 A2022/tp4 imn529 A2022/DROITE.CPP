
#include "droite.h"
#include "geo.h"
#include "utilalg.h"
#include "transfo.h"
#include "definition.h"
#include "alg.h"
#include "attr.h"
#include "englobe.h"

Droite::Droite ()
{
	s = uneDroite;
}

Droite::Droite (const droite& x)
{
	s = uneDroite;
	d = x;
}

const	droite&	Droite::mdroite () const
{
	return(d);
}

void	Droite::attributs (const Attributs& a)
{
	Attributs	b = a;

	b.transformation (N);

	Objet::attributs (b);
	d = a.transformation().transforme(d);
	Touche();
}

void	Droite::attributs (const Attributs* a)
{
	Attributs	b = *a;

	b.transformation (N);

	Objet::attributs (&b);
	d = a->transformation().transforme(d);
	Touche();
}

Transformation  Droite::Homothetie(const reel& scal) const
{
        return ::Deplacement(d.mpoint() - O) * Alignement(X, d.mvecteur()) * ::Homothetie(O, Y, scal) * ::Homothetie(O,Z, scal) * Alignement(d.mvecteur(), X) * ::Deplacement(O - d.mpoint());
}

Transformation  Droite::HomothetieUnitaire(const reel&) const
{
	return N;
}

Transformation  Droite::Rotation(const reel& angle) const
{
        return ::Rotation(d.mpoint(), d.mvecteur(), angle);
}

Transformation  Droite::Deplacement() const
{
	return N;
}

Transformation  Droite::DeplacementUnitaire(const reel& unite) const
{
        return ::Deplacement(d.mvecteur().unitaire() * unite);
}


Objet*	Droite::copie () const
{
	Droite	*o = new Droite;

	*o = *this;
	if (this->defvol) o->vol = this->vol->copie();
	return(o);
}

const	Englobant&    Droite::volume() const
{
        if (!defvol) {
		((Objet*)this)->vol = new VolVide();
		((Objet*)this)->defvol = VRAI;
	}
	return *vol;
}

