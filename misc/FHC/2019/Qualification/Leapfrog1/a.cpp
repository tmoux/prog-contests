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
        bool flag = false;
        for (char c: s) {
            if (c == 'B') bc++;
        }
        if (bc < n/2) {
            flag = false;    
        }
        else if (bc == n-1) {
            //all filled, can't win
            flag = false;
        }
        else {
            flag = true;
        }
        cout << (flag ? "Y" : "N") << '\n';
    }

}

