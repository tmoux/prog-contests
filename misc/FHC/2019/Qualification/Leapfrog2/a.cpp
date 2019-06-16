#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cout << "Case #" << qq << ": ";
        string s; cin >> s;
        int n = s.size();
        int bc = 0;
        for (char c: s) {
            if (c == 'B') bc++;
        }
        bool flag = false;
        if (n == 1) {
            assert(s == "A");
            flag = true;
        }
        else if (bc == n-1) {
            //all filled
            flag = false;
        }
        else if (bc == 0) {
            flag = false;
        }
        else if (bc == 1) {
            if (n == 3) {
                flag = true;
            }
            else flag = false;
        }
        else {
            assert(bc >= 2 && bc < n-1);
            flag = true;
        }
        cout << (flag ? "Y": "N") << '\n';
    }
}

