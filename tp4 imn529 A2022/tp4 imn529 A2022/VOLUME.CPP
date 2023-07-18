#include <iostream>
#include "volume.h"
#include "erreur.h"
#include "geo.h"
#include "utilalg.h"
#include "ensemble.h"
#include "polygone.h"
#include "attr.h"
#include "englobe.h"

using namespace std;

#define EPSTRI 0

extern	entier	subdivisions;
extern	booleen	englobantexact;
extern	reel	wglobal;

void	Creer_PointVol (reel x,reel y,reel z, PointVol *p)
/* Retourne le point (x,y,z) */
{
	*p = new point(x,y,z);
}


PointVol	Creer_PointVol (const point& p)
/* Retourne le point (x,y,z) */
{
	point	*pv = new point;
	*pv = p;
	return pv;
}


void	Coordonnees_PointVol (PointVol p, reel *x,reel *y,reel *z)
/* Retourne les coordonnees absolues de p. */
{	
	*x = p->x();
	*y = p->y();
	*z = p->z();
	
}


sphere	Def_sphere (point pt, reel rayon)
/* Defini une sphere de centre pt et de rayon rayon */
{
	sphere	S;

	S.centre = pt;
	S.rayon = rayon;

	return S;
}


point	Centre_sphere (sphere S)
/* donne centre de la sphere S */
{
	return S.centre;
}

reel	Rayon_sphere2 (sphere S)
/* donne le rayon de la sphere S */
{
	return S.rayon;
}

extern	"C" double	sqrt(double);

reel	Rayon_sphere (sphere S)
/* donne le rayon de la sphere S */
{
	return sqrt(S.rayon);
}



Volume::Volume ()
{
	s=unVolume;
	this->nb = 0;
	this->LiTri0 = 0;
	this->Subdiv = 0;
	this->MemSubdiv = 0;
}


entier Volume::Niveau_de_Subdiv () const
/* Donne le niveau de subdivision du volume */
{
	return(this->Subdiv);
}


entier Volume::Niveau_de_Subdiv_Mem () const
/* Donne jq quel niveau de subdivision du volume qui est garde en memoire */
/* il faut que MemSubdiv <= Subdiv */
{
	return(this->MemSubdiv);
}


reel Volume::Coefficient_Tension() const
/* Donne le coefficient de tension de la surface du volume */
/* 0 le plus tendu; 1/16 le mois tendu sans etre fractal, max 1/4 ??? */
{
	return(this->w);
//	return(wglobal);
}


void Volume::Niveau_de_Subdiv (entier niveau)
/* Assigne le niveau de subdivision du volume */
{
	this->Subdiv = niveau;
}


void Volume::Niveau_de_Subdiv_Mem (entier niveau)
/* Assigne jq quel niveau de subdivision du volume qui est garde en memoire */
/* il faut que MemSubdiv <= Subdiv */
{
	this->MemSubdiv = niveau;
}


void Volume::Coefficient_Tension(reel w)
/* Assigne le coefficient de tension de la surface du volume */
/* 0 le plus tendu; 1/16 le mois tendu sans etre fractal, max 1/4 ??? */
{
	this->w = w;
}


void	Def_Triangle (PointVol pt1, PointVol pt2, PointVol pt3, Triangle *tri)
/* Retourne un triangle (pt1,pt2,pt3) */
{
	tri->eti = TI;
	tri->pt1 = pt1;
	tri->pt2 = pt2;
	tri->pt3 = pt3;
}

void	Point_Creer_par_Tri(entier no_tri, const Triangle& tri)
{
	if (tri.eti == T0)
		tri.Tri0->a_cree_pm[no_tri-1] = 1;
	else
		tri.STri->a_cree_pm[no_tri-1] = 1;
}

void	Point_Detruit_par_Tri(entier no_tri, const Triangle& tri)
{
	if (tri.eti == T0)
		tri.Tri0->a_cree_pm[no_tri-1] = 0;
	else
		tri.STri->a_cree_pm[no_tri-1] = 0;
}

void	Pts_Triangle (const Triangle& tri, PointVol *pt1, PointVol *pt2, PointVol *pt3)
{
	if (tri.eti == TI) {
		*pt1 = tri.pt1;
		*pt2 = tri.pt2;
		*pt3 = tri.pt3;
	} else {
		if (tri.eti == T0) {
			*pt1 = tri.Tri0->pt1;
			*pt2 = tri.Tri0->pt2;
			*pt3 = tri.Tri0->pt3;
		} else {
			*pt1 = tri.STri->pt1;
			*pt2 = tri.STri->pt2;
			*pt3 = tri.STri->pt3;
		}
	}
}


void	Pts_Milieu_Triangle (const Triangle& tri, PointVol *pm1, PointVol *pm2, PointVol *pm3)
{

	if (tri.eti == T0) {
		*pm1 = tri.Tri0->pm1;
		*pm2 = tri.Tri0->pm2;
		*pm3 = tri.Tri0->pm3;
	} else {
		*pm1 = tri.STri->pm1;
		*pm2 = tri.STri->pm2;
		*pm3 = tri.STri->pm3;
	}
}

void	Pts_Milieu_Cree_par_Triangle(const Triangle& tri, booleen *a_cree_pm1, booleen *a_cree_pm2, booleen *a_cree_pm3)
{

	if (tri.eti == T0) {
		*a_cree_pm1 = tri.Tri0->a_cree_pm[0];
		*a_cree_pm2 = tri.Tri0->a_cree_pm[1];
		*a_cree_pm3 = tri.Tri0->a_cree_pm[2];
	} else {
		*a_cree_pm1 = tri.STri->a_cree_pm[0];
		*a_cree_pm2 = tri.STri->a_cree_pm[1];
		*a_cree_pm3 = tri.STri->a_cree_pm[2];
	}
}


void	Donne_Triangles (STriangle *prem_tri, STriangle **triA, STriangle **triB, STriangle **triC, STriangle **triD)
{
	if (prem_tri != 0) {
		*triA=prem_tri;
		*triB=prem_tri+1;
		*triC=prem_tri+2;
		*triD=prem_tri+3;
	} else {
		*triA=0;
		*triB=0;
		*triC=0;
		*triD=0;
	}
}

