#include <bits/stdc++.h>
using namespace std;
using ll = long long;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;
        int mLeft = 0, mRight = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '<') mLeft++;
            else break;
        }
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '>') mRight++;
            else break;
        }
        cout << min(mLeft,mRight) << '\n';
    }

}

