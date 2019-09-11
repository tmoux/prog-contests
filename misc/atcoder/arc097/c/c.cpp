#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s;
    int K; 
    cin >> s >> K;
    set<string> ss;
    for (int i = 0; i < s.size(); i++) {
        for (int j = 1; i+j <= s.size() && j <= K; j++) {
            string sub = s.substr(i,j);
            ss.insert(sub);            

            if (ss.size() > K) {
                ss.erase(prev(ss.end()));
            }
        }
    }

    string ans = *ss.rbegin();
    cout << ans << '\n';
}

