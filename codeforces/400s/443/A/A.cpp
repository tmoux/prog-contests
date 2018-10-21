#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    set<char> c;
    string s; getline(cin,s);
    for (int i = 0; i < s.size(); i++) if ('a' <= s[i] && s[i] <= 'z') {
        c.insert(s[i]);
    }
    cout << c.size() << '\n';

    return 0;
}
	

