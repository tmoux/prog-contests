#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int k; cin >> k;
    int numChar = 0;
    for (char c: s) {
        if (c != '*' && c != '?') numChar++;
    }
    if (numChar == k) {
        //do nothing
        for (char c: s) {
            if (c != '*' && c != '?') cout << c;
        }
        cout << '\n';
        return 0;
    }
    else if (numChar < k) {
        string out;
        bool poss = false;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c != '*' && c != '?') out += c;
            else if (c == '?') continue;
            else {
                assert(c == '*');
                if (poss) continue;
                else {
                    poss = true;
                    for (int a = 0; a < k-numChar; a++) {
                        out += s[i-1];
                    }
                }
            }
        }
        if (poss) {
            cout << out << '\n';
        }
        else {
            cout << "Impossible\n";
        }
    }
    else {
        string out;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c != '*' && c != '?') out += c;
            else {
                if (numChar > k) {
                    out.pop_back();
                    numChar--;    
                }
            }
        }
        if (numChar == k) {
            cout << out << '\n';
        }
        else {
            cout << "Impossible\n";
        }
    }

    return 0;
}

