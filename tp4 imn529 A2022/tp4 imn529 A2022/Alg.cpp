//*******************************************************************

//*																	*

//* Programme: alg.cpp												*

//*																	*

//*******************************************************************

//*																	*

//* Description:													*

//*		Implantation des points, vecteurs, droites, plans, matrices	*

//*																	*

//*******************************************************************


#include "alg.h"

#include "utilreel.h"
#include "utilalg.h"
#include <cmath>

const	point	O(0.0, 0.0, 0.0);

const	vecteur	X(1.0, 0.0, 0.0);
const	vecteur Y(0.0, 1.0, 0.0);
const	vecteur	Z(0.0, 0.0, 1.0);

const matrice	I(	1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0 );

#ifdef INLINE

inline

#endif

const	reel&	point::x() const

{

	return px;

}



#ifdef INLINE

inline

#endif

const	reel&	point::y() const

{

	return py;

}



#ifdef INLINE

inline

#endif

const	reel&	point::z() const

{

	return pz;

}
/*
#ifdef INLINE

inline

#endif

const point& point::operator = ( const point& pt )
{
    px = pt.px;
    py = pt.py;
    pz = pt.pz;

    return *this;
}
*/


#ifdef INLINE

inline

#endif

const	reel&	vecteur::x() const

{

	return px;

}



#ifdef INLINE

inline

#endif

const	reel&	vecteur::y() const

{

	return py;

}



#ifdef INLINE

inline

#endif

const	reel&	vecteur::z() const

{

	return pz;

}
/*
#ifdef INLINE

inline

#endif

const vecteur& vecteur::operator = ( const point& vc )
{
    px = vc.px;
    py = vc.py;
    pz = vc.pz;

    return *this;
}

*/
#ifdef INLINE

inline

#endif

vecteur::vecteur()

{

}



#ifdef INLINE

inline

#endif

point::point()

{

}



#ifdef INLINE

inline

#endif

droite::droite()

{

}



#ifdef INLINE

inline

#endif

plan::plan()

{

}



/* OPERATIONS DE POINTS */



#ifdef INLINE

inline

#endif

point::point(const reel& x, const reel& y, const reel& z)

/* Retourne le point (x,y,z) */

{

	px = x;

	py = y;

	pz = z;

}



#ifdef INLINE

inline

#endif

void	point::coordonnees (reel *x, reel *y, reel *z) const

/* Retourne les coordonnees du point. */

{

	*x = px;

	*y = py;

	*z = pz;

}



/* OPERATIONS DE VECTEURS */



#ifdef INLINE

inline

#endif

vecteur::vecteur(const reel& x, const reel& y, const reel& z)

/* Retourne le point (x,y,z) */

{

	px = x;

	py = y;

	pz = z;

}



#ifdef INLINE

inline

#endif

vecteur::vecteur(const point& p, const point& q)

{

	px = q.x()-p.x(); py = q.y()-p.y(); pz = q.z()-p.z();

}



#ifdef INLINE

inline

#endif

void	vecteur::composantes (reel *x, reel *y, reel *z) const

/* Retourne les composantes du vecteur. */

{

	*x = px;

	*y = py;

	*z = pz;

}



#ifdef INLINE

inline

#endif

reel	vecteur::norme () const

{

	return(sqrt (px*px+py*py+pz*pz));

}



#ifdef INLINE

inline

#endif

reel	vecteur::norme2 () const

{

	return(px*px+py*py+pz*pz);

}



#ifdef INLINE

inline

#endif

vecteur	vecteur::unitaire () const

{

	reel	k = norme();

	return vecteur(px/k,py/k,pz/k);

}



#ifdef INLINE

inline

#endif

void	vecteur::normalise ()

{

	reel	k = norme();

	px /= k;

	py /= k;

	pz /= k;

}





/* OPERATIONS DE DROITES ET PLANS */



// droites



#ifdef INLINE

inline

#endif

droite::droite(const point& q, const vecteur& u)

{

	droite::p = q;

	droite::v = u;

}



#ifdef INLINE

inline

#endif

droite::droite(const point& q, const point& r)

{

	droite::p = q;

	droite::v = vecteur(q,r);

	//droite::v.normalise();

}



#ifdef INLINE

inline

#endif

const	point&	droite::mpoint() const

{

	return(p);

}



#ifdef INLINE

inline

#endif

const	vecteur&	droite::mvecteur() const

{

	return(v);

}



// plans



#ifdef INLINE

inline

#endif

plan::plan(const reel& a, const reel& b, const reel& c, const reel& d)

{

	plan::a = a;

	plan::b = b;

	plan::c = c;

	plan::d = d;

	plan::n = vecteur(a,b,c);



	reel	k = -d/(a*a+b*b+c*c);

	p = point(k*a,k*b,k*c);

}



#ifdef INLINE

inline

#endif

plan::plan(const point& q, const vecteur& v)

{

	plan::p = q;

	n = v;

	n.normalise();

	a = n.x();

	b = n.y();

	c = n.z();

	d = -(a*p.x()+b*p.y()+c*p.z());

}



#ifdef INLINE

inline

#endif

