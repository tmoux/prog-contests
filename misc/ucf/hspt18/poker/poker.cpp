#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<string,int> mp = {{"Straight flush",0},{"Four of a kind",1},{"Full house",2},{"Flush",3},{"Straight",4},{"Three of a kind",5},{"Two pair",6},{"Pair",7},{"High card",8}};

int main()
{
    int g; cin >> g;
    string thr;
    getline(cin,thr);
    for (int a = 1; a <= g; a++) {
        string ryan; getline(cin,ryan);
        string tyler; getline(cin,tyler);
        /*
        cout << ryan;
        cout << tyler;
        */
        int r = mp[ryan], t = mp[tyler];
        /*
        cout << "ryan = " <<  ryan << ' ' << r << '\n';
        cout << "tyler = " << tyler << ' ' << t << '\n';
        */
        printf("Game #%d: %s\n",a,(r<t?"Ryan":"Tyler"));
    }

    return 0;
}

