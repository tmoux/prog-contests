#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 30005;
int n;
string s;
int d[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        d[i] = s[i]-'0';
    }
    int ans = 0;
    for (int d1 = 0; d1 <= 9; d1++) {
        for (int d2 = 0; d2 <= 9; d2++) {
            for (int d3 = 0; d3 <= 9; d3++) {
                vector<int> v = {d1,d2,d3};
                int p = 0;
                for (int i = 0; i < n; i++) {
                    if (p < 3 && d[i] == v[p]) {
                        p++;
                    }
                }
                if (p == 3) {
                    ans++;
                }
            }
        }
    }
    cout << ans << '\n';
}

