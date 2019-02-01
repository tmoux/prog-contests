#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, M;
int indegree[maxn];
vector<int> dir[maxn], rev[maxn];
int order[maxn];
int par[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for (int i = 0; i < N - 1 + M; i++) {
        int a, b; cin >> a >> b;
        dir[a].push_back(b);
        rev[b].push_back(a);
        indegree[b]++;
    }
    queue<int> q;
    for (int i = 1; i <= N; i++) if (indegree[i] == 0) q.push(i);
    int ta = 1;
    while (!q.empty()) {
        int f = q.front(); q.pop();
        order[f] = ta++;
        for (int j: dir[f]) {
            if (--indegree[j] == 0) {
                q.push(j);
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        pair<int,int> best = {-1,0};
        for (int j: rev[i]) {
            if (best.first < order[j]) {
                best.first = order[j];
                best.second = j;
            }
        }
        par[i] = best.second;
    }

    for (int i = 1; i <= N; i++) {
        cout << par[i] << '\n';
    }


    return 0;
}

