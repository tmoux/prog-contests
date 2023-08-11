#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
	int s, e, m;
	//covers s,e;
	ll maxi;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
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

	void update(int idx, ll x) {
		if (s == e) {
            maxi = max(maxi,x);
			return;
		}
		if (idx <= m) {
			l->update(idx,x);
		}
        else {
			r->update(idx,x);
		}
		maxi = max(l->maxi,r->maxi);
	}

	ll getmaxi(int st, int en) {
		//if completely included
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
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    Node *seg = new Node(1,m); 
    int maxNondecreasing = 0;
    for (int i = 0; i < n; i++) {
        int j; double x; cin >> j >> x;
        int q = seg->getmaxi(1,j) + 1;
        seg->update(j,q);            
        maxNondecreasing = max(maxNondecreasing,q);
    }
    int ans = n - maxNondecreasing;
    cout << ans << '\n';

    return 0;
}
	