void	Volume::Ajoute (const Triangle& tri)
{
	entier i = this->nb++;
	if (i == 0) {
		this->LiTri0 = new Triangle0;
	} else {
		Triangle0 *temp = new Triangle0[i+1];
		for (entier j=0; j<i; j+=1) {
			temp[j] = this->LiTri0[j];
		}
		delete this->LiTri0;
		this->LiTri0 = temp;
	}

	Triangle0 Tri0;

	Pts_Triangle(tri, &Tri0.pt1,&Tri0.pt2,&Tri0.pt3);

	Tri0.k_rayon2 = 1.0;
	Tri0.etiq = T0;
	Tri0.pm1 = 0;
	Tri0.pm2 = 0;
	Tri0.pm3 = 0;
	Tri0.a_cree_pm[0] = 0;
	Tri0.a_cree_pm[1] = 0;
	Tri0.a_cree_pm[2] = 0;

	Tri0.STrianglei = 0;

	Tri0.TriAdj12 = 0;
	Tri0.TriAdj23 = 0;
	Tri0.TriAdj31 = 0;

	this->LiTri0[i] = Tri0;
}

entier	Volume::Nb_Triangle () const
{
	return this->nb;
}

Triangle Volume::Ieme_Triangle (entier i) const
{
	Triangle tri;

	tri.eti = T0;
	tri.Tri0 = &(this->LiTri0[i-1]);

	return tri;
}

booleen egalpts3(PointVol ipt1, PointVol ipt2, PointVol jpt1, PointVol jpt2, PointVol jpt3)
{
	return ((ipt1 == jpt1) || (ipt1 == jpt2) || (ipt1 == jpt3)) && ((ipt2 == jpt1) || (ipt2 == jpt2) || (ipt2 == jpt3));
}

booleen egalpts2(PointVol ipt1, PointVol ipt2, PointVol jpt1, PointVol jpt2)
{
	return ((ipt1 == jpt1) || (ipt1 == jpt2)) && ((ipt2 == jpt1) || (ipt2 == jpt2));
}

void	troisieme_pts (PointVol pta, PointVol ptb, const Triangle& tri, Objet *o, PointVol *ptc)
{
	PointVol pt1,pt2,pt3;

	Pts_Triangle (tri, &pt1,&pt2,&pt3);
	if (egalpts2(pta,ptb, pt1,pt2))
		*ptc = pt3;
	else if (egalpts2(pta,ptb, pt1,pt3))
		*ptc = pt2;
	else if (egalpts2(pta,ptb, pt2,pt3))
		*ptc = pt1;
	else Erreur(20, "");
}

booleen	Volume::Organise ()
{
	entier i,j,n;
	Triangle iTri,jTri;
	PointVol ipt1,ipt2,ipt3,jpt1,jpt2,jpt3;

	n = this->Nb_Triangle();

	if (n==0) return FAUX;

	for (i=1; i <= n ; i++) {
		iTri=this->Ieme_Triangle(i);
		iTri.Tri0->TriAdj12 = 0;
		iTri.Tri0->TriAdj23 = 0;
		iTri.Tri0->TriAdj31 = 0;
	}
	for (i=1; i <= n ; i++) {
		iTri=this->Ieme_Triangle(i);
		Pts_Triangle(iTri, &ipt1,&ipt2,&ipt3);

		for (j=1; j <= n; j++) {
			if (i!=j) {
				jTri=this->Ieme_Triangle(j);
				Pts_Triangle(jTri, &jpt1,&jpt2,&jpt3);
				if (egalpts3(ipt1,ipt2,jpt1,jpt2,jpt3)) { iTri.Tri0->TriAdj12 = jTri.Tri0; }
				if (egalpts3(ipt2,ipt3,jpt1,jpt2,jpt3)) { iTri.Tri0->TriAdj23 = jTri.Tri0; }
				if (egalpts3(ipt3,ipt1,jpt1,jpt2,jpt3)) { iTri.Tri0->TriAdj31 = jTri.Tri0; }
			}
		} /* for j */
	} /* for i */

	booleen	ok = VRAI;
	for (i=1; i <= n ; i++) {
		iTri=this->Ieme_Triangle(i);
		if (iTri.Tri0->TriAdj12 == 0 || iTri.Tri0->TriAdj23 == 0 || iTri.Tri0->TriAdj31 == 0) {
			ok = FAUX; break;
		}
	}
	return ok;
}


void	Pts_Objet(const Objet& O, const Attributs& a, entier *nbpv, PointVol lipv[])
{
	entier i,j;
	point	ptv;

	if (O.type()==unEnsemble)
		for (i=1; i <= ((Ensemble&)O).composantes() ; i++) {
			Pts_Objet(*((Ensemble&)O).composante(i), a * O.attributs(), nbpv,lipv);
		}
	else if (O.type()==unPolygone) {
			for (i=1; i<=((Polygone&)O).sommets(); i++) {
				ptv = a.transformation().transforme(((Polygone&)O).sommet(i));
				for (j=0; j<*nbpv; j++) {
					if (*lipv[j] == ptv) break;
				}
				if (j==*nbpv) lipv[(*nbpv)++] = Creer_PointVol(ptv);
			}
		}
}
				
				
void	Ajoute_Tri(const Objet& O, const Attributs& a, entier nbpv, const PointVol lipv[], Volume *vol)
{
	entier i,j;
	PointVol p[3];
	Triangle tri;

	if (O.type()==unEnsemble) {
		for (i=1; i <= ((Ensemble&)O).composantes() ; i++) {
			Ajoute_Tri(*((Ensemble&)O).composante(i), a * O.attributs(), nbpv,lipv,vol);
		}
	} else {
		if (O.type()==unPolygone && ((Polygone&)O).sommets() == 3) {
			for (i=1; i<=3; i++) {
				for (j=0; j<nbpv; j++) {
					if (*lipv[j] == a.transformation().transforme(((Polygone&)O).sommet(i))) {
						p[i-1]=lipv[j];
						break;
					}
				}
			}
			Def_Triangle (p[0],p[1],p[2], &tri);
			vol->Ajoute (tri);
		}
	}
}


booleen	Volume::Organise (const Objet &O)
{
	PointVol lipv[20];
	entier nbpv=0;

	Pts_Objet(O,ATTR,&nbpv,lipv);
	Ajoute_Tri(O,ATTR,nbpv,lipv,this);
	return this->Organise();
}


void	Pere_Tri (const Triangle& tri, Objet *o, Triangle *Ptri)
{
	Ptri->eti = (tri.STri)->pere.T0->etiq;
	if (Ptri->eti == T0)
		Ptri->Tri0 = tri.STri->pere.T0;
	else
		Ptri->STri = tri.STri->pere.ST;
}


