#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
#include <map>
using namespace std;
typedef long long ll;

struct Obj
{
    int first;
    ll second;
    int orig;
    bool operator<(const Obj& rhs) {
        return first < rhs.first;
    }
};

const int maxn = 100005;
int n, k;
Obj A[maxn];
multiset<ll> s;
ll ans[maxn];
//first = power, second = numcoins

ll countCoins() {
    ll ans = 0;
    int a = 0;
    for (auto it = s.rbegin(); it != s.rend() && a < k; ++it) {
        ans += *it;
        a++;
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int pi; cin >> pi;
        A[i].first = pi;
    }
    for (int i = 0; i < n; i++) {
        ll pi; cin >> pi;
        A[i].second = pi;
        A[i].orig = i;
    }
    sort(A,A+n);
    for (int i = 0; i < n; i++) {
        ans[A[i].orig] = A[i].second + countCoins();
        s.insert(A[i].second);
    }
    //output
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }

    return 0;
}
	

