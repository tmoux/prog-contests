#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//Attack: X >= Y, get X-Y
//Defense: X > Y, get 0
//So choose the weakest attack cards, 
//then the weakest defense cards

const int maxn = 105;
int n, m;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    multiset<int> attack, defense, my;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        int t; cin >> t;
        if (s == "ATK") attack.insert(t);
        else defense.insert(t);
    }
    for (int i = 0; i < m; i++) {
        int t; cin >> t;
        my.insert(t);
    }
    //only ATTACK
    int ans = 0;
    multiset<int> a = my, b = attack;
    int r1 = 0;
    while (!a.empty()) {
        int f = *a.rbegin(); a.erase(prev(a.end()));
        if (b.empty()) continue;
        else if (f >= *b.begin()) {
            r1 += f-*b.begin();
            b.erase(b.begin());
        }
    }
    //cout << "first ans = " << r1 << '\n';
    ans = max(ans,r1);
    //now try destroying everything
    int r2 = 0;
    bool poss = true;
    while (!defense.empty()) {
        int f = *defense.begin();
        auto it = my.upper_bound(f);
        if (it == my.end()) {
            poss = false;
            break;
        }
        else {
            defense.erase(defense.begin());
            my.erase(it);
        }
    }
    if (poss) {
        while (!my.empty()) {
            int f = *my.rbegin();
            my.erase(prev(my.end()));
            if (attack.empty()) r2 += f;
            else {
                int g = *attack.rbegin();
                if (f >= g) {
                    attack.erase(prev(attack.end()));
                    r2 += f-g;
                }
                else {
                    r2 = 0;
                    break;
                }
            }
        }
        ans = max(ans,r2);
    }
    cout << ans << '\n';
}
