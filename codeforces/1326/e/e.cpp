#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, p[maxn], q[maxn], pos[maxn];

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
		int ret = -3*maxn;
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
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        pos[p[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> q[i];
    }
    int ans = n;
    Node *root = new Node(1,n);
    root->add(1,pos[ans],1);
    for (int i = 1; i <= n; i++) {
        while (root->getmaxi(1,n) <= 0) {
            ans--;
            root->add(1,pos[ans],1);
        }
        cout << ans << ' ';
        root->add(1,q[i],-1);
    }
    cout << '\n';
}
