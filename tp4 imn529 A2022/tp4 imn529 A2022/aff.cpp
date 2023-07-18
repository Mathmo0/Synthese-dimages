#include <cmath>			//cos,sin
#include "aff.h"
#include "utilalg.h"
#include "camera.h"
#include "geo.h"
#include "objets.h"
#include "definition.h"		//PI, entier
#include "canon.h"
#include "main.h"
#include "global.h"

static	double	*VX = new double[4];
static	double	*VY = new double[4];
static	double	*VZ = new double[4];
static	double	*nx = new double[4];
static	double	*ny = new double[4];
static	double	*nz = new double[4];
static	double	*vx=VX;
static	double	*vy=VY;
static	double	*vz=VZ;
static	entier	n=4;

static  const	point	p1(0.0, 0.0, 0.0);
static  const	point	p2(0.0, 0.0, 1.0);
static  const	point	p3(0.0, 1.0, 0.0);
static  const	point	p4(0.0, 1.0, 1.0);
static  const	point	p5(1.0, 0.0, 0.0);
static  const	point	p6(1.0, 0.0, 1.0);
static  const	point	p7(1.0, 1.0, 0.0);
static  const	point	p8(1.0, 1.0, 1.0);
static	const	point	cube[8] = { p1,p2,p3,p4,p5,p6,p7,p8, };

void	Projection(const Camera& camera, const Transformation& v, const point& p, reel *x, reel *y)
{
	reel	z;
	point p2 = v.transforme(p);
	p2.coordonnees (x,y,&z); 
	if (camera.perspective()) 
	{
		*x /= z;
		*y /= z;
	}
}

void Affiche_Ligne(const point& p1, const point& p2, const Transformation& v, const Attributs& a)
{
	if ( pFenAff3D->Display()->Settings()->OpenGL() ) 
	{
		point	q1 = v.transforme(p1);
		point	q2 = v.transforme(p2);

		pFenAff3D->Display()->Ligne((double)q1.x(),(double)q1.y(),(double)q1.z(), (double)q2.x(),(double)q2.y(),(double)q2.z(), a);
	} 
	else 
	{
		reel	x1,y1,x2,y2;

		Projection (pFenAff3D->Scene()->GetCamera(), v, p1, &x1,&y1);
		Projection (pFenAff3D->Scene()->GetCamera(), v, p2, &x2,&y2);
		pFenAff3D->Display()->Ligne((double)x1,(double)y1, (double)x2,(double)y2, a);
	}
}


void Affiche_Trigone(const point& p1, const point& p2, const point& p3, const Transformation& v, const Attributs& a)
{
	if ( pFenAff3D->Display()->Settings()->OpenGL() ) 
	{
		point	q1 = v.transforme(p1);
		point	q2 = v.transforme(p2);
		point	q3 = v.transforme(p3);

		vx[0] = q1.x(); vy[0] = q1.y(); vz[0] = q1.z();
		vx[1] = q2.x(); vy[1] = q2.y(); vz[1] = q2.z();
		vx[2] = q3.x(); vy[2] = q3.y(); vz[2] = q3.z();

		pFenAff3D->Display()->Polygone(3,vx,vy,vz,a);
	} 
	else 
	{
		reel	x,y;
		Projection (pFenAff3D->Scene()->GetCamera(), v, p1, &x,&y);
		vx[0] = x; vy[0] = y;
		Projection (pFenAff3D->Scene()->GetCamera(), v, p2, &x,&y);
		vx[1] = x; vy[1] = y;
		Projection (pFenAff3D->Scene()->GetCamera(), v, p3, &x,&y);
		vx[2] = x; vy[2] = y;
		pFenAff3D->Display()->Polygone(3,vx,vy,a);
	}
}

