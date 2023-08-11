#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6+6;
int n, A[maxn], t1[maxn], t2[maxn];

class Node {
public:
	int s, e, m;
	//coverse s,e;
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

	int getsum(int st, int en) {
		//if completely included
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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    cin >> n;
    map<int,int> mp1;
    for (int i = 1; i <= n; i++) {
    	cin >> A[i];
    	mp1[A[i]]++;
    	t1[i] = mp1[A[i]];
    }
    Node* root = new Node(0,n);
    map<int,int> mp2;
    for (int i = n; i >= 1; i--) {
    	mp2[A[i]]++;
    	t2[i] = mp2[A[i]];
    	root->add(t2[i],1);
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
    	root->add(t2[i],-1);
    	ans += root->getsum(1,t1[i]-1);
    }

    cout << ans << '\n';

    return 0;
}