#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int n;
pair<int,int> obs[maxn], clues[maxn];
map<pair<int,int>,int> cnt;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> obs[i].first >> obs[i].second;
    }
    for (int i = 0; i < n; i++) {
        cin >> clues[i].first >> clues[i].second;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x = obs[i].first + clues[j].first;
            int y = obs[i].second + clues[j].second;
            cnt[make_pair(x,y)]++;
        }
    }
    for (auto p: cnt) {
        if (p.second == n) {
            cout << p.first.first << ' ' << p.first.second << '\n';
            return 0;
        }
    }

    return 0;
}

