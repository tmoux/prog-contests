#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("out","w",stdout);
    cout << 700 << '\n';
    vector<int> as;
    for (int i = 0; i < 700; i++) {
        int r = rand() % (1000000001);
        as.push_back(r);
    }
    sort(as.begin(),as.end());
    for (int i: as) cout << i << ' ';

    return 0;
}
	

