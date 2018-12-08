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
	}
	bool isBelow(Point p) {
		if (a.x < p.x && p.x < b.x) {
			ll c1 = Cross(b-a,p-a);
			return c1 < 0;
		}
		return false;
	}

    bool isAbove(Point p) {
		if (a.x < p.x && p.x < b.x) {
			ll c1 = Cross(b-a,p-a);
			return c1 > 0;
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

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("triangles.in","r",stdin); freopen("triangles.out","w",stdout);
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


    int cnt = 0;
    for (int i = 0; i < N; i++) {
    	for (int j = i + 1; j < N; j++) {
    		for (int k = j + 1; k < N; k++) {
                Line a = Line(pts[i],pts[j]);
                Line b = Line(pts[j],pts[k]);
                Line c = Line(pts[i],pts[k]);
                int ij = lines[i][j], jk = lines[j][k], ik = lines[i][k]; 
                int v = 5;
                if (a.isBelow(pts[k])) {
                    v = ij-jk-ik-1;
                }
                else if (b.isBelow(pts[i])) {
                    v = jk-ij-ik-1; 
                }
                else if (c.isBelow(pts[j])) {
                    v = ik-ij-jk-1;
                }
                else if (a.isAbove(pts[k])) {
                    v = jk+ik-ij;
                }
                else if (b.isAbove(pts[i])) {
                    v = ij+ik-jk;
                }
                else if (c.isAbove(pts[j])) {
                    v = ij+jk-ik;
                }
                else {
                    assert(false);
                }
                //printf("%d %d %d: %d\n",ij,jk,ik,v);
                ans[v]++;
            }
    	}
    }

    for (int i = 0; i <= N - 3; i++) {
    	cout << ans[i] << '\n';
    }

    return 0;
}
