/***************************************************************************
                          radiosite.cpp    
                         -------------------
Votre (vos) nom(s) et CIP(s). 
1.   MOYSE Mathis   22 090 087 
2.   MOUSTAQIM Hicham   22 090 032

 ***************************************************************************/

#include "radiosite.h"
#include "ensemble.h"
#include "alg.h"
#include "definition.h"
#include "util.h"
#include "utilalg.h"
#include "inter.h"
#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include <sys/timeb.h>
#include "rayons.h"

#define vabs(a) (a)<0 ? -(a) : (a)  // Valeur absolue

// Précision de 100x100 sur la grande face de l'hémi-cube et de 50x100 sur les 4 autres cotés.
// Vous devez utiliser cette constante pour votre hémi-cube.
// Avant le turnin, assurez-vous de fixer cette valeur à 100.
const int PRECISION_HEMICUBE=100;

// Précision pour la résolution avec Gauss-Seidel.  Ne pas changer
const reel EPS_B=0.000001;

//Variables globales pour la radiosité
int nbPieces;										// Nombre de pièces
Piece* lespieces;                       // Tableau de pièces
reel** FacteursDeFormes;		// Matrice   F ij  (pour Gauss-Seidel)



// Compte et numérote les pièces de la scènes.
void DeterminerPiecesPasse1(Objet* o, int& numero){
  if(o->type() == unEnsemble){
    Ensemble* e = (Ensemble*)o;
    for(int i=1;i<=e->composantes();i++)
      DeterminerPiecesPasse1(e->composante(i), numero);
  }else{
    int t = o->getNombrePieces();
    if(t>0){
      o->setNumeroPiece0(numero);
      numero+=t;
    }
  }
}

// Pour chaque pièce, on garde en mémoire CD, CE, l'aire, etc.
void DeterminerPiecesPasse2(Objet* o, Attributs a0){
  Attributs a1 = a0 * o->attributs();
  if(o->type() == unEnsemble){
    Ensemble* e = (Ensemble*)o;
    for(int i=1;i<=e->composantes();i++)
      DeterminerPiecesPasse2(e->composante(i), a1);
  }else{
    int t = o->getNombrePieces();
    if(t>0){
     for(int i=0;i<t;i++){
        int nopiece = o->getNumeroPiece0()+i;
        lespieces[nopiece].objscene=o;
        lespieces[nopiece].radiosite = a1.emis();
        lespieces[nopiece].emis = a1.emis();
        lespieces[nopiece].diffus = a1.diffus();
        o->setRadiosite(i, a1.emis());

        // suite uniquement pour propagation
        lespieces[nopiece].ERaP = a1.emis();
        const Transformation& transfo = a1.transformation();
        point ptcentre;
        vecteur v1, v2, vn;
        o->centrePiece(i, ptcentre, v1, v2, vn);
        lespieces[nopiece].centre = transfo.transforme(ptcentre);
        lespieces[nopiece].vn = transfo.transforme(vn).unitaire();
        lespieces[nopiece].v1 = transfo.transforme(v1).unitaire();
        lespieces[nopiece].v2 = transfo.transforme(v2).unitaire();
        lespieces[nopiece].aire = o->calculAirePiece(i, a1.transformation());
     }
    }
  }
}
// Appel les procèdures récursives qui compte et numérote les pièces.
void DeterminerPieces(Objet* scene){
 nbPieces=0;
 DeterminerPiecesPasse1(scene, nbPieces);
 lespieces = new Piece[nbPieces];
 Attributs a;
 DeterminerPiecesPasse2(scene, a);
}



