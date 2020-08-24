#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	int lazy_swap, lazy_rev;
    int depth;
	Node *l, *r;
	
	Node(int a, int b, int d) {
		s = a;
		e = b;
		sum = 0;
		lazy_swap = lazy_rev = 0;
        depth = d;
		if (s != e) {
			m = (s+e)/2;
			l = new Node(s,m,d-1);
			r = new Node(m+1,e,d-1);
		}
		else {
			l = NULL;
			r = NULL;
		}
	}

	void push() {
		if (s != e) {
            l->lazy_swap = lazy_swap;
            l->lazy_rev = lazy_rev;

            r->lazy_swap = lazy_swap;
            r->lazy_rev = lazy_rev;
		}
	}

	void update(int i, ll x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (s == e) {
            sum = x;
			return;
		}
		push();
        if (lazy_rev & (1<<depth)) {
            i = e - i + s;
        }
        assert(depth > 0);
        bool swp = lazy_swap & (1<<depth);
		if (i <= m) {
            if (!swp) {
                l->update(i,x);
            }
            else {
                r->update(i+(1<<(depth-1)),x);
            }
		}
        else if (i > m) {
            if (!swp) {
                r->update(i,x);
            }
            else {
                l->update(i-(1<<(depth-1)),x);
            }
		}
		sum = l->sum + r->sum;
	}

    void reverse(int k) {
        lazy_rev ^= (1<<k);
    }

    void swapk(int k) {
        lazy_swap ^= (1<<k);
    }

	ll getsum(int st, int en) {
		push();
		//if completely included
        st = max(st,s);
        en = min(en,e);
		if (st <= s && e <= en) {
			return sum;
		}
		ll ret = 0;
        if (lazy_rev & (1<<depth)) {
            st = e - st + s;
            en = e - en + s;
            swap(st,en);
        }
        bool swp = lazy_swap & (1<<depth);
        assert(depth > 0);
		if (st <= m) {
            if (!swp) {
                ret += l->getsum(st,en);
            }
            else {
                ret += r->getsum(st+(1<<(depth-1)),en+(1<<(depth-1)));
            }
		}
		if (en > m) {
            if (!swp) {
                ret += r->getsum(st,en);
            }
            else {
                ret += l->getsum(st-(1<<(depth-1)),en-(1<<(depth-1)));
            }
		}
		return ret;
	}
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> n >> q;
    Node *root = new Node(0,(1<<n)-1,n);
    for (int i = 0; i < (1<<n); i++) {
        int ai; cin >> ai;
        root->update(i,ai);
    }
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int x, k; cin >> x >> k;
            x--;
            root->update(x,k);
        }
        else if (t == 2) {
            int k; cin >> k;
            root->reverse(k);
        }
        else if (t == 3) {
            int k; cin >> k;
            root->swapk(k+1);
        }
        else if (t == 4) {
            int l, r; cin >> l >> r;
            l--; r--;
            cout << root->getsum(l,r) << '\n';
        }
    }
}
