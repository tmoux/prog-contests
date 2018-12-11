#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    ll total = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];    
        total += a[i];
    }
    ll mn = total/2;



    return 0;
}

