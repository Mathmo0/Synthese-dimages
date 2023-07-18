
#include "eps.h"
#include "geo.h"
#include "canon.h"
#include "utilreel.h"
#include "utilalg.h"
#include "alg.h"
#include "transfo.h"
#include "definition.h"
#include "segment.h"
#include "point.h"
#include "global.h"

extern	"C" double	sqrt(double);

booleen	Select_Point(const point& pt, const point& p, const vecteur& v, reel* k)
{
	Transformation	t = Homo_X(1.0/epselect) * Homo_Y(1.0/epselect) * Homo_Z(1.0/epselect) * Deplacement(O-pt);

	point	p2 = t.transforme(p);
	vecteur	v2 = t.transforme(v);

	reel    a = v2.x()*v2.x() + v2.y()*v2.y() + v2.z()*v2.z();
	reel    b = 2.0*(v2.x()*p2.x() + v2.y()*p2.y() + v2.z()*p2.z());
	reel    c = p2.x()*p2.x() + p2.y()*p2.y() + p2.z()*p2.z() - 1.0;

	reel    disc = b*b - 4.0*a*c;

	if (ppe(disc,0.0)) return FAUX;

	reel    sq = sqrt(disc);
	reel    k2 = -b - sq;
	if (ppe(k2,0.0)) {
		k2 = -b + sq;
		if (ppe(k2,0.0)) return FAUX;
	}
	k2 /= 2*a;
	if (pp(k2,*k)) { *k = k2; return VRAI; }
	else return FAUX;
}

booleen	Select_Segment(const point& q1, const point& q2, const point& p, const vecteur& v, reel* k)
{
	Transformation	t = Homo_X(1.0/(q2-q1).norme()) * Homo_Y(1.0/epselect) * Homo_Z(1.0/epselect) * Alignement(q2-q1,X) * Deplacement(O-q1);

	point	p2 = t.transforme(p);
	vecteur	v2 = t.transforme(v);

	reel    a = v2.y()*v2.y() + v2.z()*v2.z();
	reel    b = 2.0*(v2.y()*p2.y() + v2.z()*p2.z());
	reel    c = p2.y()*p2.y() + p2.z()*p2.z() - 1.0;

	reel    disc = b*b - 4.0*a*c;

	if (ppe(disc,0.0)) return FAUX;

	reel    sq = sqrt(disc);
	reel    k2 = -b - sq;
	if (ppe(k2,0.0)) {
		k2 = -b + sq;
		if (ppe(k2,0.0)) return FAUX;

		k2 /= 2*a;
		if (pge(k2,*k)) return FAUX;

		reel    x = p2.x() + k2*v2.x();
		if (ppe(x, 1.0) && pge(x, 0.0)) { *k = k2; return VRAI; }
		else return FAUX;
	}
	k2 /= 2*a;
	if (pp(k2,*k)) {
		reel    x = p2.x() + k2*v2.x();
		if (ppe(x, 1.0) && pge(x, 0.0)) { *k = k2; return VRAI; }
	}
	k2 = (-b + sq)/2.0/a;
	if (pge(k2,*k)) return FAUX;
 
	reel    x = p2.x() + k2*v2.x();
	if (ppe(x, 1.0) && pge(x, 0.0)) { *k = k2; return VRAI; }
	else return FAUX;
}

booleen	Segment_Inter(const Segment& o, const Transformation& t, const point& p, const vecteur& v, reel* k)
{
	return Select_Segment(t.transforme(o.p1()),t.transforme(o.p2()), p,v,k);
}

booleen	Point_Inter(const Point& o, const Transformation& t, const point& p, const vecteur& v, reel* k)
{
	return Select_Point(t.transforme(o.pt()), p,v,k);
}

