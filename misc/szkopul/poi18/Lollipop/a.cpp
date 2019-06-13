#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, m; 
int a[maxn], pre[maxn], pos[2*maxn];

pair<int,int> ans[2*maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        char c; cin >> c;
        if (c == 'T') {
            a[i] = 2;
        }
        else a[i] = 1;
        pre[i] = pre[i-1] + a[i];
        pos[pre[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        ans[pre[i]] = {1,i};
    }
    set<int> n1, n2;
    for (int i = 1; i <= pre[n]; i++) {
        if (ans[i] == make_pair(0,0)) {
            if (ans[i+2] == make_pair(0,0)) {
                n2.insert(i);
            }
            else {
                n1.insert(i);
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        while (!n1.empty() && pre[n] - pre[i-1] < *n1.rbegin()) {
            n1.erase(prev(n1.end()));
        }
        while (!n2.empty() && pre[n] - pre[i-1] < *n2.rbegin()) {
            n2.erase(prev(n2.end()));
        }
        /*
        cout << i << ":\n";
        for (int j: n1) {
            cout << j << ' ';
        }
        cout << '\n';
        for (int j: n2) {
            cout << j << ' ';
        }
        cout << '\n';
        */
        if (a[i-1] == 1) {
            //end all of them
            for (int j: n1) {
                ans[j] = {i,pos[pre[i-1]+j]};
            }
            for (int j: n2) {
                ans[j] = {i,pos[pre[i-1]+j]};
            }
            break;
        }
        else {
            //end 1's
            set<int> adds;
            for (int j: n1) {
                ans[j] = {i,pos[pre[i-1]+j]};
                if (j-2 > 0 && ans[j-2] == make_pair(0,0)) {
                    if (n2.count(j-2)) n2.erase(j-2);
                    adds.insert(j-2);
                }
            }
            n1 = adds;
        }
    }

    while (m--) {
        int k; cin >> k;
        if (ans[k] == make_pair(0,0)) {
            cout << "NIE\n";
        }
        else {
            //assert(pre[ans[k].second]-pre[ans[k].first-1] == k);
            cout << ans[k].first << ' ' << ans[k].second << '\n';
        }
    }
}

