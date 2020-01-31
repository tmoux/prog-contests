#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, maxx = 2e6+6;
int n, m;
int a[maxn];
int prime[maxx];

vector<int> ps;

void sieve() {
    for (int i = 2; i < maxx; i++) prime[i] = 1;
    for (int i = 2; i <= 2000000; i++) {
        if (prime[i]) {
            ps.push_back(i);
            for (int j = 2*i; j <= 2000000; j += i) {
                prime[j] = 0;
            }
        }
    }
}

int ans[maxn];

void pr(int x) {
    cout << "YES\n";
    assert ((m-x) % 2 == 0);
    int aa = (m-x)/2;
    for (int i = 1; i <= n; i++) {
        int inc = 0, dec = 0;
        if (ans[i] <= a[i]) {
            dec = a[i]-ans[i];
        }
        else {
            inc = ans[i]-a[i];
        }
        if (i == 1) {
            inc += aa;
            dec += aa;
        }
        cout << dec << ' ' << inc << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ps.push_back(-1e9);
    sieve();
    ps.push_back(1e9);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll tot = 0;
    for (int i = 1; i <= n; i++) {
        auto it = lower_bound(begin(ps),end(ps),a[i]);
        int hi = *it;
        int lo = *prev(it);
        if (hi-a[i] < a[i]-lo) {
            ans[i] = hi;
            tot += hi-a[i];
        }
        else {
            ans[i] = lo;
            tot += a[i]-lo;
        }
    }
    if (tot <= m) {
        if ((tot % 2) == (m % 2)) {
            pr(tot);
        }
        else {
            int add = 1e9+9;
            int idx = -1, newnum = -1;
            for (int i = 1; i <= n; i++) {
                int change;
                if (a[i] <= 2) {
                    change = 1;
                    if (change < add) {
                        add = change;
                        idx = i;
                        newnum = 3;
                    }
                }
                else {
                    change = (a[i]-2) - abs(a[i]-ans[i]);
                    if (change < add) {
                        add = change;
                        idx = i;
                        newnum = 2;
                    }
                }
            }
            if (tot + add <= m) {
                ans[idx] = newnum;
                pr(tot+add);
            }
            else {
                cout << "NO\n";
            }
        }
    }
    else {
        cout << "NO\n";
    }
}

