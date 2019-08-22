#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int N;

vector<vector<int>> invl;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int d = N-1; d >= 0; d--) {
        for (int i = 1; i+d <= N; i++) {
            int l = i;
            int r = i+d;
            bool found = 0;
            for (auto v: invl) {
                bool ok = true;
                for (int j = l; j <= r; j++) {
                    if (v[j] == 1) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    for (int j = l; j <= r; j++) {
                        v[j] = 1;
                    }
                    found = true;
                    break;
                }
            }
            if (!found) {
                vector<int> v(N+1,0);
                for (int j = l; j <= r; j++) {
                    v[j] = 1;
                }
                invl.push_back(v);
            }
        }
    }
    cout << invl.size() << '\n';
}

