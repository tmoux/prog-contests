#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[maxn];
int q;

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll maxi;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
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

pair<int,int> lastupdate[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cin >> q;
    Node *root = new Node(0,q+1);
    for (int i = 1; i <= q; i++) {
        int t; cin >> t;
        if (t == 1) {
            int p, x; cin >> p >> x;
            lastupdate[p] = {x,i};
        }
        else {
            int x; cin >> x;
            root->add(i,x);
        }
    }
    for (int i = 1; i <= n; i++) {
        int curr = a[i];
        if (lastupdate[i].second != 0) {
            curr = lastupdate[i].first;
        }
        curr = max(curr,(int)root->getmaxi(lastupdate[i].second+1,q+1));
        cout << curr << ' ';
    }
    cout << '\n';
}