void	Assigne_pt_milieu (PointVol pm1, PointVol pm2, PointVol pm3, const Triangle& tri, Objet *o)
{
	if (tri.eti == T0) {
		tri.Tri0->pm1 = pm1;
		tri.Tri0->pm2 = pm2;
		tri.Tri0->pm3 = pm3;
	} else {
		tri.STri->pm1 = pm1;
		tri.STri->pm2 = pm2;
		tri.STri->pm3 = pm3;
	}
}


void creer_STri (PointVol pm1, PointVol pm2, PointVol pm3, const Triangle& tri, Objet *o)
{
	STriangle *ptr_strii,*ptr_striA,*ptr_striB,*ptr_striC,*ptr_striD;
	PointVol pt1,pt2,pt3;

	ptr_strii = new STriangle[4];
	if (ptr_strii == 0) Erreur(20, "");
	Donne_Triangles(ptr_strii, &ptr_striA, &ptr_striB, &ptr_striC, &ptr_striD);

	if (tri.eti == T0) {
		tri.Tri0->STrianglei = ptr_strii;

		ptr_striA->pere.T0 = tri.Tri0;
		ptr_striB->pere.T0 = tri.Tri0;
		ptr_striC->pere.T0 = tri.Tri0;
		ptr_striD->pere.T0 = tri.Tri0;
	} else {
		tri.STri->STrianglei = ptr_strii;

		ptr_striA->pere.ST = tri.STri;
		ptr_striB->pere.ST = tri.STri;
		ptr_striC->pere.ST = tri.STri;
		ptr_striD->pere.ST = tri.STri;
	}

	Pts_Triangle(tri, &pt1,&pt2,&pt3);

	ptr_striA->etiq = TA;
	ptr_striA->pt1 = pt1;
	ptr_striA->pt2 = pm1;
	ptr_striA->pt3 = pm3;
	ptr_striA->pm1 = 0;
	ptr_striA->pm2 = 0;
	ptr_striA->pm3 = 0;
	ptr_striA->a_cree_pm[0] = 0;
	ptr_striA->a_cree_pm[1] = 0;
	ptr_striA->a_cree_pm[2] = 0;
	ptr_striA->STrianglei = 0;

	ptr_striB->etiq = TB;
	ptr_striB->pt1 = pm1;
	ptr_striB->pt2 = pt2;
	ptr_striB->pt3 = pm2;
	ptr_striB->pm1 = 0;
	ptr_striB->pm2 = 0;
	ptr_striB->pm3 = 0;
	ptr_striB->a_cree_pm[0] = 0;
	ptr_striB->a_cree_pm[1] = 0;
	ptr_striB->a_cree_pm[2] = 0;
	ptr_striB->STrianglei = 0;

	ptr_striC->etiq = TC;
	ptr_striC->pt1 = pm3;
	ptr_striC->pt2 = pm2;
	ptr_striC->pt3 = pt3;
	ptr_striC->pm1 = 0;
	ptr_striC->pm2 = 0;
	ptr_striC->pm3 = 0;
	ptr_striC->a_cree_pm[0] = 0;
	ptr_striC->a_cree_pm[1] = 0;
	ptr_striC->a_cree_pm[2] = 0;
	ptr_striC->STrianglei = 0;


	ptr_striD->etiq = TD;
	ptr_striD->pt1 = pm1;
	ptr_striD->pt2 = pm2;
	ptr_striD->pt3 = pm3;
	ptr_striD->pm1 = 0;
	ptr_striD->pm2 = 0;
	ptr_striD->pm3 = 0;
	ptr_striD->a_cree_pm[0] = 0;
	ptr_striD->a_cree_pm[1] = 0;
	ptr_striD->a_cree_pm[2] = 0;
	ptr_striD->STrianglei = 0;

}


booleen	A_Sous_Tri (const Triangle& tri, Objet* o)
{
	if (tri.eti != T0) return (tri.STri->STrianglei != 0);
	else return (tri.Tri0->STrianglei != 0);
}


void	Sous_Tri (const Triangle& tri, Objet *o, Triangle *STriA, Triangle *STriB, Triangle *STriC, Triangle *STriD)
{
	STriangle *ptr_STriA,*ptr_STriB,*ptr_STriC,*ptr_STriD;

	if (tri.eti != T0)
		{
		Donne_Triangles(tri.STri->STrianglei, &ptr_STriA, &ptr_STriB, &ptr_STriC, &ptr_STriD);
		}
	else
		{
		Donne_Triangles(tri.Tri0->STrianglei, &ptr_STriA, &ptr_STriB, &ptr_STriC, &ptr_STriD);
		}

	STriA->STri = ptr_STriA;
	STriA->eti = TA;

	STriB->STri = ptr_STriB;
	STriB->eti = TB;

	STriC->STri = ptr_STriC;
	STriC->eti = TC;

	STriD->STri = ptr_STriD;
	STriD->eti = TD;
}


void	Sous_Triangle (PointVol pt, const Triangle& tri, Volume *o, Triangle *STri)
{
	PointVol pt1,pt2,pt3;
	Triangle STriA,STriB,STriC,STriD;

	if (tri.eti == T0)
		{
		pt1 = tri.Tri0->pt1;
		pt2 = tri.Tri0->pt2;
		pt3 = tri.Tri0->pt3;

		o->Subdivise_Tri(tri, &STriA, &STriB, &STriC, &STriD);
/*		STriA.STri = tri.Tri0->STriangleA;
		STriB.STri = tri.Tri0->STriangleB;
		STriC.STri = tri.Tri0->STriangleC; */
		}
	else
		{
		pt1 = tri.STri->pt1;
		pt2 = tri.STri->pt2;
		pt3 = tri.STri->pt3;

		o->Subdivise_Tri(tri, &STriA, &STriB, &STriC, &STriD);
/*		STriA.STri = tri.STri->STriangleA;
		STriB.STri = tri.STri->STriangleB;
		STriC.STri = tri.STri->STriangleC; */
		}

	if (pt == pt1)
		*STri = STriA;
	else if (pt == pt2)
		*STri = STriB;
	else if (pt == pt3)
		*STri = STriC;

	STri->eti = STri->STri->etiq;


}


void	Tri_Adj0(PointVol pta, PointVol ptb, const Triangle& tri, Volume* o, Triangle *triadj)
{
	Triangle0 *tri0;
	PointVol pt1,pt2,pt3;

	triadj->eti = T0;
	Pts_Triangle(tri, &pt1,&pt2,&pt3);
	tri0 = tri.Tri0;
	if ( egalpts2(pta,ptb, pt1,pt2) )
			triadj->Tri0 = tri0->TriAdj12;

	else if ( egalpts2(pta,ptb, pt2,pt3) )
			triadj->Tri0 = tri0->TriAdj23;

	else if ( egalpts2(pta,ptb, pt3,pt1) )
			triadj->Tri0 = tri0->TriAdj31;

}


