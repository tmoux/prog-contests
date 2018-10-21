#include <iostream>
using namespace std;

int main()
{
    long long n; cin >> n;
    long long ans;
    switch (n % 3) {
        case 0:
            ans = n/3*2;
            break;
        case 1:
            ans = (n-1)/3*2;
            break;
        case 2:
            ans = (n/3)*2+1;
            break;
    }
    cout << ans << '\n';
}
