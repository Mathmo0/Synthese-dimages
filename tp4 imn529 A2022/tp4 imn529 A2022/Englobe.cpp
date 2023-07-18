//*******************************************************************

//*																	*

//* Programme: englobe.h											*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation des volume englobant.							*

//*																	*

//*******************************************************************


#include "englobe.h"
#include "geo.h"
#include "utilreel.h"
#include "utilalg.h"

#include "definition.h"

entier	NbEnglobant = 0;

//*******************************************************************

//	Englobant

//*******************************************************************



Englobant::Englobant(){
	NbEnglobant += 1;
}

Englobant::~Englobant()
{
	NbEnglobant -= 1;
}

void	Englobant::transformation(const Transformation &t2)
{
	t = t2 * t;
}

const	Transformation& Englobant::transformation() const
{
	return t;
}

point	Englobant::transforme(const point &p) const
{
	return t.transforme(p);
}

point	Englobant::inverse(const point &p) const
{
	return t.inverse(p);
}

booleen Englobant::infini() const
{
	return FAUX;
}

booleen Englobant::vide() const
{
	return FAUX;
}

//*******************************************************************

//	VolVide
//*******************************************************************



Englobant	*VolVide::copie () const
{
	return new VolVide;
}

booleen	VolVide::vide () const
{
	return VRAI;
}

booleen VolVide::inter(const point& p, const vecteur& v) const
{
	return FAUX;
}

booleen VolVide::inter(const point& p, const vecteur& v, reel *k) const
{
	return FAUX;
}


//*******************************************************************

//	Infini

//*******************************************************************



Englobant	*Infini::copie () const
{
	return new Infini;
}

booleen	Infini::infini () const
{
	return VRAI;
}

booleen Infini::inter(const point& p, const vecteur& v) const
{
	return VRAI;
}

booleen Infini::inter(const point& p, const vecteur& v, reel *k) const
{
	return VRAI;
}

//*******************************************************************

//	CubeInfini

//*******************************************************************



CubeInfini::CubeInfini() : Cube()
{
}

CubeInfini::CubeInfini(const Transformation& x) : Cube(x)
{
}

Englobant	*CubeInfini::copie () const
{
	CubeInfini *c = new CubeInfini();
	*c = *this;
	return c;
}

booleen CubeInfini::inter(const point& p, const vecteur& v) const
{
	return VRAI;
}

booleen CubeInfini::inter(const point& p, const vecteur& v, reel *k) const
{
	return VRAI;
}

//*******************************************************************

//	Carre

//*******************************************************************



Carre::Carre()
{
	t = N;
}

Carre::Carre(const Transformation& x)
{
	t = x;
}

Englobant	*Carre::copie () const
{
	Carre *c = new Carre();
	*c = *this;
	return c;
}


static	const	plan	XY(0.0,0.0,1.0,0.0);



booleen	Carre::inter (const point& p, const vecteur& v, reel *k) const

{

	if (*k == INFINI) return this->inter(p,v);



	point	p2 = t.inverse(p);

	vecteur	v2 = t.inverse(v);

	point	pi;

	reel	k2;



	return XY.inter(p2,v2, &pi, &k2) && k2 < *k && pge(pi.x(), 0.0) && ppe(pi.x(), 1.0) && pge(pi.y(), 0.0) && ppe(pi.y(), 1.0);

}



booleen	Carre::inter (const point& p, const vecteur& v) const

{

	point	p2 = t.inverse(p);

	vecteur	v2 = t.inverse(v);

	point	pi;

	reel	k;



	return XY.inter(p2,v2, &pi, &k) && pge(pi.x(), 0.0) && ppe(pi.x(), 1.0) && pge(pi.y(), 0.0) && ppe(pi.y(), 1.0);

}


//*******************************************************************

//	Cube

//*******************************************************************



Cube::Cube()
{
	t = N;
}

Cube::Cube(const Transformation& x)
{
	t = x;
}

Englobant	*Cube::copie () const
{
	Cube *c = new Cube();
	*c = *this;
	return c;
}

