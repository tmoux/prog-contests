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
    string s; cin >> s;
    for (int i = 0; i < s.size(); i++) {
        if (s.substr(i,7) == "1111111" || s.substr(i,7) == "0000000") {
            cout << "YES" << '\n';
            return 0;
        }
    }
    cout << "NO\n";


    return 0;
}
	

