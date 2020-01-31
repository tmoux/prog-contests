#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, m;
vector<int> msg[maxn];
int mn[maxn], mx[maxn];
int a[maxn];

int bit[maxn];
int on[maxn];
void add(int i, int x) {
    for (; i <= m; i += i & (-i))
        bit[i] += x;
}

int sum(int i) {
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

struct Query
{
    int bucket, l, r, id, bound;

    bool operator<(const Query& rhs) const {
        return bucket != rhs.bucket ? bucket < rhs.bucket : r < rhs.r;
    }
};

int brute(int l, int r, int bound) {
    int res = bound;
    set<int> s;
    for (int i = l; i <= r; i++) {
        if (a[i] >= bound) s.insert(a[i]);
    }
    res += s.size();
    return res;
}

int main() {
    scanf("%d %d\n",&n,&m);
    for (int i = 1; i <= m; i++) {
        scanf("%d",a+i);
        msg[a[i]].push_back(i);
    }
    vector<Query> queries;
    int sz = (int)(sqrt(m)+1);
    for (int i = 1; i <= n; i++) {
        mn[i] = msg[i].empty() ? i : 1;
        msg[i].push_back(m+1);

        for (int j = 0; j < (int)(msg[i].size())-1; j++) {
            queries.push_back({(msg[i][j]+1)/sz,msg[i][j]+1,msg[i][j+1]-1,i,1});
        }
    }
    for (int i = n; i >= 1; i--) {
        mx[i] = sum(msg[i][0]-1) + i;
        add(msg[i][0],1);
    }
    vector<Query> qs;
    for (auto q: queries) {
        if (q.l <= q.r) qs.push_back(q);
    }
    sort(qs.begin(),qs.end());
    int L = 1, R = 1;
    int curr = 0;
    for (Query q: qs) {
        while (L <= q.l) {
            if (--on[a[L]] == 0) {
                curr--;
            }
            L++;
        }
        while (L > q.l) {
            if (++on[a[L-1]] == 1) {
                curr++;
            }
            L--;
        }
        while (R <= q.r) {
            if (++on[a[R]] == 1) {
                curr++;
            }
            R++;
        }
        while (R > q.r + 1) {
            if (--on[a[R-1]] == 0) {
                curr--;
            }
            R--;
        }
        int tr = curr + q.bound;
        mx[q.id] = max(mx[q.id],tr);
    }
    for (int i = 1; i <= n; i++) {
        printf("%d %d\n",mn[i],mx[i]);
    }
}

