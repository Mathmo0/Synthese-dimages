#include "scene.h"
#include "vision.h"



/* Affiche l'objet selon les parametres de vision. */

void	Affiche_Scene (const Objet& o, const Attributs& a)

{
//	Transformation v = Vision_Normee(p);
	Transformation v;



	o.Afficher(v, a);
}

