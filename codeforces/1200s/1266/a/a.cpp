#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    while (n--) {
        string s; cin >> s;
        int sum = 0;
        int even = 0;
        bool has0 = false;
        for (char c: s) {
            sum += c-'0';
            if ((c-'0') % 2 == 0) even++;
            if (c == '0') has0 = true;
        }
        cout << ((sum%3==0&&has0&&even>1)?"red":"cyan") << '\n';
    }
}

