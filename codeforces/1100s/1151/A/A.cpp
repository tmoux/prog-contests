#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const string pattern = "ACTG";
int n;
string s;

int g(const string& a, const string& b) {
    assert(a.size() == b.size());
    int r = 0;
    for (int i = 0; i < a.size(); i++) {
        int d = a[i] > b[i] ? a[i]-b[i] : b[i]-a[i];
        r += min(d,26-d);
    }
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> s;
    int ans = 99;
    for (int i = 0; i <= n - 4; i++) {
        ans = min(ans,g(pattern,s.substr(i,4)));
    }
    cout << ans << '\n';
}

