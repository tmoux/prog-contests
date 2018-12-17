#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll lazy;
	ll mini;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		lazy = 0;
		mini = 0;
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
			l->mini += lazy;

			r->lazy += lazy;
			r->sum += (r->e - r->s + 1) * lazy;
			r->mini += lazy;
		}
		lazy = 0;
	}

	void add(int st, int en, ll x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy += x;
			sum += (e - s + 1) * x;
			mini += x;
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
		mini = min(l->mini,r->mini);
	}

	ll getmini(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return mini;
		}
		ll ret = 1000000000000000000;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
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
	freopen("haybales.in","r",stdin); freopen("haybales.out","w",stdout);
    int n, q; cin >> n >> q;
	Node *root = new Node(1,n);
    for (int i = 1; i <= n; i++) {
        ll ai; cin >> ai;
        root->add(i,i,ai);
    }
    while (q--) {
        char c; cin >> c;
        if (c == 'P') {
            ll a, b, c; cin >> a >> b >> c;
            root->add(a,b,c);
        }
        else if (c == 'M') {
            ll a, b; cin >> a >> b;
            //fout << root->getmini(a,b) << '\n';
            cout << root->getmini(a,b) << '\n';
        }
        else if (c == 'S') {
            ll a, b; cin >> a >> b;
            //fout << root->getsum(a,b) << '\n';
            cout << root->getsum(a,b) << '\n';
        }
    }
    return 0;
}
