// Arup Guha
// 5/1/2016
// Solution to 2016 Spring COP 4516 Final Team Contest Problem: Taxable Area
// Edited on 7/18/2018 to be solution to 2018 SI@UCF Problem: Farmer John's Forest

import java.util.*;

public class forest {

	public static void main(String[] args) throws Exception {

		Scanner stdin = new Scanner(System.in);

		// Get the tree radius and the points.
		int n = stdin.nextInt();
		int r = stdin.nextInt();
		pt[] pts = new pt[n];
		for (int i=0; i<n; i++) {
			int x = stdin.nextInt();
			int y = stdin.nextInt();
			pts[i] = new pt(x, y);
		}

		// Set the reference point.
		int refIndex = getIndexMin(pts, n);
		pt.refX = pts[refIndex].x;
		pt.refY = pts[refIndex].y;

		// Get the convex hull.
		pt[] hull = grahamScan(pts, n);

		// Length of convex hull of points.
		double hullLength = perimeter(hull);
		
		// This is our actual perimeter - add in the full circle around all trees.
		double peri = hullLength + 2*Math.PI*r;
		
		// Area of the convex hull of points.
		double hullArea = doubleArea(hull)/2.0;
		
		// Three parts: convex hull, the circle, and the rectangles formed by
		// the straight lines of the hull and the clearance to the fence.
		double area = hullArea + Math.PI*r*r + hullLength*r;
		
		System.out.printf("%.2f %.2f\n", peri, area);
	}

	// Uses cross product magnitude sums to get area of poly.
	public static int doubleArea(pt[] poly) {
		int res = 0;
		for (int i=0; i<poly.length; i++)
			res = res + poly[i].x*poly[(i+1)%poly.length].y - poly[i].y*poly[(i+1)%poly.length].x;
		return Math.abs(res);
	}
	
	// Returns the perimeter of the polygon specified by poly.
	public static double perimeter(pt[] poly) {
		double res = 0;
		for (int i=0; i<poly.length; i++)
			res += poly[i].dist(poly[(i+1)%poly.length]);
		return res;
	}	

	// Returns the point in pts with minimum y breaking tie by minimum x.
	public static int getIndexMin(pt[] pts, int n) {
		int res = 0;
		for (int i=1; i<n; i++)
			if (pts[i].y < pts[res].y || (pts[i].y == pts[res].y && pts[i].x < pts[res].x))
				res = i;
		return res;
	}

	// Returns the convex hull of the points in pts.
	public static pt[] grahamScan(pt[] pts, int n) {

		// Sort the points by angle with reference point.
		Arrays.sort(pts);

		// Push first two points on.
		Stack<pt> myStack = new Stack<pt>();
		myStack.push(pts[0]);
		myStack.push(pts[1]);

		// Go through the rest of the points.
		for (int i=2; i<n; i++) {

			// Get last three pts.
			pt cur = pts[i];
			pt mid = myStack.pop();
			pt prev = myStack.pop();

			// Pop off the left turns.
			while (myStack.size() > 0 && !prev.isRightTurn(mid, cur)) {
				mid = prev;
				prev = myStack.pop();
			}

			// Push back the last right turn.
			myStack.push(prev);
			myStack.push(mid);
			myStack.push(cur);
		}

		// Pop everything off and store it.
		int size = myStack.size();
		pt[] res = new pt[size];
		for (int i=size-1; i>=0; i--)
			res[i] = myStack.pop();

		// Return.
		return res;
	}
}

class pt implements Comparable<pt> {

	// Stores reference pt
	public static int refX;
	public static int refY;

	public int x;
	public int y;

	public pt(int myx, int myy) {
		x = myx;
		y = myy;
	}

	// Returns the vector from this to other.
	public pt getVect(pt other) {
		return new pt(other.x-x, other.y-y);
	}

	// Returns the distance between this and other.
	public double dist(pt other) {
		return Math.sqrt((other.x-x)*(other.x-x) + (other.y-y)*(other.y-y));
	}

	// Returns the magnitude ot this cross product other.
	public int crossProductMag(pt other) {
		return this.x*other.y - other.x*this.y;
	}

	// returns true iff this to mid to next is a right turn (180 degree is considered right turn).
	public boolean isRightTurn(pt mid, pt next) {
		pt v1 = getVect(mid);
		pt v2 = mid.getVect(next);
		return v1.crossProductMag(v2) > 0; /*** Change to > 0 to skip collinear points. ***/
	}

	// Returns true iff this pt is the origin.
	public boolean isZero() {
		return x == 0 && y == 0;
	}

	public int compareTo(pt other) {

		pt myRef = new pt(refX, refY);
		pt v1 = myRef.getVect(this);
		pt v2 = myRef.getVect(other);

		// To avoid 0 issues.
		if (v1.isZero()) return -1;
		if (v2.isZero()) return 1;

		// Angles are different, we are going counter-clockwise here.
		if (v1.crossProductMag(v2) != 0)
			return -v1.crossProductMag(v2);

		// This should work, smaller vectors come first.
		if (myRef.dist(v1) < myRef.dist(v2)) return -1;
		return 1;
	}
}
