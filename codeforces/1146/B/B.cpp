#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    string t; cin >> t;
    string ta = "";
    for (char c: t) {
        if (c != 'a') ta += c;
    }
    if (ta == "") {
        cout << t << '\n';
        return 0;
    }
    //cout << ta << '\n';
        
    if (ta.size() % 2 == 0 && ta.substr(0,ta.size()/2) == ta.substr(ta.size()/2) && ta.substr(0,ta.size()/2) == t.substr(t.size()-(ta.size()/2))) {
        cout << t.substr(0,t.size()-ta.size()/2) << '\n';        
    }
    else {
        cout << ":(\n";    
    }
}