/*  FacteursFormePiece calcul les facteurs de formes d'une pièce i.
     Cette fonction doit envoyer des rayons vers chaque pixel de l'hémi-cube.

	 scene est la scene.
     centre et le point central de la piece i.  Les rayons doivent partir de ce point.
	 v1 et v2 sont 2 vecteurs normalisés definissant un plan ou se trouve la piece i.
     vn est le vecteur normal de la piece i.
     ligneFF est un pointeur sur la ligne i de la matrice des facteurs de formes.  ( Fi,j = ligneFF[j] )
*/
void FacteursFormePiece(Objet* scene, const point& centre, const vecteur& v1, const vecteur& v2, const vecteur& vn,  reel* ligneFF){
  // ***** À Coder ******
  int numero_piece;
  bool intersection;

  //PATCH DU DESSUS 100x100 SENS DE VN (y)
  for (int no_z = -PRECISION_HEMICUBE; no_z <= PRECISION_HEMICUBE; no_z++)
  {
      for (int no_x = -PRECISION_HEMICUBE; no_x <= PRECISION_HEMICUBE; no_x++)
      {
          reel x = no_x;
          reel y = PRECISION_HEMICUBE/2; 
          reel z = no_z;

          point PM = point(x, y, z); //Point milieu du pixel de la face de l'hémicube 

          vecteur v = v1 * x + y * vn + v2 * z; //On s'assure que la direction est bien dans le bon repère pour gérer les cas de patch incliné

          int numero_piece_inter;

          //pour chaque pixel de l'hémicube, appeler la fonction :
          intersection = Objet_InterPiece(*scene, centre, v, &numero_piece_inter);
          if (intersection) {
              reel cos_theta_i_p = y / v.norme();
              reel cos_theta_p = y / v.norme();

              ligneFF[numero_piece_inter] += ((cos_theta_i_p * cos_theta_p) / (PI * pow(v.norme(), 2))) * 1; // aire du pixel = 1 
          }
      }
  }

  //PATCH DU COTE DROIT 100x50 SENS DE v1 (x)
  for (int no_z = -PRECISION_HEMICUBE / 2; no_z <= PRECISION_HEMICUBE/2; no_z++)
  {
      for (int no_y = 0; no_y <= PRECISION_HEMICUBE / 2; no_y++)
      {
          reel x = PRECISION_HEMICUBE / 2;
          reel y = no_y;
          reel z = no_z;

          point PM = point(x, y, z); //Point milieu du pixel de la face de l'hémicube

          vecteur v = v1 * x + y * vn + v2 * z; //On s'assure que la direction est bien dans le bon repère pour gérer les cas de patch incliné

          int numero_piece_inter;

          //pour chaque pixel de l'hémicube, appeler la fonction :
          intersection = Objet_InterPiece(*scene, centre, v, &numero_piece_inter);
          if (intersection) {
              reel cos_theta_i_p = y / v.norme();
              reel cos_theta_p = y / v.norme();

              ligneFF[numero_piece_inter] += ((cos_theta_i_p * cos_theta_p) / (PI * pow(v.norme(), 2))) * 1; // aire du pixel = 1
          }
      }
  }

  //PATCH DU COTE DROIT 100x50 SENS DE -v1 (-x)
  for (int no_z = -PRECISION_HEMICUBE / 2; no_z <= PRECISION_HEMICUBE / 2; no_z++)
  {
      for (int no_y = 0; no_y <= PRECISION_HEMICUBE; no_y++)
      {
          reel x = -PRECISION_HEMICUBE / 2;
          reel y = no_y;
          reel z = no_z;

          point PM = point(x, y, z); //Point milieu du pixel de la face de l'hémicube

          vecteur v = v1 * x + y * vn + v2 * z; //On s'assure que la direction est bien dans le bon repère pour gérer les cas de patch incliné

          int numero_piece_inter;

          //pour chaque pixel de l'hémicube, appeler la fonction :
          intersection = Objet_InterPiece(*scene, centre, v, &numero_piece_inter);
          if (intersection) {
              reel cos_theta_i_p = y / v.norme();
              reel cos_theta_p = y / v.norme();
              
              ligneFF[numero_piece_inter] += ((cos_theta_i_p * cos_theta_p) / (PI * pow(v.norme(), 2))) * 1; // aire du pixel = 1
          }
      }
  }

  //PATCH DU COTE AU FOND 100x50 SENS DE v2 (z)
  for (int no_y = 0; no_y <= PRECISION_HEMICUBE / 2; no_y++)
  {
      for (int no_x = -PRECISION_HEMICUBE / 2; no_x <= PRECISION_HEMICUBE / 2; no_x++)
      {
          reel x = no_x;
          reel y = no_y;
          reel z = PRECISION_HEMICUBE / 2;

          point PM = point(x, y, z); //Point milieu du pixel de la face de l'hémicube

          vecteur v = v1 * x + y * vn + v2 * z; //On s'assure que la direction est bien dans le bon repère pour gérer les cas de patch incliné

          int numero_piece_inter;

          //pour chaque pixel de l'hémicube, appeler la fonction :
          intersection = Objet_InterPiece(*scene, centre, v, &numero_piece_inter);
          if (intersection) {
              reel cos_theta_i_p = y / v.norme();
              reel cos_theta_p = y / v.norme();

              ligneFF[numero_piece_inter] += ((cos_theta_i_p * cos_theta_p) / (PI * pow(v.norme(), 2))) * 1; // aire du pixel = 1
          }
      }
  }

  //PATCH DU COTE AU FOND 100x50 SENS DE -v2 (-z)
  for (int no_y = 0; no_y <= PRECISION_HEMICUBE / 2; no_y++)
  {
      for (int no_x = -PRECISION_HEMICUBE / 2; no_x <= PRECISION_HEMICUBE/2; no_x++)
      {
          reel x = no_x;
          reel y = no_y;
          reel z = -PRECISION_HEMICUBE / 2;

          point PM = point(x, y, z); //Point milieu du pixel de la face de l'hémicube

          vecteur v = v1 * x + y * vn + v2 * z; //On s'assure que la direction est bien dans le bon repère pour gérer les cas de patch incliné

          int numero_piece_inter;

          //pour chaque pixel de l'hémicube, appeler la fonction :
          intersection = Objet_InterPiece(*scene, centre, v, &numero_piece_inter);
          if (intersection) {
              reel cos_theta_i_p = y / v.norme();
              reel cos_theta_p = y / v.norme();

              ligneFF[numero_piece_inter] += ((cos_theta_i_p * cos_theta_p) / (PI * pow(v.norme(), 2))) * 1; // aire du pixel = 1
          }
      }
  }
}


