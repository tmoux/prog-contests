#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define all(x) begin(x),end(x)
const int maxn = 1e5+5;
int N;

template <typename T>
struct Point
{
	T x, y;
	bool operator<(const Point& A) const 
	{
		return x < A.x || (x == A.x && y < A.y);
	}
	Point operator-(const Point& A) {
		return {x-A.x,y-A.y};
	}
};

typedef Point<ll> iPoint;

template <typename T>
T Cross(Point<T> A, Point<T> B) {
	return A.x * B.y - A.y * B.x;
}

vector<iPoint> points;
vector<iPoint> hull;

void buildHull() {
	sort(all(points));
	int n = points.size();
	hull.resize(points.size()+2);
	int m = 0;
	for (int i = 0; i < n; i++) {
		while (m > 1 && Cross(hull[m-1]-hull[m-2],points[i]-hull[m-2]) <= 0) {
			m--;
		}
		hull[m++] = points[i];
	}
	int k = m;
	for (int i = n - 2; i >= 0; i--) {
		while (m > k && Cross(hull[m-1]-hull[m-2],points[i]-hull[m-2]) <= 0) {
			m--;
		}
		hull[m++] = points[i];
 	}
 	hull.resize(m);
}

ll f[maxn];
ll ans[maxn];

pair<ll,ll> interpolate(const iPoint& a, const iPoint& b, int j) {
    ll num = 1LL*(b.y-a.y)*(j-a.x) + 1LL*(a.y*(b.x-a.x));
    ll den = b.x-a.x;
    return {num,den};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("balance.in","r",stdin); freopen("balance.out","w",stdout);
    cin >> N;
    points.push_back({0,0});
    points.push_back({N+1,0});
    for (int i = 1; i <= N; i++) {
        int ai; cin >> ai;
        f[i] = ai;
        points.push_back({i,f[i]});
    }
    buildHull();
    reverse(hull.begin(),hull.end());
    for (int i = 0; i < hull.size() - 1; i++) {
        if (hull[i].x == N + 1) break;
        for (int j = hull[i].x; j < hull[i+1].x; j++) {
            auto p =  interpolate(hull[i],hull[i+1],j);
            ans[j] = 100000LL*p.first/p.second;
        }
    }
    //output
    for (int i = 1; i <= N; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}

