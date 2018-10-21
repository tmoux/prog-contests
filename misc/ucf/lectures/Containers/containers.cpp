#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (true) {
        string s; cin >> s;
        if (s == "end") break;
        set<char> ss;
        for (char c: s) {
            bool found = false;
            for (char top: ss) {
                if (top >= c) {
                    found = true;
                    ss.erase(top);
                    ss.insert(c);
                    break;
                }
            }
            if (!found) {
                ss.insert(c);
            }
        }
        
        printf("Case %d: %d\n",t++,ss.size());
    }

    return 0;
}
	

