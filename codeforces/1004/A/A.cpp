#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;

set<int> seen;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, d; cin >> n >> d;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int newx = A[i] - d;
        if (seen.find(newx) != seen.end()) continue;
        int mindist = d;
        for (int j = 0; j < n; j++) {
            mindist = min(mindist,abs(A[j]-newx));
        }
        if (mindist == d) {
            ans++;
        }
        seen.insert(newx);
    }
    for (int i = 0; i < n; i++) {
        int newx = A[i] + d;
        if (seen.find(newx) != seen.end()) continue;
        int mindist = d;
        for (int j = 0; j < n; j++) {
            mindist = min(mindist,abs(A[j]-newx));
        }
        if (mindist == d) {
            ans++;
        }
        seen.insert(newx);
    }
    cout << ans << '\n';

    return 0;
}
	

