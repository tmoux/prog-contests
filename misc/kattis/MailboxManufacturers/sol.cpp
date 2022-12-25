#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
// dp[k][l][r] = max possible # of crackers needed to determine the answer 
// with k mailboxes, knowing the answer is between [l, r]
int dp[11][101][101];

int f(int k, int l, int r) {
    if (l > r) return 0;
    if (k == 0) return INF;
    int& res = dp[k][l][r];
    if (res != -1) return res;

    res = INF;
    for (int i = l; i <= r; i++) {
        //try i: breaks? go left, with one less mailbox
        int c1 = f(k-1,l,i-1);
        //try i: doesn't break? go right, with same # of mailboxes
        int c2 = f(k,i+1,r);

        res = min(res, i + max(c1,c2));
    }
    return res;
}

int main() {
    int N; cin >> N;
    memset(dp, -1, sizeof dp);
    while (N--) {
        int k, m; cin >> k >> m;
        cout << f(k, 1, m) << '\n';
    }
}
