#include <bits/stdc++.h>
using namespace std;
using ll = long long;


bool canWin(ll s, ll e) {
    if (e % 2 == 1) {
        return s % 2 == 0;
    }
    else {
        ll m = e/2;
        if (m % 2 == 1) m++;
        else m += 2;
        if (m <= s) {
            return s % 2 == 1;
        }
        else {
            ll m2 = m/2;
            if (m2 <= s) return true;
            else {
                return canWin(s,m2-1);
            }
        }
    }
}

bool canLose(ll s, ll e) {
    ll m = e/2;
    if (m < s) {
        return true;
    }
    else {
        if (m % 2 == 1) {
            return s % 2 == 0;
        }
        else {
            ll m2 = m/2;
            if ((m2%2) == (m%2)) m2++;
            if (m2 <= s) {
                return (s%2) == (m2%2);
            }
            else {
                return canLose(s,m2-1);
            }
        }
    }
}

const int maxn = 1e5+5;
int WIN[maxn], LOSE[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    LOSE[0] = 1;
    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        ll s, e; cin >> s >> e;
        WIN[i] = (LOSE[i-1] && canWin(s,e))
              || (WIN[i-1] && !canWin(s,e));
        LOSE[i] = (LOSE[i-1] && canLose(s,e))
              || (WIN[i-1] && !canLose(s,e));
    }
    cout << WIN[t] << ' ' << LOSE[t] << '\n';
}
