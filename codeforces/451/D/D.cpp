#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
string s;

ll aL[2], aR[2], bL[2], bR[2];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s;
    n = s.size();
    for (int i = 1; i <= n; i++) {
        if (s[i-1] == 'a') {
            ++aR[i&1];
        }
        else {
            ++bR[i&1];
        }
    }
    //cout << aR[0] << ' ' << aR[1] << '\n';
    ll odd = 0, even = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i-1] == 'a') {
            --aR[i&1];
            ++aL[i&1];
        }
        else {
            --bR[i&1];
            ++bL[i&1];
        }
        int x = i&1;
        int y = !x;
        //cout << aL[x] << ' ' << aL[y] << ' ' << aR[x] << ' ' << aR[y] << '\n';
        if (s[i-1] == 'a') {
            even += aR[y];
            odd += aR[x];
            odd++;
        }
        else {
            even += bR[y];
            odd += bR[x];
            odd++;
        }
    }
    cout << even << ' ' << odd << '\n';
}

