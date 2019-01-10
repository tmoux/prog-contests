#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

#define all(x) begin(x),end(x)

struct Fen {
    int* bit;
    int s;
    vector<int> cols;
    gp_hash_table<int,int> colToIdx;
    void init(int _s) {
        s = _s;
        bit = new int[s+1];
        for (int i = 0; i <= s; i++) bit[i] = 0;
    }
    void init(const vector<int>& _c) {
        s = _c.size();
        cols = _c;
        bit = new int[s+1];
        for (int i = 0; i <= s; i++) bit[i] = 0;

        //indexing
        colToIdx[0] = 0;
        for (int i = 0; i < cols.size(); i++) {
            colToIdx[cols[i]] = i+1;
        }
    }

    void add(int i, int x) {
        for (; i && i <= s; i += i & (-i)) {
            bit[i] += x;
        }
    }

    int sum(int i) {
        if (i == 0) return 0;
        int r = 0;
        for (; i; i -= i & (-i)) {
            r = (r+bit[i]);
        }
        return r;
    }

    int idxForQuery(int i) {
        auto it = upper_bound(all(cols),i);
        if (it == cols.begin()) return 0;
        --it;
        return colToIdx[*it];
    }

    void insertValue(int col, int x) {
    	//assert(colToIdx.count(col));
        int i = colToIdx[col];
        add(i,x);
    }

    int getValue(int col) {
        int i = idxForQuery(col);
        return sum(i);
    }
};

const int maxn = 1e5+5;
int N, K;
int a[maxn], pos[maxn];
int s[4*maxn], e[4*maxn];
vector<int> covers[4*maxn];
Fen seg[4*maxn];
void build(int i, int l, int r) {
	s[i] = l;
	e[i] = r;
	if (l == r) {
		//add y-coordinate
		covers[i].push_back(pos[l]);
		seg[i].init(covers[i]);
	}
	else {
		int m = (l+r)/2;
		build(i*2,l,m);
		build(i*2+1,m+1,r);
		covers[i].reserve(covers[i*2].size()+covers[i*2+1].size());
		merge(all(covers[i*2]),all(covers[i*2+1]),back_inserter<vector<int>>(covers[i]));
		seg[i].init(covers[i]);
	}
}

void add(int i, int x, int y) {
	seg[i].insertValue(y,1);
	if (s[i] == e[i]) return;
	if (x <= (s[i]+e[i])/2) add(i*2,x,y);
	else add(i*2+1,x,y);
}

int getsum(int i, int x0, int x1, int y1) {
	if (x0 <= s[i] && e[i] <= x1) return seg[i].getValue(y1-1);
	int res = 0;
	if (x0 <= (s[i]+e[i])/2) res += getsum(i*2,x0,x1,y1);
	if (x1 > (s[i]+e[i])/2) res += getsum(i*2+1,x0,x1,y1);
	return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("friendcross.in","r",stdin); freopen("friendcross.out","w",stdout);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
    	cin >> a[i];
    }
    for (int i = 1; i <= N; i++) {
    	int ai; cin >> ai;
    	pos[ai] = i;
    }
    build(1,1,N);
    ll ans = 0;

    for (int i = N; i >= 1; i--) {
    	int q = getsum(1,1,N,pos[a[i]]) - getsum(1,max(1,a[i]-K),min(N,a[i]+K),pos[a[i]]);
    	ans += q;
    	//cout << a[i] << ": " << q << '\n';
    	add(1,a[i],pos[a[i]]);
    }
    
    cout << ans << '\n';
    
    

    return 0;
}
