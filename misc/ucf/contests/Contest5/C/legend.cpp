#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

vector<pair<int,int>> probs;
double C;

bool isValid(int a) {
    double res = 1;
    for (int i = 0; i < probs.size(); i++) {
        res *= 1-pow(1-(double)probs[i].first/probs[i].second,a);
    }
    return res >= C;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    cin >> C;
    for (int i = 0; i < n; i++) {
        int p, q; cin >> p >> q;
        probs.push_back({p,q});
    }
    int lo = 0, hi = 1e9;
    while (lo + 5 < hi) {
        int mid = (lo + hi) / 2;
        if (isValid(mid)) {
            hi = mid;     
        }
        else {
            lo = mid;
        }
        //cout << mid << '\n';
    }
    while (!isValid(lo)) lo++;
    cout << lo << '\n';
    return 0;
}
	

