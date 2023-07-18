
#include "segment.h"
#include "point.h"

booleen Select_Point(const point& pt, const point& p, const vecteur& v, reel* k);
booleen Select_Segment(const point& p1, const point& p2, const point& p, const vecteur& v, reel* k);

booleen Segment_Inter(const Segment& o, const Transformation& t, const point& p, const vecteur& v, reel* k);
booleen Point_Inter(const Point& o, const Transformation& t, const point& p, const vecteur& v, reel* k);