plan::plan(const point& q, const vecteur& u, const vecteur& v)

{

	*this = plan(q, u^v);

}



#ifdef INLINE

inline

#endif

plan::plan(const point& q, const point& r, const point& s)

{

	*this = plan(q, r-q, s-q);

}



#ifdef INLINE

inline

#endif

const	point&	plan::mpoint() const

{

	return(p);

}



#ifdef INLINE

inline

#endif

const	vecteur&	plan::normale() const

{

	return(n);

}



#ifdef INLINE

inline

#endif

plan	plan::unitaire() const

{

	plan	pl;



	reel	k = sqrt(a*a+b*b+c*c);



	pl.a = a/k;

	pl.b = b/k;

	pl.c = c/k;

	pl.d = d/k;

	pl.n = vecteur(pl.a,pl.b,pl.c);

	pl.p = p;



	return(pl);

}



#ifdef INLINE

inline

#endif

void	plan::normalise()

{

	reel	k = sqrt(a*a+b*b+c*c);



	a /= k;

	b /= k;

	c /= k;

	d /= k;

	n = vecteur(a,b,c);

}



#ifdef INLINE

inline

#endif

void	plan::abcd(reel *a, reel *b, reel *c, reel *d) const

{

	*a = plan::a;

	*b = plan::b;

	*c = plan::c;

	*d = plan::d;

}



#ifdef INLINE

inline

#endif

reel	plan::distance (const point& q) const

{

	return(a*q.x() + b*q.y() + c*q.z() + d);

}



#ifdef INLINE

inline

#endif

booleen	plan::inter (const droite& d, point* pt, reel *k) const

{

	vecteur	v = d.mvecteur();

	*k = a*v.x() + b*v.y() + c*v.z();

	if (neg(*k, 0.0)) {

		point	p = d.mpoint();

		*k = -(a*p.x()+b*p.y()+c*p.z()+plan::d) / *k;

		*pt = p + *k*v;

		return (VRAI);

	} return (FAUX);

}



#ifdef INLINE

inline

#endif

booleen	plan::inter (const point& pt, const vecteur& v, point* pi, reel *k) const

{

	*k = a*v.x() + b*v.y() + c*v.z();

	if (neg(*k,0.0)) {

		*k = -(a*pt.x()+b*pt.y()+c*pt.z()+plan::d) / *k;

		if (ppe(*k, 0.0)) return(FAUX);

		*pi = pt + *k*v;

		return (VRAI);

	} return (FAUX);

}





/* OPERATIONS DE MATRICES */



#ifdef INLINE

//inline

#endif

matrice::matrice(const reel& a11, const reel& a12, const reel& a13, const reel& a14, const reel& a21, const reel& a22, const reel& a23, const reel& a24, const reel& a31, const reel& a32, const reel& a33, const reel& a34)

{

	matrice::m[0][0] = a11;

	matrice::m[0][1] = a12;

	matrice::m[0][2] = a13;

	matrice::m[0][3] = a14;



	matrice::m[1][0] = a21;

	matrice::m[1][1] = a22;

	matrice::m[1][2] = a23;

	matrice::m[1][3] = a24;



	matrice::m[2][0] = a31;

	matrice::m[2][1] = a32;

	matrice::m[2][2] = a33;

	matrice::m[2][3] = a34;

}



#ifdef INLINE

#endif

matrice::matrice()

