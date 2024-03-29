#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, q;

pair<int,int> ans[maxn];
int f[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> q;
    deque<int> deq;
    int mx = -1;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        mx = max(mx,ai);
        deq.push_back(ai);
    }
    int offset = -1;

    for (int i = 1; i <= n; i++) {
        /*
        for (int j: deq) {
            cout << j << ' ';
        }
        cout << '\n';
        */

        int a = deq[0];
        int b = deq[1];
        ans[i] = {a,b};
        if (b >= a) {
            swap(a,b);
        }
        deq.pop_front();
        deq.pop_front();
        deq.push_front(a);
        deq.push_back(b);
        if (a == mx) {
            //we are done
            offset = i; 
            for (int j = 1; j < deq.size(); j++) {
                f[j-1] = deq[j];
            }
            break;    
        }
        
    }

    while (q--) {
        ll t; cin >> t;
        if (t <= offset) {
            cout << ans[t].first << ' ' << ans[t].second << '\n';
        }
        else {
            ll m = (t-1-offset) % (n-1);
            cout << mx << ' ' << f[m] << '\n';
        }
    }
}

