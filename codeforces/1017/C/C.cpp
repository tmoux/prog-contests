#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int block = (int)(sqrt(n));
    for (int i = 1; i*block <= n; i++) {
        for (int j = i * block; j > (i-1)*block; j--) {
            cout << j << ' ';
        }
    }
    for (int i = n; i > (n/block)*block; i--) {
        cout << i << ' ';
    }

    return 0;
}
	