{

	//matrice(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}



#ifdef INLINE

inline

#endif

reel&	matrice::e(const entier& i, const entier& j)

{

	return m[i-1][j-1];

}



#ifdef INLINE

inline

#endif

void	matrice::transpose()

{

	entier	i,j;

	reel	t;



	for (i=0; i<=2; i+=1) {

		for (j=0; j<i; j+=1) {

			t = m[i][j];

			m[i][j] = m[j][i];

			m[j][i] = t;

		}

		m[i][3] = 0;

	}

}



#ifdef INLINE

inline

#endif

point	operator*(const matrice& m, const point& p)

{

return(

	point(m.m[0][0]*p.x() + m.m[0][1]*p.y() + m.m[0][2]*p.z() + m.m[0][3],

	 m.m[1][0]*p.x() + m.m[1][1]*p.y() + m.m[1][2]*p.z() + m.m[1][3],

	 m.m[2][0]*p.x() + m.m[2][1]*p.y() + m.m[2][2]*p.z() + m.m[2][3])

);

}



#ifdef INLINE

inline

#endif

vecteur	operator*(const matrice& m, const vecteur& v)

{

return(

	vecteur(m.m[0][0]*v.x() + m.m[0][1]*v.y() + m.m[0][2]*v.z(),

		m.m[1][0]*v.x() + m.m[1][1]*v.y() + m.m[1][2]*v.z(),

		m.m[2][0]*v.x() + m.m[2][1]*v.y() + m.m[2][2]*v.z())

);

}



#ifdef INLINE

inline

#endif

droite	operator*(const matrice& m, const droite& d)

{

	return(droite(m*d.mpoint(), m*d.mvecteur()));

}



#ifdef INLINE

inline

#endif

plan	operator*(const matrice& m, const plan& p)

{

// en entrée la matrice inverse



	reel	a,b,c,d;



	p.abcd(&a,&b,&c,&d);

	return	plan(m.m[0][0]*a + m.m[1][0]*b + m.m[2][0]*c,

		 m.m[0][1]*a + m.m[1][1]*b + m.m[2][1]*c,

		 m.m[0][2]*a + m.m[1][2]*b + m.m[2][2]*c,

		 m.m[0][3]*a + m.m[1][3]*b + m.m[2][3]*c + d).unitaire();



}



plan	mult(const matrice& m,const matrice& mi, const plan& p)

{

	reel	a,b,c,d;

	plan pltemp;

	point pttemp;

	pttemp=m*p.mpoint();



	p.abcd(&a,&b,&c,&d);

	pltemp=	plan(mi.m[0][0]*a + mi.m[1][0]*b + mi.m[2][0]*c,

		 mi.m[0][1]*a + mi.m[1][1]*b + mi.m[2][1]*c,

		 mi.m[0][2]*a + mi.m[1][2]*b + mi.m[2][2]*c,

		 mi.m[0][3]*a + mi.m[1][3]*b + mi.m[2][3]*c + d).unitaire();



	return plan(pttemp,pltemp.normale()); 



}



#ifdef INLINE

inline

#endif

matrice	operator*(const matrice& m1, const matrice& m2)

{

	matrice	m3;

	entier	i,j,k;

	reel	s;



	for (i=0; i<=2; i+=1) {

		for (j=0; j<=3; j+=1) {

			s = 0;

			for (k=0; k<=2; k+=1) {

				s += m1.m[i][k] * m2.m[k][j];

			}

			if (j==3) s += m1.m[i][j];

			m3.m[i][j] = s;

		}

	}

	return(m3);

}



typedef struct 

{

	reel    c[4];

} Colonne;

 

typedef struct 

{

	reel    m[4][4];

} Matrice;

 

//

// Nonzero: Retourne VRAI si il existe une ligne i dans la colonne j

// qui contient un element non nul. Le cas echeant,

// la fonction retourne ce i.

//

static	booleen	Nonzero (Matrice a, entier j, entier *i)

{

	reel x;

 

	*i = j;

	for (;;) {

		if (*i+1 == 4) {

			return FAUX;

		}

		x = a.m[*i][j];

		if (neg(x,0.0)) {

			return VRAI;

		}

		*i += 1;

	}

}

 

 

//

// Exchange: Echange les lignes i et j dans la matrice a.

//

static	void	Exchange (entier i, entier j, Matrice *A, Colonne *K)

{

	entier k;

	reel t;

 

	for (k=0; k<4; k+=1) {

		t = A->m[i][k];

		A->m[i][k] = A->m[j][k];

		A->m[j][k] = t;

	}

	t = K->c[i];

	K->c[i] = K->c[j];

	K->c[j] = t;

}



//

// Resolve: Retourne le vecteur X provenant de la resolution du

//	systeme AX=K.

//

static	booleen	Resolve (Matrice A, Colonne K, Colonne *X)

{

	entier i,j,k;

	int i2;

	reel p;

 

	for (j=0; j<3; j+=1) {

		if (!Nonzero (A,j, &i2)) {

			return FAUX;

		}

		if (i2 != j) Exchange (i2,j, &A,&K);



		for (i=j+1; i<4; i+=1) {

			p = A.m[i][j]/A.m[j][j];

			for (k=j; k<4; k+=1) {

				A.m[i][k] -= p * A.m[j][k];

			}

			K.c[i] -= p * K.c[j];

		}

	}

 

	for (i=3; i>=0; i-=1) {

		p = 0;

		for (j=i+1; j<4; j+=1) {

			p += A.m[i][j] * X->c[j];

		}

		X->c[i] = (K.c[i] - p)/A.m[i][i];

	}

 

	return VRAI;

}

 

booleen	matrice::inverse(matrice *mi)

{

	Colonne K,X;

	Matrice m;

	entier i,j;

 

	for (i=0; i<3; i+=1) for (j=0; j<4; j+=1) m.m[i][j] = this->e(i+1,j+1);

	for (j=0; j<4; j+=1) m.m[3][j] = (j==3)?1.0:0.0;



	for (j=0; j<4; j+=1) {

		for (i=0; i<4; i+=1)

			K.c[i] = (i==j)?1.0:0.0;



		if (!Resolve (m,K, &X)) return FAUX;



		for (i=0; i<3; i+=1)

			mi->e(i+1,j+1) = X.c[i];

	}

	return VRAI;

}

 

booleen	matrice::identite() const

{

	entier i,j;



	for (j=1; j<=4; j+=1) 

	{

		for (i=1; i<=3; i+=1) 

		{

			if ( neg(m[i-1][j-1], (i==j)?reel(1):reel(0)) ) 

				return FAUX;

		}

	}



	return VRAI;

}

 

const matrice& matrice::operator = ( const matrice& mat )
{
    for ( int i = 0; i < 3; i++ )
        for ( int j = 0; j < 4; j++ )
            m[i][j] = mat.m[i][j];

    return *this;
}
