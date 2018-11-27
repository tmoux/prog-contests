#include <bits/stdc++.h>

using namespace std;

int main()
{
    int e; cin >> e;
    for(int env = 1; env <= e; env++)
    {
        int n; cin >> n;
        vector<int> lerpRooms(n);
        for(int i = 0; i < n; i++)cin >> lerpRooms[i];

        vector<int> preSum(n, lerpRooms[0]);
        for(int i = 1; i < n; i++) preSum[i] = lerpRooms[i] + preSum[i-1];

        int lerpPop = 0;
        lerpPop = preSum[n-1];
        int best = 2000000000;

        if(lerpPop % 2 == 0)
        {
            best = 0;
        }
        else
        {
            for(int i = 0; i < n; i++)
            {
                int numberOnLeft = (i? preSum[i-1]: 0);
                int numberOnRight = lerpPop - lerpRooms[i] - numberOnLeft;

                if(numberOnLeft % 2 == 0 and numberOnRight % 2 == 0)
                {
                    best = min(best, lerpRooms[i]);
                }
            }
        }

        printf("Environment #%d: %d lerps\n", env, lerpPop - best);
    }
    return 0;
}
