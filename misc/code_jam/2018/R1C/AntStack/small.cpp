#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
const ll INF = 1e18;
int N;

ll dp[maxn][155]; //dp[i][ans] = min weight;
ll wt[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll mini;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = INF;
		mini = INF;
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
			mini = min(mini,x);
            sum = mini;
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
		mini = min(l->mini,r->mini);
	}

	ll getmini(int st, int en) {
		if (st <= s && e <= en) {
			return mini;
		}
		ll ret = INF+1;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
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

    void del() {
        if (l) l->del();
        if (r) r->del();
        delete this;
    }
};

Node* segs[155];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cin >> N;
        for (int i = 0; i < N; i++) cin >> wt[i];
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j <= min(150,N); j++) {
                dp[i][j] = INF;
            }
        }
        for (int i = 0; i < 150; i++) {
            segs[i] = new Node(0,N-1);    
        }
        int maxans = 1;
        for (int i = 0; i < N; i++) {
            dp[i][1] = 0;
            segs[1]->add(i,0+wt[i]);
            for (int a = 2; a < 150 && i - (a-1) >= 0; a++) {
                ll mn = segs[a-1]->getmini(0,i-1);
                dp[i][a] = mn;
                if (wt[i]*6 >= mn) {
                    segs[a]->add(i,mn+wt[i]);
                    maxans = max(maxans,a);
                    //printf("[%d][%d]: %d\n",i,a,(int)dp[i][a]);
                }
                /*
                for (int j = 0; j < i; j++) {
                    if (wt[i]*6 >= dp[j][a-1] + wt[j]) {
                        dp[i][a] = min(dp[i][a],dp[j][a-1]+wt[j]);
                        maxans = max(maxans,a);
                    }
                }
                */
            }
        }
        //cout << segs[8]->getmini(0,N-1) << '\n';
        for (int i = 0; i < 150; i++) {
            segs[i]->del();
        }
        cout << "Case #" << qq << ": " << maxans << '\n';
    }

}

