#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int n;

vector<int> mod1, mod2;

void output(const vector<int>& A) {
    //check if not all zeros
    bool has1 = false;
    for (int i: A) {
        has1 |= i != 0;
    }
    if (!has1) {
        cout << 0 << '\n';
        return;
    }
    for (int i = A.size() - 1; i >= 0; i--) {
        cout << A[i];
    }
    cout << '\n';
}
    
int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    bool has0 = false;
    int sum = 0;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        has0 |= A[i] == 0;
        sum += A[i];
        if (A[i] % 3 == 1) mod1.push_back(A[i]);
        else if (A[i] % 3 == 2) mod2.push_back(A[i]);
    }
    sort(A.begin(),A.end());
    sort(mod1.begin(),mod1.end());
    sort(mod2.begin(),mod2.end());
    if (!has0) {
        cout << -1 << '\n';
        return 0;
    }
    if (sum % 3 == 0) {
        output(A);
    }
    else if (sum % 3 == 1) {
        if (!mod1.empty()) {
            auto pos = find(A.begin(),A.end(),mod1[0]);
            A.erase(pos);
        }
        else {
            auto pos1 = find(A.begin(),A.end(),mod2[0]);
            mod2.erase(mod2.begin());
            A.erase(pos1);
            auto pos2 = find(A.begin(),A.end(),mod2[0]);
            A.erase(pos2);
        }
        output(A);
    }
    else {
        if (!mod2.empty()) {
            auto pos = find(A.begin(),A.end(),mod2[0]);
            A.erase(pos);
        }
        else {
            auto pos1 = find(A.begin(),A.end(),mod1[0]);
            mod1.erase(mod1.begin());
            A.erase(pos1);
            auto pos2 = find(A.begin(),A.end(),mod1[0]);
            A.erase(pos2);
        }
        output(A);
    }
    

    return 0;
}
	

