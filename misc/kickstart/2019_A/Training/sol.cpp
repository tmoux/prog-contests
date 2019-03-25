#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
ll skill[maxn], pre[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int q = 1; q <= t; q++) {
        int N, P; cin >> N >> P;
        memset(skill,0,sizeof skill);
        memset(pre,0,sizeof pre);
        for (int i = 1; i <= N; i++) {
            cin >> skill[i];
        }
        sort(skill+1,skill+N+1);
        pre[1] = skill[1];
        for (int i = 2; i <= N; i++) {
            pre[i] = pre[i-1] + skill[i];
        }
        ll minans = 1e18;
        for (int i = P; i <= N; i++) {
            ll need = (skill[i]*P) - (pre[i] - pre[i-P]);
            minans = min(minans,need);
        }
        cout << "Case #" << q << ": " << minans << '\n';
    }
}

