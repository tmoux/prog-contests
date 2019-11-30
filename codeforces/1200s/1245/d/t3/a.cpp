#include <iostream>
#include <unordered_map>
#include <map>
using namespace std;

int main()
{
    map<int,int> mp;
    mp[5] = 6;
    mp[5] = 7;
    mp[0] = 3;
    mp[3] = 3;
    cout << mp[5] << ' ' << mp[-1] << '\n';
    if (mp.count(0)) {
        cout << "found it" << '\n';
    }
    for (auto p: mp) {
        cout << p.first << ' ' << p.second << '\n';
    }
    pair<int,int> p = *mp.begin();
    cout << p.first << ' ' << p.second << '\n';
}