void	Volume::Triangle_Adjacent(PointVol pta, PointVol ptb, const Triangle& tri, Triangle *triadj) 

{
//	Triangle0 *tri0;
	PointVol pt1,pt2,pt3, ppm1,ppm2,ppm3, ppt1,ppt2,ppt3;
	Triangle Ptri,atri,PStriA,PStriB,PStriC,PStriD;

	if (tri.eti == T0) Tri_Adj0(pta,ptb,tri,this,triadj);
	else {
		Pere_Tri(tri,this, &Ptri);
		Pts_Triangle(Ptri, &ppt1,&ppt2,&ppt3);
		Subdivise_Tri(Ptri, &PStriA, &PStriB, &PStriC, &PStriD);
		Pts_Milieu_Triangle(Ptri, &ppm1,&ppm2,&ppm3);
		Pts_Triangle(tri, &pt1,&pt2,&pt3);

		if (tri.eti == TD) {
			if (egalpts2(pta,ptb, ppm1,ppm2))
				*triadj = PStriB;
			else if (egalpts2(pta,ptb, ppm2,ppm3))
				*triadj = PStriC;
			else if (egalpts2(pta,ptb, ppm3,ppm1))
				*triadj = PStriA;
			else Erreur(20, "");
		}

		if (tri.eti == TA) {
			if (egalpts2(pta,ptb, ppm3,ppm1))
				*triadj = PStriD;
			else if (egalpts2(pta,ptb, ppt1,ppm1)) {
				Triangle_Adjacent(ppt1,ppt2,Ptri, &atri);
				Sous_Triangle(ppt1,atri,this, triadj);
			} else if (egalpts2(pta,ptb, ppt1,ppm3)) {
				Triangle_Adjacent(ppt1,ppt3,Ptri, &atri);
				Sous_Triangle(ppt1,atri,this, triadj);
			} else Erreur(20, "");
		}

		if (tri.eti == TB) {
			if (egalpts2(pta,ptb, ppm1,ppm2))
				*triadj = PStriD;
			else if (egalpts2(pta,ptb, ppm1,ppt2)) {
				Triangle_Adjacent(ppt1,ppt2,Ptri, &atri);
				Sous_Triangle(ppt2,atri,this, triadj);
			} else if (egalpts2(pta,ptb, ppt2,ppm2)) {
				Triangle_Adjacent(ppt2,ppt3,Ptri, &atri);
				Sous_Triangle(ppt2,atri,this, triadj);
			}
			else Erreur(20, "");
		}

		if (tri.eti == TC) {
			if (egalpts2(pta,ptb, ppm2,ppm3))
				*triadj = PStriD;
			else if (egalpts2(pta,ptb, ppm2,ppt3)) {
				Triangle_Adjacent(ppt2,ppt3,Ptri, &atri);
				Sous_Triangle(ppt3,atri,this, triadj);
			} else if (egalpts2(pta,ptb, ppt3,ppm3)) {
				Triangle_Adjacent(ppt3,ppt1,Ptri, &atri);
				Sous_Triangle(ppt3,atri,this, triadj);
			}
			else Erreur(20, "");
		}
	}
}


void	calcul_coor_ptinter(reel w, reel c1, reel c2, reel c3, reel c4, reel c5, reel c6, reel c7, reel c8, reel *inter)
{
	*inter = 0.5*(c1+c2) + 2*w*(c3+c4) - w*(c5+c6+c7+c8);
}


void	Calcul_pt_inter(PointVol pta, PointVol ptb, reel w, const Triangle& tri, Volume* o, PointVol *ptinter)
{
	Triangle triadj,aile_ad,aile_bd,aile_ac,aile_bc;
	PointVol ptc,ptd,ptad,ptbd,ptac,ptbc,pt1,pt2,pt3;
	reel interx,intery,interz;

	o->Triangle_Adjacent(pta,ptb,tri,&triadj);
	troisieme_pts(pta,ptb,tri,o, &ptc);
	troisieme_pts(pta,ptb,triadj,o, &ptd);
	o->Triangle_Adjacent(pta,ptc,tri,&aile_ac);
	o->Triangle_Adjacent(ptb,ptc,tri,&aile_bc);
	o->Triangle_Adjacent(pta,ptd,triadj,&aile_ad);
	o->Triangle_Adjacent(ptb,ptd,triadj,&aile_bd);
	troisieme_pts(pta,ptc,aile_ac,o, &ptac);
	troisieme_pts(ptb,ptc,aile_bc,o, &ptbc);
	troisieme_pts(pta,ptd,aile_ad,o, &ptad);
	troisieme_pts(ptb,ptd,aile_bd,o, &ptbd);
	calcul_coor_ptinter(w,pta->x(),ptb->x(),ptc->x(),ptd->x(),ptac->x(),ptad->x(),ptbc->x(),ptbd->x(),&interx);
	calcul_coor_ptinter(w,pta->y(),ptb->y(),ptc->y(),ptd->y(),ptac->y(),ptad->y(),ptbc->y(),ptbd->y(),&intery);
	calcul_coor_ptinter(w,pta->z(),ptb->z(),ptc->z(),ptd->z(),ptac->z(),ptad->z(),ptbc->z(),ptbd->z(),&interz);
	**ptinter = point (interx,intery,interz);


/* patch */

	Pts_Triangle(triadj,&pt1,&pt2,&pt3);
	if (triadj.eti == T0)
		{

		if (egalpts2(pta,ptb,pt1,pt2))
			(triadj.Tri0)->pm1 = *ptinter;
		else	if (egalpts2(pta,ptb,pt2,pt3))
			(triadj.Tri0)->pm2 = *ptinter;
		else	if (egalpts2(pta,ptb,pt3,pt1))
			(triadj.Tri0)->pm3 = *ptinter;

		}
	else
		{
		if (egalpts2(pta,ptb,pt1,pt2))
			(triadj.STri)->pm1 = *ptinter;
		else	if (egalpts2(pta,ptb,pt2,pt3))
			(triadj.STri)->pm2 = *ptinter;
		else	if (egalpts2(pta,ptb,pt3,pt1))
			(triadj.STri)->pm3 = *ptinter;

		}
}


