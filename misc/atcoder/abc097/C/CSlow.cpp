#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;

string s;
int k;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s >> k;
    set<string> substrings;
    for (int i = 0; i < s.size(); i++) {
        for (int len = 1; len <= s.size()-i; len++) {
            string sub = s.substr(i,len);
            substrings.insert(sub);
        }
    }
    
    auto it = substrings.begin();
    for (int i = 0; i < k-1; i++) {
        it++;
    }
    cout << *it << '\n';


    return 0;
}
	

