#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

string a, b;

string smallest(string s) {
    if (s.length() % 2 == 1) return s;
    string s1 = smallest(s.substr(0,s.length()/2));
    string s2 = smallest(s.substr(s.length()/2));
    if (s1 < s2) return s1 + s2;
    else return s2 + s1;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> a >> b;
    cout << (smallest(a) == smallest(b) ? "YES" : "NO") << '\n';

    return 0;
}
	

