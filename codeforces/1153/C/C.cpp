#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n;
string s;
int pre[maxn]; //can never go below 0

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    if (n&1) {
        cout << ":(\n";
        return 0;
    }
    cin >> s;
    s = '#' + s;
    int open = n/2, close = n/2;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '(') open--;
        else if (s[i] == ')') close--;
    }
    for (int i = 1; i <= n; i++) {
        if (s[i] == '?') {
            if (open > 0) {
                s[i] = '(';
                open--;
            }
            else {
                s[i] = ')';
                close--;
            }
        }
        if (s[i] == '(') pre[i] = pre[i-1] + 1;
        if (s[i] == ')') pre[i] = pre[i-1] - 1;
    }
    
    for (int i = 1; i <= n; i++) {
        if (pre[i] < 0) {
            cout << ":(\n";
            return 0;
        }
        if (i < n && pre[i] == 0) {
            cout << ":(\n";
            return 0;
        }
    }
    if (pre[n] != 0) {
        cout << ":(\n";
        return 0;
    }
    cout << s.substr(1) << '\n';
}

