#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll det(ll a, ll b, ll c, ll d) { return a*d-b*c; }

struct Line
{
	ll x0, x1, y0, y1;
	Line() {}
	Line(int _x0, int _y0, int _x1, int _y1) :
		x0(_x0),
		y0(_y0),
		x1(_x1),
		y1(_y1) {}

	bool integer_intersect(pair<ll,ll> t) {
		ll p = t.first, q = t.second;
		if (q == 0 || p*q < 0 || abs(p) > abs(q)) return false;
		return (p*(x1-x0)) % q == 0 && (p*(y1-y0)) % q == 0;
	}
	pair<ll,ll> get_intersect(pair<ll,ll> t) {
		return {x0+t.first*(x1-x0)/t.second,y0+t.first*(y1-y0)/t.second};
	}
};

pair<ll,ll> find_intersect(Line& a, Line& b) {
	ll D = det(a.x1-a.x0,-(b.x1-b.x0),a.y1-a.y0,-(b.y1-b.y0));
	ll Dt = det(b.x0-a.x0,-(b.x1-b.x0),b.y0-a.y0,-(b.y1-b.y0));
	ll gc = __gcd(D,Dt);
	return {Dt/gc,D/gc};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    ll res = 0;
    vector<Line> lines(n);
    for (int i = 0; i < n; i++) {
    	int x0, y0, x1, y1; cin >> x0 >> y0 >> x1 >> y1;
    	Line l(x0,y0,x1,y1);
    	lines[i] = l;
    	res += __gcd(abs(x0-x1),abs(y0-y1)) + 1;
    }
    for (int i = 0; i < n; i++) {
    	set<pair<ll,ll>> found;
    	for (int j = i + 1; j < n; j++) {
    		auto t = find_intersect(lines[i],lines[j]);
    		auto s = find_intersect(lines[j],lines[i]);
    		if (lines[i].integer_intersect(t) && lines[j].integer_intersect(s) && found.count(lines[i].get_intersect(t)) != 1) {
    			auto p = lines[i].get_intersect(t);
    			found.insert(p);
    			res--;
    		}
    	}
    }
    cout << res << '\n';
    return 0;
}