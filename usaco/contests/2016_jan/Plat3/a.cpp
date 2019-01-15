#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point
{
	int x, y;
	Point operator-(const Point& b) {
		return {x-b.x,y-b.y};
	}


};

int Cross(Point a, Point b) {
	ll c = a.x*b.y-a.y*b.x;
	if (c < 0) return -1;
	else return 1;
}

int dist(const Point& a, const Point& b) {
		return (int)(sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)));
	}

const int maxn = 205;
int N;
Point pts[maxn];


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) cin >> pts[i].x >> pts[i].y;
    pts[N] = pts[0];
    //point, dist, point, dist...starting point
    //starting point is 0,
    vector<int> hs;
	hs.push_back(0);
	for (int i = 1; i <= N; i++) {
		hs.push_back(dist(pts[i],pts[i-1]));
		if (i < N) {
			hs.push_back(Cross(pts[i+1]-pts[i],pts[i]-pts[i-1]));
		}
	}

	//try clockwise
	for (int i = 0; i < N; i++) {
		int j = 2*i;
		
	}



    return 0;
}