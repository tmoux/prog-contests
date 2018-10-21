#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;

map<string,string> mp = {{"purple","Power"},{"green","Time"},{"blue","Space"},{"orange","Soul"},{"red","Reality"},{"yellow","Mind"}};

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        mp.erase(mp.find(s));
    }
    cout << mp.size() << '\n';
    for (auto p: mp) {
        cout << p.second << '\n';
    }


    return 0;
}
	

