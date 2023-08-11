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
    string res;
    for (int i = 0; i < s.size(); i++) {
        if (res.size() >= 2) {
            if (res[res.size()-1] == s[i] && res[res.size()-2] == s[i]) {
                continue;
            }
            if (res.size() >= 3) {
                if (res[res.size()-3] == res[res.size()-2] && res[res.size()-1] == s[i]) {
                    continue;
                }
            }
        }
        res += s[i];
    }
    cout << res << '\n';

    return 0;
}
	

