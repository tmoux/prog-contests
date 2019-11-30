#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
void madd(int& a, int b) {
    a = (a+b) % M;
}
string s;
const int maxn = 1e5+5;
int dp[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s;
    dp[0] = 1; 
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'm' || s[i] == 'w') {
            //cannot be possible
            cout << 0 << '\n';
            return 0;
        }
        dp[i+1] = dp[i];
        if (i > 0 && ((s[i] == 'u' && s[i-1] == 'u')
                    ||(s[i] == 'n' && s[i-1] == 'n'))) {
            madd(dp[i+1],dp[i-1]);
        }
    }
    cout << dp[s.size()] << '\n';
}

