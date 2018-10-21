#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int n, k;
int cei(int a, int b) {
    return (a % b == 0 ? a/b : a/b+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    vector<pair<int,int>> res;
    int len = cei(n-1,k);
    int m = n-1, curr = 2;
    int numbig = 0;
    for (int i = k; i >= 1; i--) {
        int l;
        if (cei(m,i) != (len-1)) {
            l = len;
            numbig++;
        }
        else {
            l = len-1;
        }
        //cout << l << ' ' << m << '\n';
        m -= l;
        for (int j = 0; j < l; j++) {
            if (j == 0) {
                res.push_back({curr,1});
            }
            else {
                res.push_back({curr,curr-1});
            }
            curr++;
        }
    }

    if (numbig == 0) {
        cout << (2*(len-1)) << '\n';
    }
    else if (numbig == 1) {
        cout << (2*len-1) << '\n';
    }
    else {
        cout << (2*len) << '\n';
    }
    for (auto p: res) {
        cout << p.first << ' ' << p.second << '\n';
    }

    return 0;
}
	

