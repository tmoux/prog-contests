#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
//vowel cont, last vowel
map<pair<int,char>,string> mp;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    vector<pair<string,string>> pairs;
    map<int,vector<string>> extras;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        int idx = -1;
        int vowel = 0;
        for (int j = 0; j < s.size(); j++) {
            if (s[j] == 'a' ||
                s[j] == 'e' ||
                s[j] == 'i' ||
                s[j] == 'o' || 
                s[j] == 'u') {
                idx = j;
                vowel++;
            }
        }
        assert(idx != -1);
        if (pairs.size() * 2 + 2 > n/2) {
            extras[vowel].push_back(s);
        }
        else {
            if (mp.count(make_pair(vowel,s[idx]))) {
                pairs.push_back({s,mp[make_pair(vowel,s[idx])]});   
                auto it = mp.find(make_pair(vowel,s[idx]));
                mp.erase(it);
            }
            else {
                mp[make_pair(vowel,s[idx])] = s;
            }
        }
    }
    for (auto& p: mp) {
        extras[p.first.first].push_back(p.second);
    }
    for (auto& p: extras) {
        if (p.second.size() % 2 == 1) {
            p.second.pop_back();
        }
    }
    for (auto it = extras.begin(); it != extras.end();) {
        if (it->second.empty()) {
            extras.erase(it++);
        }
        else {
            ++it;
        }
    }
    /*
    for (auto p: pairs) {
        cout << p.first << ' ' << p.second << '\n';
    }
    cout << "extras:\n";
    for (auto& p: extras) {
        cout << p.first << '\n';
        for (auto s: p.second) {
            cout << s << ' ';
        }
        cout << '\n';
    }
    */
    int r = pairs.size();
    vector<vector<string>> ans;
    for (int i = 0; i < r; i++) {
        string a = pairs[i].first;
        string b = pairs[i].second;
        //try to look for extras
        if (!extras.empty()) {
            auto& p = *extras.begin();
            string c = p.second.back();
            p.second.pop_back();
            string d = p.second.back();
            p.second.pop_back();
            if (p.second.empty()) {
                extras.erase(extras.begin());
            }
            ans.push_back({c,a,d,b});
        }
        else {
            r--;
            if (r <= i) break;
            string c = pairs[r].first;
            string d = pairs[r].second;
            ans.push_back({c,a,d,b});
        }
    }

    //output
    cout << ans.size() << '\n';
    for (auto& p: ans) {
        cout << p[0] << ' ' << p[1] << '\n';
        cout << p[2] << ' ' << p[3] << '\n';
    }
}

