#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int dig[] = {1, 1, 2, 6, 4, 2, 2, 4, 2, 8}; 
  
int getd(int n) 
{ 
     if (n < 10) 
        return dig[n]; 
    // Check whether tens (or second last) digit 
    // is odd or even 
    // If n = 375, So n/10 = 37 and (n/10)%10 = 7 
    // Applying formula for even and odd cases. 
    if (((n/10)%10)%2 == 0) 
        return (6*getd(n/5)*dig[n%10]) % 10; 
    else
        return (4*getd(n/5)*dig[n%10]) % 10; 
} 

long long numd(int n) 
{ 
    // factorial of -ve number  
    // doesn't exists 
    if (n < 0) 
        return 0; 
  
    // base case 
    if (n <= 1) 
        return 1; 
  
    // Use Kamenetsky formula to calculate 
    // the number of digits 
    double x = ((n * log10(n / M_E) +  
                 log10(2 * M_PI * n) / 
                 2.0)); 
  
    return floor(x) + 1; 
} 

/*
int numd(int x) {
    long double d = 0.0;
    for (int i = 2; i <= x; i++) {
        d += log10(i);
    }
    return (int)(ceil(d));
}
*/

int c5(int x) {
    int res = 0;
    int add = x/5;
    while (add > 0) {
        res += add;
        add /= 5;
    }
    return res;
}

int main() {
    string n; cin >> n;
    int numZeros = 0;
    int digit;
    for (int i = n.size()-1; i >= 0; i--) {
        if (n[i] == '0') numZeros++;
        else {
            digit = n[i]-'0';
            break;
        }
    }
    /*
    cout << n.size() << "::\n";
    for (int x = 1; x <= 27; x++) {
        cout << numd(x) << '\n';
    }
    */
    for (int x = 1; x <= 1000000; x++) {
        //printf("%d: (%d,%d), (%d,%d)\n",x,getd(x),digit,numd(x), n.size());
        if (c5(x) == numZeros && getd(x) == digit && numd(x) == n.size()) {
            cout << x << '\n';
            return 0;
        }
    }
}

