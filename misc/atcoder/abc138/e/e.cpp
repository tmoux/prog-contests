#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string s, t; 
const int maxn = 1e5+5;
const ll INF = 1LL<<55;
int nxt[2*maxn][26];
ll dist[2*maxn][26];

int n;

void precomp() {
    n = s.size();
    s += s;
    for (int i = s.size()-1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) {
            if (i == s.size()-1) {
                nxt[i][j] = -1;
                dist[i][j] = INF;
            }
            else {
                nxt[i][j] = nxt[i+1][j];
                dist[i][j] = 1 + dist[i+1][j];
            }
        }
        nxt[i][s[i]-'a'] = i % n;
        dist[i][s[i]-'a'] = 0;

        /*
        for (int j = 0; j < 26; j++) {
            cout << i << ' ' << j << ": " << nxt[i][j] << '\n';
        }
        */
    }

}

bool check(ll x) {
    int curr = 0;
    for (int i = 0; i < t.size(); i++) {
        int nx = nxt[curr][t[i]-'a'];
        ll d = dist[curr][t[i]-'a'];
        assert(nx != -1);
        x -= d;
        if (i < t.size()-1) {
            curr = (nx+1) % n;
            x--;
        }
        if (x < 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s >> t;
    //if all letters of t are in s, then it's possible
    set<char> ss;
    for (char c: s) {
        ss.insert(c);
    }
    bool poss = true;
    for (char c: t) {
        if (!ss.count(c)) {
            poss = false;
            break;
        }
    }
    if (!poss) {
        cout << -1 << '\n';
        return 0;
    }
    precomp();
    /*
    cout << check(8) << '\n';
    return 0;
    */
    ll lo = -1, hi = 1e16;
    while (lo + 1 < hi) {
        ll mid = (lo+hi)/2;
        if (check(mid)) {
            hi = mid;
        }
        else lo = mid;
    }
    cout << (hi+1) << '\n';
}

