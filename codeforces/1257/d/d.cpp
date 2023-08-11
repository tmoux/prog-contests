#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+50;
int n, a[maxn];
int m;

int power[maxn]; //max power for given >= endurance

struct Sparse
{
    //sparse table data structure for max
    static const int mk = 17; //change this number based on bounds
    int* tb[mk];
    static inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }
    Sparse(int *a, int n) {
        for (int i = 0; i < mk; i++) {
            tb[i] = new int[n];
        }
        for (int i = 0; i < n; i++) tb[0][i] = a[i];
        for (int k = 1; k <= lg(n); k++) {
            for (int i = 0; i < n; i++) {
                int nx = i + (1<<(k-1));
                if (nx < n) tb[k][i] = max(tb[k-1][i],tb[k-1][nx]);
                else tb[k][i] = tb[k-1][i];
            }
        }
    }
    int getmax(int l, int r) {
        int g = lg(r-l+1);
        return max(tb[g][l],tb[g][r-(1<<g)+1]);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        cin >> m;
        for (int j = 0; j <= n; j++) {
            power[j] = 0;
        }
        for (int j = 0; j < m; j++) {
            int pow, endu; cin >> pow >> endu;
            power[endu] = max(power[endu],pow);
        }
        for (int j = n-1; j >= 0; j--) {
            power[j] = max(power[j],power[j+1]);
        }
        Sparse sp = Sparse(a,n);
        vector<int> dp(n+5,maxn);
        dp[n] = 0;
        bool flag = true;
        for (int i = n-1; i >= 0; i--) {
            int ni = i;
            for (int k = 17; k >= 0; k--) {
                int j = min(n,ni+(1<<k));
                if (power[j-i] >= sp.getmax(i,j-1)) {
                    ni = j;
                }
            }
            if (ni == i) {
                flag = false;
                break;
            }
            dp[i] = dp[ni] + 1;
            //cout << i << ": " << dp[i] << '\n';
        }
        if (!flag) {
            cout << -1 << '\n';
        }
        else {
            cout << dp[0] << '\n';
        }
    }
}

