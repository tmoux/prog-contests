#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
using namespace std;
typedef long long ll;

int n, k, A[2005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    vector<pair<int,int>> vec;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        vec.push_back({a,i});
    }
    sort(vec.begin(),vec.end());
    int ans = 0;
    for (int i = n - 1; i >= n - k; i--) {
        A[vec[i].second] = 1;
        ans += vec[i].first;
    }
    vector<int> as;
    int curr = 0;
    for (int i = 0; i < n; i++) {
        curr++;
        if (A[i] == 1) {
            as.push_back(curr);
            curr = 0;
        }
    }
    as.back() += curr;

    //output
    cout << ans << '\n';
    for (int i: as) {
        cout << i << ' ';
    }

    return 0;
}
	

