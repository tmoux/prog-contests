#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> v1, v2;
bool check(int x, int a, int b) {
    if (x*(x+1)/2 > a+b) return false;
    vector<int> a1, b1;
    for (int i = x; i >= 1; i--) {
        if (a >= i) {
            a -= i;
            a1.push_back(i);
        }
        else if (b >= i) {
            b -= i;
            b1.push_back(i);
        }
        else {
            return false;
        }
    }
    v1 = a1;
    v2 = b1;
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b; 
    cin >> a >> b;
    int lo = 0, hi = 2*sqrt(a+b) + 5;
    while (lo + 1 < hi) {
        int mid = (lo+hi)>>1;
        if (check(mid,a,b)) {
            lo = mid;
        }
        else hi = mid;
    }
    //output
    cout << v1.size() << '\n';
    for (int i: v1) cout << i << ' ';
    cout << '\n';
    cout << v2.size() << '\n';
    for (int i: v2) cout << i << ' ';
    cout << '\n';

    return 0;
}

