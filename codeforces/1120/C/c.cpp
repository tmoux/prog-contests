#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
int n, a, b;
string s;

//dp[i] = min cost to compress s[i..n]
//dp[i] = min(a+dp[i+1],
//            b+min_j(dp[j]) with s[i..j-1] is a substring
//basically need to find longest string starting at i
//that is a substring of s[1..i-1]
//oh wait it's n=5000, we can just do z-algorithm or smth n times

vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}
int dp[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> a >> b >> s;
    for (int i = n-1; i >= 0; i--) {
        dp[i] = a + dp[i+1];
        string t = s.substr(i) + "#" + s.substr(0,i);
        auto z = z_function(t);
        int longest = 0;
        for (int j = s.size()-i+1; j < z.size(); j++) {
            longest = max(longest,z[j]);
        }
        for (int j = 1; j <= longest; j++) {
            dp[i] = min(dp[i],dp[i+j]+b);
        }
        //cout << i << ": " << dp[i] << endl;
    }
    cout << dp[0] << endl;
}
