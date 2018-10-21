#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;

int n, m, k;
int A[100005];
multiset<int> B;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    sort(A,A+n);
    for (int i = 0; i < m; i++) {
        int ai; cin >> ai;
        B.insert(ai);
    }
    for (int i = 0; i < n; i++) {
        auto it = B.lower_bound(A[i]);
        if (it == B.end()) {
            cout << "YES\n";
            return 0;
        }
        B.erase(it);
    }
    cout << "NO\n";


    return 0;
}
	

