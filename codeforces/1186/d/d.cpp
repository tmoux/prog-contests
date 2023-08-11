#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
double a[maxn];
int down[maxn], up[maxn];

int ans[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        down[i] = (int)(floor(a[i]));
        up[i] = (int)(ceil(a[i]));
        //cout << down[i] << ' ' << up[i] << endl;
        sum += up[i];
    }
    for (int i = 0; i < n; i++) {
        if (sum == 0) {
            ans[i] = up[i];
        }
        else {
            if (down[i] == up[i]-1) {
                sum--;
                ans[i] = down[i];
            }
            else {
                ans[i] = up[i];
            }
        }
    }
    assert(sum == 0);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }
}

