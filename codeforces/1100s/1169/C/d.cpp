#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, m, a[maxn];

bool check(int num) {
    int curr = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > curr) {
            int numToEven = m-(a[i]-curr);
            if (numToEven <= num) {
                continue;
            }
            else {
                curr = max(curr,a[i]);
            }
        }
        else {
            int numToEven = curr - a[i];
            if (numToEven <= num) {
                continue;
            }
            else {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    bool poss = true;
    for (int i = 1; i < n; i++) {
        if (a[i+1] < a[i]) {
            poss = false;
            break;
        }
    }
    if (poss) {
        cout << 0 << '\n';
        return 0;
    }
    else {
        int lo = 0, hi = m;
        while (lo + 1 < hi) {
            int mid = (lo+hi)/2;
            if (check(mid)) hi = mid;
            else lo = mid;
        }
        cout << hi << '\n';
    }
}

