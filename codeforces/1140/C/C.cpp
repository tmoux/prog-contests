#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
struct Song
{
    ll len, beauty;
};

vector<Song> songs;
int n, k;

struct ms
{
    multiset<ll> m;
    ll sum = 0;
    void insert(ll x) {
        if (m.size() < k) {
            m.insert(x);
            sum += x;
        }
        else {
            m.insert(x);
            sum += x;
            int mn = *m.begin();
            sum -= mn;
            m.erase(m.begin());
        }
    }
    ll getsum() {
        return sum;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int t, b; cin >> t >> b;
        songs.push_back({t,b});
    }
    sort(songs.begin(),songs.end(),[](auto a, auto b) {
            if (a.beauty != b.beauty) return a.beauty > b.beauty;
            return a.len > b.len;
            });
    ms aa;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int currB = songs[i].beauty;
        aa.insert(songs[i].len);
        while (i + 1 < n && songs[i+1].beauty == currB) {
            aa.insert(songs[i+1].len);    
            i++;
        }
        ans = max(ans,1LL*currB*aa.getsum());
    }
    cout << ans << '\n';
}

