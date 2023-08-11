#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, p[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    string s; cin >> s;
    int mn = 0;
    for (int i = 0; i < s.size(); i++) {
        p[i+1] = s[i] == '(' ? 1 : -1;
        p[i+1] += p[i];
        mn = min(mn,p[i+1]);
    }
    if (p[n] != 0) {
        cout << "No\n";
    }
    else {
        if (mn >= -1) {
            cout << "Yes\n";
        }
        else {
            cout << "No\n";
        }
    }
}

