#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    if (n == 1 && m == 2) {
        cout << "YES\n";
        cout << "1\n";
    }
    else if (max(n,m) == 3) {
        cout << "NO\n";
    }
    else {
        bool swp = false;
        if (n > m) {
            swap(n,m);
            swp = true;
        }
        //offset rows
        vector<vector<int>> v;
        for (int i = 0; i < n; i++) {
            vector<int> u;
            for (int j = 0; j < m; j++) {
                u.push_back(i*m + j);
            }
            vector<int> uu;
            //add vector twice
            for (int j = 1; j < m; j += 2) {
                uu.push_back(u[j]);
            }
            for (int j = 0; j < m; j += 2) {
                uu.push_back(u[j]);
            }
            for (int j = 1; j < m; j += 2) {
                uu.push_back(u[j]);
            }
            for (int j = 0; j < m; j += 2) {
                uu.push_back(u[j]);
            }
            
            cout << i << ": ";
            for (int j: uu) {
                cout << j << ' ';
            }
            cout << '\n';
            v.push_back(vector<int>());
            for (int j = i; j < i + m; j++) {
                v[i].push_back(uu[j]);
            }
        }
        return 0;
        if (!swp) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << (v[i][j]+1) << ' ';
                }
                cout << '\n';
            }
        }
        else {
            for (int j = 0; j < m; j++) {
                for (int i = 0; i < n; i++) {
                    cout << (v[i][j]+1) << ' ';
                }
                cout << '\n';
            }
        }
    }
}

