#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 305;
int n;

vector<int> ans[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n/2; j++) {
            ans[i].push_back(n*j+i);
        }
        for (int j = n/2; j < n; j++) {
            ans[i].push_back(n*(j+1)-i+1);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j: ans[i]) {
            cout << j << ' ';
        }
        cout << '\n';
    }
}

