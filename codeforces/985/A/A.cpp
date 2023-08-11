#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;
int n; 
int getPar1(vector<int> v) {
    int ret = 0;
    for (int i = 0; i < v.size(); i++) {
        int sup = 1 + 2*i;
        ret += abs(v[i] - sup);
    }
    return ret;
}

int getPar0(vector<int> v) {
    int ret = 0;
    for (int i = 0; i < v.size(); i++) {
        int sup = 2 + 2*i;
        ret += abs(v[i] - sup);
    }
    return ret;
}


int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<int> v(n/2);
    for (int i = 0; i < n/2; i++) {
        cin >> v[i];
    }
    sort(v.begin(),v.end());
    int ans = min(getPar0(v),getPar1(v));
    cout << ans << '\n';


    return 0;
}
	