void Affiche_Tetragone(const point& p1, const point& p2, const point& p3, const point& p4, const Transformation& v, const Attributs& a)
{
	if ( pFenAff3D->Display()->Settings()->OpenGL() ) 
	{
		point	q1 = v.transforme(p1);
		point	q2 = v.transforme(p2);
		point	q3 = v.transforme(p3);
		point	q4 = v.transforme(p4);

		vx[0] = q1.x(); vy[0] = q1.y(); vz[0] = q1.z();
		vx[1] = q2.x(); vy[1] = q2.y(); vz[1] = q2.z();
		vx[2] = q3.x(); vy[2] = q3.y(); vz[2] = q3.z();
		vx[3] = q4.x(); vy[3] = q4.y(); vz[3] = q4.z();

		pFenAff3D->Display()->Polygone(4,vx,vy,vz,a);
	} 
	else 
	{
		reel	x,y;
		Projection (pFenAff3D->Scene()->GetCamera(), v, p1, &x,&y);
		vx[0] = x; vy[0] = y;
		Projection (pFenAff3D->Scene()->GetCamera(), v, p2, &x,&y);
		vx[1] = x; vy[1] = y;
		Projection (pFenAff3D->Scene()->GetCamera(), v, p3, &x,&y);
		vx[2] = x; vy[2] = y;
		Projection (pFenAff3D->Scene()->GetCamera(), v, p4, &x,&y);
		vx[3] = x; vy[3] = y;
		pFenAff3D->Display()->Polygone(4,vx,vy,a);
	}
}


void Affiche_Trigone(const point& p1, const point& p2, const point& p3,  const vecteur& n1, const vecteur& n2, const vecteur& n3, const Transformation& v, const Attributs& a)
{
	if ( pFenAff3D->Display()->Settings()->OpenGL() ) 
	{
		point	q1 = v.transforme(p1);
		point	q2 = v.transforme(p2);
		point	q3 = v.transforme(p3);

		vx[0] = q1.x(); vy[0] = q1.y(); vz[0] = q1.z();
		vx[1] = q2.x(); vy[1] = q2.y(); vz[1] = q2.z();
		vx[2] = q3.x(); vy[2] = q3.y(); vz[2] = q3.z();

		vecteur	m1 = v.transforme(plan(O,n1)).normale();
		vecteur	m2 = v.transforme(plan(O,n2)).normale();
		vecteur	m3 = v.transforme(plan(O,n3)).normale();

		nx[0] = m1.x(); ny[0] = m1.y(); nz[0] = m1.z();
		nx[1] = m2.x(); ny[1] = m2.y(); nz[1] = m2.z();
		nx[2] = m3.x(); ny[2] = m3.y(); nz[2] = m3.z();

		pFenAff3D->Display()->Polygone(3, vx,vy,vz, nx,ny,nz, a);
	} 
	else 
	{
		reel	x,y;
		Projection (pFenAff3D->Scene()->GetCamera(), v, p1, &x,&y);
		vx[0] = x; vy[0] = y;
		Projection (pFenAff3D->Scene()->GetCamera(), v, p2, &x,&y);
		vx[1] = x; vy[1] = y;
		Projection (pFenAff3D->Scene()->GetCamera(), v, p3, &x,&y);
		vx[2] = x; vy[2] = y;
		pFenAff3D->Display()->Polygone(3, vx,vy, a);
	}
}


void Affiche_Tetragone(const point& p1, const point& p2, const point& p3, const point& p4, const vecteur& n1, const vecteur& n2, const vecteur& n3, const vecteur& n4, const Transformation& v, const Attributs& a)
{
	if ( pFenAff3D->Display()->Settings()->OpenGL() ) 
	{
		point	q1 = v.transforme(p1);
		point	q2 = v.transforme(p2);
		point	q3 = v.transforme(p3);
		point	q4 = v.transforme(p4);

		vx[0] = q1.x(); vy[0] = q1.y(); vz[0] = q1.z();
		vx[1] = q2.x(); vy[1] = q2.y(); vz[1] = q2.z();
		vx[2] = q3.x(); vy[2] = q3.y(); vz[2] = q3.z();
		vx[3] = q4.x(); vy[3] = q4.y(); vz[3] = q4.z();

		vecteur	m1 = v.transforme(plan(O,n1)).normale();
		vecteur	m2 = v.transforme(plan(O,n2)).normale();
		vecteur	m3 = v.transforme(plan(O,n3)).normale();
		vecteur	m4 = v.transforme(plan(O,n4)).normale();

		nx[0] = m1.x(); ny[0] = m1.y(); nz[0] = m1.z();
		nx[1] = m2.x(); ny[1] = m2.y(); nz[1] = m2.z();
		nx[2] = m3.x(); ny[2] = m3.y(); nz[2] = m3.z();
		nx[3] = m4.x(); ny[3] = m4.y(); nz[3] = m4.z();

		pFenAff3D->Display()->Polygone(4, vx,vy,vz, nx,ny,nz, a);
	} 
	else 
	{
		reel	x,y;
		Projection (pFenAff3D->Scene()->GetCamera(), v, p1, &x,&y);
		vx[0] = x; vy[0] = y;
		Projection (pFenAff3D->Scene()->GetCamera(), v, p2, &x,&y);
		vx[1] = x; vy[1] = y;
		Projection (pFenAff3D->Scene()->GetCamera(), v, p3, &x,&y);
		vx[2] = x; vy[2] = y;
		Projection (pFenAff3D->Scene()->GetCamera(), v, p4, &x,&y);
		vx[3] = x; vy[3] = y;
		pFenAff3D->Display()->Polygone(4, vx,vy, a);
	}
}

