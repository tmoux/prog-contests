#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

bool valid(int b, int a) {
    return (b-1 <= a && a <= (2*(b+1)));
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int al, ar, bl, br;
    cin >> al >> ar >> bl >> br;
    cout << (valid(al,br) || valid(ar,bl) ? "YES" : "NO") << '\n';


    return 0;
}
	