void	Volume::Subdivise_Tri (const Triangle& tri, Triangle *STriA, Triangle *STriB, Triangle *STriC, Triangle *STriD)
{
	Triangle StrianA,StrianB,StrianC,StrianD;
//	PointVol ptinter;
	PointVol pt1,pt2,pt3,pm1,pm2,pm3;

	reel w;

	if (A_Sous_Tri(tri,this)) {
		Sous_Tri (tri,this, &StrianA,&StrianB,&StrianC,&StrianD);
		*STriA = StrianA; *STriB = StrianB; *STriC = StrianC; *STriD = StrianD;
	} else {
		w=this->Coefficient_Tension();
		Pts_Triangle(tri, &pt1,&pt2,&pt3);
		Pts_Milieu_Triangle(tri,&pm1,&pm2,&pm3);
		if (pm1 == 0) {
			Creer_PointVol (0.0,0.0,0.0,&pm1);
			Point_Creer_par_Tri(1,tri);
			Calcul_pt_inter(pt1,pt2,w,tri,this,&pm1);
		}

		if (pm2 == 0) {
			Creer_PointVol (0.0,0.0,0.0,&pm2);
			Point_Creer_par_Tri(2,tri);
			Calcul_pt_inter(pt2,pt3,w,tri,this,&pm2);
		}

		if (pm3 == 0) {
			Creer_PointVol (0.0,0.0,0.0,&pm3);
			Point_Creer_par_Tri(3,tri);
			Calcul_pt_inter(pt3,pt1,w,tri,this,&pm3);
		}

		Assigne_pt_milieu(pm1,pm2,pm3,tri,this);
		creer_STri (pm1,pm2,pm3,tri,this);
		Sous_Tri (tri,this, STriA,STriB,STriC,STriD);
	}
}


void Desalloue_pts_triangle (const Triangle& tri, Volume *o)
{
	PointVol pm1,pm2,pm3;
	booleen a_cree_pm1,a_cree_pm2,a_cree_pm3;

	Pts_Milieu_Triangle(tri, &pm1,&pm2,&pm3);
	Pts_Milieu_Cree_par_Triangle(tri, &a_cree_pm1,&a_cree_pm2,&a_cree_pm3);

	if (a_cree_pm1) {
		delete pm1;
		//if (tri.eti == T0) tri.Tri0->pm1 = 0;
		//else tri.STri->pm1 = 0;
		//Point_Detruit_par_Tri (1, tri);
		//if (tri.eti == T0) TriAdj0(
	}
	if (a_cree_pm2) {
		delete pm2;
		//if (tri.eti == T0) tri.Tri0->pm2 = 0;
		//else tri.STri->pm2 = 0;
		//Point_Detruit_par_Tri (2, tri);
	}
	if (a_cree_pm3) {
		delete pm3;
		//if (tri.eti == T0) tri.Tri0->pm3 = 0;
		//else tri.STri->pm3 = 0;
		//Point_Detruit_par_Tri (3, tri);
	}
}

void Desalloue_triangles (const Triangle& tri, Volume *o)
/* Desalloue les 4 sous-triangles de tri */
{
	if (tri.eti == T0) {
		delete tri.Tri0->STrianglei;
		tri.Tri0->STrianglei = 0;
	} else {
		delete tri.STri->STrianglei;
		tri.STri->STrianglei = 0;
	}
}


void Detruit_Sous_Triangles (const Triangle& tri, Volume *o)
{
	Triangle StriA,StriB,StriC,StriD;

#if 1
	if (A_Sous_Tri(tri,o)) {
		Sous_Tri(tri,o, &StriA,&StriB,&StriC,&StriD);

		Detruit_Sous_Triangles (StriA,o);
		Detruit_Sous_Triangles (StriB,o);
		Detruit_Sous_Triangles (StriC,o);
		Detruit_Sous_Triangles (StriD,o);

		Desalloue_triangles(tri,o);
		//if (tri.eti != T0) Desalloue_pts_triangle (tri, o);
	}
	Desalloue_pts_triangle (tri, o);
#else
	if (A_Sous_Tri(tri,o)) {
		Sous_Tri(tri,o, &StriA,&StriB,&StriC,&StriD);

		Detruit_Sous_Triangles (StriA,o);
		Desalloue_pts_triangle(StriA,o);

		Detruit_Sous_Triangles (StriB,o);
		Desalloue_pts_triangle(StriB,o);

		Detruit_Sous_Triangles (StriC,o);
		Desalloue_pts_triangle(StriC,o);

		Detruit_Sous_Triangles (StriD,o);
		Desalloue_pts_triangle(StriD,o);

		Desalloue_triangles(tri,o);
        }
#endif
}


void	Reduit_Hauteur_Tri0 (const Triangle& tri, entier hauteur, Volume *o)
{
	Triangle StriA,StriB,StriC,StriD;

	if (hauteur == 0) {
		Detruit_Sous_Triangles (tri,o);
		if (tri.eti == T0) tri.Tri0->pm1 = 0;
		else tri.STri->pm1 = 0;
		Point_Detruit_par_Tri (1, tri);
		if (tri.eti == T0) tri.Tri0->pm2 = 0;
		else tri.STri->pm2 = 0;
		Point_Detruit_par_Tri (2, tri);
		if (tri.eti == T0) tri.Tri0->pm3 = 0;
		else tri.STri->pm3 = 0;
		Point_Detruit_par_Tri (3, tri);
	} else {
		if (A_Sous_Tri(tri,o)) {
			Sous_Tri(tri,o, &StriA,&StriB,&StriC,&StriD);
			Reduit_Hauteur_Tri0 (StriA,hauteur-1,o);
			Reduit_Hauteur_Tri0 (StriB,hauteur-1,o);
			Reduit_Hauteur_Tri0 (StriC,hauteur-1,o);
			Reduit_Hauteur_Tri0 (StriD,hauteur-1,o);
		}
	}
}

void	Volume::Reduit_Hauteur (entier hauteur)
{
	entier j,nb;
	Triangle jtri;

	nb = this->Nb_Triangle();

	for (j=1; j<=nb; j+=1) {
		jtri=this->Ieme_Triangle(j);
		Reduit_Hauteur_Tri0(jtri,hauteur,this);
	}
}

void	Volume::Reduit_Hauteur ()
{
	this->Reduit_Hauteur(this->Niveau_de_Subdiv_Mem());
}

