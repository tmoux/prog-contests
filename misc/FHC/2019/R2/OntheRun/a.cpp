#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int dist(pair<int,int> a, pair<int,int> b) {
    return abs(a.first-b.first) + abs(a.second-b.second);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    for (int qq = 1; qq <= T; qq++) {
        cout << "Case #" << qq << ": ";
        int N, M, K;
        cin >> N >> M >> K;
        int A, B; cin >> A >> B;
        vector<pair<int,int>> pos;
        for (int i = 0; i < K; i++) {
            int r, c; cin >> r >> c;
            pos.push_back({r,c});
        }
        if (K == 1) {
            cout << "N\n";
        }
        else {
            if (dist({A,B},pos[0]) % 2 == 0 && 
                dist({A,B},pos[1]) % 2 == 0) {
                cout << "Y\n";
            }
            else {
                cout << "N\n";
            }
        }
    }
}

