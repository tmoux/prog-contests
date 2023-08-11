#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
using namespace std;
typedef long long ll;

int dcount[11];
bool isValid(ll n) {
    while (n) {
        dcount[n % 10]++;
        n /= 10;
    }
    return (dcount[0] >= 2 || (dcount[2] >= 1 && dcount[5] >= 1) || (dcount[5] >= 1 && dcount[0] >= 1) || (dcount[7] >= 1 && dcount[5] >= 1));
}

int ndigits(ll i) {
    return i > 0 ? (int) log((double) i) + 1: 1;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    ofstream fout("fout.txt");
    ll n; cin >> n;
    if (isValid(n)) {
        queue<pair<int,ll>> q;
        q.push({0,n});
        while (!q.empty()) {
            auto p = q.front();
            cout << p.first << ' ' << p.second << '\n';
            //fout << p.first << ' ' << p.second << '\n';
            if (p.second % 25 == 0) {
                cout << p.first << '\n';
                return 0;
            }
            ll m1 = 1, m2 = 10;
            while (n/m2 != 0) {
                ll asd = p.second;
                int d1 = ((asd/m1) % 10);
                int d2 = ((asd/m2) % 10);
                asd -= d1*m1;
                asd -= d2*m2;
                asd += d2*m1;
                asd += d1*m2;
                pair<int,ll> nxt = {p.first+1,asd};
                if (d1 != 0 || n/(m2*10) != 0 && d1 != d2) {

                    q.push(nxt);
                }
                m1 *= 10;
                m2 *= 10;
            }
            q.pop();
        }
    }
    else {
        cout << "-1\n";
    }


    return 0;
}
	

