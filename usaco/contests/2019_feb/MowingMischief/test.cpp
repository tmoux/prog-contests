#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int N, T;

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
		maxi = max(l->maxi,r->maxi);
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

	ll getsum(int st, int en) {
		push();
		//if completely included
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

ll dp[maxn];
set<int> cnt[maxn];
pair<int,int> pts[maxn];

ll getarea(int i, int j, int x, int y) {
    return 1LL*(i-x)*(j-y);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("mowing.in","r",stdin); freopen("mowing.out","w",stdout);
    cin >> N >> T;
    for (int i = 1; i <= N; i++) {
        cin >> pts[i].first >> pts[i].second;
    }
    pts[N+1] = {T,T};
    sort(pts,pts+N+1,[](pair<int,int> a, pair<int,int> b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second < b.second;
            });
    Node *seg = new Node(0,T);
    cnt[0].insert(0);
    for (int i = 1; i <= N+1; i++) {
        int mxcnt = seg->getmaxi(0,pts[i].second);
        ll mn_area = (ll)(T)*T + 696969;
        int c = 0;
        for (int j: cnt[mxcnt]) {
            if (c > 800) break;
            if (pts[j].second > pts[i].second) {
                mn_area = min(mn_area,dp[j]+getarea(pts[i].first,pts[i].second,pts[j].first,pts[j].second));
            }
            else break;
            c++;
        }
        dp[i] = mn_area;
        cnt[mxcnt+1].insert(i);
        //else cnt[mxcnt+1].push_front(i);
        seg->add(pts[i].second,pts[i].second,mxcnt+1);
        //printf("%d (%d,%d): area = %d, cnt = %d\n",i,pts[i].first,pts[i].second,dp[i],mxcnt+1);
    }
    cout << dp[N+1] << '\n';
    

    return 0;
}

