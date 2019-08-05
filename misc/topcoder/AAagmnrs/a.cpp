#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string reduce(const string& s) {
    vector<char> v;
    for (char c: s) {
        if (c == ' ') continue;
        v.push_back(tolower(c));
    }
    sort(v.begin(),v.end());
    string r;
    for (char c: v) {
        r += c;
    }
    return r;
}

class Aaagmnrs
{
public:
    vector<string> anagrams(vector<string> phrases) {
        set<string> seen;
        vector<string> ans;
        for (string& s: phrases) {
            string r = reduce(s);
            if (!seen.count(r)) {
                seen.insert(r);
                ans.push_back(s);
            }
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

}

