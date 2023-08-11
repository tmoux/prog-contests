#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string a, b; cin >> a >> b;
    int ans = 0;
    if (n == 1) {
        if (a == b) {
            cout << 0 << '\n';
        }
        else {
            cout << 1 << '\n';
        }
        return 0;
    }
    int mid = n/2-1;
    for (int i = 0; i <= mid; i++) {
        char a1 = a[i], a2 = a[n-1-i];
        char b1 = b[i], b2 = b[n-1-i];
        map<int,int> a;
        a[a1]++; a[a2]++;
        a[b1]++; a[b2]++;
        if (a.size() == 4) {
            ans += 2;
        }
        else if (a.size() == 3) {
            ans += 1 + (a1 == a2);
        }
        else if (a.size() == 2) {
            ans += a[a1] != 2;
        }
        
        //cout << a1 << ' ' << a2 << ' ' << b1 << ' ' << b2 << '\n';
        //cout << i << ' ' << ans << '\n';
    }
    if (n % 2) {
        if (a[mid+1] != b[mid+1]) ans++;
    }
    cout << ans << '\n';
    


    return 0;
}
	

