#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

string plural(string s) {
    char one, two, three;
    if (s.size() > 2) {
        one = s[s.size()-3];
    }
    two = s[s.size()-2];
    three = s[s.size()-1];
    if ((two == 'c' && three == 'h') || three == 'x' || three == 's' || three == 'o') {
        return s+"es";
    }
    else if (three == 'f') {
        return s.substr(0,s.size()-1) + "ves";
    }
    else if (two == 'f' && three == 'e') {
        return s.substr(0,s.size()-2) + "ves";
    }
    else if (three == 'y') {
        return s.substr(0,s.size()-1) + "ies";
    }
    return s+"s";
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("input.in","r",stdin);
    int n; cin >> n;
    while (n--) {
        string s; cin >> s;
        cout << plural(s) << '\n';
    }


    return 0;
}
	

