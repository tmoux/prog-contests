/*
ID: silxikys
PROG: shuttle
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>
#include <array>
#include <chrono>
#include <math.h>
#include <deque>
#include <cstring>
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

int main() {
	t1 = gettime();
	ofstream fout("shuttle.out");
	ifstream fin("shuttle.in");

	int n,t,s,res[500],tt=0;
    memset(res,0,sizeof(res));
    fin>>n;
    for (int i=2;i<=n+1;i++)
    {
        if (i%2==1) t=-2;
        else t=2;
        if (i%2==1) s=n+i;
        else s=n-i+2;
        res[++tt]=s;
        for (int j=2;j<=i;j++)
        {
            s+=t;
            res[++tt]=s;
        }
    }
    for (int i=n;i>=2;i--)
    {
        if (i%2==1) t=-2;
        else t=2;
        if (i%2==1) s=n+i;
        else s=n-i+2;
        res[++tt]=s;
        for (int j=2;j<=i;j++)
        {
            s+=t;
            res[++tt]=s;
        }
    }
    res[++tt]=n+1;
    for (int i=1;i<=tt;i++)
    {
        fout<<res[i];
        if ((i%20==0)||(i==tt)) fout<<endl;
        else fout<<" ";
    }
	
	endProgram(t1);
	return 0;
}