void Conv_Tri_a_Poly(const Triangle& tri, Volume *vol, Ensemble *ens_poly, entier niveau)
{
	Triangle StriA,StriB,StriC,StriD;
	PointVol pt1,pt2,pt3;
	Polygone *poly;

	if (niveau > 0) {
		vol->Subdivise_Tri(tri, &StriA,&StriB,&StriC,&StriD);
		Conv_Tri_a_Poly(StriA,vol,ens_poly,niveau-1);
		Conv_Tri_a_Poly(StriB,vol,ens_poly,niveau-1);
		Conv_Tri_a_Poly(StriC,vol,ens_poly,niveau-1);
		Conv_Tri_a_Poly(StriD,vol,ens_poly,niveau-1);
	} else {
		Pts_Triangle(tri, &pt1,&pt2,&pt3);

		poly = new Polygone;

		poly->ajoute (*pt1);
		poly->ajoute (*pt2);
		poly->ajoute (*pt3);

		ens_poly->ajoute (poly);
	}
}

Objet	 *Volume::Converti()
{
	Triangle tri;
	Ensemble *ens = new Ensemble;

	for (entier i=1; i<=this->Nb_Triangle(); i+=1) {
		tri = this->Ieme_Triangle(i);
		Conv_Tri_a_Poly(tri,this,ens,this->Niveau_de_Subdiv());
	}

	return ens;
}


void	Volume_engl_tri(const Triangle& tri, Volume* o, sphere *vol_engl)
{
	PointVol pt1,pt2,pt3;

	Pts_Triangle(tri,&pt1,&pt2,&pt3);

	//Coordonnees_PointVol(pt1, &x1,&y1,&z1);
	//Coordonnees_PointVol(pt2, &x2,&y2,&z2);
	//Coordonnees_PointVol(pt3, &x3,&y3,&z3);

	reel	xmoy = (pt1->x()+pt2->x()+pt3->x())/3.0;
	reel	ymoy = (pt1->y()+pt2->y()+pt3->y())/3.0;
	reel	zmoy = (pt1->z()+pt2->z()+pt3->z())/3.0;
	//point	ptmoy = point(xmoy,ymoy,zmoy);

	reel x1,x2,x3,y1,y2,y3,z1,z2,z3;

	x1 = pt1->x()-xmoy; x2 = pt2->x()-xmoy; x3 = pt3->x()-xmoy;
	y1 = pt1->y()-ymoy; y2 = pt2->y()-ymoy; y3 = pt3->y()-ymoy;
	z1 = pt1->z()-zmoy; z2 = pt2->z()-zmoy; z3 = pt3->z()-zmoy;

	reel d2,d3,rayon;

	rayon = x1*x1 + y1*y1 + z1*z1;
	d2 = x2*x2 + y2*y2 + z2*z2;
	d3 = x3*x3 + y3*y3 + z3*z3;

	if (d2 > rayon) rayon = d2;
	if (d3 > rayon) rayon = d3;

	*vol_engl = Def_sphere(point(xmoy,ymoy,zmoy),rayon);
}


booleen Droite_Inter_Engl_Tri(const point& p, const vecteur& v, const Triangle& tri,reel k_rayon2, Volume* vo)
{
	sphere S;

	Volume_engl_tri(tri,vo, &S);

	reel	d2 = ((Centre_sphere(S) - p) ^ v).norme2()/v.norme2();

	return d2 < Rayon_sphere2(S)*k_rayon2;
}


booleen Demi_Droite_Inter_Tri(const point& p, const vecteur& v, const Triangle& tri, reel *k, vecteur *normal)
{
	PointVol	pt1,pt2,pt3;

	Pts_Triangle(tri,&pt1,&pt2,&pt3);

	point p1 = *pt1;
	point p2 = *pt2;
	point p3 = *pt3;

	plan	pl(p1,p2,p3);

	point	pi;

	if (!pl.inter (p,v, &pi, k)) return FAUX;

	vecteur v1(p1,p2);
	vecteur v2(p2,p3);
	vecteur v3(p3,p1);

	vecteur u1(p1,pi);
	vecteur u2(p2,pi);
	vecteur u3(p3,pi);

	vecteur n1 = v1^u1;
	vecteur n2 = v2^u2;
	vecteur n3 = v3^u3;

	n1.normalise();
	n2.normalise();
	n3.normalise();

	if (n1*n2 < EPSTRI || n2*n3 < EPSTRI || n1*n3 < EPSTRI) return FAUX;
	else {
		*normal = pl.normale ();
		reel cost = v * *normal;
		if (cost > 0) *normal = -*normal;
		return VRAI;
	}
}

booleen Rayon_Inter_Vol(const point& p, const vecteur& v, const Triangle& tri, Volume* vo, entier niveau, reel k_rayon2, reel *k, vecteur *normal)
{
	if (niveau <= 0) {
		return Demi_Droite_Inter_Tri(p,v,tri, k,normal);
	} else {
		if (Droite_Inter_Engl_Tri(p,v,tri,k_rayon2,vo)) {
			booleen	inter = FAUX;
			vecteur	norm;
			Triangle StriA,StriB,StriC,StriD;

			vo->Subdivise_Tri(tri,&StriA,&StriB,&StriC,&StriD);

			reel	 k2 = *k;
			if (Rayon_Inter_Vol(p,v,StriA,vo,niveau-1,k_rayon2, &k2,&norm)) {
				if (k2 < *k) {
					*k = k2;
					*normal = norm;
					inter = VRAI;
				}
			}

			k2 = *k;
			if (Rayon_Inter_Vol(p,v,StriB,vo,niveau-1,k_rayon2, &k2,&norm)) {
				if (k2 < *k) {
					*k = k2;
					*normal = norm;
					inter = VRAI;
				}
			}

			k2 = *k;
			if (Rayon_Inter_Vol(p,v,StriC,vo,niveau-1,k_rayon2, &k2,&norm)) {
				if (k2 < *k) {
					*k = k2;
					*normal = norm;
					inter = VRAI;
				}
			}

			k2 = *k;
			if (Rayon_Inter_Vol(p,v,StriD,vo,niveau-1,k_rayon2, &k2,&norm)) {
				if (k2 < *k) {
					*k = k2;
					*normal = norm;
					inter = VRAI;
				}
			}

			return (inter);
		} else return FAUX;
	}
}

static	entier	nbinter = 0;

