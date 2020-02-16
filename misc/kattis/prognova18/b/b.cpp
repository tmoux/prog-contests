#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;
int n;
char grid[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    multiset<int> curr, nnew;
    for (int i = 0; i < n; i++) curr.insert(0);
    for (int j = 0; j < n; j++) {
        //cout << j << endl;
        vector<int> v;
        for (int i = 0; i < n; i++) {
            v.push_back(grid[i][j]=='('?1:-1);
        }
        sort(v.begin(),v.end(),greater<int>());
        //cout << "OK" << endl;
        nnew.clear();
        for (int i: v) {
            if (*curr.begin() + i < 0) {
                cout << "No\n";
                return 0;
            }
            else {
                nnew.insert(*curr.begin()+i);
                curr.erase(curr.begin());
            }
        }
        curr = nnew;
    }
    for (int i: curr) {
        if (i != 0) {
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
}

