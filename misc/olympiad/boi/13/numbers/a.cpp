#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int dig[20];
ll dp[20][11][11][2][2]; //place, 2, 1, under, hasStarted

ll f(int len, int d1, int d2, bool under, bool started) {
    if (len == -1) return 1;
    ll& res = dp[len][d1][d2][under][started];
    if (res >= 0) return res;
    res = 0;
    if (under) {
        if (d1 != 0 && d2 != 0) res += f(len-1,d2,started?0:10,under,started);
        for (int d = 1; d <= 9; d++) {
            if (d == d1 || d == d2) continue;
            res += f(len-1,d2,d,under,true);
        }
    }
    else {
        if (dig[len] > 0 && d1 != 0 && d2 != 0) res += f(len-1,d2,started?0:10,true,started);
        for (int d = 1; d < dig[len]; d++) {
            if (d == d1 || d == d2) continue;
            res += f(len-1,d2,d,true,true);
        }
        if (dig[len] != d1 && dig[len] != d2) 
            res += f(len-1,d2,dig[len],under,true);
    }
    //printf("[%d][%d][%d][%d][%d]: %lld\n",len,d1,d2,under,started,res);
    return res;
}

ll solve(ll x) {
    if (x == -1) return 0;
    memset(dp,-1,sizeof dp);
    int len = 0;
    while (x) {
        dig[len++] = x % 10;
        x /= 10;
    }
    return f(len-1,10,10,false,false);
}

bool isPalindrome(ll x) {
    vector<int> digits;
    while (x > 0) {
        digits.push_back(x % 10);
        x /= 10;
    }
    if (digits.size() <= 1) return false;
    for (int i = 0; i < digits.size()-1; i++) {
        if (digits[i] == digits[i+1]) return true;
    }
    for (int i = 0; i < digits.size()-2; i++) {
        if (digits[i] == digits[i+2]) return true;
    }
    return false;
}

ll check(ll x) {
    ll ans = 0;
    for (ll i = 0; i <= x; i++) {
        if (!isPalindrome(i)) {
            ans++;
            //cout << i << '\n';
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll a, b; cin >> a >> b;
    ll ans = solve(b) - solve(a-1);
    cout << ans << '\n';
    /*
    ll a; cin >> a;
    cout << solve(a) << ' ' << check(a) << '\n';
    */
}

