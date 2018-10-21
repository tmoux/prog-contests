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
    int n, m; cin >> n >> m;
    vector<int> A(n);
    map<int,int> mp;
    int mass = 0;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        mp[A[i]]++;
        mass = max(mass,mp[A[i]]);
    }

    for (int i = 1; i < mass; i++) {
    
    }


    return 0;
}
	

