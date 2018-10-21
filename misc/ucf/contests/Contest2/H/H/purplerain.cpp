#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int n = s.size();
    int A[100005];
    int B[100005];
    
    for (int i = 0; i < n; i++) {
        A[i+1] = 0;
        B[i+1] = 0;
        if (s[i] == 'B') A[i+1] = 1;
        else B[i+1] = 1;
        A[i+1] += A[i];
        B[i+1] += B[i];
    }

    int maxans = 0, l, r;
    for (int i = 1; i <= s.size(); i++) {
        for (int j = i; j <= s.size(); j++) {
            int numA = A[j] - A[i-1];
            int numB = B[j] - B[i-1];
            if (abs(numA-numB) > maxans) {
                maxans = abs(numA-numB);
                l = i;
                r = j;
            }
        }
    }

    cout << l << ' ' << r << '\n';


    return 0;
}
	

