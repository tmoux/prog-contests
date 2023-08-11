#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
int a[100005], b[100005];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    if (a[0] != b[0]) {
        cout << "No\n";
    }
    else {
        vector<int> u, v;
        for (int i = 1; i < n; i++) {
            u.push_back(a[i]-a[i-1]);
            v.push_back(b[i]-b[i-1]);
        }
        sort(u.begin(),u.end());
        sort(v.begin(),v.end());
        for (int i = 0; i < u.size(); i++) {
            if (u[i] != v[i]) {
                cout << "No\n";
                return 0;
            }
        }
        cout << "Yes\n";
    }
}

