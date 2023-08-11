#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;

string s1, s2;
//plan: Find periods of s1 and s2, and find the size of their intersection

bool isPeriod(const string& s, int len) {
    string s1 = s.substr(0,len);
    for (int i = len; i < s.size(); i+= len) {
        string t = s.substr(i,len);
        if (s1 != t) return false;
    }
    return true;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s1 >> s2;
    set<string> set1;
    for (int i = 1; i <= s1.size(); i++) {
        if (s1.size() % i == 0) {
            if (isPeriod(s1,i)) set1.insert(s1.substr(0,i));
        }
    }

    int ans = 0;
    for (int i = 1; i <= s1.size(); i++) {
        if (s2.size() % i == 0) {
            if (set1.find(s2.substr(0,i)) != set1.end() && isPeriod(s2,i)) {
                ans++;
            }
        }
    }
    cout << ans << '\n';
   

    return 0;
}
	