// Fonction récursive qui parcours l'arbre de la scene et appel
// la fonction FacteursFormePiece(...) pour chaque piece.
void CalculFacteursFormes(Objet* scene, Objet* o, Transformation transfo){
  transfo = transfo * o->attributs().transformation();
  if(o->type() == unEnsemble){
    Ensemble* e = (Ensemble*)o;
    for(int i=1;i<=e->composantes();i++)
      CalculFacteursFormes(scene, e->composante(i),  transfo);
  }else{
    int t = o->getNombrePieces();
    if(t>0){
     for(int j=0;j<t;j++){
     cout << (o->getNumeroPiece0()+j) << " ";
     cout.flush();
      point ptcentre;
      vecteur v1, v2, vn;
      o->centrePiece(j, ptcentre, v1, v2, vn);
      ptcentre = transfo.transforme(ptcentre);

      v1 = transfo.transforme(v1);
      v2 = transfo.transforme(v2);
      vn = transfo.transforme(vn);

      v1.normalise();
      v2.normalise();
      vn.normalise();

      int nopiece = j+o->getNumeroPiece0();
      FacteursFormePiece(scene, ptcentre, v1, v2, vn, FacteursDeFormes[nopiece]);
    }
    }
  }
}

// Cette fonction alloue la matrice des facteur de forme et
// appel la fonction récursive qui parcours l'arbre de la scène.
void CalculerFacteursFormes(Objet* scene){
   reel* temp = new reel[nbPieces*nbPieces];
   FacteursDeFormes = new reel*[nbPieces];
   for(int i=0;i<nbPieces;i++){
      FacteursDeFormes[i] = temp + i*nbPieces; //new reel[nbPieces];
      for(int j=0;j<nbPieces;j++)
        FacteursDeFormes[i][j] = 0;
   }
   Transformation t0;
   CalculFacteursFormes(scene, scene, t0);
}

