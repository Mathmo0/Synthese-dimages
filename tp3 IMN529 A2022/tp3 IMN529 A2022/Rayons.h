#ifndef _TRACERRAYONS
#define _TRACERRAYONS

#include "Camera.h"
#include "objet.h"
#include "definition.h"

booleen TraceRayons(const Camera& pv, Objet* scene, const entier& resx, const entier& resy, char fichier[]);

#endif