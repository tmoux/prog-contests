#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5005;
const ll NANA = -1e18;
int n, k, x, a[maxn];
ll dp[maxn][maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll lazy;
	ll maxi;
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

	void add(int st, int en, ll x) {
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
		maxi = min(l->maxi,r->maxi);
	}

    void build(ll *a, int n) {
        for (int i = 1; i <= n; i++) {
            add(i,i,a[i]);
        }
    }

	ll getmaxi(int st, int en) {
		push();
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

Node *tables[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k >> x;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= k; i++) {
        dp[1][i] = a[i];
    }
    tables[1] = new Node(1,n);
    tables[1]->build(dp[1],n);
    for (int j = 2; j <= x; j++) {
        for (int i = 1; i <= n; i++) {
            ll m = tables[j-1]->getmaxi(max(1,i-k),i-1);
            if (m > 0) dp[j][i] = m + a[i];
            cout << i << ' ' << j << ": " << dp[j][i] << '\n';
            /*
            ll m = 0;
            for (int p = max(1,i-k); p < i; p++) {
                m = max(m,dp[j-1][p]);
            }
            */
            //if (m > 0) dp[j][i] = m + a[i];
            //cout << i << ' ' << j << ": " << dp[j][i] << '\n';
        }
        tables[j] = new Node(1,n);
        //tables[j]->build(dp[j],n);
    }
    ll ans = 0;
    for (int i = n-k+1; i <= n; i++) {
        ans = max(ans,dp[x][i]);
    }
    cout << (ans==0?-1:ans) << '\n';
    

    return 0;
}

