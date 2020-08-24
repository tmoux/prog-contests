#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7, maxn = 5e5+5;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}
int fac[maxn], ifac[maxn];
int choose(int n, int k) {
    assert(k <= n);
    int ret = fac[n];
    ret = mult(ret,ifac[k]);
    ret = mult(ret,ifac[n-k]);
    return ret;
}

struct Node {
	int s, e, m;
	//covers s,e;
    int prod = 1;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		prod = 1;
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

	void add(int i, int x) {
		if (s == e) {
            madd(prod,x);
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		prod = mult(l->prod,r->prod);
	}

	int getprod(int st, int en) {
		if (st <= s && e <= en) {
			return prod;
		}
		int ret = 1;
		if (st <= m) {
            ret = mult(ret,l->getprod(st,en));
		}
		if (en > m) {
            ret = mult(ret,r->getprod(st,en));
		}
		return ret;
	}
};

void solve() {
    int n; cin >> n;
    vector<int> a(n), freq(n+1,0);
    vector<vector<int>> level(n+1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ++freq[a[i]];
        level[freq[a[i]]].push_back(a[i]);
    }
    Node *segLess = new Node(0,n+1);
    Node *segMore = new Node(0,n+1);
    for (int i = 1; i <= n; i++) segMore->add(i,freq[i]);
    vector<int> ans(n+1,0);
    for (int j = 1; j <= n; j++) {
        for (int i: level[j]) {
            int ci = freq[i];
            int add = choose(ci,j);
            add = mult(add,segLess->getprod(0,i-1));
            add = mult(add,segMore->getprod(i+1,n+1));
            madd(ans[i],add);
        }
        for (int i: level[j]) {
            segLess->add(i,choose(freq[i],j));
        }
        if (j+1 <= n) for (int i: level[j+1]) {
            segMore->add(i,choose(freq[i],j+1));
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) {
        fac[i] = mult(fac[i-1],i);
        ifac[i] = inverse(fac[i]);
    }
    int t; cin >> t;
    while (t--) solve();
}
