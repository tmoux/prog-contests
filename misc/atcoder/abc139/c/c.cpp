#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int H[maxn];
int ans[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> H[i];
    }
    ans[0] = 0;
    int res = 0;
    for (int i = 1; i < N; i++) {
        if (H[i] <= H[i-1]) {
            ans[i] = ans[i-1] + 1;
        }
        else {
            ans[i] = 0;
        }
        res = max(res,ans[i]);
    }
    cout << res << '\n';
}

