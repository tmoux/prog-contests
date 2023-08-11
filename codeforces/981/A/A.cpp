#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

bool isPalindrome(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != s[s.size()-i-1]) return false;
    }
    return true;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int ans = 0;
    bool keep = true;
    for (int len = s.size(); len > 0 && keep; len--) {
        for (int i = 0; i <= s.size() - len; i++) {
            string sub = s.substr(i,len);
            if (!isPalindrome(sub)) {
                ans = len;
                keep = false;
                break;
            }
        }
    }
    cout << ans << '\n';


    return 0;
}
	