void Englobant::Afficher(const Transformation& v, const Attributs& a) const
{
}

void VolVide::Afficher(const Transformation& v, const Attributs& a) const
{
}

void Infini::Afficher(const Transformation& v, const Attributs& a) const
{
}

void Carre::Afficher(const Transformation& v, const Attributs& a) const
{
	Attributs	attr = pFenAff3D->Display()->Settings()->CouleurContourPolygone();

	Transformation	t = v * a.transformation() * transformation();

	if (a.highlight()) attr.highlight(VRAI);

	Affiche_Ligne(cube[0], cube[1], t, attr);
	Affiche_Ligne(cube[0], cube[2], t, attr);
	Affiche_Ligne(cube[0], cube[4], t, attr);
	Affiche_Ligne(cube[1], cube[3], t, attr);
	Affiche_Ligne(cube[1], cube[5], t, attr);
	Affiche_Ligne(cube[2], cube[3], t, attr);
	Affiche_Ligne(cube[2], cube[6], t, attr);
	Affiche_Ligne(cube[3], cube[7], t, attr);
	Affiche_Ligne(cube[4], cube[5], t, attr);
	Affiche_Ligne(cube[4], cube[6], t, attr);
	Affiche_Ligne(cube[5], cube[7], t, attr);
	Affiche_Ligne(cube[6], cube[7], t, attr);
}

void Cube::Afficher (const Transformation& v, const Attributs& a) const
{
	Attributs	attr = pFenAff3D->Display()->Settings()->CouleurContourPolygone();

	Transformation	t = v * a.transformation() * transformation();

	if (a.highlight()) attr.highlight(VRAI);

	Affiche_Ligne(cube[0], cube[1], t, attr);
	Affiche_Ligne(cube[0], cube[2], t, attr);
	Affiche_Ligne(cube[0], cube[4], t, attr);
	Affiche_Ligne(cube[1], cube[3], t, attr);
	Affiche_Ligne(cube[1], cube[5], t, attr);
	Affiche_Ligne(cube[2], cube[3], t, attr);
	Affiche_Ligne(cube[2], cube[6], t, attr);
	Affiche_Ligne(cube[3], cube[7], t, attr);
	Affiche_Ligne(cube[4], cube[5], t, attr);
	Affiche_Ligne(cube[4], cube[6], t, attr);
	Affiche_Ligne(cube[5], cube[7], t, attr);
	Affiche_Ligne(cube[6], cube[7], t, attr);
}

void Ensemble::Afficher(const Transformation& v, const Attributs& a0) const
{
	Attributs	a1 = a0 * (((Objet *)this)->attributs());

	if (profondeur == 0 || profondeur == 1) return;

	profondeur -= 1;
	for (entier i=1; i<=composantes(); i+=1) 
		composante(i)->Afficher(v, a1);

	profondeur += 1;
}

void Affiche_point (const point& p, const Transformation& v, const Attributs& a)
{
	point	p1(p.x()-epselect, p.y(), p.z());
	point	p2(p.x()+epselect, p.y(), p.z());
	point	q1(p.x(), p.y()-epselect, p.z());
	point	q2(p.x(), p.y()+epselect, p.z());
	point	r1(p.x(), p.y(), p.z()-epselect);
	point	r2(p.x(), p.y(), p.z()+epselect);

	Affiche_Ligne(p1,p2, v, a);
	Affiche_Ligne(q1,q2, v, a);
	Affiche_Ligne(r1,r2, v, a);
}

void Point::Afficher(const Transformation& v, const Attributs& a0) const
{
	Attributs	a1 = a0 * ((Objet *)this)->attributs();

	Affiche_point (pt(), v * a1.transformation(), a1);
}

