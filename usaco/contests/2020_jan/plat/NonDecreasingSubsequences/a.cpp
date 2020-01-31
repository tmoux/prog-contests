#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}

struct QNode
{
    vector<vector<int>> dp;
};

QNode merge(const QNode& a, const QNode& b) {
    int s = a.dp.size();
    QNode ret;
    ret.dp.resize(s,vector<int>(s,0));
    for (int i = 1; i < s; i++) {
        for (int j = i; j < s; j++) {
            ret.dp[i][j] = a.dp[i][j];
            madd(ret.dp[i][j],b.dp[i][j]);
            int right = 0;
            for (int k = j; k >= i; k--) {
                madd(right,b.dp[k][j]);
                madd(ret.dp[i][j],mult(a.dp[i][k],right));
            }
        }
    }
    return ret;
}

const int maxn = 50005, maxk = 21;
int N, K, Q;
int A[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
    QNode sum;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
        sum.dp.resize(K+1,vector<int>(K+1,0));
		if (s != e) {
			m = (s+e)/2;
			l = new Node(s,m);
			r = new Node(m+1,e);
            sum = merge(l->sum,r->sum);
		}
		else {
            sum.dp[A[s]][A[s]] = 1;
			l = NULL;
			r = NULL;
		}
	}

    /*
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
    */

	QNode getsum(int st, int en) {
		if (st <= s && e <= en) {
			return sum;
		}
		QNode ret;
        ret.dp.resize(K+1,vector<int>(K+1,0));
		if (st <= m) {
            ret = merge(ret,l->getsum(st,en));
		}
		if (en > m) {
            ret = merge(ret,r->getsum(st,en));
		}
		return ret;
	}
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("nondec.in","r",stdin); freopen("nondec.out","w",stdout);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    Node *root = new Node(1,N);
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int l, r; cin >> l >> r;
        QNode ret = root->getsum(l,r);
        int ans = 1;
        for (int i = 1; i <= K; i++) {
            for (int j = i; j <= K; j++) {
                madd(ans,ret.dp[i][j]);
            }
        }
        cout << ans << '\n';
    }
}

