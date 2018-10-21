#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    int x = n/4+1;
    for (int i = 0; i < x; i++) {
        cout << 4;
    }
    cout << '\n';
    for (int i = 0; i < x - 1; i++) {
        cout << 5;
    }
    cout << "6\n";

    return 0;
}
	

