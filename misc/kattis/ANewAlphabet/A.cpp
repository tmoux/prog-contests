#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    map<char,string> mp;
    mp['a'] = "@";
    mp['b'] = "8";
    mp['c'] = "(";
    mp['d'] = "|)";
    mp['e'] = "3";
    mp['f'] = "#";
    mp['g'] = "6";
    mp['h'] = "[-]";
    mp['i'] = "|";
    mp['j'] = "_|";
    mp['k'] = "|<";
    mp['l'] = "1";
    mp['m'] = "[]\\/[]";
    mp['n'] = "[]\\[]";
    mp['o'] = "0";
    mp['p'] = "|D";
    mp['q'] = "(,)";
    mp['r'] = "|Z";
    mp['s'] = "$";
    mp['t'] = "']['";
    mp['u'] = "|_|";
    mp['v'] = "\\/";
    mp['w'] = "\\/\\/";
    mp['x'] = "}{";
    mp['y'] = "`/";
    mp['z'] = "2";
    string s; getline(cin,s);
    string out;
    for (char c: s) {
        if (mp.count(tolower(c)))
            out += mp[tolower(c)];
        else out += c;
    }
    cout << out << '\n';

    return 0;
}

