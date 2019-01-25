#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, M = 1e9+7;
const int MAX = 5;
int N, K, a[maxn], mn[maxn];

ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}

struct Node {
	int s, e, m;
	//covers s,e;
	ll mini;
	Node *l, *r;

	Node(int a, int b) {
		s = a;
		e = b;
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
			mini = x;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		mini = min(l->mini,r->mini);
	}

	ll getmini(int st, int en) {
		if (st <= s && e <= en) {
			return mini;
		}
		ll ret = 2e9+9;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
	}
};

int main()
{
    //freopen("tracking2.in","r",stdin); freopen("tracking2.out","w",stdout);
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 1; i <= N + 1 - K; i++) cin >> mn[i];
    for (int i = 1; i < N + 1 - K; i++) {
        if (mn[i+1] > mn[i]) a[i] = mn[i];    
        else if (mn[i] > mn[i+1]) a[i+K] = mn[i+1];
    }
    if (K == 1) {
        ll ans = 1;
        cout << ans << '\n';
        return 0;
    }
    bool allSame = true;
    for (int i = 1; i < N + 1 - K; i++) {
        if (mn[i] != mn[i+1]) {
            allSame = false;
            break;
        }
    }
    if (allSame) {
        ll ans = (modexp(MAX-mn[1]+1,N) - modexp(MAX-mn[1],N) + M) % M;
        cout << ans << '\n';
        return 0;
    }
    if (K == 2 && N != 4) assert(false);
    for (int i = 1; i <= N; i++) {
        cout << i << ": " << a[i] << ' ' << mn[i] << '\n';
    }
    cout << '\n';
    ll ans = 1;
    for (int i = 1; i <= N;) {
        if (a[i] == 0) {
            int len = 0;
            int k;
            k = mn[min(N+K-1,i)];
            //cout << i << " k = " << k << '\n';
            while (i <= N && a[i] == 0) {
                len++;
                i++;
            }
            ll add = (modexp(MAX-k+1,len) - modexp(MAX-k,len) + M) % M;
            printf("%d, k = %d, len = %d: %d\n",i,k,len,add);
            ans = (ans * add) % M;
        }
        else i++;
    }
    cout << ans << '\n';

    return 0;
}

