/*
ID: silxikys
PROG: picture
LANG: C++11
*/

#include <iostream>
#include <fstream>
#define MAX 10001

using namespace std;

typedef struct 
{
    int s,t,p;
    bool start;
}Line;

ifstream fi("picture.in");
ofstream fo("picture.out");

int N,ans=0;
int *level;
Line Lx[MAX],Ly[MAX];

inline int cmp(const void *a,const void *b)
{
    if (((Line*)a)->p==((Line*)b)->p)
    {
        if (((Line*)a)->start)
            return -1;
        else
            return 1;
    }
    return ((Line *)a)->p < ((Line *)b)->p ? -1 : 1;
}

void init()
{
    int i,x1,x2,y1,y2;
    fi >> N;
    for (i=1;i<=N;i++)
    {
        fi >> x1 >> y2 >> x2 >> y1;
        Lx[i*2-1].p=y1;
        Lx[i*2-1].s=x1;
        Lx[i*2-1].t=x2;
        Lx[i*2-1].start=false;
        Lx[i*2].p=y2;
        Lx[i*2].s=x1;
        Lx[i*2].t=x2;
        Lx[i*2].start=true;
        Ly[i*2-1].p=x1;
        Ly[i*2-1].s=y2;
        Ly[i*2-1].t=y1;
        Ly[i*2-1].start=true;
        Ly[i*2].p=x2;
        Ly[i*2].s=y2;
        Ly[i*2].t=y1;
        Ly[i*2].start=false;
    }
    N*=2;
    qsort(Lx+1,N,sizeof(Lx[0]),cmp);
    qsort(Ly+1,N,sizeof(Ly[0]),cmp);
    level=(int *)malloc(sizeof(int)*20002);
    level+=10000;
}

void Scan(Line *L)
{
    int i,j;
    for (i=-10000;i<=10000;i++)
        level[i]=0;
    for (i=1;i<=N;i++)
    {
        if (L[i].start)
        {
            for (j=L[i].s;j<L[i].t;j++)
            {
                level[j]++;
                if (level[j]==1)
                    ans++;
            }
        }
        else
        {
            for (j=L[i].s;j<L[i].t;j++)
            {
                level[j]--;
                if (level[j]==0)
                    ans++;
            }
        }
    }
}

void print()
{
    cout << ans << endl;
    fo << ans << endl;
    fi.close();
    fo.close();
}

int main()
{
    init();
    Scan(Lx);
    Scan(Ly);
    print();
    return 0;
}