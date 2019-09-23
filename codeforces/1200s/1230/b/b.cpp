#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, k;
string s;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    cin >> s;
    if (n == 1) {
        if (k > 0) cout << 0 << '\n';
        else cout << s << '\n';
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (k == 0) continue;
        if (i == 0) {
            if (s[i] == '1') continue;
            s[i] = '1';
            k--;
        }
        else {
            if (s[i] == '0') continue;
            else {
                s[i] = '0';
                k--;
            }
        }
    }
    cout << s << '\n';
}

