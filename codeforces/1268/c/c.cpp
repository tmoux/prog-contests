#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//remember long longs dammit!

const int maxn = 2e5+5;
int bit[maxn]; //pos of active numbers
int n, p[maxn];

void add(int i, int x) {
    for (; i <= n; i += i & (-i))
        bit[i] += x;
}

int sum(int i) {
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

int pos[maxn];
ll ans[maxn];

//f(k) = # inversions 1..k
//       + # moves needed to squeeze all k numbers together

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        pos[p[i]] = i;
    }
    add(pos[1],1);
    ll gap = 0, inv = 0;
    int median = pos[1];
    for (int i = 2; i <= n; i++) {
        //update inversions
        inv += i-1-sum(pos[i]);
        add(pos[i],1);
        if (i&1) {
            //update median and gap
            int lo = 0, hi = n;
            while (lo + 1 < hi) {
                int mid = (lo+hi)/2;
                if (sum(mid) >= (i+1)/2) {
                    hi = mid;
                }
                else lo = mid;
            }
            median = hi;
        }

        if (pos[i] <= median) {
            gap -= sum(pos[i]-1);
        }
        else {
            gap -= i-sum(pos[i]);
        }

		int place = sum(pos[i]);
		int target = median+place-sum(median);
		gap += abs(pos[i]-target);

        /*
        cout << "adding " << abs(pos[i]-target) << endl;
        cout << i << ": " << median << endl;
        cout << "gap = " << gap << endl;
        cout << "inv = " << inv << endl;
        */
        ans[i] = gap + inv;
    }
    //output
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}
