#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1000006;
int a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    for (int i = 0; i < s.size(); i++) {
        a[i+1] = s[i]-'0';
    }
    int ans = 0;
    for (int i = s.size(); i >= 1; i--) {
        if (a[i] == 10) {
            a[i] = 0;
            a[i-1]++;
        }
        else if (a[i] == 5) {
            if (a[i-1] >= 5) {
                a[i-1]++;
                ans += 5;
            }
            else {
                ans += 5;
            }
        }
        else if (a[i] < 5) {
            ans += a[i];
        }
        else if (a[i] > 5) {
            ans += 10-a[i];
            a[i-1]++;
        }
    }
    ans += a[0];
    cout << ans << endl;
}

