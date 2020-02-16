#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int ans[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<pair<int,int>> a;
    vector<int> b;
    for (int i = 0; i < N+1; i++) {
        int ai; cin >> ai;
        a.push_back({ai,i});
    }
    for (int i = 0; i < N; i++) {
        int bi; cin >> bi;
        b.push_back(bi);
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    multiset<int> left, right;
    for (int i = 0; i < N; i++) {
        right.insert(max(0,a[i+1].first-b[i]));
    }
    for (int i = 0; i < N+1; i++) {
        int mx = 0;
        if (!left.empty()) mx = max(mx,*left.rbegin());
        if (!right.empty()) mx = max(mx,*right.rbegin());
        ans[a[i].second] = mx;
        auto it = right.find(max(0,a[i+1].first-b[i]));
        if (it != right.end()) right.erase(it);
        left.insert(max(0,a[i].first-b[i]));
    }
    for (int i = 0; i < N+1; i++) {
        cout << ans[i] << " \n"[i==N];
    }
}
