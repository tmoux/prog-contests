#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//partition tree into m subtrees, s.t.
//# of subtrees with sum(a[i]) > 0 is maximal
//Let's check if winning x subtrees is possible
//start out as all independent, need to merge n-m times
//and maximize # of components w/ positive sum at the end
//Answer is obviously bounded by # w/ positive a[i] in the beginning
//Intuitively, we want to merge + with -, and - with -,
//Since adding two +'s lowers the number
//Conjecture: for any positive component, there is a sequence of merges such that the partial sum is always nonnegative

const int maxn = 3005;
int n, m;
int a[maxn];
vector<int> adj[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            int bi; cin >> bi;
            a[i] = -bi;
        }
        for (int i = 1; i <= n; i++) {
            int wi; cin >> wi;
            a[i] += wi;
        }
        for (int i = 0; i < n; i++) {
            int a, b; cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

    }
}