void Droite::Afficher(const Transformation& v, const Attributs& a0) const
{
	Attributs	a1 = a0 * ((Objet *)this)->attributs();

	reel	x1,y1,x2,y2;

	Projection (pFenAff3D->Scene()->GetCamera(), v * a1.transformation(), this->mdroite().mpoint(), &x1,&y1);
	Projection (pFenAff3D->Scene()->GetCamera(), v * a1.transformation(), this->mdroite().mpoint()+this->mdroite().mvecteur(), &x2,&y2);
	pFenAff3D->Display()->Ligne((double)x1,(double)y1, (double)x2,(double)y2, a1);
}

void Plan::Afficher(const Transformation& v, const Attributs& a0) const
{
	Attributs	a1 = a0 * ((Objet *)this)->attributs();

	if ( pFenAff3D->Display()->Settings()->OpenGL() && !a1.highlight() ) 
	{
		Transformation	t = Alignement (this->mplan().normale(), X);
		point	p1 = this->mplan().mpoint() + t.inverse(vecteur(0.0,0.0,100.0) + vecteur(0.0,100.0,0.0));
		point	p2 = this->mplan().mpoint() + t.inverse(vecteur(0.0,0.0,-100.0) + vecteur(0.0,100.0,0.0));
		point	p3 = this->mplan().mpoint() + t.inverse(vecteur(0.0,0.0,-100.0) + vecteur(0.0,-100.0,0.0));
		point	p4 = this->mplan().mpoint() + t.inverse(vecteur(0.0,0.0,100.0) + vecteur(0.0,-100.0,0.0));

		Affiche_Tetragone(p1,p2,p3,p4, v * a1.transformation(), a1);
	} 
	else 
	{
		point p = this->mplan().mpoint();
		vecteur n = this->mplan().normale().unitaire();
		n = n *(epselect*7);

		pFenAff3D->Display()->Pointille((short)0xD739,1);
		Affiche_Ligne (p, p+n, v * a1.transformation(), a1);

		pFenAff3D->Display()->DesactivePointille();
	}
}

#ifdef LinkSphere
void Sphere::Afficher(const Transformation& v, const Attributs& a0) const
{
	Attributs	a1 = a0 * attributs();
	Transformation t = v * a1.transformation();

	entier nm = pFenAff3D->Display()->Settings()->Meridiens();
	entier np = pFenAff3D->Display()->Settings()->Paralleles();

	point	pl1,pl2,p1,p2,p3,p4;
	reel anglemer = 2*PI/nm;
	reel anglepar = PI/(np+1);
	entier	m,p;
	p1 = point(0.0, 1.0, 0.0);
	p2 = Rot_X(anglepar).transforme(p1);

	for (p=0; p<=np; p+=1) 
	{
		p3 = Rot_Y(anglemer).transforme(p1);
		p4 = Rot_Y(anglemer).transforme(p2);

		for (m=0; m<nm; m+=1) 
		{
			Affiche_Tetragone(p1,p2,p4,p3, p1-O,p2-O,p4-O,p3-O, t, a1); // CCWise

			p1 = p3;
			p2 = p4;
			p3 = Rot_Y(anglemer).transforme(p3);
			p4 = Rot_Y(anglemer).transforme(p4);
		}

		p1 = p2;
		p2 = Rot_X(anglepar).transforme(p2);
	}
}
#endif

void Cylindre::Afficher(const Transformation& v, const Attributs& a0) const
{
	Attributs	a1 = a0 * attributs();
	Transformation t = v * a1.transformation();

	entier nm = pFenAff3D->Display()->Settings()->Meridiens();
	entier np = pFenAff3D->Display()->Settings()->Paralleles();
	reel am = 2*PI/nm;
	reel ap = PI/np;
	reel ap2 = PI/(np+1);
	
	point	p0,p1,p2,p3;
	entier	m;
	reel	a,b;
	reel	cosa,sina;
	reel	cosa2,sina2;

	cosa = 1.0; sina = 0.0;
	for (m=0, a=0; m<nm; m+=1, a+=am) {
		cosa2 = cos(a+am); sina2 = sin(a+am);

		p1 = point(0.0,cosa,sina);
		p0 = point(0.0,cosa2,sina2);
		b = PI;

		p2 = point(b/PI,cosa,sina);
		p3 = point(b/PI,cosa2,sina2);

		if ( pFenAff3D->Display()->Settings()->PolygoneRemplit() )
		{
			vecteur	n0 = vecteur(reel(0.0),p0.y(),p0.z());
			vecteur	n1 = vecteur(reel(0.0),p1.y(),p1.z());
			vecteur	n2 = vecteur(reel(0.0),p2.y(),p2.z());
			vecteur	n3 = vecteur(reel(0.0),p3.y(),p3.z());

			Affiche_Tetragone(p3,p2,p1,p0, n3,n2,n1,n0, t, a1);
		} 
		else 
			Affiche_Tetragone(p3,p2,p1,p0, t, a1);

		sina = sina2;
		cosa = cosa2;
	}
}

