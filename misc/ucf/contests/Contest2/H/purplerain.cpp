#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int A[maxn], n;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    n = s.size();
    for (int i = 0; i < n; i++) {
        if (s[i] == 'B') {
            A[i+1] = 1;
        }
        else {
            A[i+1] = -1;
        }
        A[i+1] += A[i];
    }

    int maxa = 0;
    vector<int> maxes;
    int mina = 999999999;
    vector<int> mins;
    for (int i = 0; i < n; i++) {
        if (A[i] > maxa) {
            maxa = A[i];
            maxes = {i};
        }
        else if (A[i] == maxa) {
            maxes.push_back(i);
        }
        if (A[i] < mina) {
            mina = A[i];
            mins = {i};
        }
        else if (A[i] == mina) {
            mins.push_back(i);
        }
    }

    int aa = min(maxes.front(),mins.front());
    int bb = max(maxes.front(),mins.front());
    cout << aa+1 << ' ' << bb << '\n';

    /*
    for (int i = 0; i < n; i++) {
        cout << i << ' ' << A[i] << '\n';
    }
    */

    return 0;
}
	

