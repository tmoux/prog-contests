#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string text="CBAEB CCADD CCCAC AEBEE CCAEE BCACB DCBBC CDEAC CCCBC BECCD DCDBE ECBDC CCDBC ABEAC CCCBA EEBCB ECDCB EAEEB DACCC CDBDC BEEEA EBCDB CEDCA CDDEB CBBCD CDBCB DCAEE BDACC EBACC CEBCA DCDBE BBBCD CCEDA EEBDB EDCEE BCBEB CABEE DEDCC CACAC EBECD EDACE CDECB EBDBE BCDEC CABCC AAAAA";
    std::string::iterator end_pos = std::remove(text.begin(), text.end(), ' ');
    text.erase(end_pos, text.end());
    cout << text << '\n';
    cout << text.size() << '\n';
    string s2;
    for (int i = 0; i < text.size(); i += 2) {
        int a = text[i]-'A';
        int b = text[i+1]-'A';
        int c = a*5+b;
        cout << (char)(c+'A');
        s2 += (char)(c+'A');
    }
    cout << '\n';
    map<char,int> cnt;
    for (char c: s2) {
        cnt[c]++;
    }
    vector<pair<int,char>> vs;
    for (auto p: cnt) vs.push_back({p.second,p.first});
    sort(vs.begin(),vs.end());
    for (auto p: vs) {
        cout << p.first << ": " << p.second << '\n';
    }

    return 0;
}

