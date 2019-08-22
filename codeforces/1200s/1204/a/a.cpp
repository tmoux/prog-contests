#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int cnt = s.size()-1;
    bool allZeros = true;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] != '0') allZeros = false;
    }
    if (cnt % 2 == 0) {
        //cout << allZeros << '\n';
        if (allZeros) {
            cout << cnt/2 << '\n';
        }
        else {
            cout << (cnt/2+1) << '\n';
        }
    }
    else {
        cout << ((cnt+1)/2) << '\n';
    }
}

