#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int n, k;
void print(int n, int k) {
    cout << '.';
    for (int i = 0; i < k; i++) {
        cout << '#';
    }
    for (int i = 0; i < n-k-1; i++) {
        cout << '.';
    }
    cout << '\n';
}
void printn(int n, char c) {
    for (int i = 0; i < n; i++) {
        cout << c;
    }
}
int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    if (k % 2 == 0) {
      cout << "YES\n";
      print(n,0);
      print(n,k/2);
      print(n,k/2);
      print(n,0);
    }
    else if (k == n-2) {
        cout << "YES\n";
        print(n,0);
        print(n,k);
        print(n,0);
        print(n,0);
    }
    else {
        cout << "YES\n";
        print(n,0);
        if (k >= n-2) {
            print(n,n-2);
            int numLeft = k % (n-2);
            printn(1,'.');
            printn(numLeft-1,'#');
            printn(n-2-numLeft,'.');
            printn(1,'#');
            printn(1,'.');
            cout << '\n';
            print(n,0);
        }
        else {
            print(n,0);
            int numleft = k % (n-2);
            int sides = (n-numleft)/2;
            printn(sides,'.');
            printn(numleft,'#');
            printn(sides,'.');
            cout << '\n';
            print(n,0);
        }
    }


    return 0;
}
	

