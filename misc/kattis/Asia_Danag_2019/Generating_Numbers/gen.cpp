#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 10005;
int dp[maxn];
int nxt[maxn];

int solve(int x) {
    //cout << x << endl;
    if (x <= 10) return x-1;
    if (dp[x] != -1) return dp[x];
    vector<int> d;
    int c = x;
    while (c > 0) {
        d.push_back(c%10);
        c /= 10;
    }
    sort(d.begin(),d.end());
    if (d[0] == 0) {
        auto it = upper_bound(d.begin(),d.end(),0);
        //assert(it != d.end());
        int s = *it;
        d.erase(it);
        d.insert(d.begin(),s);
    }
    int num = 0;
    for (int i = d.size()-1, mult = 1; i >= 0; i--, mult *= 10) {
        num += d[i]*mult;
    }
    dp[x] = x+5;
    for (int i = 1; i < x; i++) {
        if (x-i+solve(i) < dp[x]) {
            dp[x] = x-i+solve(i);
            nxt[x] = i;
        }
    }
    if (num < x && 1+solve(num) < dp[x]) {
        dp[x] = 1+solve(num);
        nxt[x] = num;
    }
    return dp[x];
}

int count_nonzero(int x) {
    int r = 0;
    while (x > 0) {
        if (x%10 != 0) r++;
        x /= 10;
    }
    return r;
}

int rearrange(int x) {
    vector<int> d;
    int c = x;
    while (c > 0) {
        d.push_back(c%10);
        c /= 10;
    }
    sort(d.begin(),d.end());
    if (d[0] == 0) {
        auto it = upper_bound(d.begin(),d.end(),0);
        //assert(it != d.end());
        int s = *it;
        d.erase(it);
        d.insert(d.begin(),s);
    }
    int num = 0;
    for (int i = d.size()-1, mult = 1; i >= 0; i--, mult *= 10) {
        num += d[i]*mult;
    }
    return num;
}

int solve_t(int x) {
    if (x <= 20) return x-1;
    if (x % 10 == 0 && count_nonzero(x) > 1 || count_nonzero(x-1) == 1 && rearrange(x) < x) {
        return 1+solve_t(rearrange(x));
    }
    return 1+solve_t(x-1);
}

int main() {
    /*
    memset(dp,-1,sizeof dp);
    for (int i = 1; i <= 5000; i++) {
        cout << i << ": " << solve(i) << ' ' << solve_t(i) << endl;
        assert(solve(i) == solve_t(i));
    }
    return 0;
    */
    int t; cin >> t;
    while (t--) {
        int x; cin >> x;
        cout << solve_t(x) << '\n';
    }
}
