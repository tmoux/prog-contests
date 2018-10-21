#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, m, a[maxn], b[maxn];

class Node {
public:
	int s, e, m;
	//covers s,e;
	ll sum;
	Node *l, *r;

	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0LL;
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

	void add(int ind, int x) {
		sum += x;
		if (s == e) {
			return;
		}
		int m = (s+e)/2;
		if (ind <= m) {
			l->add(ind,x);
		}
		else {
			r->add(ind,x);
		}
	}

	ll getsum(int st, int en) {
        if (en < st) return 0LL;
		//if completely included
		if (st <= s && e <= en) {
			return sum;
		}
		ll ret = 0LL;
		if (st <= m) {
			ret += l->getsum(st,en);
		}
		if (en > m) {
			ret += r->getsum(st,en);
		}
		return ret;
	}
};

vector<int> aa, bb;

ll calc(int meet, Node* sa, Node* sb) {
    auto it1 = upper_bound(aa.begin(),aa.end(),meet);
    int idx = (int)(distance(aa.begin(),it1)) - 1;
    ll diff1 = 1LL*(idx+1)*meet - sa->getsum(0,idx);
    auto it2 = lower_bound(bb.begin(),bb.end(),meet);
    idx = m - (int)(distance(it2,bb.end()));
    ll diff2 = sb->getsum(idx,m-1) - 1LL*(m-idx)*meet;
    return diff1+diff2;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    sort(a,a+n);
    sort(b,b+m);
    /*
    int ar = n - 1;
    while (a[ar] >= b[m-1]) {
        ar--;
        if (ar == -1) break;
    }
    int bl = 0;
    while (b[bl] <= a[0]) {
        bl++;
        if (bl == m) break;
    }
    if (ar == -1 || bl == m) {
        cout << 0 << '\n';
        return 0;
    }
    */
    for (int i = 0; i < n; i++) {
        aa.push_back(a[i]);
    }
    for (int i = 0; i < m; i++) {
        bb.push_back(b[i]);
    }
    n = aa.size(), m = bb.size();
    Node *sa = new Node(0,n-1), *sb = new Node(0,m-1);
    for (int i = 0; i < n; i++) {
        sa->add(i,aa[i]);
    }
    for (int i = 0; i < m; i++) {
        sb->add(i,bb[i]);
    }

    int lo = -1, hi = 1e9+5;
    while (true) {
        int mid = (lo+hi)/2;
        ll a1 = calc(mid-1,sa,sb), a2 = calc(mid,sa,sb), a3 = calc(mid+1,sa,sb);
        if (a2 <= a1 && a2 <= a3) {
            cout << a2 << '\n';
            return 0;
        }
        else if (a3 >= a1) {
            hi = mid;
        }
        else {
            lo = mid;
        }
    }

    return 0;
}
	

