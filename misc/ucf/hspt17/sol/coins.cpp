#include <bits/stdc++.h>

using namespace std;

int main()
{

    int t; cin >> t;
    for(int i = 0; i < t; i++)
    {

        int n, k; cin >> n >> k;
        string firstPlayer; cin >> firstPlayer;

        if (n % (k+1) != 0)
        {
            cout <<"Game #" << i+1 <<": "<< firstPlayer << endl;
        }
        else
        {
            cout <<"Game #" << i+1 << ": " << (firstPlayer == "Matthew"? "Bill":"Matthew") << endl;
        }

    }
    return 0;
}
