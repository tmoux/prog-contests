#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5+5;
int n;
struct Invl
{
    int l, r, id;
};
bool used[N];

int move(int& i, int l, int r) {
    if (l <= i && i <= r) return 0;    
    int ret = 0;
    if (i > r) {
        ret = i-r;
        i = r;
    }
    else if (i < l) {
        ret = l-i;
        i = l;
    }
    else assert(false);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<Invl> u, v;
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        u.push_back({l,r,i});
        v.push_back({l,r,i});
    }
    sort(u.begin(),u.end(),[](auto a, auto b) {
            return a.l > b.l;
            });
    sort(v.begin(),v.end(),[](auto a, auto b) {
            return a.r < b.r;
            });
    /*
    for (auto p: v) {
        cout << p.l << ' ' << p.r << '\n';
    }
    */
    int i = 0, j = 0;
    int curr = 0;
    ll ans = 0;
    while (i < n && j < n) {
        while (i < n && used[v[i].id]) i++;
        if (i < n) {
            ans += move(curr,v[i].l,v[i].r);
            used[v[i].id] = true;
            //cout << "taking " << v[i].l << ' ' << v[i].r << '\n';
        }

        while (j < n && used[u[j].id]) j++;
        if (j < n) {
            ans += move(curr,u[j].l,u[j].r);
            used[u[j].id] = true;
            //cout << "taking " << u[j].l << ' ' << u[j].r << '\n';
        }
        //cout << ans << '\n';
    }
    ans += abs(curr);
    //try other way
    i = j = curr = 0;
    ll ans2 = 0;
    memset(used,0,sizeof used);
    while (i < n && j < n) {
        while (j < n && used[u[j].id]) j++;
        if (j < n) {
            ans2 += move(curr,u[j].l,u[j].r);
            used[u[j].id] = true;
            //cout << "taking " << u[j].l << ' ' << u[j].r << '\n';
        }

        while (i < n && used[v[i].id]) i++;
        if (i < n) {
            ans2 += move(curr,v[i].l,v[i].r);
            used[v[i].id] = true;
            //cout << "taking " << v[i].l << ' ' << v[i].r << '\n';
        }
        //cout << ans << '\n';
    }
    ans2 += abs(curr);

    cout << max(ans,ans2) << '\n';
}

