#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+9;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int msub(int a, int b) {
    madd(a,M-b);
    return a;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}

const int maxn = 2e5+5;
int n, q;
int d[maxn];
int base = 2;
int expo[maxn], inv[maxn];

struct QNode
{
    int l, r, hash, len;
};
QNode empty = {-1,-1,-1,0};

QNode merge(QNode a, QNode b) {
    if (a.len == 0) return b;
    if (b.len == 0) return a;
    if (a.r == 1 && a.len == 1 && b.l == 1 && b.len == 1) {
        return empty;
    }
    if (a.r == 1 && a.len == 1 && b.l == 1) {
        int new_hash = mult(msub(b.hash,1),inv[1]);
        return {0,b.r,new_hash,b.len-1};
    }
    if (b.l == 1 && b.len == 1 && a.r == 1) {
        int new_hash = msub(a.hash,expo[a.len-1]);
        return {a.l,0,new_hash,a.len-1};
    }
    if (a.r != 1 || b.l != 1) {
        int new_hash = a.hash;
        madd(new_hash,mult(b.hash,expo[a.len]));
        return {a.l,b.r,new_hash,a.len+b.len};
    }
    else {
        int new_hash = msub(a.hash,expo[a.len-1]);
        madd(new_hash,mult(
                        mult(msub(b.hash,1),inv[1]),
                        expo[a.len-1]));
        return {a.l,b.r,new_hash,a.len+b.len-2};
    }
}

struct Node {
	int s, e, m;
	//covers s,e;
    QNode sum;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		if (s != e) {
			m = (s+e)/2;
			l = new Node(s,m);
			r = new Node(m+1,e);
            sum = merge(l->sum,r->sum);
		}
		else {
            if (d[s] == 0) {
                sum = {0,0,0,1};
            }
            else if (d[s] == 1) {
                sum = {1,1,1,1};
            }
            else assert(false);
			l = NULL;
			r = NULL;
		}
        /*
        printf("[%d,%d]:\n",s,e);
        printf("[%d %d]\n",sum.l,sum.r);
        printf("hash = %d, len = %d\n",sum.hash,sum.len);
        */
	}

	QNode getsum(int st, int en) {
		if (st <= s && e <= en) {
			return sum;
		}
        QNode ret = empty;
		if (st <= m) {
			ret = merge(l->getsum(st,en),ret);
		}
		if (en > m) {
            ret = merge(ret,r->getsum(st,en));
		}
		return ret;
	}
};

int main() {
    expo[0] = inv[0] = 1;
    for (int i = 1; i < maxn; i++) {
        expo[i] = mult(expo[i-1],base);
        inv[i] = inverse(expo[i]);
    }
    cin >> n;
    string s; cin >> s;
    for (int i = 0; i < n; i++) {
        d[i] = s[i] == '1';
    }
    Node *root = new Node(0,n-1);
    cin >> q;
    while (q--) {
        int l1, l2, len; cin >> l1 >> l2 >> len;
        --l1; --l2;
        auto h1 = root->getsum(l1,l1+len-1);
        auto h2 = root->getsum(l2,l2+len-1);
        cout << (h1.hash == h2.hash && h1.len == h2.len ? "Yes" : "No") << '\n';
    }
}
