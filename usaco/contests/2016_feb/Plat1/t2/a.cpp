#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
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


	void add(int i, int x) {
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

const int maxn = 1e5+5, MAX = 1e6+6;
map<int,vector<int>> ps;
map<int,int> mp;
int cnt = 1;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("balancing.in","r",stdin); freopen("balancing.out","w",stdout);
    int N; cin >> N;
    Node *lseg = new Node(0,maxn), *rseg = new Node(0,maxn);
    vector<pair<int,int>> vs;
    for (int i = 0; i < N; i++) {
    	int x, y; cin >> x >> y;
    	vs.push_back(make_pair(y,x));
    }
    sort(vs.begin(),vs.end());
    for (auto p: vs) {
    	int y_c;
    	if (mp.count(p.first)) y_c = mp[p.first];
    	else {
    		y_c = cnt;
    		mp[p.first] = cnt;
    		cnt++;
    	}
    	rseg->add(y_c,1);
    	ps[p.second].push_back(y_c);
    }

    int ans = N;
    for (auto& p: ps) {
    	for (int y: p.second) {
    		lseg->add(y,1);
    		rseg->add(y,-1);
    	}
    	int lo = 0, hi = maxn;
    	while (lo + 1 < hi) {
    		int m = (lo+hi)>>1;
    		int a1 = max(lseg->getsum(m+1,maxn),rseg->getsum(m+1,maxn));
    		int a2 = max(lseg->getsum(0,m),rseg->getsum(0,m));
    		ans = min(ans,max(a1,a2));
    		if (a1 < a2) {
    			hi = m;
    		}
    		else if (a2 < a1) {
    			lo = m;
    		}
    		else {
    			break;
    		}
    	}
    }
    cout << ans << '\n';
    return 0;
}