void Segment::Afficher(const Transformation& v, const Attributs& a0) const
{
	Attributs	a1 = a0 * ((Objet *)this)->attributs();

	Affiche_Ligne(p1(),p2(), v * a1.transformation(), a1);
}

void Polygone::Afficher(const Transformation& v, const Attributs& a0) const
{
	entier	nb = sommets();
	entier i;
	if ( nb == 0) return;

	Attributs	a1 = a0 * ((Objet *)this)->attributs();

	if (nb>n) 
	{
		n = nb;
		delete vx;
		delete vy;
		delete vz;
		vx = new double[n];
		vy = new double[n];
		vz = new double[n];
		delete nx;
		delete ny;
		delete nz;
		nx = new double[n];
		ny = new double[n];
		nz = new double[n];
	}

	Transformation t = v * a1.transformation();

	if ( pFenAff3D->Display()->Settings()->OpenGL() ) 
	{
		point	p2;
		for (i=1; i<=nb; i+=1) 
		{
			p2 = t.transforme(sommet(i));
			vx[i-1] = p2.x();
			vy[i-1] = p2.y();
			vz[i-1] = p2.z();
		}

		vecteur v1(vx[1]-vx[0],vy[1]-vy[0],vz[1]-vz[0]);
		vecteur v2(vx[2]-vx[1],vy[2]-vy[1],vz[2]-vz[1]);
		vecteur normal = v1^v2;

		for (i = 0; i < nb; i++)
		{
			nx[i] = normal.x();
			ny[i] = normal.y();
			nz[i] = normal.z();
		}

		pFenAff3D->Display()->Polygone(nb, vx,vy,vz, nx,ny,nz, a1);
	} 
	else 
	{
		reel	x,y;
		for (entier i=1; i<=nb; i+=1) 
		{
			Projection(pFenAff3D->Scene()->GetCamera(), t, sommet(i), &x,&y);
			vx[i-1] = x;
			vy[i-1] = y;
		}
		pFenAff3D->Display()->Polygone(nb, vx,vy, a1);
	}
}

vecteur	gradient_triangle(const point &p1, const point& p2, const point& p3)
// retourne le gradient au triangle p1 p2 p3
{
	return ((p2-p1)^(p3-p1)).unitaire();
}

void	troisieme_pts(PointVol p1, PointVol p2, const Triangle& tri, Objet* o, PointVol *p3);

void	PointVol_Adjacent(PointVol p1, PointVol p2, Triangle& tri, Volume& o, PointVol *p3)
// retourne le point du triangle qui n'est pas p1 ou p2
{

	PointVol	pt1,pt2,pt3;
	Pts_Triangle (tri, &pt1,&pt2,&pt3);
	if (pt1 == p1) {
		if (pt2 == p2) {
			*p3 = pt3;
		} else { // pt3==p2
			*p3 = pt2;
		}
	} else {
		if (pt1 == p2) {
			if (pt2 == p1) {
				*p3 = pt3;
			} else { // pt3==p1
				*p3 = pt2;
			}
		} else {
			*p3 = pt1;
		}
	}
}

vecteur	gradient_sommet(PointVol pt1, PointVol pt2, PointVol pt3, const Triangle& tri, Volume &o)
// retourne une estimation du gradient au volume au point pt1
{
	int	c;
	vecteur n = gradient_triangle(*pt1,*pt2,*pt3);
	PointVol	p3, p2 = pt3;

	Triangle t2=tri, t3;

	c = 1;
	do {
		o.Triangle_Adjacent(pt1,p2,t2, &t3);
		t2 = t3;
		//PointVol_Adjacent(pt1,p2,t2,o, &p3);
		troisieme_pts(pt1,p2,t2,&o, &p3);
		n = n + gradient_triangle(*pt1,*p2,*p3);
		c += 1;

		p2 = p3;
	} while (!(*p2 == *pt2));

	return n * (1.0/c);
}

