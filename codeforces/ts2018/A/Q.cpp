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
    int perm[] = {1,2,3,4,5,6,7};
    int cc = 0;
    do {
        bool isValid = true;
        for (int i = 0; i < 7; i++) {
            int c2 = perm[perm[perm[i]]];
            int c3 = perm[c2];
            if (c2 == perm[i] || c3 == perm[i]) {
               isValid = false; 
            }
        }
        if (isValid) {
            cc++;
        }
        
        //for (int i = 0; i < 7; i++) {
            //cout << perm[i] << ' ';
        //}
        //cout << "valid: " << isValid << '\n';
       
    } while (next_permutation(perm,perm+7)); 
    cout << cc << '\n';

    return 0;
}
	

