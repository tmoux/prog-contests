#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int n;

bool isPrime(int x) {
    for (int i = 2; i*i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

vector<pair<int,int>> ans;
int deg[maxn];
void addEdge(int a, int b) {
    ans.push_back({a,b});
    deg[a]++;
    deg[b]++;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<int> primes;
    for (int i = 2; i <= 3500; i++) {
        if (isPrime(i)) primes.push_back(i);
    }
    /*
    for (int i = 3; i <= 3000; i++) {
        auto it = lower_bound(primes.begin(),primes.end(),i);
        cout << i << ' ' << *it << endl;
        assert(*it <= i+i/2);
    }
    */
    int curr = n;
    for (int i = 1; i <= n; i++) {
        if (i < n) addEdge(i,i+1);
        else addEdge(i,1);
    }
    for (int j = 1; j <= n/2; j++) {
        if (isPrime(curr)) break;                    
        curr++;
        addEdge(j,j+n/2);
    }

    //output
    assert(isPrime(curr));
    for (int i = 1; i <= n; i++) {
        //cout << i << ": " << deg[i] << '\n';
        assert(isPrime(deg[i]));
    }
    cout << ans.size() << '\n';
    for (auto p: ans) {
        cout << p.first << ' ' << p.second << '\n';
    }
}

