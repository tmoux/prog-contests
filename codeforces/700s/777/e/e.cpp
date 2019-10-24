#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll maxi;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
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


	void add(int i, ll x) {
		if (s == e) {
			sum = max(sum,x);
			maxi = sum;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		sum = l->sum + r->sum;
		maxi = max(l->maxi,r->maxi);
	}

	ll getmaxi(int st, int en) {
		if (st <= s && e <= en) {
			return maxi;
		}
		ll ret = 0;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}	

	ll getsum(int st, int en) {
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

const int maxn = 1e5+5;
int n;
struct Point
{
    int a, b, h;
} pts[maxn];

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    set<int> s;
    for (int i = 0; i < n; i++) {
        cin >> pts[i].a >> pts[i].b >> pts[i].h;
        s.insert(pts[i].a);
        s.insert(pts[i].b);
    }
    map<int,int> as;
    int pt = 1;
    for (int i: s) {
        as[i] = pt++;
    }
    for (int i = 0; i < n; i++) {
        pts[i].a = as[pts[i].a];
        pts[i].b = as[pts[i].b];
    }
    Node *root = new Node(0,2*n+5);
    sort(pts,pts+n,[](auto a, auto b) {
            if (a.b != b.b) return a.b > b.b;
            return a.a > b.a;
            });
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll t = root->getmaxi(0,pts[i].b-1) + pts[i].h;
        //printf("a = %d, b = %d, h = %d, t = %d\n",pts[i].a,pts[i].b,pts[i].h,t);
        ans = max(ans,t);
        root->add(pts[i].a,t);
    }
    cout << ans << '\n';
}
