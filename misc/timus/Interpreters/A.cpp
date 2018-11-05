#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<string> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    if (n == 1) {
        cout << 0 << '\n';
    }
    else if (n == 2) {
        if (v[0] == v[1]) {
            cout << 0 << '\n';
        }
        else {
            cout << 1 << '\n';
            printf("%s-%s\n",v[0].c_str(),v[1].c_str());
        }
    }
    else {
        bool allDiff = true;
        set<string> s;
        for (string f: v) {
            if (s.count(f)) allDiff = false;
            s.insert(f);
        }
        if (!allDiff) {
            cout << "Impossible\n";
        }
        else {
            cout << n << '\n';
            for (string f: v) {
                printf("%s-zqxwcevrbt\n",f.c_str());
            }
        }
    }

    return 0;
}

