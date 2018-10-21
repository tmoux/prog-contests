#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 200003;
const int maxa = 21;
int n, a, b;

ll llexp(ll n, int b, int exp) {
    ll res = 1;
    for (;;) {
        if (exp&1) {
            res *= b;
        }
        exp >>= 1;
        if (!exp) break;
        b *= b;
    }

    return n*res;
}
struct Creature
{
    ll hp, dmg;
    bool operator<(const Creature& rhs) const {
        return (hp-dmg) > (rhs.hp-rhs.dmg);
    }
} arr[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //read input
    //freopen("in","r",stdin);
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) {
        ll hpi, dmgi;
        cin >> hpi >> dmgi;
        arr[i] = {hpi,dmgi};
    }
    sort(arr,arr+n);
    //compute total, max for each value try putting all 'a' spells on it
    //this is assuming there is at least one 'b' spell. Otherwise, break
    ll total = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        if (i < b) {
            total += max(arr[i].hp,arr[i].dmg);
        }
        else {
            total += arr[i].dmg;
        }
    }
    ans = total;
    ll smallestDiff = 0;
    if (b > 0) {
        smallestDiff = max(smallestDiff,arr[b-1].hp-arr[b-1].dmg);
    }
    for (int i = 0; i < n && b > 0; i++) {
        ll curr = total;
        if (i < b) {
            curr -= max(arr[i].hp,arr[i].dmg);
        }
        else {
            curr -= smallestDiff;
            curr -= arr[i].dmg;
        }
        ll newhp = llexp(arr[i].hp,2,a);
        curr += newhp;
        ans = max(ans,curr);
        //cout << curr << '\n';
    }
    //output
    cout << ans << '\n';

    return 0;
}
	

