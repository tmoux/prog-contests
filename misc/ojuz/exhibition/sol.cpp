#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, M;
int frames[maxn];
int dp[maxn];

struct SegDyn
{
	int s, e, m; //represents range [s,e]
	SegDyn *l, *r;
	int sum; //sum for this interval
	SegDyn(int _s, int _e) {
		s = _s;
		e = _e;
		m = (s+e)/2;
		l = NULL;
		r = NULL;
		sum = 0;
	}

	void prepareL() { if (l == NULL) l = new SegDyn(s,m); }
	void prepareR() { if (r == NULL) r = new SegDyn(m+1,e); }

	void pull() {
		sum = 0;
		if (l) sum = max(sum,l->sum);
		if (r) sum = max(sum,r->sum);
	}

	void add(int idx, int x) { //a[idx] = max(a[idx],x)
		//cout << s << ' ' << e << '\n';
		if (s == e && s == idx) {
			//at the node, stop
			sum = max(sum,x);
			return;
		}
		if (idx <= m) {
			prepareL();
			assert(l);
			l->add(idx,x);
		}
		else {
			prepareR();
			r->add(idx,x);
		}
		pull(); //updates current node based on the children
	}

	int getmax(int se, int en) {
		if (se <= s && e <= en) return sum;
		int res = 0;
		if (l && se <= m) res = max(res,l->getmax(se,en));
		if (r && en > m) res = max(res,r->getmax(se,en));
		return res;	
	}
};

int main()
{
    cin >> N >> M;
    vector<pair<int,int>> pictures;
    for (int i = 0; i < N; i++) {
        int a, b; cin >> a >> b;
        pictures.push_back({a,b});
    }

    sort(pictures.begin(),pictures.end(),[](auto a, auto b) {
            if (a.second != b.second) return a.second < b.second;
            return a.first < b.first;
            });
    for (int i = 1; i <= M; i++) cin >> frames[i];
    sort(frames+1,frames+M+1);

    SegDyn *root = new SegDyn(0,1000000007);
    int ans = 0;            
    for (int i = N - 1; i >= 0; i--) {
        int sz = pictures[i].first;
        if (frames[M] >= sz) {
            dp[i] = root->getmax(sz,1000000007) + 1;
        }
        if (dp[i] < M) root->add(frames[M-dp[i]],dp[i]);
        ans = max(ans,dp[i]);
    }
    cout << ans << '\n';
}

