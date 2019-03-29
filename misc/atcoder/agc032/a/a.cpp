#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int N;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    vector<int> b = {0};
    for (int i = 1; i <= N; i++) {
        int bi; cin >> bi;
        b.push_back(bi);
    }
    vector<int> ans;
    while (ans.size() < N) {
        bool found = false;
        for (int i = b.size() - 1; i >= 1; i--) {
            if (b[i] == i) {
                ans.push_back(i);
                b.erase(b.begin()+i);
                found = true;
                break;
            }
        }
        /*
        for (int i: b) {
            cout << i << ' ';
        }
        cout << '\n';
        */
        if (!found) {
            cout << -1 << '\n';
            return 0;
        }
    }
    reverse(ans.begin(),ans.end());
    for (int i: ans) {
        cout << i << '\n';
    }
}

