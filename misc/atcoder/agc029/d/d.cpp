#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int H, W, N;

set<int> cols[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> H >> W >> N;
    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        cols[y].insert(x);
    }
    int ans = H;
    int curr = 0;
    for (int i = 1; i <= W; i++) {
        cols[i].insert(H+1);
        curr++;
        while (curr <= H && cols[i].count(curr)) curr++;
        if (curr > H) break;
        ans = min(ans,*cols[i].upper_bound(curr)-1);
    }
    cout << ans << '\n';
}

