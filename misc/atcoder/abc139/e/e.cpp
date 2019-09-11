#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int N, A[maxn][maxn];

vector<pair<int,int>> dir[maxn][maxn];
int in[maxn][maxn];

pair<int,int> mn(pair<int,int> p) {
    if (p.first > p.second) swap(p.first,p.second);
    return p;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N-1; j++) {
            cin >> A[i][j];
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N-2; j++) {
            dir[min(i,A[i][j])][max(i,A[i][j])].push_back(mn({i,A[i][j+1]}));
            in[min(i,A[i][j+1])][max(i,A[i][j+1])]++;
        }
    }
    queue<pair<int,int>> q;
    for (int i = 1; i <= N; i++) {
        for (int j = i+1; j <= N; j++) {
            if (in[i][j] == 0) {
                q.push({i,j});
            }
        }
    }
    queue<pair<int,int>> batch;
    int steps = 0;
    int cnt = 0;
    while (true) {
        steps++;
        while (!q.empty()) {
            auto p = q.front(); q.pop();
            cnt++;
            for (auto j: dir[p.first][p.second]) {
                if (--in[j.first][j.second] == 0) {
                    batch.push(j);
                }
            }
        }
        while (!batch.empty()) {
            auto p = batch.front(); batch.pop();
            q.push(p);
        }

        if (q.empty()) break;
    }
    if (cnt < (N*(N-1))/2) {
        cout << -1 << '\n';
    }
    else {
        cout << steps << '\n';
    }
}

