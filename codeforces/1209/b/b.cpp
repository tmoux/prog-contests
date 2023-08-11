#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int n;
string s;
int a[maxn], b[maxn];

int cnt[5005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    cin >> s;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    for (int i = 0; i < n; i++) {
        int curr = s[i] == '0' ? 0 : 1;
        for (int t = 0; t < 5005; t++) {
            if (t >= b[i] && (((t-b[i]) % a[i]) == 0)) {
                curr ^= 1;
            }
            //cout << i << " " << t << ": " << curr << '\n';
            cnt[t] += curr;
        }
    }

    int maxans = 0;
    for (int t = 0; t < 5005; t++) {
        //cout << t << ": " << cnt[t] << '\n';
        maxans = max(maxans,cnt[t]);
    }
    cout << maxans << '\n';
}