booleen Volume::inter(const point& p, const vecteur& v, reel *k)
{
	Triangle tri;
	reel k2;
	vecteur norm;
	booleen	inter = FAUX;

	//*k = INFINI;

	for (entier i=1; i<=this->Nb_Triangle(); i+=1) {
		tri = this->Ieme_Triangle(i);
		k2 = *k;
		if (Rayon_Inter_Vol(p,v,tri,this,this->Subdiv,tri.Tri0->k_rayon2, &k2,&norm)) {
			if (k2 < *k) {
				*k = k2;
				this->normal = norm;
				inter = VRAI;
			}
		}
	}
	if ((++nbinter%16)==0) {
		this->Reduit_Hauteur(0);
		nbinter = 0;
	}
	return inter;
}

vecteur	Volume::gradient(const point &p)
{
	return this->normal; // ???
}

Volume	*Volume::Subdivise()
{
	PointVol pts[100000];
	PointVol pts2[100000];
	entier	n=0;

	Triangle tri,A,B,C,D;
	PointVol p1,p2,p3;
	PointVol q1,q2,q3;

	entier i,j;
	for (i=1; i<=this->Nb_Triangle(); i+=1) {
		tri = this->Ieme_Triangle (i);
		this->Subdivise_Tri(tri, &A,&B,&C,&D);

		Pts_Triangle (A, &p1,&p2,&p3);

		for (j=0; j<n; j+=1) if (p1 == pts[j]) break;
		if (j==n) {
			pts[n] = p1;
			Creer_PointVol(p1->x(),p1->y(),p1->z(), &q1);
			pts2[n++] = q1;
		}

		for (j=0; j<n; j+=1) if (p2 == pts[j]) break;
		if (j==n) {
			pts[n] = p2;
			Creer_PointVol(p2->x(),p2->y(),p2->z(), &q2);
			pts2[n++] = q2;
		}

		for (j=0; j<n; j+=1) if (p3 == pts[j]) break;
		if (j==n) {
			pts[n] = p3;
			Creer_PointVol(p3->x(),p3->y(),p3->z(), &q3);
			pts2[n++] = q3;
		}

		Pts_Triangle (B, &p1,&p2,&p3);

		for (j=0; j<n; j+=1) if (p1 == pts[j]) break;
		if (j==n) {
			pts[n] = p1;
			Creer_PointVol(p1->x(),p1->y(),p1->z(), &q1);
			pts2[n++] = q1;
		}

		for (j=0; j<n; j+=1) if (p2 == pts[j]) break;
		if (j==n) {
			pts[n] = p2;
			Creer_PointVol(p2->x(),p2->y(),p2->z(), &q2);
			pts2[n++] = q2;
		}

		for (j=0; j<n; j+=1) if (p3 == pts[j]) break;
		if (j==n) {
			pts[n] = p3;
			Creer_PointVol(p3->x(),p3->y(),p3->z(), &q3);
			pts2[n++] = q3;
		}

		Pts_Triangle (C, &p1,&p2,&p3);

		for (j=0; j<n; j+=1) if (p1 == pts[j]) break;
		if (j==n) {
			pts[n] = p1;
			Creer_PointVol(p1->x(),p1->y(),p1->z(), &q1);
			pts2[n++] = q1;
		}

		for (j=0; j<n; j+=1) if (p2 == pts[j]) break;
		if (j==n) {
			pts[n] = p2;
			Creer_PointVol(p2->x(),p2->y(),p2->z(), &q2);
			pts2[n++] = q2;
		}

		for (j=0; j<n; j+=1) if (p3 == pts[j]) break;
		if (j==n) {
			pts[n] = p3;
			Creer_PointVol(p3->x(),p3->y(),p3->z(), &q3);
			pts2[n++] = q3;
		}

		Pts_Triangle (D, &p1,&p2,&p3);

		for (j=0; j<n; j+=1) if (p1 == pts[j]) break;
		if (j==n) {
			pts[n] = p1;
			Creer_PointVol(p1->x(),p1->y(),p1->z(), &q1);
			pts2[n++] = q1;
		}

		for (j=0; j<n; j+=1) if (p2 == pts[j]) break;
		if (j==n) {
			pts[n] = p2;
			Creer_PointVol(p2->x(),p2->y(),p2->z(), &q2);
			pts2[n++] = q2;
		}

		for (j=0; j<n; j+=1) if (p3 == pts[j]) break;
		if (j==n) {
			pts[n] = p3;
			Creer_PointVol(p3->x(),p3->y(),p3->z(), &q3);
			pts2[n++] = q3;
		}
	}

	Volume	*v = new Volume;
	entier	k,l;

	for (i=1; i<=this->Nb_Triangle(); i+=1) {
		tri = this->Ieme_Triangle (i);

		this->Subdivise_Tri(tri, &A,&B,&C,&D);

		Pts_Triangle (A, &p1,&p2,&p3);

		for (j=0; j<n; j+=1) if (p1 == pts[j]) break;
		for (k=0; k<n; k+=1) if (p2 == pts[k]) break;
		for (l=0; l<n; l+=1) if (p3 == pts[l]) break;

		Def_Triangle (pts2[j],pts2[k],pts2[l], &tri);

		v->Ajoute(tri);

		Pts_Triangle (B, &p1,&p2,&p3);

		for (j=0; j<n; j+=1) if (p1 == pts[j]) break;
		for (k=0; k<n; k+=1) if (p2 == pts[k]) break;
		for (l=0; l<n; l+=1) if (p3 == pts[l]) break;

		Def_Triangle (pts2[j],pts2[k],pts2[l], &tri);

		v->Ajoute(tri);

		Pts_Triangle (C, &p1,&p2,&p3);

		for (j=0; j<n; j+=1) if (p1 == pts[j]) break;
		for (k=0; k<n; k+=1) if (p2 == pts[k]) break;
		for (l=0; l<n; l+=1) if (p3 == pts[l]) break;

		Def_Triangle (pts2[j],pts2[k],pts2[l], &tri);

		v->Ajoute(tri);

		Pts_Triangle (D, &p1,&p2,&p3);

		for (j=0; j<n; j+=1) if (p1 == pts[j]) break;
		for (k=0; k<n; k+=1) if (p2 == pts[k]) break;
		for (l=0; l<n; l+=1) if (p3 == pts[l]) break;

		Def_Triangle (pts2[j],pts2[k],pts2[l], &tri);

		v->Ajoute(tri);
	}

	v->Organise();
	v->attributs(this->attributs());
	return v;
}

