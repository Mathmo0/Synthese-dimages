//*******************************************************************

//*																	*

//* Programme: couleurs.h											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Définition des couleurs.									*

//*			Diffus, Spéculaire, Ambien, Réfléchi, Transmis, Ombre	*

//*			Emis.													*

//*																	*

//*******************************************************************


#ifndef	_COULEURS
#define	_COULEURS


#include "couleur.h"


class Couleurs 

{
	Couleur	cd,td,cs,ts,ca,ta,cr,ct,co,ce;


public:
	Couleurs();

	const	Couleur&	diffus() const;
	void	diffus(const Couleur & c);

	const	Couleur&	speculaire() const;
	void	speculaire(const Couleur & c);

	const	Couleur&	t_diffus() const;
	void	t_diffus(const Couleur & c);

	const	Couleur&	t_speculaire() const;
	void	t_speculaire(const Couleur & c);

	const	Couleur&	ambiant() const;
	void	ambiant(const Couleur & c);

	const	Couleur&	t_ambiant() const;
	void	t_ambiant(const Couleur & c);

	const	Couleur&	reflechi() const;
	void	reflechi(const Couleur & c);

	const	Couleur&	transmis() const;
	void	transmis(const Couleur & c);

	const	Couleur&	ombre() const;
	void	ombre(const Couleur & c);

	const	Couleur&	emis() const;
	void	emis(const Couleur & c);
};

#endif

