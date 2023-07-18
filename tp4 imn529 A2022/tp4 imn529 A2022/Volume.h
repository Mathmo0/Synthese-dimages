#ifndef _VOLUME
#define _VOLUME


#include "definition.h"
#include "alg.h"
#include "objet.h"

typedef	point	*PointVol;

void    Creer_PointVol (reel, reel, reel, PointVol *);

void    Coordonnees_PointVol (PointVol, reel *, reel *, reel *);


typedef enum { TA,TB,TC,TD,T0,TI} etiquette;
	// sorte de triangles: sous triangle TA, TB, TC ou TD
	// (sous triangle du milieu) de niveau 0 = T0 et indefini = TI
 
struct Triangle0;

struct STriangle 

{
	etiquette etiq;
	PointVol pt1,pt2,pt3;
	PointVol pm1,pm2,pm3;
	unsigned char a_cree_pm[3];
	union {
		STriangle *ST;
		Triangle0 *T0;
	} pere;
	STriangle *STrianglei;
// STrianglei[0] == STriangleA, ..., STrianglei[3] = STriangleD
};
 
struct Triangle0 

{
	etiquette etiq;
	PointVol pt1,pt2,pt3;
	PointVol pm1,pm2,pm3;
	unsigned char a_cree_pm[3];
	STriangle *STrianglei;
// STrianglei[0] == STriangleA, ..., Strianglei[3] = StriangleD
	Triangle0 *TriAdj12, *TriAdj23, *TriAdj31;
	reel k_rayon2;
};

struct Triangle 

{
	etiquette eti;
	PointVol pt1,pt2,pt3;
	Triangle0 *Tri0;
	STriangle *STri;
};

void	Def_Triangle (PointVol pt1, PointVol pt2, PointVol pt3, Triangle *tri);
 
void    Pts_Triangle (const Triangle& tri, PointVol *pt1, PointVol *pt2, PointVol *pt3);

typedef struct 

{
	point   centre;
	reel    rayon;
} sphere;

sphere  Def_sphere (point pt = O, reel rayon = 1.0);
point   Centre_sphere (sphere S);
reel    Rayon_sphere (sphere  S);

class Volume : public Objet 

{
	entier nb;
	Triangle0 *LiTri0;
	entier Subdiv;		// niveau de subdivision du volume
	entier MemSubdiv;	// niveau jq on garde les calculs
	reel w;			// coefficient de tension
	vecteur	normal;
        void	volume(int);
public:
	Volume ();

	void    Ecrire(Fichier *);

	void    Afficher(const Transformation&, const Attributs&) const;

	const   Englobant&      volume() const;

	entier	Niveau_de_Subdiv () const;
	void	Niveau_de_Subdiv (entier niveau);

	entier	Niveau_de_Subdiv_Mem () const;
	void	Niveau_de_Subdiv_Mem (entier niveau);

	reel	Coefficient_Tension() const;
	void	Coefficient_Tension(reel w);
	// 0 le plus tendu; 1/16 le mois tendu sans etre fractal, max 1/4 ?

	void	Ajoute (const Triangle& tri);

	entier	Nb_Triangle () const;

	Triangle Ieme_Triangle (entier i) const;

	booleen	Organise();

	booleen	Organise(const Objet& o);


	void	Subdivise_Tri(const Triangle&, Triangle *A, Triangle *B, Triangle *C, Triangle *D);

	void	Triangle_Adjacent(PointVol, PointVol, const Triangle &, Triangle *);


	Volume	*Subdivise();

	void	Reduit_Hauteur();
	void	Reduit_Hauteur(entier hauteur);

	Objet	*Converti();

	booleen	inter(const point& p, const vecteur& v, reel *dist_inter);
	vecteur	gradient(const point& p);

	Objet	*copie() const;

	~Volume();
};

#endif

