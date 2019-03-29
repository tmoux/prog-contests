#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<pair<int,int>> edges;
void add(int a, int b) {
    edges.push_back({a,b});
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    if (N&1) {
        for (int i = 1; i < N; i++) add(i,N);
        for (int i = 1; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (j != N - i) add(i,j);
            }
        }
    }
    else {
        for (int i = 1; i <= N; i++) {
            for (int j = i + 1; j <= N; j++) {
                if (i+j != N+1) add(i,j);
            }
        }
    }
    //output
    cout << edges.size() << '\n';
    for (auto p: edges) {
        cout << p.first << ' ' << p.second << '\n';
    }
}

