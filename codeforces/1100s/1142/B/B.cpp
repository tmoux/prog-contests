#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
const int maxk = 18;
int n, m, q;
int p[2*maxn], a[maxn];
int nxt[maxn];
int last[maxn];
int ptr[maxn]; //points to next jump index
int cnt[maxn], f[maxn];
int jmp[maxk][maxn];

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

int walk(int i, int l) {
    for (int k = maxk - 1; k >= 0; k--) {
        if (l&(1<<k)) {
            i = jmp[k][i];
            if (i == -1) return i;
        }
    }
    return i;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        p[i+n] = p[i];
    }
    for (int i = 1; i <= n; i++) nxt[p[i]] = p[i+1];
    for (int i = 1; i <= m; i++) cin >> a[i];
    for (int i = 0; i < maxn; i++) last[i] = -1;
    memset(jmp,0,sizeof jmp);
    for (int i = m; i >= 1; i--) {
        jmp[0][i] = last[nxt[a[i]]];
        last[a[i]] = i;
        //cout << i << ": " << ptr[i] << '\n';
    }
    for (int k = 1; k < maxk; k++) {
        for (int i = 1; i <= m; i++) {
            if (jmp[k-1][i] == -1) jmp[k][i] = -1;
            else jmp[k][i] = jmp[k-1][jmp[k-1][i]];
            //cout << k << ' ' << i << ": " << jmp[k][i] << '\n';
        }
    }
    Node *root = new Node(1,m);
    for (int i = 1; i <= m; i++) {
        int x = walk(i,n-1);
        if (x != -1) {
            root->add(i,i,x); 
        }
        else root->add(i,i,1e18);
    }
    while (q--) {
        int l, r; cin >> l >> r;
        //cout << cnt[l] << ' ' << f[l] << '\n';
        if (root->getmini(l,r) <= r) {
            //cout << root->getmini(l,r) << '\n';
            cout << 1;
        }
        else cout << 0;
    }
    cout << '\n';
}
