#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    int n; cin >> n;
    multiset<int> s;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
    	int ai; cin >> ai;
    	s.insert(ai);
    	A[i] = ai;
    }
    sort(A.begin(),A.end());
    int ans = 0;
    for (int i: A) {
    	int m = *s.rbegin();
    	if (m >= 2*i) {
    		auto it = s.find(m);
    		s.erase(it);
    		it = s.find(i);
    		s.erase(it);
    	}
    	else ans++;
    }
    cout << ans << '\n';



    return 0;
}