#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct st
{
    string a;
    int id;
};
int n;

char ans[500];

bool check(const vector<st>& vs, string prefix, string suffix) {
    bool poss = true;
    for (int i = 2; i < vs.size(); i += 2) {
        int len = n - 1 - i/2;
        if (prefix.substr(0,len) == vs[i].a && suffix.substr(n-1-len) == vs[i+1].a) {
            ans[vs[i].id] = 'P';
            ans[vs[i+1].id] = 'S';        
        }
        else {
            bool is = prefix.substr(0,len) == vs[i+1].a && suffix.substr(n-1-len) == vs[i].a;
            if (!is) {
                poss = false;
                break;
            }
            ans[vs[i].id] = 'S';
            ans[vs[i+1].id] = 'P';
        }
    }
    return poss;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    string s(n,'0');
    vector<st> vs;
    for (int i = 0; i < 2*n-2; i++) {
        string a; cin >> a;
        vs.push_back({a,i});
    }
    sort(vs.begin(),vs.end(),[](auto& l, auto& r) {
            return l.a.size() > r.a.size();
    });
    ans[vs[0].id] = 'P';
    ans[vs[1].id] = 'S';
    if (check(vs,vs[0].a,vs[1].a)) {
        
    }
    else {
        ans[vs[1].id] = 'P';
        ans[vs[0].id] = 'S';
        assert(check(vs,vs[1].a,vs[0].a));
    }
    //output
    for (int i = 0; i < 2*n-2; i++) {
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}

