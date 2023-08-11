#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, A[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    unordered_map<int,int> fir, sec;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        if (fir.count(A[i]) == 0) {
            fir[A[i]] = i;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        if (sec.count(A[i]) == 0) {
            sec[A[i]] = i;
        }
    }
    vector<int> vec1, vec2;
    for (auto& p: fir) {
        vec1.push_back(p.second);
    }
    for (auto& p: sec) {
        vec2.push_back(p.second);
    }
    sort(vec1.begin(),vec1.end());
    sort(vec2.begin(),vec2.end());

    ll ans = 0;
    for (int p: vec1) {
        auto it = upper_bound(vec2.begin(),vec2.end(),p);
        ans += (ll)(distance(it,vec2.end()));
    }
    cout << ans << '\n';

    return 0;
}
	

