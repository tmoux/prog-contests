#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
};

const int maxn = 2e5+5;
int N, h[maxn], a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> h[i];
    }
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }
    Node *root = new Node(0,N);
    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        ll r = a[i] + root->getmaxi(0,h[i]-1);            
        root->add(h[i],r);
        ans = max(ans,r);
    }
    cout << ans << '\n';


    return 0;
}

