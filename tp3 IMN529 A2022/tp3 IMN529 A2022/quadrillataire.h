/***************************************************************************
                          quadrilataire.h  -  Quadrillataire (4 sommets)
                             -------------------
    begin                : Fri Feb 1 2002
 ***************************************************************************/

 #if !defined(__QUADRILLATAIRE_H__)
 #define __QUADRILLATAIRE_H__

 #include "polygone.h"

class Quadrillataire : public Polygone{
  public:
     Quadrillataire(int nbsub1=1, int nbsub2=1);
 	
     virtual void     centrePiece(int numerolocal, point&p, vecteur& v1, vecteur& v2, vecteur& vn);
     virtual int      getNumeroPiece(const point& p);
     virtual int      getNombrePieces() const;
     virtual void     Afficher(const Transformation&, const Attributs&) const;
 	
     virtual void     mettreRadioDansEmis(const point&, Attributs& c);
     virtual double   calculAirePiece(int numero, const Transformation&) const;

  protected:
     int              nombreSubdivision1,
                      nombreSubdivision2;
     bool             defVecteursCoor, baseOrtho;
     vecteur          V1, V2;
     Couleur          MoyenneCoinPatch(int i, int j) const;
};


 #endif
