#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, x;

struct SegDyn
{
	int s, e, m; //represents range [s,e]
	SegDyn *l, *r;
    int maxi;
	SegDyn(int _s, int _e) {
		s = _s;
		e = _e;
		m = (s+e)/2;
		l = NULL;
		r = NULL;
        maxi = 0;
	}

	void prepareL() { if (l == NULL) l = new SegDyn(s,m); }
	void prepareR() { if (r == NULL) r = new SegDyn(m+1,e); }

	void pull() {
        maxi = 0;
        if (l) maxi = max(maxi,l->maxi);
        if (r) maxi = max(maxi,r->maxi);
	}

	void add(int idx, int del) { //a[idx] += del
		//cout << s << ' ' << e << '\n';
		if (s == e && s == idx) {
			//at the node, stop
            maxi = max(maxi,del);
			return;
		}
		if (idx <= m) {
			prepareL();
			l->add(idx,del);
		}
		else {
			prepareR();
			r->add(idx,del);
		}
		pull(); //updates current node based on the children
	}

    int getmaxi(int se, int en) {
		if (se <= s && e <= en) return maxi;
		int res = 0;
		if (l && se <= m) res = max(res,l->getmaxi(se,en));
		if (r && en > m) res = max(res,r->getmaxi(se,en));
		return res;	
	}
};

int a[maxn];
int f[maxn], b[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    SegDyn *fwd = new SegDyn(0,1e9+1);
    SegDyn *bck = new SegDyn(0,1e9+1);
    for (int i = 1; i <= n; i++) {
        int m = fwd->getmaxi(0,a[i]-1) + 1;    
        f[i] = m;
        fwd->add(a[i],m);
    }
    int ans = 0;
    for (int i = n; i >= 1; i--) {
        int curr = f[i];
        int added = bck->getmaxi(max(1,a[i]+1-x),1e9+1);
        ans = max(ans,curr+added);
        int m = bck->getmaxi(a[i]+1,1e9+1) + 1;
        b[i] = m;
        bck->add(a[i],m);
    }
    cout << ans << '\n';
}

