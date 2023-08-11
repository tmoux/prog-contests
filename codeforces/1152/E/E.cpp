#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, b[maxn], c[maxn];
gp_hash_table<int,multiset<int>> adj;
gp_hash_table<int,int> deg;

void NO() {
    cout << -1 << '\n';
    exit(0);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n - 1; i++) cin >> b[i];
    for (int i = 0; i < n - 1; i++) cin >> c[i];
    set<int> nums;
    for (int i = 0; i < n - 1; i++) {
        if (c[i] < b[i]) {
            NO();
        }
        adj[b[i]].insert(c[i]);
        adj[c[i]].insert(b[i]);
        ++deg[b[i]]; ++deg[c[i]];
        nums.insert(b[i]);
        nums.insert(c[i]);
    }
    int numOdd = 0;
    int startpoint = -1;
    for (int i: nums) {
        if (deg[i]&1) {
            numOdd++;
            startpoint = i;    
        }
    }
    if (numOdd == 0 || numOdd == 2) {
        vector<int> stack, path;
        if (startpoint == -1) startpoint = *nums.begin();
        int cur = startpoint;
        while (!stack.empty() or deg[cur] != 0) {
            if (deg[cur] == 0) {
                path.push_back(cur);
                cur = stack.back();
                stack.pop_back();
            }
            else {
                for (int i: adj[cur]) {
                    stack.push_back(cur);
                    auto it = adj[i].find(cur);
                    adj[i].erase(it);
                    it = adj[cur].find(i);
                    adj[cur].erase(it);
                    deg[i]--;
                    deg[cur]--;
                    cur = i;
                    break;
                }
            }
        }
        path.push_back(cur);
        if (path.size() != n) {
            NO();
        }
        for (int i: path) {
            cout << i << ' ';
        }
        cout << '\n';
    }
    else NO();
}
