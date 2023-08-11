#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, k;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    string s; cin >> s;
    map<char,int> cnt;
    for (int i = 0; i < n-k+1;) {
        bool poss = true;
        for (int j = i + 1; j < i+k; j++) {
            if (s[j] != s[i]) {
                poss = false;
                i = j;
                break;
            }
        }
        if (poss) {
            cnt[s[i]]++;
            i += k;
        }
    }
    int x = 0;
    for (auto p: cnt) {
        x = max(x,p.second);
    }
    cout << x << '\n';

    return 0;
}

