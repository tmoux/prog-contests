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
    int n; cin >> n;
    while (n--) {
        string s; cin >> s;
        if (s.size() <= 10) {
            cout << s << '\n';
        }
        else {
            cout << s[0] << (s.size()-2) << s.back() << '\n';
        }
    }


    return 0;
}
	

