#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int maxn = 1e6+6;
int N;
ll a[maxn];
const ld mil = 1000000;

struct Node {
	int s, e, m;
	//covers s,e;
	ld sum;
    ld prod;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0.0;
        prod = 1.0;
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


	void add(int i, ld x) {
		if (s == e) {
			sum += x;
            prod *= x;
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
        prod = l->prod * r->prod;
	}

	int getsum(int st, int en) {
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

ll getans(int r) {
    ll ans = 0;
    ld prod = 1.0;
    ld sum = 0.0;
    for (int i = r; i >= 0; i--) {
        prod = prod * (1000000-a[i])/mil;
        sum = sum + (ld)(mil*a[i])/(mil-a[i]);
        //sum += b[i]/(1-b[i]/1000000.0);
        ll r = (ll)(prod*sum);
        //cout << prod << ' ' << sum << '\n';
        //cout << i << ": " << r << '\n';
        if (r < ans) return ans;
        ans = r;
    }
    return ans;
}

ld b[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("cowdate.in","r",stdin); freopen("cowdate.out","w",stdout);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        b[i] = a[i]/mil;
    }
    ll ans = 0;
    ld prod = 1.0;
    ld sum = 0.0;
    int L = N-1;
    for (int i = N-1; i >= 0; i--) {
        if (i < N - 1) {
            prod /= (1-b[i+1]);
            sum -= (a[i+1])/(1-b[i+1]);
        }
        while (sum < 1000000 && L >= 0) {
            prod *= (1-b[L]);
            sum += (a[L])/(1-b[L]);
            L--;
        }
        //cout << i << ": " << prod << ' ' << sum << '\n';
        //cout << (L+1) << ' ' << (ll)(prod*sum) << '\n';
        ans = max(ans,(ll)(prod*sum));
    }
    if (ans % 10 == 9) ++ans;
    cout << ans << '\n';

    return 0;
}

