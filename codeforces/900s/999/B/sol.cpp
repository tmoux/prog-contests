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
    int n; string s;
    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            reverse(s.begin(),s.begin()+i);
        }
    }
    cout << s << '\n';


    return 0;
}
	

