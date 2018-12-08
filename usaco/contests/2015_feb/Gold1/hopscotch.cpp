#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x),end(x)
typedef long long ll;

const int M = 1e9+7;
const int maxn = 755;

struct Fen {
    int* bit;
    int s;
    vector<int> cols;
    map<int,int> colToIdx;
    void init(int _s) {
        s = _s;
        bit = new int[s+1];
        for (int i = 0; i <= s; i++) bit[i] = 0;
    }
    void init(const vector<int>& _c) {
        s = _c.size();
        cols = _c;
        sort(all(cols));
        cols.erase(unique(all(cols)),cols.end());
        bit = new int[s+1];
        for (int i = 0; i <= s; i++) bit[i] = 0;

        //indexing
        colToIdx[0] = 0;
        for (int i = 0; i < cols.size(); i++) {
            colToIdx[cols[i]] = i+1;
        }
    }

    void add(int i, int x) {
        for (; i <= s; i += i & (-i))
            bit[i] = (bit[i]+x) % M;
    }

    int sum(int i) {
        if (i == 0) return 0;
        int r = 0;
        for (; i; i -= i & (-i)) {
            r = (r+bit[i]) % M;
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
        int i = colToIdx[col];
        add(i,x);
    }

    int getValue(int col) {
        int i = idxForQuery(col);
        return sum(i);
    }
};
  

int R, C, K, a[maxn][maxn]; //a[i][j] is one-indexed
Fen cols;
Fen nums[maxn*maxn];

int main()
{
    freopen("hopscotch.in","r",stdin); freopen("hopscotch.out","w",stdout);
    scanf("%d %d %d",&R,&C,&K);
    map<int,vector<int>> mp;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf("%d",&a[i][j]);
            mp[a[i][j]].push_back(j);
        }
    }
    //init fenwick trees
    cols.init(C);
    for (auto& p: mp) {
        nums[p.first].init(p.second);
    }
    cols.add(1,1);
    nums[a[1][1]].insertValue(1,1);
    //dp down rows, right-to-left cols 
    int ans;
    for (int i = 2; i <= R; i++) {
        for (int j = C; j >= 2; j--) {
            int se = cols.sum(j-1);
            int subtract = nums[a[i][j]].getValue(j-1);
            se = (se - subtract + M) % M;
            //update bits
            cols.add(j,se);
            nums[a[i][j]].insertValue(j,se);

            if (i == R && j == C) {
                ans = se;
                break;
            }
        }
    }
    printf("%d\n",ans);
}