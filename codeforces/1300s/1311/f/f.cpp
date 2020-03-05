#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
pair<int,int> a[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
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
    for (int i = 0; i < n; i++) {
        cin >> a[i].second;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
    }
    sort(a,a+n);
    map<int,int> mp;
    int pt = 0;
    for (int i = 0; i < n; i++) {
        if (!mp.count(a[i].first)) mp[a[i].first] = pt++;
    }
    sort(a,a+n,[](auto x, auto y) {
            return x.second < y.second;
            });
    Node *upper = new Node(0,n);
    Node *lower = new Node(0,n);
    Node *upper_cnt = new Node(0,n);
    Node *lower_cnt = new Node(0,n);
    for (int i = 0; i < n; i++) {
        upper->add(mp[a[i].first],a[i].second);
        upper_cnt->add(mp[a[i].first],1);
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int slope = mp[a[i].first];
        ll b = a[i].second;

        upper->add(slope,-b);
        upper_cnt->add(slope,-1);
        ans += lower_cnt->getsum(0,slope)*b-lower->getsum(0,slope);
        ans += upper->getsum(slope,n)-upper_cnt->getsum(slope,n)*b;
        lower->add(slope,b);
        lower_cnt->add(slope,1);
    }
    cout << ans/2 << endl;
}
