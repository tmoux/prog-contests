#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int n, h;
int a[maxn];

int f(int i) {
    vector<int> b;
    for (int j = 0; j <= i; j++) b.push_back(a[j]);
    sort(b.begin(),b.end(),greater<int>());
    int ans = 0;
    int hh = h;
    /*
    for (int bb: b) {
        cout << bb << '\n';
    }
    */
    for (int i = 0; i < b.size(); i += 2) {
        if (i == b.size()-1) {
            if (b[i] <= hh) ans++;
        }
        else {
            if (hh >= max(b[i],b[i+1])) {
                hh -= max(b[i],b[i+1]);
                ans += 2;
            }
            else break;
        }
    }
    //cout << i << ": " << ans << '\n';
    if (ans == i+1) return ans;
    else return -1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> h;
    for (int i = 0; i < n; i++) cin >> a[i];
    int ans = 0;
    for (int i = 0; i < n; i++) ans = max(ans,f(i));
    cout << ans << '\n';
}

