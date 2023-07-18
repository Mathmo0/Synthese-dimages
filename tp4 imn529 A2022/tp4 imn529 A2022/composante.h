
#ifndef	_COMPOSANTE
#define	_COMPOSANTE

#include "definition.h"

class Composante {
public:
virtual	Transformation	Homothetie(const reel&) const = 0;
virtual	Transformation	HomothetieUnitaire(const reel&) const = 0;
virtual	Transformation	Rotation(const reel&) const = 0;
virtual	Transformation	Deplacement() const = 0;
virtual	Transformation	DeplacementUnitaire(const reel&) const = 0;
};

#endif

