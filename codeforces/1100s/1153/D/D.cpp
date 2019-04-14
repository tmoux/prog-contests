#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n;
vector<int> child[maxn];
bool isMax[maxn];
int discard = 0;
int leafs[maxn];

void DFS(int i) {
    for (int j: child[i]) 
        DFS(j);
    if (child[i].empty()) leafs[i] = 1;
    else {
        if (isMax[i]) {
            //take the smallest child leafs number,
            //discard the rest
            int minLeafs = maxn + 5;
            int total = 0;
            for (int j: child[i]) {
                total += leafs[j];
                minLeafs = min(minLeafs,leafs[j]);
            }
            discard += (total-minLeafs);
            leafs[i] = minLeafs;
        }
        else {
            leafs[i] = 0;
            for (int j: child[i]) {
                leafs[i] += leafs[j];
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> isMax[i];
    for (int i = 2; i <= n; i++) {
        int ai; cin >> ai;
        child[ai].push_back(i);
    }
    DFS(1);
    int ans = 1 + discard;
    cout << ans << '\n';
}

