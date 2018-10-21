#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;
typedef long long ll;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int N; cin >> N;
    double total = 0;
    for (int i = 0; i < N; i++) {
        string s;
        double r, d;
        cin >> s >> r >> d;
        total += (double)d - (double)d/(double)r;
    }
    cout << fixed << setprecision(2) << total << '\n';

    return 0;
}
	

