#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, maxk = 105;
int N, K, dp[maxn][maxk][2]; //0 --> take whole interval, 1 --> from skip
const int NANA = -2e9;
struct Line {
    int start, end;
    bool operator<(const Line& r) const {
        if (start != r.start) return start < r.start;
        return end > r.end;
    }
} lines[maxn];

int skip[maxn], before[maxn]; //skip to last one that starts before [i] ends

int f(int i, int k, int q) {
    if (dp[i][k][q] != -1) return dp[i][k][q];
    if (i == N) {
        return k == 0 ? 0 : NANA;
    }
    //go to next
    dp[i][k][q] = f(i+1,max(0,k-1),0);
    //take it and skip
    int add;
    if (q == 0) {
        add = lines[i].end - lines[i].start;
    }
    else {
        add = lines[i].end - max(lines[i].start,lines[before[i]].end);
    }
    dp[i][k][q] = max(dp[i][k][q],add+f(skip[i],max(0,k-(skip[i]-i-1)),1));
    return dp[i][k][q];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("lifeguards.in","r",stdin); freopen("lifeguards.out","w",stdout);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> lines[i].start >> lines[i].end;
    }
    sort(lines,lines+N);
    vector<Line> st;
    for (int i = 0; i < N; i++) {
        if (st.empty() || lines[i].end > st.back().end) {
            st.push_back(lines[i]);
        }
        else {
            K--;
        }
    }

    N = st.size();
    queue<pair<int,int>> q;
    for (int i = 0; i < N; i++) {
        lines[i] = st[i];
        skip[i] = i;
        q.push({lines[i].end,i});
        while (lines[i].start > q.front().first) {
            auto f = q.front();
            q.pop();
            skip[q.front().second] = max(skip[q.front().second],skip[f.second]);
        }
        skip[q.front().second] = max(skip[q.front().second],i);
    }
    while (!q.empty()) {
        auto f = q.front();
        q.pop();
        if (!q.empty()) skip[q.front().second] = max(skip[q.front().second],skip[f.second]);
    }
    for (int i = 0; i < N; i++) {
        if (skip[i] == i) skip[i] = i+1;
    }
    for (int i = N - 1; i >= 0; i--) {
        before[skip[i]] = i;
    }
   
    K = max(K,0);
    memset(dp,-1,sizeof dp);
    int ans = f(0,K,0);
    cout << ans << '\n';

    return 0;
}
