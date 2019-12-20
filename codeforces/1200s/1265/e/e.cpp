#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353;
const int maxn = 2e5+5;
ll mult(ll a, ll b) {
    return (a*b) % M;
}
ll madd(ll a, ll b) {
    a += b;
    if (a >= M) a -= M;
    return a;
}
ll modexp(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
ll inverse(ll x) {
    return modexp(x,M-2);
}
ll p[maxn];
int n, q;

struct QNode {
    ll sum, prod;
    QNode() {
        sum = 0;
        prod = 1;
    }
    QNode(ll a, ll b) {
        sum = a;
        prod = b;
    }
};

QNode merge(QNode a, QNode b) {
    QNode ret = QNode();
    ret.prod = mult(a.prod,b.prod);
    ret.sum = madd(a.sum,mult(a.prod,b.sum));
    return ret;
}

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
    ll prod;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		if (s != e) {
			m = (s+e)/2;
			l = new Node(s,m);
			r = new Node(m+1,e);
            prod = mult(l->prod,r->prod);
            sum = madd(l->sum,mult(l->prod,r->sum));
		}
		else {
            sum = p[a];
            prod = p[a];
			l = NULL;
			r = NULL;
		}
	}

    ll getprod(int st, int en) {
        if (st <= s && e <= en) {
			return prod;
		}
        ll ret = 1;
		if (st <= m) {
			ret = mult(ret,l->getprod(st,en));
		}
		if (en > m) {
			ret = mult(ret,r->getprod(st,en));
		}
		return ret; 
    }

	QNode getsum(int st, int en) {
		if (st <= s && e <= en) {
			return QNode(sum,prod);
		}
        QNode ret = QNode();
		if (st <= m) {
            ret = merge(l->getsum(st,en),ret);
		}
		if (en > m) {
            ret = merge(ret,r->getsum(st,en));
		}
		return ret;
	}

    ll getans(int st, int en) {
        ll num = getsum(st,en).sum;
        num = madd(num,1);
        ll den = getprod(st,en);
        num = madd(num,M-den);
        return mult(num,inverse(den));
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        p[i] = mult(p[i],inverse(100));
    }
    Node *root = new Node(1,n);
    ll ans = root->getans(1,n);
    cout << ans << '\n';
}
