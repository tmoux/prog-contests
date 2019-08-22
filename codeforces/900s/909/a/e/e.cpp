#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, M;
vector<int> dir[maxn];
//top sort the dag
//maintain queue of current

int in[maxn];
bool isCo[maxn];

int ord[maxn]; //top order

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> isCo[i];
    }
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        dir[b].push_back(a);
        in[a]++;
    }
    queue<int> batch;
    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (in[i] == 0) {
            if (isCo[i]) batch.push(i);
            else q.push(i);
        }
    }
    int cnt = 0;
    int ans = 0;
    while (cnt < N) {
        while (!q.empty()) {
            int f = q.front(); q.pop();
            cnt++;
            for (int j: dir[f]) {
                if (--in[j] == 0) {
                    if (!isCo[j]) {
                        q.push(j);
                    }
                    else {
                        batch.push(j);
                    }
                }
            }
        }
        if (cnt == N) break;
        assert(!batch.empty());
        while (!batch.empty()) {
            int f = batch.front(); batch.pop();
            cnt++;
            for (int j: dir[f]) {
                if (--in[j] == 0) {
                    if (!isCo[j]) {
                        q.push(j);
                    }
                    else {
                        batch.push(j);
                    }
                }
            }
        }
        ans++;
    }
    cout << ans << '\n';
}

