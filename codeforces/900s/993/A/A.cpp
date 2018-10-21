#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

struct Vertex {
    int x, y;
};

int det(int a, int b, int c, int d) {
    return a*d-b*c;
}

struct Square {
    Vertex vs[4];    
    bool isIntersect(Vertex a1, a2, b1, b2) {
        //if ab intersects cd
        int a = a2.x-a1.x;
        int b = b2.x-b1.x;
        int c = b1.x-a1.x;
        int d = a2.y-a1.y;
        
    }
};

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    //then check if sides ever intersect
    //check if completely contained
    



    return 0;
}
	

