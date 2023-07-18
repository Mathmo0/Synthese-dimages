#include "objet.h"
#include "attr.h"
#include "transfo.h"

void Affiche_Attributs(const Attributs&);
void AfficheEnglobant(int);


void Affiche_Tetragone(const point& p1, const point& p2, const point& p3, const point& p4, const Transformation& v, const Attributs& a);

void Affiche_Tetragone(const point& p1, const point& p2, const point& p3, const point& p4, const vecteur& n1, const vecteur& n2, const vecteur& n3, const vecteur& n4, const Transformation& v, const Attributs& a);



void Affiche_Trigone(const point& p1, const point& p2, const point& p3, const Transformation& v, const Attributs& a);

void Affiche_Trigone(const point& p1, const point& p2, const point& p3, const vecteur& n1, const vecteur& n2, const vecteur& n3, const vecteur& n4, const Transformation& v, const Attributs& a);

void Affiche_Ligne(const point& p1, const point& p2, const Transformation& v, const Attributs& a);
