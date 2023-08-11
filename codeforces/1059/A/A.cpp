#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, L, a; cin >> n >> L >> a;
    vector<pair<int,int>> s(n+2);
    for (int i = 1; i <= n; i++) {
        int ti, li; cin >> ti >> li;
        s[i] = {ti,ti+li};
    }
    s[0] = {0,0};
    s[n+1] = {L,L};
    int r = 0;
    for (int i = 1; i <= n+1; i++) {
        int d = s[i].first - s[i-1].second;
        r += d/a;
    }
    cout << r << '\n';

    return 0;
}

