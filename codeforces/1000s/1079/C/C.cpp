#include <bits/stdc++.h>

using namespace std;

int arr[100000];
bool can[100000][5];
int pre[100000][5];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    for (int i = 0; i < 5; ++i)
        can[0][i] = 1;
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] == arr[i - 1])
        {
            for (int j = 0; j < 5; ++j)
            {
                for (int k = 0; k < 5; ++k)
                {
                    if (k != j)
                    {
                        if (can[i - 1][k])
                        {
                            can[i][j] = 1;
                            pre[i][j] = k;
                            break;
                        }
                    }
                }
            }
        }
        else if (arr[i] > arr[i - 1])
        {
            for (int j = 0; j < 5; ++j)
            {
                for (int k = 0; k < j; ++k)
                {
                    if (can[i - 1][k])
                    {
                        can[i][j] = 1;
                        pre[i][j] = k;
                        break;
                    }
                }
            }
        }
        else
        {
            for (int j = 0; j < 5; ++j)
            {
                for (int k = j + 1; k < 5; ++k)
                {
                    if (can[i - 1][k])
                    {
                        can[i][j] = 1;
                        pre[i][j] = k;
                    }
                }
            }
        }
    }
    int me = -1;
    for (int i = 0; i < 5; ++i)
    {
        if (can[n - 1][i])
        {
            me = i;
            break;
        }
    }
    if (me == -1)
    {
        cout << -1;
        exit(0);
    }
    stack<int> ans;
    while (n)
    {
        ans.push(me);
        n--;
        me = pre[n][me];
    }
    while (ans.size())
    {
        cout << ans.top() + 1 << " ";
        ans.pop();
    }
}
