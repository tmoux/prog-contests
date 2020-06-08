#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cout << "Case #" << qq << ": ";
        int R, C; cin >> R >> C;
        vector<vector<int>> skill(R,vector<int>(C));
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cin >> skill[i][j];
            }
        }
        vector<vector<pair<int,int>>> Up(R,vector<pair<int,int>>(C));
        vector<vector<pair<int,int>>> Down(R,vector<pair<int,int>>(C));
        vector<vector<pair<int,int>>> Left(R,vector<pair<int,int>>(C));
        vector<vector<pair<int,int>>> Right(R,vector<pair<int,int>>(C));
        vector<vector<bool>> used(R,vector<bool>(C,false));
        //fill in tables
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                Up[i][j] = {i-1,j};
                Down[i][j] = {i+1,j};
                Left[i][j] = {i,j-1};
                Right[i][j] = {i,j+1};
            }
        }

        auto valid = [&](pair<int,int> p) {
            int i = p.first;
            int j = p.second;
            return 0 <= i && i < R && 0 <= j && j < C;
        };
        auto calc = [&](int i, int j) { //returns true if needs to be removed
            int cnt = 0;
            int sum = 0;
            if (valid(Up[i][j])) {
                cnt++;
                sum += skill[Up[i][j].first][Up[i][j].second];
            }
            if (valid(Down[i][j])) {
                cnt++;
                sum += skill[Down[i][j].first][Down[i][j].second];
            }
            if (valid(Left[i][j])) {
                cnt++;
                sum += skill[Left[i][j].first][Left[i][j].second];
            }
            if (valid(Right[i][j])) {
                cnt++;
                sum += skill[Right[i][j].first][Right[i][j].second];
            }
            return skill[i][j]*cnt < sum; //if cnt == 0, returns false
        };

        ll total = 0;
        vector<pair<int,int>> v;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                total += skill[i][j];
                if (calc(i,j)) v.push_back({i,j});
            }
        }

        ll ans = 0;
        for (int round = 1; ; round++) {
            ans += total;            
            if (v.empty()) break;
            for (auto& p: v) {
                int i = p.first;
                int j = p.second;
                used[i][j] = true;
                total -= skill[i][j];
                if (valid(Up[i][j])) {
                    Down[Up[i][j].first][Up[i][j].second] = Down[i][j];
                }
                if (valid(Down[i][j])) {
                    Up[Down[i][j].first][Down[i][j].second] = Up[i][j];
                }
                if (valid(Left[i][j])) {
                    Right[Left[i][j].first][Left[i][j].second] = Right[i][j];
                }
                if (valid(Right[i][j])) {
                    Left[Right[i][j].first][Right[i][j].second] = Left[i][j];
                }
            }

            vector<pair<int,int>> nv;
            for (auto p: v) {
                int i = p.first;
                int j = p.second;
                if (valid(Up[i][j]) && !used[Up[i][j].first][Up[i][j].second] && calc(Up[i][j].first,Up[i][j].second)) {
                    nv.push_back(Up[i][j]);
                }
                if (valid(Down[i][j]) && !used[Down[i][j].first][Down[i][j].second] && calc(Down[i][j].first,Down[i][j].second)) {
                    nv.push_back(Down[i][j]);
                }
                if (valid(Left[i][j]) && !used[Left[i][j].first][Left[i][j].second] && calc(Left[i][j].first,Left[i][j].second)) {
                    nv.push_back(Left[i][j]);
                }
                if (valid(Right[i][j]) && !used[Right[i][j].first][Right[i][j].second] && calc(Right[i][j].first,Right[i][j].second)) {
                    nv.push_back(Right[i][j]);
                }
            }
            sort(nv.begin(),nv.end());
            nv.erase(unique(nv.begin(),nv.end()),nv.end());
            v = nv;
        }
        cout << ans << '\n';
    }
}

