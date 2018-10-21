#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include <set>
using namespace std;
typedef long long ll;

set<set<char>> se;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    while (n--) {
        string s; cin >> s;
        set<char> as;
        for (int i = 0; i < s.size(); i++) {
            as.insert(s[i]);
        }
        se.insert(as);
    }
    cout << se.size() << '\n';


    return 0;
}
	

