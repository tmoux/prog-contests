#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
	int x, y;
	Point operator-(Point b) {
		return {x-b.x,y-b.y};
	}
};

ll Cross(Point a, Point b) {
	return 1LL*a.x*b.y-1LL*a.y*b.x;
}

struct Line {
	Point a, b;
	Line() {}
	Line(Point _a, Point _b) {
		a = _a;
		b = _b;
		if (a.x > b.x) swap(a,b);
        if (a.x == b.x && a.y > b.y) swap(a,b);
	}
	bool isBelow(Point p) {
		if (a.x < p.x && p.x < b.x) {
			ll c1 = Cross(b-a,p-a);
			return c1 < 0;
		}
		return false;
	}
    bool isBelowUnstrict(Point p) {
		if (a.x <= p.x && p.x <= b.x) {
			ll c1 = Cross(b-a,p-a);
			return c1 < 0;
		}
		return false;
	}
};

int N;
const int maxn = 305;
Point pts[maxn];
int lines[maxn][maxn];
int ans[maxn];
int below[maxn]; //# points directly below this

void add(int& tot, int i, int j, int k) {
    Line l = Line(pts[i],pts[j]);
    if (l.isBelowUnstrict(pts[k]) || Line(l.a,k)) {
        tot += lines[i][j];
        tot += below[i];
        tot += below[j];
    }
    else {
        tot -= lines[i][j];
        tot -= below[i];
        tot -= below[j];
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("triangles.in","r",stdin); freopen("triangles.out","w",stdout);
    cin >> N;
    for (int i = 0; i < N; i++) {
    	cin >> pts[i].x >> pts[i].y;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (pts[j].x == pts[i].x && pts[j].y < pts[i].y) {
                below[i]++;
            }
        }
    }

    for (int i = 0; i < N; i++) {
    	for (int j = 0; j < N; j++) {
    		Line l = Line(pts[i],pts[j]);
    		for (int k = 0; k < N; k++) {
    			if (l.isBelow(pts[k])) lines[i][j]++;
    			//printf("(%d %d), (%d %d): (%d, %d): %d\n",pts[i].x,pts[i].y,pts[j].x,pts[j].y,pts[k].x,pts[k].y,l.isBelow(pts[k]));
    		}
    	}
    }

    for (int i = 0; i < N; i++) {
    	for (int j = i + 1; j < N; j++) {
    		for (int k = j + 1; k < N; k++) {
                int tot = 0;
                add(tot,i,j,k);    
                add(tot,j,k,i);
                add(tot,i,k,j);
                ans[tot]++;
                printf("%d %d %d: %d\n",i,j,k,tot);
            }
    	}
    }

    for (int i = 0; i <= N - 3; i++) {
    	cout << ans[i] << '\n';
    }

    return 0;
}
