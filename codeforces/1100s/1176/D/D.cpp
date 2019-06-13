#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
const int maxx = 3e6+6;
int n, b[2*maxn];

bool composite[maxx];
int ord[maxx]; //ord of prime number
int num[maxx];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    multiset<int> bb;
    for (int i = 1; i <= 2*n; i++) {
        cin >> b[i];
        bb.insert(b[i]);
        num[b[i]]++;
    }
    int cnt = 1;
    for (int i = 2; i < maxx; i++) {
        if (composite[i]) continue;
        else {
            ord[i] = cnt++;
            for (int j = 2*i; j < maxx; j += i) {
                composite[j] = true;
            }
        }
    }
    vector<int> a;
    for (int r = 2750131; r >= 2;) {
        if (num[r] == 0) {
            r--;
            continue;
        }
        if (!composite[r]) {
            //prime
            int o = ord[r];
            a.push_back(o);
            assert(!composite[o] && num[o] > 0);
            num[o]--;
        }
        else {
            a.push_back(r);
            for (int i = 2; i*i <= r; i++) {
                if (r % i == 0) {
                    int o = r/i;
                    assert(num[o] > 0);
                    num[o]--;
                    break;
                }
            }
        }
        num[r]--;
    }
    for (int i: a) {
        cout << i << ' ';
    }
    cout << '\n';
}

