#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, a[maxn];
int b[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    int sum = 0;
    map<int,int> mp;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }
    //check if possible
    bool poss = false;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            if (--mp[a[i]] == 0) mp.erase(a[i]);
            ++mp[a[i]-1];
            if (mp.size() == n) {
                poss = true;
            }
            if (--mp[a[i]-1] == 0) mp.erase(a[i]-1);
            ++mp[a[i]];
        }
    }
    if (!poss) {
        cout << "cslnb" << '\n';
        return 0;
    }
    sort(a,a+n);
    b[0] = 0;
    for (int i = 1; i < n; i++) {
        b[i] = min(a[i],b[i-1]+1);
    }
    for (int i = 0; i < n; i++) {
        sum += (a[i]-b[i]+2)%2;
        sum %= 2;
    }
    cout << (sum == 1 ? "sjfnb" : "cslnb") << '\n';
}

