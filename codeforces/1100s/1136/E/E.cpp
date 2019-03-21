#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
const ll INV = -(1LL<<62);
int n, q;
ll a[maxn], k[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll lazy;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		lazy = 0;
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
			l->lazy = max(l->lazy,lazy);
			l->sum = max(l->sum,(l->e - l->s + 1) * l->lazy);

			r->lazy = max(r->lazy,lazy);
			r->sum = max(r->sum,(r->e - r->s + 1) * r->lazy);
		}
		lazy = 0;
	}

	void pull() {
		sum = l->sum + r->sum;
	}

	void add(int st, int en, ll x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy = max(lazy,x);
			sum = max(sum,(e - s + 1) * lazy);
			return;
		}
		push();
		if (st <= m) {
			l->add(st,en,x);
		}
		if (en > m) {
			r->add(st,en,x);
		}
		pull();
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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2; i <= n; i++) {
        cin >> k[i];
        //k[i] = max(k[i],a[i]-a[i-1]);
    }
    /*
    for (int i = 1; i <= n; i++) {
        cout << "k " << i << ": " << k[i] << '\n';
    }
    */
    //make k a prefix sum
    for (int i = 1; i <= n; i++) k[i] += k[i-1];
    Node *root = new Node(1,n);
    for (int i = 1; i <= n; i++) {
        root->add(i,i,a[i]-k[i]);
    }
    for (int i = 1; i <= n; i++) k[i] += k[i-1];
    
    /*
    for (int i = 1; i <= n; i++) {
        cout << i << ": " << root->getsum(i,i) << '\n';
    }
    */
    cin >> q;
    while (q--) {
        char c; cin >> c;
        if (c == 's') {
            int l, r; cin >> l >> r;
            ll ans = root->getsum(l,r) + k[r] - k[l-1];
            cout << ans << '\n';
        }
        else {
            int i, x; cin >> i >> x;
            ll ai = root->getsum(i,i);
            root->add(i,n,ai+x); //make x the max of invl [i,n]

            /*
            for (int i = 1; i <= n; i++) {
                cout << i << ": " << root->getsum(i,i) << '\n';
            }
            */
        }
    }
}

