#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
//bin search to find max # of soldiers
//decision problem: can we make it with x soldiers?
//only consider traps with danger >= min agility
//go out, disarm the trap, come back, move with squad
const int maxn = 2e5+5;
int m, n, k, t;
vector<int> agility;
struct Trap
{
    int l, r, d;
} traps[maxn];
 
bool check(int x) {
    int mn_agility = agility[x-1];
    vector<pair<int,int>> v;
    for (int i = 0; i < k; i++) {
        if (traps[i].d > mn_agility) {
            v.push_back({traps[i].l,traps[i].r});
        }
    }
    sort(v.begin(),v.end(),[](auto a, auto b) {
            return a.first != b.first ? a.first < b.first : a.second < b.second;
            });
    int need = 0;
    pair<int,int> curr = {1,0};
    for (auto p: v) {
        if (p.first > curr.second) {
            need += 2*(curr.second-(curr.first-1));
            curr = p;
        }
        else {
            curr.second = max(curr.second,p.second);
        }
    }
    need += 2*(curr.second-(curr.first-1));
    need += n+1;

    //cout << x << ": " << need << '\n';
    /*
    cout << x << ", min_agility = " << mn_agility << '\n';
    cout << mx << '\n';
    cout << x << ": " << need << '\n';
    */
    return need <= t;
}
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> m >> n >> k >> t;
    for (int i = 0; i < m; i++) {
        int ai; cin >> ai;
        agility.push_back(ai);
    }
    sort(agility.begin(),agility.end(),greater<int>());
    for (int i = 0; i < k; i++) {
        cin >> traps[i].l >> traps[i].r >> traps[i].d;
    }
    if (!check(1)) {
        cout << 0 << '\n';
        return 0;
    }
    int l = 1, r = m+1;
    while (l + 1 < r) {
        int mid = (l+r)/2;
        if (check(mid)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }
    cout << l << '\n';
}
