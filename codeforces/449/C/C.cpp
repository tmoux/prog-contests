#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
bool used[maxn];
bool prime(int x) {
    for (int i = 2; i*i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<pair<int,int>> ans;
    for (int i = 3; i <= n/2; i += 2) {
        if (used[i] || !prime(i)) continue;
        int cnt = 0;
        for (int j = i; j <= n; j += i) {
            if (!used[j]) {
                cnt++;
            }
        }
        pair<int,int> curr = {0,0};
        for (int j = i; j <= n; j += i) {
            if (used[j] || (j == 2*i && cnt%2 == 1)) continue;
            if (curr.first == 0) curr.first = j;
            else {
                curr.second = j;
                ans.push_back(curr);
                curr = {0,0};
            }
            used[j] = true;
        }
    }
    pair<int,int> curr = {0,0};
    for (int i = 2; i <= n; i += 2) {
        if (used[i]) continue;
        if (curr.first == 0) curr.first = i;
        else {
            curr.second = i;
            ans.push_back(curr);
            used[curr.first] = true;
            used[curr.second] = true;
            curr = {0,0};
        }
    }

    //output
    cout << ans.size() << '\n';
    for (auto p: ans) {
        cout << p.first << ' ' << p.second << '\n';
    }

    return 0;
}

