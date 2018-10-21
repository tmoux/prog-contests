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
    vector<string> res;
    string curr;
    for (int i = 0; i < s.size(); i++) {
        if (s.substr(i,3) == "WUB") {
            i += 2;
            res.push_back(curr);
            curr = "";
        }
        else {
            curr += s[i];
        }
    }
    res.push_back(curr);
    for (string a: res) {
        if (a != "") cout << a << ' ';
    }

    return 0;
}
	

