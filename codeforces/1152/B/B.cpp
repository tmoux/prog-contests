#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool ispow2(int x) {
    return x > 0 && (x & (x-1)) == 0;
}

vector<int> ans;
void FLIP(int& x) {
    bool seen1 = false;
    for (int i = 21; i >= 0; i--) {
        if (!seen1) {
            if (!(x & (1<<i))) continue;
            else seen1 = true;
        }
        else {
            if (!(x & (1<<i))) {
                //cout << bitset<20>(x) << ' ' << (i+1) << '\n';
                x ^= ((1<<(i+1))-1);
                //cout << bitset<20>(x) << '\n';
                ans.push_back(i+1);
                return;
            }
        }
    }
}

int sz = 0;
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int x; cin >> x;
    while (!ispow2(x+1)) {
        FLIP(x); sz++;
        if (ispow2(x+1)) break;
        x++; sz++;
        bitset<20> p(x);
        //cout << "x = " << p << '\n';
    }
    cout << sz << '\n';
    for (int i: ans) cout << i << '\n';
    

    return 0;
}

