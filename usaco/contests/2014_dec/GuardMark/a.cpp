#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 21;
const ll INF = 1e18+5;
int N, H;
struct Cow
{
    int height, weight, strength;
} cows[maxn];

int main()
{
    freopen("guard.in","r",stdin); freopen("guard.out","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> H;
    for (int i = 0; i < N; i++) {
        cin >> cows[i].height >> cows[i].weight >> cows[i].strength;
    }
    sort(cows,cows+N,[](const Cow& a, const Cow& b) {
            return a.weight + a.strength > b.weight + b.strength;
            });

    ll ans = -1;
    for (int mask = 1; mask < (1<<N); mask++) {
        bool poss = true;
        //check if possible
        ll minExcess = INF;    
        for (int i = 0; i < N; i++) {
            if (mask & (1<<i)) {
                ll strength = cows[i].strength;
                ll weightAbove = 0;
                for (int j = i + 1; j < N; j++) {
                    if (mask & (1<<j)) weightAbove += cows[j].weight;
                }
                if (weightAbove > strength) {
                    poss = false;
                    break;
                }
                minExcess = min(minExcess,strength-weightAbove);
            }
        }
        if (poss) {
            assert(minExcess != INF);
            ll height = 0LL;
            for (int i = 0; i < N; i++) {
                if (mask & (1<<i)) height += cows[i].height;
            }
            if (height >= H) ans = max(ans,minExcess);
        }
    }

    if (ans == -1) {
        cout << "Mark is too tall\n";    
    }
    else {
        cout << ans << '\n';
    }

    return 0;
}