void Affiche_Tri(const Triangle& tri, Volume& o, const Transformation& v, const Attributs& a, entier niveau)
{
	if (niveau <= 0) 
	{
		PointVol	pt1,pt2,pt3;
		Pts_Triangle (tri, &pt1,&pt2,&pt3);
		if ( pFenAff3D->Display()->Settings()->PolygoneRemplit() && !a.highlight() )
		{
			vecteur	n1 = gradient_sommet(pt1,pt2,pt3,tri,o);
			vecteur	n2 = gradient_sommet(pt2,pt3,pt1,tri,o);
			vecteur	n3 = gradient_sommet(pt3,pt1,pt2,tri,o);
			
			Affiche_Tetragone(*pt1,*pt1,*pt2,*pt3, n1,n1,n2,n3, v, a);
		} 
		else 
			Affiche_Tetragone(*pt1,*pt1,*pt2,*pt3, v, a);
	} 
	else 
	{
		Triangle StriA,StriB,StriC,StriD;

		o.Subdivise_Tri(tri, &StriA,&StriB,&StriC,&StriD);
		Affiche_Tri (StriA,o,v,a,niveau-1);
		Affiche_Tri (StriB,o,v,a,niveau-1);
		Affiche_Tri (StriC,o,v,a,niveau-1);
		Affiche_Tri (StriD,o,v,a,niveau-1);
	}
}

void Volume::Afficher(const Transformation& v, const Attributs& a0) const
{
	Attributs	a1 = a0*attributs();

	Triangle tri;
 
	Transformation t = v * a1.transformation();

	((Volume*)this)->Reduit_Hauteur(0); // evite le warning du const
	for (entier i=1; i<=Nb_Triangle(); i+=1) 
	{
		tri = Ieme_Triangle(i);
//Modification apportee
//		Affiche_Tri(tri,*this,t,a1,volumeoriginal||a1.highlight()?0:this->Subdiv,f);
//		Affiche_Tri(tri,*this,t,a1,volumeoriginal||a1.highlight()?0:this->Subdiv,f);
	}
	((Volume*)this)->Reduit_Hauteur(0);
}


void Objet::Afficher(const Transformation& v, const Attributs& a0) const
{
}

void Vide::Afficher(const Transformation& v, const Attributs& a0) const
{
}

void Particule::Afficher(const Transformation& v, const Attributs& a0) const
{
	reel	x,y;

	Projection(pFenAff3D->Scene()->GetCamera(), v * a0.transformation() * ((Objet *)this)->attributs().transformation(), *pt(), &x,&y);
	pFenAff3D->Display()->Ligne((double)(x-0.01),(double)y, (double)(x+0.01),(double)y, a0 * ((Objet *)this)->attributs() * pFenAff3D->Display()->Settings()->CouleurContourPolygone());
	pFenAff3D->Display()->Ligne((double)x,(double)(y-0.01), (double)x,(double)(y+0.01), a0 * ((Objet *)this)->attributs() * pFenAff3D->Display()->Settings()->CouleurContourPolygone());
}


void Affiche_Fractal (const Fractal& o, const point& p1, const point& p2, const point& p3, const Transformation& v, const Attributs& a, entier n, const reel& h1, const reel& h2)
{



	if (n>0) 
	{
		point	p1p2 = o.milieu(p1,p2,h1,h2);
		point	p2p3 = o.milieu(p2,p3,h1,h2);
		point	p3p1 = o.milieu(p3,p1,h1,h2);

		Affiche_Fractal (o, p1,p1p2,p3p1, v, a, n-1, h1/2,h2/2);
		Affiche_Fractal (o, p1p2,p2,p2p3, v, a, n-1, h1/2,h2/2);
		Affiche_Fractal (o, p3p1,p2p3,p3, v, a, n-1, h1/2, h2/2);
		Affiche_Fractal (o, p1p2,p2p3,p3p1, v, a, n-1, h1/2, h2/2);
	}
	else 
	   {
		vecteur n=gradient_triangle(p1,p2,p3);
		Affiche_Trigone(p1,p2,p3,n,n,n, v, a);
	   }
}

void Fractal::Afficher(const Transformation& v, const Attributs& a0) const
//  Méthode à compléter pour le TP2
// Voir le fichier fractal.h

{
	int nbiter = pFenAff3D->Display()->Settings()->Nbiter();
//  nbiter = niveau de subdivision du fractal à afficher

	Attributs	a1 = a0*attributs();
	Transformation	t = v * a1.transformation();

	Affiche_Fractal (*this, p1(),p2(),p3(), t, a1, nbiter, hinf(), hsup());
}
