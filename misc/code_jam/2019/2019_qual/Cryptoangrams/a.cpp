#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        int N; cin >> N;
        int L; cin >> L;
        vector<ll> p(L);
        for (int i = 0; i < L; i++) {
            cin >> p[i];
        }
        vector<ll> an;
        for (int i = 1; i < L; i++) {
            if (p[i-1] == p[i]) continue;
            an.push_back(__gcd(p[i-1],p[i]));
        }
        sort(an.begin(),an.end());
        an.erase(unique(an.begin(),an.end()),an.end());
        map<ll,char> mp;
        for (int i = 0; i < min((int)an.size(),26); i++) {
            mp[an[i]] = 'A'+i;
            //cout << mp[an[i]] << ": " << an[i] << '\n';
        }
        vector<char> ans;
        int r = sqrt(p[0]);
        int prev;
        if (r*r == p[0]) {

        }
        for (int i = 1; i < L; i++) {
            if (prev ==         
        }
    }
}

