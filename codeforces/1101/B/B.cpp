#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int n = s.size();
    int l = -1, r = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '[') {
            l = i;
            break;
        }
    }
    for (int i = n-1; i >= 0; i--) {
        if (s[i] == ']') {
            r = i;
            break;
        }
    }
    if (l == -1 || r == -1) {
        cout << -1 << '\n';
        return 0;
    }
    int lCol = -1, rCol = -1;
    for (int i = l + 1; i < n; i++) {
        if (s[i] == ':') {
            lCol = i;
            break;
        }
    }
    for (int i = r - 1; i > max(lCol,l); i--) {
        if (s[i] == ':') {
            rCol = i;
            break;
        }
    }
    if (lCol == -1 || rCol == -1) {
        cout << -1 << '\n';
        return 0;
    }
    int cnt = 0;
    for (int i = lCol + 1; i < rCol; i++) {
        if (s[i] == '|') cnt++;
    }
    cout << (cnt+4) << '\n';


    return 0;
}

