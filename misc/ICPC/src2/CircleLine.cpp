#include "Point.h"
#include "lineDistance.h"
#include "LineProjectionReflection.h"

template<class P>
vector<P> circleLine(P c, double r, P a, P b) {
	double h2 = r*r - a.cross(b,c)*a.cross(b,c)/(b-a).dist2();
	if (h2 < 0) return {};
	P p = lineProj(a, b, c), h = (b-a).unit() * sqrt(h2);
	if (h2 == 0) return {p};
	return {p - h, p + h};
}
