#include "quadrillataire.h"
#include "utilalg.h"
#include <math.h>


Quadrillataire::Quadrillataire(int nbsub1, int nbsub2){
   nombreSubdivision1 = nbsub1;
   nombreSubdivision2 = nbsub2;
   defVecteursCoor = false;
}

int Quadrillataire::getNombrePieces() const{
   return nombreSubdivision1 * nombreSubdivision2;
}
void Quadrillataire::centrePiece(int numerolocal, point&p, vecteur& v1, vecteur& v2, vecteur& vn){
   v1 = sommet(2) - sommet(1);
   v2 = sommet(4) - sommet(1);
   p = sommet(1)
        + (0.5 + numerolocal%nombreSubdivision1)/(nombreSubdivision1) * v1
        + (0.5 + numerolocal/nombreSubdivision1)/(nombreSubdivision2) * v2;
   vn = mplan().normale();
   v2 = v1 ^ vn;
}
int Quadrillataire::getNumeroPiece(const point& p){
  if(!defVecteursCoor){
    V1 = sommet(2) - sommet(1);
    V2 = sommet(4) - sommet(1);
    
    baseOrtho = V1*V2 == 0.0;
    defVecteursCoor = true;
  }
  vecteur u = p - sommet(1);
  reel x, y;
  if(baseOrtho){
    x = u*V1 / V1.norme2();
    y = u*V2 / V2.norme2();
  }else{
    vecteur v2p = (V1*V2/V1.norme2()) * V1;
    vecteur v2c = V2 - v2p;
    y = u * v2c / v2c.norme2();
    u = u - y*v2p;
    x = u * V1 / V1.norme2();
  }
  int numero = (int) (y * nombreSubdivision2);
  numero*=nombreSubdivision1;
  numero += (int)(x * nombreSubdivision1);
  return numero;
}


void Quadrillataire::mettreRadioDansEmis(const point& p, Attributs& a){
  if(!radiosite) return;
  vecteur u = p - sommet(1);
  reel x, y;
  if(baseOrtho){
     x = u*V1 / V1.norme2();
     y = u*V2 / V2.norme2();
  }else{
     vecteur v2p = (V1*V2/V1.norme2()) * V1;
     vecteur v2c = V2 - v2p;
     y = u * v2c / v2c.norme2();
     u = u - y*v2p;
     x = u * V1 / V1.norme2();
  }
  y *=  nombreSubdivision2;
  x  *= nombreSubdivision1;
  y -= 0.5;  x-=0.5;
  Couleur c1(0, 0, 0), c2(0, 0, 0);
//  int ix = (int)x;
//  int iy = (int)y;
  int ix = (int)floor(x);  // nouveau !
  int iy = (int)floor(y);  // nouveau !

  x = x - ix;  y=y-iy;
  c1 = radiosite[ (ix>=0 ? ix : 0) + (iy>=0 ? iy : 0) * nombreSubdivision1] * (1-x)
       + radiosite[ (ix+1<nombreSubdivision1 ? ix +1: nombreSubdivision1-1)
                 + (iy>=0 ? iy : 0) * nombreSubdivision1] * x;

  c2 = radiosite[ (ix>=0 ? ix : 0) + (iy+1<nombreSubdivision2 ? iy+1 : nombreSubdivision2-1) * nombreSubdivision1] * (1-x)
       + radiosite[ (ix+1<nombreSubdivision1 ? ix+1 : nombreSubdivision1-1)
                 + (iy+1<nombreSubdivision2 ? iy+1 : nombreSubdivision2-1) * nombreSubdivision1] * x;
  a.emis( c1*(1-y) + c2*y);
}

double Quadrillataire::calculAirePiece(int numero, const Transformation& t) const{
   return Polygone::calculAirePiece(numero, t) / (nombreSubdivision1*nombreSubdivision2);
}

