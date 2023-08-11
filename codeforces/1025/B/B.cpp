#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void getPrime(int i, set<int>& ps) {
    if (i == 1) return;
    for (int j = 2; j*j <= i; j++) {
        if (i % j == 0) {
            while (i % j == 0) {
                i /= j;
            }
            ps.insert(j);
            getPrime(i,ps);
            return;
        }
    }
    ps.insert(i);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<pair<int,int>> as;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        as.push_back({a,b});
    }

    set<int> p1;
    getPrime(as[0].first,p1);
    for (int i = 1; i < n; i++) {
        set<int> removes;
        for (int j: p1) {
            if (as[i].first % j == 0 || as[i].second % j == 0) {

            }
            else {
                removes.insert(j);
            }
        }
        for (int j: removes) {
            p1.erase(j);
        }
    }

    set<int> p2;
    getPrime(as[0].second,p2);
    for (int i = 1; i < n; i++) {
        set<int> removes;
        for (int j: p2) {
            if (as[i].first % j == 0 || as[i].second % j == 0) {

            }
            else {
                removes.insert(j);
            }
        }
        for (int j: removes) {
            p2.erase(j);
        }
    }

    if (p1.size() > 0) {
        cout << (*p1.begin()) << '\n';
    }
    else if (p2.size() > 0) {
        cout << (*p2.begin()) << '\n';
    }
    else {
        cout << -1 << '\n';
    }
    

    return 0;
}
	

