#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 55;
int n, m;
int A[maxn][maxn], B[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> A[i][j];
        }
    }
    vector<pair<int,int>> ans;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < m-1; j++) {
            if (A[i][j] == 1 && 
                A[i+1][j] == 1 &&
                A[i][j+1] == 1 && 
                A[i+1][j+1] == 1) {
                ans.push_back({i,j});
                B[i][j] = 1;
                B[i+1][j] = 1;
                B[i][j+1] = 1;
                B[i+1][j+1] = 1;
            }
        }
    }
    bool flag = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] != B[i][j]) {
                flag = false;
                break;
            }
        }
    }
    if (flag) {
        cout << ans.size() << '\n';
        for (auto p: ans) {
            cout << (p.first+1) << ' ' << (p.second+1) << '\n';
        }
    }
    else {
        cout << -1 << '\n';
    }
}

