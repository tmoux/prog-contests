#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string core(string s) {
    string r;
    for (char c: s) {
        if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
            r += c;
        }
    }
    for (char& c: r) {
        c = tolower(c);
    }
    return r;
}

bool sim(string a, string b) {
    if (sim(b,a)) return true;
    if (a.size() == b.size() + 1) {
        //try deleting
        for (int i = 0; i < a.size(); i++) {
            string r = a;
            r.erase(r.begin()+i);
            if (r == b) return true;
        }
    }
    if (a.size() == b.size()) {
        int numdiff = 0;
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) numdiff;
        }
        if (numdiff <= 1) return true;
        
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);

}

