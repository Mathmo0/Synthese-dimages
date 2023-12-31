#include <stdlib.h>
#include "objets.h"

void	Lire_Sorte (Fichier &f, Type *s);
void	Lire_vecteur(Fichier &f, vecteur *v);
void	Lire_point(Fichier &f, point *p);
void	Lire_Sommet(Fichier &f, point* &p);
void	Lire_Identite (Fichier &, Transformation *t);
void	Lire_Translation (Fichier &f, Transformation *t);
void	Lire_Homothetie (Fichier &f, Transformation *t);
void	Lire_Rotation (Fichier &f, Transformation *t);
void	Lire_Alignement (Fichier &f, Transformation *t);
void	Lire_Cisaillement (Fichier &f, Transformation *t);
void	Lire_Matrice (Fichier &f, Transformation *t);
Couleur Lire_Couleur(Fichier &f);

void	Lire_Attributs (Fichier &f, Attributs *a0);

Objet*	Lire_Point (Fichier &f);
Objet*	Lire_Segment (Fichier &f);
Objet*	Lire_Plan (Fichier &f);
Objet*	Lire_Sphere (Fichier &);
Objet*	Lire_Cylindre (Fichier &f);
Objet*	Lire_Triangle (Fichier &f);
Objet*	Lire_Polygone (Fichier &f);

//#IFT692
Objet*  Lire_Quadrillataire(Fichier& f);


const	Objet*	Lire_Lien(Fichier &f);
void	Lire_PointVol(Fichier &f, PointVol *p);
Objet*	Lire_Volume (Fichier &f);
void	Lire_Type(Fichier &f, Type *t);
void	Lire_Type2(Fichier &f, Type *t);
Objet*	Lire_Ensemble (Fichier &f);
booleen	Lire_Objet2 (Fichier &f, const Objet* &o);
Objet*	Lire_Branche (Fichier &f);
booleen	Lire_Arbre (Fichier &f, const Objet* &o);
//Objet*	Objet::Lecture (Fichier &f);
void	Ecrire_vecteur(Fichier *f, vecteur v);
void	Ecrire_point(Fichier *f, point p);
void	Ecrire_Matrice (Fichier *f, Transformation t);
void	Ecrire_Coefficient (Fichier *f, const Coefficient& c, char *s);
void	Ecrire_Attributs (Fichier *f, Attributs a);
void	Ecrire_Type(Fichier *f, Type t);
booleen	Deja_Ecrit(Fichier &f, const Objet& o);
//void	Point::Ecrire(Fichier *f) const;
//void	Droite::Ecrire(Fichier *f) const;
//void	Objet::Ecrire(Fichier *f) const;
//void	Fractal::Ecrire(Fichier *f) const;
//void	Particule::Ecrire(Fichier *f) const;
//void	Segment::Ecrire (Fichier *f) const;
//void	Plan::Ecrire (Fichier *f) const;
//void	Sphere::Ecrire (Fichier *f) const;
//void	Cylindre::Ecrire (Fichier *f) const;
//void	Polygone::Ecrire (Fichier *f) const;
void	Ecrire_PointVol(Fichier *f, PointVol p);
//void	Volume::Ecrire (Fichier *f) const;
//void	Vide::Ecrire (Fichier *f) const;
//void	Ensemble::Ecrire (Fichier *f) const;
