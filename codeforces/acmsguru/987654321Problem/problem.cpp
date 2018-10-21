#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    for (long long i = 100000000; i < 1000000000; i++) {
        if (i*i % 1000000000 == 987654321) {
            cout << i << ' ' << i*i << '\n';
        }
    }
}
