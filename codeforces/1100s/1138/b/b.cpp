#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
int n;
int a[maxn], b[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char c; cin >> c;
        a[i] = c-'0';
    }
    for (int i = 1; i <= n; i++) {
        char c; cin >> c;
        b[i] = c-'0';
    }
    map<int,int> cnt;
    for (int i = 1; i <= n; i++) {
        int r = 10*a[i]+b[i];
        cnt[r]++;
    }
    for (auto p: cnt) {
        cout << p.first << ' ' << p.second << '\n';
    }
}
