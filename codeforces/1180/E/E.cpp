#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5, maxx = 1e6+6;
int n, m, q;
int a[maxn], b[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	int lazy;
	int maxi;
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

	void add(int st, int en, int x) {
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

	int getmaxi(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return maxi;
		}
		int ret = -999999999;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}	

	int getsum(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return sum;
		}
		int ret = 0;
		if (st <= m) {
			ret += l->getsum(st,en);
		}
		if (en > m) {
			ret += r->getsum(st,en);
		}
		return ret;
	}
    
    int walk() { //returns highest index such that maxi > 0
        push();
        if (maxi <= 0) return -1;
        if (s == e) return s;
        if (r->maxi > 0) return r->walk();
        return l->walk();
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    Node *root = new Node(1,maxx);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        root->add(1,a[i],1);
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
        root->add(1,b[i],-1);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        int idx, x; cin >> idx >> x;
        if (t == 1) {
            root->add(1,a[idx],-1);
            root->add(1,x,1);
            a[idx] = x;
        }
        else if (t == 2) {
            root->add(1,b[idx],1);
            root->add(1,x,-1);
            b[idx] = x;
        }
        int ans = root->walk();
        cout << ans << '\n';
    }
}