/* Fonction de résulution par Gauss Seidel.

    Gauss_Seidel() doit résoudre l'équation de radiosité vu en classe par
    une méthode intérative.

	 À chaque itération, vous devez améliorer les vateurs de lespieces[i].radiosite.

    Pour accédez à la matrice, utilisez des expressions des la forme FacteursDeFormes[i][j].
    FacteursDeFormes[i][j] représente la proportion d'énergie quittant la pièce i et qui atteint
    la pièce j.

    Pour le nombre de pièces total, utilisez la variable nbPieces.
*/
void Gauss_Seidel(){
	// ****** À Coder ******
    boolean PRECIS = FAUX;

    for (int index = 0; index < nbPieces; index++)
    {
        lespieces[index].radiosite = lespieces[index].emis;
        //B_i <- E_i
    }

    Piece* lespieces_old = new Piece[nbPieces];

    while (!PRECIS)
    {
        for (int index_i = 0; index_i < nbPieces; index_i++)
        {
            lespieces_old[index_i].radiosite = lespieces[index_i].radiosite; 
            //B_i_old <- B_i
        }

        for (int index_i = 0; index_i < nbPieces; index_i++)
        {
            Couleur sum(0.0, 0.0, 0.0);

            for (int index_j = 0; index_j < nbPieces; index_j++)
            {
                sum += lespieces[index_j].radiosite * FacteursDeFormes[index_i][index_j];
                //Somme(sur j allant de 1 à n) [ F_i_j * B_j ]
            }

            lespieces[index_i].radiosite = lespieces[index_i].emis + lespieces[index_i].diffus * sum;
            //B_i <- E_i + R_i + Somme(sur j allant de 1 à n) [ F_i_j * B_j ]
        }

        PRECIS = (vabs(lespieces - lespieces_old) > EPS_B);
    }
}

// Pour chaque pièce, on affecte la radiosité dans l'objet atomique.
void AffecterRadiositeScene(){
   for(int i=0;i<nbPieces;i++){
      int t =lespieces[i].objscene->getNumeroPiece0();
      lespieces[i].objscene->setRadiosite(i-t, lespieces[i].radiosite);
   }
}


void CalculRadiosite_GS(Objet* scene){
   
   struct timeb tempsDebut, tempsFin;
   ftime(&tempsDebut);

   cout << "Calcul de la radiosité..." << endl;
   cout << "Comptage et numérotation des pieces..." << endl;
   DeterminerPieces(scene);
   cout << "Nombre de piece(s) : " << nbPieces << endl;

   cout << "Calcul des facteurs de forme ..." << endl;
//   PrecalculFormeFactHemiCube(); // optionel
   CalculerFacteursFormes(scene);
   cout << endl;

   cout << "Gauss_Seidel... " << endl;
   Gauss_Seidel();
   AffecterRadiositeScene();

   ftime(&tempsFin);
   long nbms = 1000*(tempsFin.time-tempsDebut.time) + (tempsFin.millitm-tempsDebut.millitm);
   printf("Duré du calcul: %.03f sec.\n", nbms/1000.0);
   delete lespieces;
   delete FacteursDeFormes[0];
   delete FacteursDeFormes;
//   pFenAff3D->Redraw();
 
}

//--------- Propagation ---------------------------//
void CalculRadiositePropagation(Objet* scene){
   printf("Calcul Radio Propagation...\n");
  
}
