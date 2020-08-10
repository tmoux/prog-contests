#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, b[maxn];
ll a[maxn];
int in[maxn];

ll ans = 0;
vector<int> ord;
queue<int> sources;
vector<int> neg_sources;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        if (b[i] != -1) ++in[b[i]];
    }
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            sources.push(i);
        }
    }
    while (!sources.empty()) {
        int i = sources.front(); sources.pop();
        if (a[i] >= 0) {
            ans += a[i];
            ord.push_back(i);
            if (b[i] != -1) {
                a[b[i]] += a[i];
            }
        }
        else {
            neg_sources.push_back(i);
        }
        if (b[i] != -1) {
            if (--in[b[i]] == 0) {
                sources.push(b[i]);
            }
        }
    }
    reverse(neg_sources.begin(),neg_sources.end());
    for (int i: neg_sources) {
        ans += a[i];
        ord.push_back(i);
    }
    cout << ans << '\n';
    for (auto i: ord) {
        cout << i << ' ';
    }
    cout << '\n';
}
