#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m, p;

ll yc[1000006];

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll lazy;
	ll maxi;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		lazy = 0;
		maxi = 0;
		if (s != e) {
			m = (s+e)/2;
			l = new Node(s,m);
			r = new Node(m+1,e);
		}
		else {
			l = NULL;
			r = NULL;
		}
	}

	void push() {
		if (s != e) {
			l->lazy += lazy;
			l->sum += (l->e - l->s + 1) * lazy;
			l->maxi += lazy;

			r->lazy += lazy;
			r->sum += (r->e - r->s + 1) * lazy;
			r->maxi += lazy;
		}
		lazy = 0;
	}

	void add(int st, int en, ll x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy += x;
			sum += (e - s + 1) * x;
			maxi += x;
			return;
		}
		push();
		if (st <= m) {
			l->add(st,en,x);
		}
		if (en > m) {
			r->add(st,en,x);
		}
		sum = l->sum + r->sum;
		maxi = max(l->maxi,r->maxi);
	}

	ll getmaxi(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return maxi;
		}
		ll ret = -1e18;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}	

	ll getsum(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return sum;
		}
		ll ret = 0;
		if (st <= m) {
			ret += l->getsum(st,en);
		}
		if (en > m) {
			ret += r->getsum(st,en);
		}
		return ret;
	}
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> p;
    vector<pair<int,int>> xs;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        xs.push_back({a,b});
    }
    sort(xs.begin(),xs.end());
    for (int i = 0; i <= 1000000; i++) yc[i] = 1e15;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        yc[a] = min(yc[a],(ll)b);
    }
    for (int i = 999999; i >= 1; i--) {
        yc[i] = min(yc[i],yc[i+1]);
    }
    vector<pair<pair<int,int>,int>> pts;
    for (int i = 0; i < p; i++) {
        int x, y, z; cin >> x >> y >> z;
        pts.push_back({{x,y},z});
    }
    sort(pts.begin(),pts.end(),[](auto a, auto b) {
            return a.first.first < b.first.first;
            });
    int pt = 0;
    ll ans = -1e18;
    Node *root = new Node(1,1000000);
    for (int i = 1; i <= 1000000; i++) {
        root->add(i,i,-yc[i]);
    }
    for (auto p: xs) {
        int x = p.first;
        int xcost = p.second;
        while (pt < pts.size() && pts[pt].first.first < x) {
            int y = pts[pt].first.second;
            int z = pts[pt].second;
            if (y < 1000000) {
                root->add(y+1,1000000,z);
            }
            ++pt;
        }
        ll tr = root->getmaxi(1,1000000)-xcost;
        //cout << x << ": " << tr << endl;
        ans = max(ans,tr);
    }
    cout << ans << endl;
}
