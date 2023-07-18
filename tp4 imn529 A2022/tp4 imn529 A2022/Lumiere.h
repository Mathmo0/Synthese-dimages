//*******************************************************************

//*																	*

//* Programme: lumiere.h											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation d'une lumiere.									*

//*																	*

//*******************************************************************



#ifndef _LUMIERE

#define _LUMIERE



#include "transfo.h"

#include "couleur.h"



// type de lumiere
enum TypeLumiere
{
    unSpotlight,
    uneLumierePonctuelle

};


class Lumiere

{

protected:

	point m_Position;		//Point source lumineuse



	Couleur m_IntensiteAmbiante;	//Couleur ambiante de la source

	Couleur m_Intensite;	        //Couleur diffuse de la source

    Couleur m_EnergiePhoton;        // Puissance de la source lumineuse


	booleen m_bActive;		//Indique si la lumiere est active


    TypeLumiere m_Type;     // Indique le type de lumiere ( spotlight ou lumiere ordinaire )


public:

	Lumiere();

	Lumiere( TypeLumiere type, point pos, reel ra, reel ga, reel ba, reel rd, reel gd, reel bd, reel rph, reel gph, reel bph );

	~Lumiere() {}



	Lumiere(const Lumiere& l);

	virtual void operator=(const Lumiere& l);



	void Active(booleen b);

	const booleen& Active() const;



	const point& Position() const;

	void Position(const point& p);



	virtual const Couleur& IntensiteAmbiante() const;

	virtual const Couleur& Intensite() const;

    virtual const Couleur& EnergiePhoton() const; // puissance de la source lumineuse

//	virtual Couleur IntensiteAmbiante( point pt ) const;

//	virtual Couleur Intensite( point pt ) const;

    virtual vecteur RayonAleatoire( void ) const = 0;


	void IntensiteAmbiante(const Couleur& c);

	void Intensite(const Couleur& c);


    const TypeLumiere Type( void ) const;           // retourne le type de la lumiere

    virtual booleen Eclaire( const point& Point ) const { return VRAI; }

};



#endif


