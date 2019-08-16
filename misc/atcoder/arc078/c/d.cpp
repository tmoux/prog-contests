#include <bits/stdc++.h>
using namespace std;
using ll = long long;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    random_device device;
    mt19937 gen(device());
    uniform_int_distribution<int> dist(1,36);
    cout << dist(gen) << '\n';

}

