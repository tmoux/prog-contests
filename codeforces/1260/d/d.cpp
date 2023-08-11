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
    map<int,int> mx_for_l;
    for (int i = 0; i < k; i++) {
        if (traps[i].d > mn_agility) {
            mx_for_l[traps[i].l] = max(mx_for_l[traps[i].l],traps[i].r);
        }
    }
    int need = 0;
    int mx_seen = 0;
    cout << "x = " << x << '\n';
    cout << "mn agi = " << mn_agility << '\n';
    for (int i = 0; i <= n; i++) {
        if (mx_for_l[i+1] > mx_seen) {
            need += 2*(mx_for_l[i+1]-i);
            mx_seen = max(mx_seen,mx_for_l[i+1]);
        }
        need++;
        cout << i << ", " << mx_for_l[i+1] << ": " << need << '\n';
    }
    cout << x << ": " << need << '\n';
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
    for (int i = m-2; i >= 0; i--) {
        agility[i] = min(agility[i],agility[i-1]);
    }
    for (int i = 0; i < k; i++) {
        cin >> traps[i].l >> traps[i].r >> traps[i].d;
    }
    int l = -1, r = m+1;
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

