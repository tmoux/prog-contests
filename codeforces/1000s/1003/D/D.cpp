#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;

const int maxn = 200005;
const int INF = 2000000007;
int n, q;
map<int,int> A;

int query(int bj) {
    int ans = 0;
    for (auto it = A.rbegin(); it != A.rend(); ++it) {
        if (bj == 0) return ans;    
        if (it->first > bj) continue;
        int numSub = bj / it->first;
        int numActual = min(numSub,it->second);
        bj -= numActual * it->first;
        ans += numActual;
    }

    if (bj == 0) return ans;
    else return -1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        A[ai]++;
    }
    
    while (q--) {
        int bj; cin >> bj;
        cout << query(bj) << '\n';
    }
    

    return 0;
}
	

