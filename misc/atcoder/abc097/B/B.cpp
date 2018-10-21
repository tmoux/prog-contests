#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;

vector<int> perfects = {1};

void getPerfects() {
    for (int i = 2; i < 33; i++) {
        int ii = i*i;
        while (ii <= 1000) {
            perfects.push_back(ii);
            ii *= i;
        }
    }
    sort(perfects.begin(),perfects.end());
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int X; cin >> X;
    getPerfects();
    auto it = upper_bound(perfects.begin(),perfects.end(),X);
    it--;
    cout << *it << '\n';

    return 0;
}
	

