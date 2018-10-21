#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;


int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    set<char> c;
    for (char a: s) {
        c.insert(a);
    }
    cout << (c.size() % 2 ? "IGNORE HIM!" : "CHAT WITH HER!") << '\n';


    return 0;
}
	

