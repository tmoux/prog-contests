#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; string s; cin >> n >> s;
    char curr = s[0];
    int k = 1;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] != curr) {
            curr = s[i];
            k++;
        }
    }
    cout << min(n,k+2) << '\n';

    return 0;
}
	