Objet	*Volume::copie() const
{
	//this->Reduit_Hauteur(0);

	PointVol pts[500];
	PointVol pts2[500];
	entier	n=0;

	Triangle tri;
	PointVol p1,p2,p3;
	PointVol q1,q2,q3;

	entier i,j;
	for (i=1; i<=this->Nb_Triangle(); i+=1) {
		tri = this->Ieme_Triangle (i);
		Pts_Triangle (tri, &p1,&p2,&p3);

		for (j=0; j<n; j+=1) if (p1 == pts[j]) break;
		if (j==n) {
			pts[n] = p1;
			Creer_PointVol(p1->x(),p1->y(),p1->z(), &q1);
			pts2[n++] = q1;
		}

		for (j=0; j<n; j+=1) if (p2 == pts[j]) break;
		if (j==n) {
			pts[n] = p2;
			Creer_PointVol(p2->x(),p2->y(),p2->z(), &q2);
			pts2[n++] = q2;
		}

		for (j=0; j<n; j+=1) if (p3 == pts[j]) break;
		if (j==n) {
			pts[n] = p3;
			Creer_PointVol(p3->x(),p3->y(),p3->z(), &q3);
			pts2[n++] = q3;
		}
	}

	Volume	*v = new Volume;
	entier	k,l;

	for (i=1; i<=this->Nb_Triangle(); i+=1) {
		tri = this->Ieme_Triangle (i);
		Pts_Triangle (tri, &p1,&p2,&p3);

		for (j=0; j<n; j+=1) if (p1 == pts[j]) break;
		for (k=0; k<n; k+=1) if (p2 == pts[k]) break;
		for (l=0; l<n; l+=1) if (p3 == pts[l]) break;

		Def_Triangle (pts2[j],pts2[k],pts2[l], &tri);

		v->Ajoute(tri);
	}

	v->Organise();
	v->attributs(this->attributs());
	v->defvol = this->defvol;
	if (this->defvol) v->vol = this->vol->copie();
	return v;
}

static	reel	max4(reel a, reel b, reel c, reel d)
{
	reel max=a;

	if (b>max) max=b;
	if (c>max) max=c;
	if (d>max) max=d;
	return(max);
}

static	reel	MaxRayon(const Triangle& tri, Volume* vo, entier niveau)
{
	sphere S,Sa,Sb,Sc,Sd;

	if (niveau == 0)
		return(1.0);
	
	else {
		Triangle StriA,StriB,StriC,StriD;

		vo->Subdivise_Tri(tri,&StriA,&StriB,&StriC,&StriD);

		reel ka=MaxRayon(StriA,vo,niveau-1);
		reel kb=MaxRayon(StriB,vo,niveau-1);
		reel kc=MaxRayon(StriC,vo,niveau-1);
		reel kd=MaxRayon(StriD,vo,niveau-1);
		reel k=max4(ka,kb,kc,kd);
	
		Volume_engl_tri(tri,vo, &S);
		reel r2 = Rayon_sphere2(S);
		point c = Centre_sphere(S);
					
		Volume_engl_tri(StriA,vo, &Sa);
		reel r2a = Rayon_sphere2(Sa);
		point ca = Centre_sphere(Sa);
		if (((c-ca).norme2()+r2a*ka) > (k*r2)) 
			k=((c-ca).norme2()+r2a*ka)/r2;
			
		Volume_engl_tri(StriB,vo, &Sb);
		reel r2b = Rayon_sphere2(Sb);
		point cb = Centre_sphere(Sb);
		if (((c-cb).norme2()+r2b*kb) > (k*r2)) 
			k=((c-cb).norme2()+r2b*kb)/r2;
			
		Volume_engl_tri(StriC,vo, &Sc);
		reel r2c = Rayon_sphere2(Sc);
		point cc = Centre_sphere(Sc);
		if (((c-cc).norme2()+r2c*kc) > (k*r2)) 
			k=((c-cc).norme2()+r2c*kc)/r2;
			
		Volume_engl_tri(StriD,vo, &Sd);
		reel r2d = Rayon_sphere2(Sd);
		point cd = Centre_sphere(Sd);
		if (((c-cd).norme2()+r2d*kd) > (k*r2)) 
			k=((c-cd).norme2()+r2d*kd)/r2;
			
		return(k);
	}
}

void	Volume::volume(int)
{
	Triangle tri;
	sphere S;
//	Triangle0 Tri0;
	entier i;

	this->Reduit_Hauteur(0);
	
	if (englobantexact) {
		cout << "Englobant du volume exacte, debut calcul:\n";
		cout << "\n";
		}

	for (i=1; i<=this->Nb_Triangle(); i+=1) {
		tri = this->Ieme_Triangle(i);
		if (englobantexact) {
			tri.Tri0->k_rayon2 = MaxRayon(tri, this, this->Subdiv);
			this->Reduit_Hauteur(0);
		} else {
			tri.Tri0->k_rayon2 = 1.0;
		}
	}


	tri = this->Ieme_Triangle(1);
	Volume_engl_tri(tri,this, &S);

	reel	r = Rayon_sphere(S)*sqrt(tri.Tri0->k_rayon2);
	point	c = Centre_sphere(S);

	reel	xmin = c.x()-r;
	reel	ymin = c.y()-r;
	reel	zmin = c.z()-r;
	reel	xmax = c.x()+r;
	reel	ymax = c.y()+r;
	reel	zmax = c.z()+r;

	for (i=2; i<=this->Nb_Triangle(); i+=1) {
		tri = this->Ieme_Triangle(i);
		Volume_engl_tri(tri,this, &S);

		r = Rayon_sphere(S)*sqrt(tri.Tri0->k_rayon2);
		c = Centre_sphere(S);

		if (xmin > c.x()-r) xmin = c.x()-r;
		if (ymin > c.y()-r) ymin = c.y()-r;
		if (zmin > c.z()-r) zmin = c.z()-r;

		if (xmax < c.x()+r) xmax = c.x()+r;
		if (ymax < c.y()+r) ymax = c.y()+r;
		if (zmax < c.z()+r) zmax = c.z()+r;
	}

        this->vol = new Cube(Deplacement(point(xmin,ymin,zmin) - O) *
                       Homothetie (O,X, xmax-xmin) *
                       Homothetie (O,Y, ymax-ymin) *
                       Homothetie (O,Z, zmax-zmin));
        this->defvol = VRAI;

	if (englobantexact) {
		cout << "Englobant du volume exacte, fin calcul\n";
		}

}

const	Englobant&	Volume::volume() const
{
	if (!defvol) ((Volume*)this)->volume(0);
	return *vol;
}

Volume::~Volume()
{
	this->Reduit_Hauteur(0);

	delete this->LiTri0;
	this->LiTri0 = 0;
}

