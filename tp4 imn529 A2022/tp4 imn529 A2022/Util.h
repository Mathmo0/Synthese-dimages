

#include "definition.h"
#include "alg.h"
#include "ensemble.h"
#include "polygone.h"
#include "objet.h"

vecteur	Reflechi(const vecteur&, const vecteur&);

vecteur	Transmis(const vecteur&, const vecteur&);

reel	Uniforme(const reel&, const reel&);

reel    Uniforme(const reel& s);

point	Centre(const Polygone& o);

void	Couture(Objet*, Ensemble* &);

void	Print_Objet(Objet* o);

#define Abs(x)  (((x)<0) ? (-(x)) : (x))
#define Sgn(x)  (((x)<0) ? (-1) : (1))
#define Max(x,y) (((x)<(y)) ? (y) : (x))
#define Min(x,y) (((x)>(y)) ? (y) : (x))

