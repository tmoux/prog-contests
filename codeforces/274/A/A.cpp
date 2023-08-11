#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_set>
using namespace std;
typedef long long ll;

int n, k;
const int maxn = 100005;
unordered_set<ll> s;
ll A[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    sort(A,A+n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (!(A[i] % k == 0 && s.find(A[i]/k) != s.end())) {
            ans++;
            s.insert(A[i]);
        }
    }
    cout << ans << '\n';

    return 0;
}
	