booleen	Cube::inter (const point& p2, const vecteur& v, reel *k) const
{
	if (*k == INFINI) return (this->inter(p2,v));

	reel	k2;
	reel	x1,y1,z1;
	booleen inter;

	point	p = t.inverse(p2);
	vecteur r = t.inverse(v);

	inter = FAUX;
 
	r = *k * r;

	point	q = p + r;

	if (ppe(p.x(),1.0) && ppe(q.x(),1.0) && pge(p.x(),0.0) && pge(q.x(),0.0) &&
		ppe(p.y(),1.0) && ppe(q.y(),1.0) && pge(p.y(),0.0) && pge(q.y(),0.0) &&
		ppe(p.z(),1.0) && ppe(q.z(),1.0) && pge(p.z(),0.0) && pge(q.z(),0.0)) return VRAI;

	if (p.x() < 1 && q.x() > 1) {
		k2 = (1-q.x())/r.x();
		y1 = q.y() + k2*r.y();
		z1 = q.z() + k2*r.z();
		inter = (0 <= y1) && (y1 <= 1) &&
			(0 <= z1) && (z1 <= 1);
		if (!inter) q = point(1.0,y1,z1); // q = q + k2*r;
	}

	if (inter) return VRAI;

	if (p.y() < 1 && q.y() > 1) {
		k2 = (1-q.y())/r.y();
		x1 = q.x() + k2*r.x();
		z1 = q.z() + k2*r.z();
		inter = (0 <= x1) && (x1 <= 1) &&
			(0 <= z1) && (z1 <= 1);
		if (!inter) q = point(x1,1.0,z1); // q = q + k2*r;
	}

	if (inter) return VRAI;

	if (p.z() < 1 && q.z() > 1) {
		k2 = (1-q.z())/r.z();
		y1 = q.y() + k2*r.y();
		x1 = q.x() + k2*r.x();
		inter = (0 <= y1) && (y1 <= 1) &&
			(0 <= x1) && (x1 <= 1);
		if (!inter) q = point(x1,y1,1.0); // q = q + k2*r;
	}

	if (inter) return VRAI;

	if (p.x() > 0 && q.x() < 0) {
		k2 = -q.x()/r.x();
		y1 = q.y() + k2*r.y();
		z1 = q.z() + k2*r.z();
		inter = (0 <= y1) && (y1 <= 1) &&
			(0 <= z1) && (z1 <= 1);
		if (!inter) q = point(0.0,y1,z1); // q = q + k2*r;
	}

	if (inter) return VRAI;

	if (p.y() > 0 && q.y() < 0) {
		k2 = -q.y()/r.y();
		z1 = q.z() + k2*r.z();
		x1 = q.x() + k2*r.x();
		inter = (0 <= z1) && (z1 <= 1) &&
			(0 <= x1) && (x1 <= 1);
		if (!inter) q = point(x1,0.0,z1); // q = q + k2*r;
	}

	if (inter) return VRAI;

	if (p.z() > 0 && q.z() < 0) {
		k2 = -q.z()/r.z();
		y1 = q.y() + k2*r.y();
		x1 = q.x() + k2*r.x();
		inter = (0 <= y1) && (y1 <= 1) &&
			(0 <= x1) && (x1 <= 1);
		if (!inter) q = point(x1,y1,0.0); // q = q + k2*r;
	}

	if (inter) return VRAI;

	if (p.x() > 1 && q.x() < 1) {
		k2 = (1-p.x())/r.x();
		y1 = p.y() + k2*r.y();
		z1 = p.z() + k2*r.z();
		inter = (0 <= y1) && (y1 <= 1) &&
			(0 <= z1) && (z1 <= 1);
		if (!inter) p = point(1.0,y1,z1); // p = p + k2*r;
	}

	if (inter) return VRAI;

	if (p.y() > 1 && q.y() < 1) {
		k2 = (1-p.y())/r.y();
		x1 = p.x() + k2*r.x();
		z1 = p.z() + k2*r.z();
		inter = (0 <= x1) && (x1 <= 1) &&
			(0 <= z1) && (z1 <= 1);
		if (!inter) p = point(x1,1.0,z1); // p = p + k2*r;
	}

	if (inter) return VRAI;

	if (p.z() > 1 && q.z() < 1) {
		k2 = (1-p.z())/r.z();
		y1 = p.y() + k2*r.y();
		x1 = p.x() + k2*r.x();
		inter = (0 <= y1) && (y1 <= 1) &&
			(0 <= x1) && (x1 <= 1);
		if (!inter) p = point(x1,y1,1.0); // p = p + k2*r;
	}

	if (inter) return VRAI;

	if (p.x() < 0 && q.x() > 0) {
		k2 = -p.x()/r.x();
		y1 = p.y() + k2*r.y();
		z1 = p.z() + k2*r.z();
		inter = (0 <= y1) && (y1 <= 1) &&
			(0 <= z1) && (z1 <= 1);
		if (!inter) p = point(0.0,y1,z1); // p = p + k2*r;
	}

	if (inter) return VRAI;

	if (p.y() < 0 && q.y() > 0) {
		k2 = -p.y()/r.y();
		z1 = p.z() + k2*r.z();
		x1 = p.x() + k2*r.x();
		inter = (0 <= z1) && (z1 <= 1) &&
			(0 <= x1) && (x1 <= 1);
		if (!inter) p = point(x1,0.0,z1); // p = p + k2*r;
	}

	if (inter) return VRAI;

	if (p.z() < 0 && q.z() > 0) {
		k2 = -p.z()/r.z();
		y1 = p.y() + k2*r.y();
		x1 = p.x() + k2*r.x();
		inter = (0 <= y1) && (y1 <= 1) &&
			(0 <= x1) && (x1 <= 1);
		if (!inter) p = point(x1,y1,0.0); // p = p + k2*r;
	}

	return inter;
}

