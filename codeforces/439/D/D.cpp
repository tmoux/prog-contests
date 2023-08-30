#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, m, a[maxn], b[maxn];

class Node {
public:
	int s, e, m;
	//covers s,e;
	int sum;
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
    vector<int> aa, bb;
    for (int i = 0; i <= ar; i++) {
        aa.push_back(a[i]);
    }
    for (int i = bl; i <= m-1; i++) {
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

    ll minans = 1e18;
    for (int i = 0; i < n; i++) {
        ll diff1 = 1LL*aa[i]*(i+1) - sa->getsum(0,i);
        auto it = lower_bound(bb.begin(),bb.end(),aa[i]);
        int idx = (int)(distance(bb.begin(),it));
        ll diff2 = sb->getsum(idx,m-1) - 1LL*(m-idx)*aa[i];
        //minans = min(minans,diff1+diff2);
    }

    for (int i = 0; i < m; i++) {
        ll diff1 = sb->getsum(i,m-1) - 1LL*bb[i]*(m-i);
        auto it = lower_bound(aa.begin(),aa.end(),bb[i]);
        int idx = (int)(distance(aa.begin(),it));
        if (it == aa.end()) idx--; 
        ll diff2 = 1LL*bb[i]*(idx+1) - sa->getsum(0,idx);
        minans = min(minans,diff1+diff2);
        //cout << diff1 << ' ' << diff2 << '\n';
    }

    cout << minans << '\n';
    

    return 0;
}
	
