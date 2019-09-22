#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Comp
{
    int ans;
    int prefix;
    int suffix;
};

Comp comb(Comp a, Comp b) {
    int ans = max(a.ans,max(b.ans,a.suffix+b.prefix));
    int prefix;
    if (a.prefix == 0) prefix = 0;
    else prefix = (a.ans == a.prefix) ? a.prefix + b.prefix : a.prefix;
    int suffix;
    if (b.suffix == 0) suffix = 0;
    else suffix = (b.ans == b.suffix) ? b.suffix + a.suffix : b.suffix;
    /*
    cout << "a: " << a.ans << ' ' << a.prefix << ' ' << a.suffix << '\n';
    cout << "b: " << b.ans << ' ' << b.prefix << ' ' << b.suffix << '\n';
    cout << "res: " << ans << ' ' << prefix << ' ' << suffix << '\n';
    */
    return {ans,prefix,suffix};
}

struct Node {
	int s, e, m;
	//covers s,e;
    Comp c;
    int curr;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
        c = {0,0,0};
        curr = 0;
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
            curr += x;
            if (curr == 0) {
                c = {0,0,0};
            }
            else if (curr < 0) {
                c.ans = 1;
                c.prefix = 1;
                c.suffix = 0;
            }
            else {
                c.ans = 1;
                c.prefix = 0;
                c.suffix = 1;
            }
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
        c = comb(l->c,r->c);
	}

	Comp getsum(int st, int en) {
		if (st <= s && e <= en) {
			return c;
		}
        Comp ret = {0,0,0};
		if (st <= m) {
            ret = comb(ret,l->getsum(st,en));
		}
		if (en > m) {
            ret = comb(ret,r->getsum(st,en));
		}
		return ret;
	}

	int debug(int st, int en) {
		if (st <= s && e <= en) {
			return curr;
		}
		if (st <= m) {
            return l->debug(st,en);
		}
		if (en > m) {
            return r->debug(st,en);
		}
	}
};

const int maxn = 3e5+5;
int a[maxn];
int n, m;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    Node *root = new Node(0,n);
    for (int i = 1; i <= n-1; i++) {
        root->add(i,a[i+1]-a[i]);
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int l, r, d; cin >> l >> r >> d;
        root->add(l-1,d);
        root->add(r,-d);
        /*
        for (int i = 1; i <= n-1; i++) {
            cout << i << ": " << root->debug(i,i) << '\n';
        }
        */
        int ans = root->getsum(1,n-1).ans;
        cout << ans+1 << '\n';
    }
}

