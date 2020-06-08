#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int N;
vector<int> a;

int dist(int i, int j) {
    i %= N;
    j %= N;
    return min(abs(a[i]-a[j]),N-abs(a[i]-a[j]));
}
int fx = 0;
int dp[maxn*2][3];
int f(int i, int j) {
    int& res = dp[i][j];
    if (res != -1) return res;
    if (i >= fx+N) {
        if (j == 0) return res = 3*N;
        else return res = 0;
    }
    if (j == 0) {
        res = dist(i,i-1) + f(i+1,1);
    }
    else if (j == 1) {
        res = min(f(i+1,0),f(i+2,2)+dist(i,i+1));
    }
    else if (j == 2) {
        res = min(dist(i,i-1)+f(i+1,1),f(i+1,0));
    }
    return res;
}

int fix(int i) {
    fx = i;
    for (int j = 0; j <= 2*N; j++) {
        for (int k = 0; k < 3; k++) {
            dp[j][k] = -1;
        }
    }
    return f((i+1)%N,0);
}

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int ai; cin >> ai;
        if (ai == 1) {
            a.push_back(i);
        }
    }
    if (a.size() == 1) {
        cout << -1 << '\n';
    }
    else {
        if (a.empty()) {
            cout << 0 << '\n';
        }
        else if (a.size() == 2) {
            cout << abs(a[0]-a[1]) << '\n';
        }
        else {
            N = a.size();
            int ans = 3*N;
            vector<int> b;
            for (int i = 0; i < N; i++) {
                b.push_back(dist(i,i+1));
            }
            a = b;
            for (int i = 0; i < 3; i++) {
                ans = min(ans,fix(i)); 
            }
            cout << ans << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}
