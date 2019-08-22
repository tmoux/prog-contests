#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    vector<int> v1;
    for (int i = 0; i < 100; i++) {
        v1.push_back(i);
    }
    vector<int> v2;
    for (int i = 1; i <= 100; i++) {
        v2.push_back(i<<7);
    }

    cout << "? ";
    for (int i = 0; i < v1.size(); i++) {
        cout << v1[i];
        if (i < v1.size()-1) cout << ' '; 
    }
    cout << endl;
    int a1; cin >> a1;
    
    cout << "? ";
    for (int i = 0; i < v2.size(); i++) {
        cout << v2[i];
        if (i < v2.size()-1) cout << ' '; 
    }
    cout << endl;
    int a2; cin >> a2;
    
    assert(a1 != -1 && a2 != -1);
    int ans = 0;
    for (int i = 0; i < 7; i++) {
        if (a2&(1<<i)) ans += (1<<i);
    }
    for (int i = 7; i < 14; i++) {
        if (a1&(1<<i)) ans += (1<<i);
    }
    cout << "! " << ans << '\n';
}

