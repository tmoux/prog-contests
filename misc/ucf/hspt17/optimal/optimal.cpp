#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool isPrime(int x) {
    if (x == 1) return false;
    for (int i = 2; i*i <= x; i++) {
        if (x%i==0) return false;
    }
    return true;
}

bool valid(const vector<int>& v) {
    int n = v.size();
    if (v[0] == 0) return false;
    int x = 0;
    int mult = 1;
    for (int i = n-1; i >= 0; i--) {
        x += mult*v[i];
        mult *= 10;
    }
    return isPrime(x);
}

int main()
{
    int t; scanf("%d\n",&t);
    for (int i = 1; i <= t; i++) {
        string s; cin >> s;
        vector<int> v;
        for (char c: s) {
            v.push_back(c-'0');
        }
        if (!valid(v)) {
            printf("Battle #%d: Oh no, the autobots are doomed!\n",i);
            continue;
        }
        sort(v.begin(),v.end());
        int cnt = 0;
        do {
            if (valid(v)) cnt++;
            if (cnt >= 2) break;
        } while (next_permutation(v.begin(),v.end()));
        if (cnt >= 2) {
            printf("Battle #%d: Autobots, roll out!\n",i);
        }
        else {
            printf("Battle #%d: Oh no, the autobots are doomed!\n",i);
        }
    }

    return 0;
}

