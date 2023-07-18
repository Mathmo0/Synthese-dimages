#include "designateur.h"

#include "util.h"

#include "canon.h"

#include "geo.h"

#include "utilalg.h"

#include "utilreel.h"

#include "objets.h"



/**********************  TP4 *************************************************/

/*                                                                           */

/*  NOMS et MATRICULES                                                       */

/*                                                                           */

/*                                                                           */

/*                                                                           */

/*                                                                           */

/*****************************************************************************/

/* OkTransformation() : applique l'attribut de la selection (m_a0) sur       */  						     

/*                 l'objet selectionne.                                      */

/*                                                                           */

/*****************************************************************************/

  

void Designateur::OkTransformation()

{

	if ( OkComposante() == VRAI && OkSelection() )

	{

		Attributs Ts;

		Attributs Rs;

		Attributs Rs_Inv;

		Attributs Total;



		Objet* sel = Selection();

		Rs     = sel->attributs();

		Rs_Inv = Rs.inverse();

		Ts     = sel->composante(1)->attributs();

  

		Total = Rs_Inv*m_a0*Rs*Ts;

 

		sel->composante(1)->attributs( &Total );



		delete sel;

		sel = new Ensemble;

		m_a0 = ATTR;

		OkComposante(FAUX);

		OkSelection(FAUX);

	}

}





/*****************************************************************************/

/* Translation() : construit une translation a partir du segment             */  						     

/*                 selectionne. Ensuite, concatène la translation à          */

/*                 l'attribut de la selection (m_a0)                         */

/*                                                                           */

/*****************************************************************************/

void Designateur::Translation(reel ktrans)

{



}



/*****************************************************************************/

/* HomothetieX() :  Contruit une homothetie selon la selection soit un point,*/                                                         

/*                  un segment ou un plan. Le tout d'un facteur xhomo.       */

/*                  Ensuite, concatène l'homothtie a                         */

/*                  l'attribut de la selection (m_a0)                        */

/*                                                                           */

/*                                                                           */

/*****************************************************************************/

void Designateur::Homothetie(reel xhomo)

{

}



/*****************************************************************************/

/* Rotation() : Construit une rotation a partir du segment selectionne.      */

/*              Le tout d'un facteur teta.                                   */

/*              Ensuite, concatène la rotation a                             */

/*              l'attribut de la selection (m_a0)                            */

/*                                                                           */

/*****************************************************************************/

void Designateur::Rotation(reel teta)

{

}

