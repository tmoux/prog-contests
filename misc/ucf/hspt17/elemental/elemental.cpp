#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool check(const string& s, const vector<string>& vs) {
    vector<bool> d(s.size());
    for (int i = 0; i < s.size(); i++) {
        for (string t: vs) {
            if (t.size() > i+1) continue;
            //cout << i << ' ' << t << ' ' << s.substr(i+1-t.size(),t.size()) << '\n';
            if (s.substr(i+1-(int)t.size(),t.size()) == t && (i+1-(int)t.size() == 0 || d[i-(int)t.size()])) {
                d[i] = true;
                break;
            }
        }
    }
    /*
    cout << s << '\n';
    for (int i = 0; i < s.size(); i++) {
        cout << i << ": " << d[i] << '\n';
    }
    */
    return d[s.size()-1];
}

int main()
{
    int c = 1;
    int n;
    while (true) {
        scanf("%d\n",&n);
        //cout << "n= " << n << '\n';
        if (!n) break;
        vector<string> vs;
        for (int i = 0; i < n; i++) {
            string ai; cin >> ai;
            vs.push_back(ai);
        }
        scanf("\n");
        string qs; getline(cin,qs);
        //cout << qs << '\n';
        vector<string> queries;
        stringstream ss(qs);
        string token;
        while (getline(ss,token,' ')) {
            queries.push_back(token);
        }
        bool poss = true;
        for (string a: queries) {
            poss &= check(a,vs);
        }
        printf("Phrase #%d: %s\n\n",c++,poss?"Elemental":"Not Elemental");    
    }

    return 0;
}

