#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5, maxb = 21;
int n, m;

struct Node {
	int s, e, m;
	//covers s,e;
	int sum[maxb];
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
        memset(sum,0,sizeof sum);
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

	void add(int i, int b, int x) {
		if (s == e) {
			sum[b] += x;
			return;
		}
		if (i <= m) {
			l->add(i,b,x);
		}
		else if (i > m) {
			r->add(i,b,x);
		}
		else assert(false);
        sum[b] = l->sum[b] + r->sum[b];
	}

	int getsum(int st, int en, int b) {
		if (st <= s && e <= en) {
			return sum[b];
		}
		int ret = 0;
		if (st <= m) {
			ret += l->getsum(st,en,b);
		}
		if (en > m) {
			ret += r->getsum(st,en,b);
		}
		return ret;
	}
};

int type[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    Node *root = new Node(1,n);
    for (int i = 1; i <= n; i++) {
        int b; cin >> b;
        root->add(i,b,1);
        type[i] = b;
    }
    while (m--) {
        int t; cin >> t;
        if (t == 1) {
            int a, b; cin >> a >> b;
            root->add(a,type[a],-1);
            type[a] = b;
            root->add(a,type[a],1);
        }
        else {
            int l, r, c; cin >> l >> r >> c;
            for (int i = 20; i >= 0; i--) {
                int sub = root->getsum(l,r,i);
                //cout << i << ": " << sub << '\n';
                if (sub >= c) {
                    cout << i << '\n';
                    break;
                }
                else {
                    c -= sub;
                }
            }
        }
    }
}

