#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6+6;
int N, M;
int previous[maxn];
int dist[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    memset(previous,-1,sizeof previous);
    for (int i = 1; i <= N; i++) dist[i] = 999999999;
    int start, end;
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        if (i == 0) {
            start = a;
            dist[start] = 0;
        }
        if (i == M - 1) end = b;
        if (dist[a] + 1 < dist[b]) {
            dist[b] = dist[a] + 1;
            previous[b] = a;
        }
    }
    int curr = end;
    vector<int> ans;
    while (true) {
        ans.push_back(curr);
        if (curr == start) break;
        curr = previous[curr];
    }
    cout << ans.size()-1 << '\n';
    for (int i = ans.size()-1; i > 0; i--) {
        cout << ans[i] << ' ' << ans[i-1] << '\n';
    }
    
    

    return 0;
}

