#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5+5;
int n, c, dp[N];
int a[N], b[N];
int pa[N], pb[N];

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll mini;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
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


	void add(int i, ll x) {
		if (s == e) {
			sum += x;
			mini = sum;
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
    cin >> n >> c;
    for (int i = 1; i <= n-1; i++) {
        cin >> a[i];
        pa[i] = a[i] + pa[i-1];
    }
    for (int i = 1; i <= n-1; i++) {
        cin >> b[i];
        pb[i] = b[i] + pb[i-1];
    }
    Node *root = new Node(1,n);
    Node *root2 = new Node(1,n);
    for (int i = 2; i <= n; i++) {
        dp[i] = min(pa[i-1]+(int)root->getmini(1,i-1),
                    pb[i-1]+(int)root2->getmini(1,i-1)+c);
        root->add(i,dp[i]-pa[i-1]);
        root2->add(i,dp[i]-pb[i-1]);
    }
    //output
    for (int i = 1; i <= n; i++) {
        cout << dp[i] << ' ';
    }
    cout << '\n';
}