booleen	Cube::inter (const point& p, const vecteur& r) const
{
	reel	k;
	reel	x1,y1,z1;
	booleen	inter;

	point	p2 = t.inverse(p);
	vecteur	r2 = t.inverse(r);

	reel	px = p2.x();

	reel	py = p2.y();

	reel	pz = p2.z();

	reel	rx = r2.x();

	reel	ry = r2.y();

	reel	rz = r2.z();

//	reel&	px = p2.x();
//	reel&	py = p2.y();
//	reel&	pz = p2.z();
//	reel&	rx = r2.x();
//	reel&	ry = r2.y();
//	reel&	rz = r2.z();

	inter = FAUX;

	if (rx < 0) 

	{
		k = -px;
		if (k < 0) 

		{
			k /= rx;
			y1 = py + k*ry;
			z1 = pz + k*rz;
			inter = (0 <= y1) && (y1 <= 1) &&
				(0 <= z1) && (z1 <= 1);
		} else return FAUX;
	} 

	else 

	{
		k = px - 1;
		if (k < 0) 

		{
			k /= -rx;
			y1 = py + k*ry;
			z1 = pz + k*rz;
			inter = (0 <= y1) && (y1 <= 1) &&
				(0 <= z1) && (z1 <= 1);
		} else return FAUX;
	}

	if (inter) return VRAI;

	if (ry < 0) 

	{
		k = -py;
		if (k < 0) 

		{
			k /= ry;
			x1 = px + k*rx;
			z1 = pz + k*rz;
			inter = (0 <= x1) && (x1 <= 1) && (0 <= z1) && (z1 <= 1);
		} 

		else 

			return FAUX;
	} 

	else 

	{
		k = py - 1;
		if (k < 0) 

		{
			k /= -ry;
			x1 = px + k*rx;
			z1 = pz + k*rz;
			inter = (0 <= x1) && (x1 <= 1) && (0 <= z1) && (z1 <= 1);
		} 

		else 

			return FAUX;
	}

	if (inter) return VRAI;

	if (rz < 0) 

	{
		k = -pz;
		if (k < 0) 

		{
			k /= rz;
			x1 = px + k*rx;
			y1 = py + k*ry;
			inter = (0 <= x1) && (x1 <= 1) && (0 <= y1) && (y1 <= 1);
		} 

		else 

			return FAUX;
	} 

	else 

	{
		k = pz - 1;
		if (k < 0) 

		{
			k /= -rz;
			x1 = px + k*rx;
			y1 = py + k*ry;
			inter = (0 <= x1) && (x1 <= 1) && (0 <= y1) && (y1 <= 1);
		} 

		else 

			return FAUX;
	}

	return inter;
}




//*******************************************************************

//	Englobe

//*******************************************************************



static  const	point	p1(0.0, 0.0, 0.0);

static  const	point	p2(0.0, 0.0, 1.0);

static  const	point	p3(0.0, 1.0, 0.0);

static  const	point	p4(0.0, 1.0, 1.0);

static  const	point	p5(1.0, 0.0, 0.0);

static  const	point	p6(1.0, 0.0, 1.0);

static  const	point	p7(1.0, 1.0, 0.0);

static  const	point	p8(1.0, 1.0, 1.0);

 

static  point	cube[8] = { p1,p2,p3,p4,p5,p6,p7,p8, };

 

static	const	reel	eps = 0.01;

 

void	Englobe(const Englobant& v1, const Englobant& v2, Englobant** v)

// v = v1 U v2

{

	if (v1.infini() || v2.infini()) {

		*v = new Infini();

		return;

	}

 

	if (v1.vide()) {

		*v = v2.copie();

		return;

	}

 

	if (v2.vide()) {

		*v = v1.copie();

		return;

	}

 

	reel	xmin=INFINI,ymin=INFINI,zmin=INFINI;

	reel	xmax=-INFINI,ymax=-INFINI,zmax=-INFINI;

	point	p;

 

	for (entier i=0; i<8; i+=1) {

		p = v1.transforme(cube[i]);

		if (p.x()<xmin) xmin = p.x();

		if (p.y()<ymin) ymin = p.y();

		if (p.z()<zmin) zmin = p.z();

		if (p.x()>xmax) xmax = p.x();

		if (p.y()>ymax) ymax = p.y();

		if (p.z()>zmax) zmax = p.z();

		p = v2.transforme(cube[i]);

		if (p.x()<xmin) xmin = p.x();

		if (p.y()<ymin) ymin = p.y();

		if (p.z()<zmin) zmin = p.z();

		if (p.x()>xmax) xmax = p.x();

		if (p.y()>ymax) ymax = p.y();

		if (p.z()>zmax) zmax = p.z();

	}

 

	if (!pg(xmax,xmin)) { xmin -= eps; xmax += eps; }

	if (!pg(ymax,ymin)) { ymin -= eps; ymax += eps; }

	if (!pg(zmax,zmin)) { zmin -= eps; zmax += eps; }

 

	*v = new Cube(Deplacement(point(xmin,ymin,zmin) - O) *

			 Homothetie (O,X, xmax-xmin) *

			 Homothetie (O,Y, ymax-ymin) *

			 Homothetie (O,Z, zmax-zmin));

}

