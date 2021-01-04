#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, q;
ll a[maxn];

ll solve(ll x, ll dy) {
    ll s = x + dy;
    if (s >= 0) return (s+1)/2;
    else return s/2;
}

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
    cin >> n;
    ll dy = 0;
    Node *root = new Node(1,n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        root->add(i,i,a[i]);
    }
    for (int i = 2; i <= n; i++) {
        dy += max(0LL,a[i]-a[i-1]);
    }
    cout << solve(a[1],dy) << '\n';
    cin >> q;
    while (q--) {
        int l, r, x; cin >> l >> r >> x;
        if (l > 1) 
            dy -= max(0LL,root->getsum(l,l)-root->getsum(l-1,l-1));
        if (r+1 <= n) dy -= max(0LL,root->getsum(r+1,r+1)-root->getsum(r,r));

        root->add(l,r,x);

        if (l > 1) 
            dy += max(0LL,root->getsum(l,l)-root->getsum(l-1,l-1));
        if (r+1 <= n) dy += max(0LL,root->getsum(r+1,r+1)-root->getsum(r,r));

        cout << solve(root->getsum(1,1),dy) << '\n';
    }
}