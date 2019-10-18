#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, a[3*maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll mini;
    ll maxi;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		mini = 0;
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

	void add(int i, ll x) {
		if (s == e) {
			sum += x;
			mini = sum;
            maxi = sum;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		sum = l->sum + r->sum;
		mini = min(l->mini,r->mini);
		maxi = max(l->maxi,r->maxi);
	}

    ll getmaxi(int st, int en) {
		if (st <= s && e <= en) {
			return maxi;
		}
		ll ret = 0;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}	

	ll getmini(int st, int en) {
		if (st <= s && e <= en) {
			return mini;
		}
		ll ret = 1e18;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
	}	

	ll getsum(int st, int en) {
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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int mn = 2e9, mx = 0;
    Node *root = new Node(0,3*n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i+n] = a[i];
        a[i+2*n] = a[i];
        mn = min(mn,a[i]);
        mx = max(mx,a[i]);
        root->add(i,a[i]);
        root->add(i+n,a[i]);
        root->add(i+2*n,a[i]);
    }
    if (mn >= (double)mx/2.0) {
        for (int i = 0; i < n; i++) {
            cout << -1 << ' ';
        }
        cout << '\n';
        return 0;
    }
    int r = 0;
    multiset<int> seen;
    seen.insert(a[0]);
    for (int i = 0; i < n; i++) {
        while (a[r] >= (double)root->getmaxi(i,r)/2.0) {
            r++;
        }
        cout << (r-i) << ' ';
    }
    cout << '\n';
}

