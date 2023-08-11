#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    string s;
    getline(cin,s);
    s += ' ';
    vector<string> ans;
    string curr = "";
    bool inWord = false, inQuote = false;
    for (int i = 0; i < s.size(); i++) {
        if (inWord) {
            if ((s[i] == ' ' && !inQuote) ||
                (s[i] == '"' && inQuote)) {
                ans.push_back(curr);
                curr.clear();
                inWord = false;
                inQuote = false;
            }
            else {
                curr += s[i];
            }
        }
        else {
            if (s[i] == ' ') continue;
            else if (s[i] == '"') {
                inWord = true;
                inQuote = true;
            }
            else {
                inWord = true;
                inQuote = false;
                curr.clear();
                curr += s[i];
            }
        }
    }
    for (auto s: ans) {
        printf("<%s>\n",s.c_str());
    }
}

