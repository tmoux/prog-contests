#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int inv[maxn];
int n, p[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        inv[p[i]] = i;
    }
    set<int> pos;
    pos.insert(inv[n]);
    ll sum = 0;
    for (int i = n-1; i >= 1; i--) {
        int curpos = inv[i];
        auto lb = pos.lower_bound(curpos);
        auto ub = pos.lower_bound(curpos);
        int l1 = 0, l2 = 0;
        if (lb != pos.begin()) {
            --lb;
            l1 = *lb;    
            if (lb != pos.begin()) {
                --lb;
                l2 = *lb;
            }
        }
        
        int r1 = n+1, r2 = n+1;
        if (ub != pos.end()) {
            r1 = *ub;
            ++ub;
            if (ub != pos.end()) {
                r2 =*ub;
            }
        }
        
        sum += 1LL*i*(r2-r1)*(curpos-l1);
        sum += 1LL*i*(l1-l2)*(r1-curpos);
        
        pos.insert(curpos);
    }
    cout << sum << '\n';
}

