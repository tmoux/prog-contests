#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int N, K;
char a[maxn];
int pre[maxn];
int dp[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	ll mini;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		mini = maxn;
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
		ll ret = maxn;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
	}	
};
map<int,multiset<int>> rolls;

int main()
{
    freopen("redistricting.in","r",stdin); freopen("redistricting.out","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        pre[i] = a[i] == 'G' ? 1 : -1;
        pre[i] += pre[i-1];
    }
    Node *seg = new Node(0,2*maxn);
    rolls[0].insert(0);
    seg->add(0+maxn,0);
    for (int i = 1; i <= N; i++) {
        /*
        dp[i] = maxn;
        for (int j = max(i-K,0); j < i; j++) {
            int d = (pre[i] - pre[j] >= 0 ? 1 : 0);
            dp[i] = min(dp[i],dp[j] + d); 
        }
        */
        //test to make sure seg tree works
        int i1 = seg->getmini(-maxn+maxn,pre[i]+maxn) + 1;
        int i2 = seg->getmini(pre[i]+1+maxn,maxn+maxn);
        dp[i] = min(i1,i2);
        //printf("dp[%d] = %d, seg says %d\n",i,dp[i],min(i1,i2));
        //update rolling guy
        //first, insert newest one
        rolls[pre[i]].insert(dp[i]);
        seg->add(pre[i]+maxn,*rolls[pre[i]].begin());
        //then delete oldest one
        if (i-K >= 0) {
            auto it = rolls[pre[i-K]].find(dp[i-K]);
            assert(it != rolls[pre[i-K]].end());
            rolls[pre[i-K]].erase(it);
            if (rolls[pre[i-K]].empty()) {
                seg->add(pre[i-K]+maxn,maxn);    
            }
            else {
                seg->add(pre[i-K]+maxn,*rolls[pre[i-K]].begin());
            }
        }
    }
    cout << dp[N] << '\n';

    return 0;
}

