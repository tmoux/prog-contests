#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n;
vector<int> child[maxn];
int leafs[maxn], cnt[maxn];

void dfs(int i) {
    if (child[i].empty()) leafs[i] = 1;
    for (int j: child[i]) {
        dfs(j);
        leafs[i] += leafs[j];
    }
    cnt[leafs[i]]++;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int pi; cin >> pi;
        child[pi].push_back(i);
    }
    dfs(1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < cnt[i]; j++) {
            cout << i << ' ';        
        }
    }
    cout << '\n';
    return 0;
}
