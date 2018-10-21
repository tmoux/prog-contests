import math
from math import sqrt

def det(l):
    n=len(l)
    if (n>2):
        i=1
        t=0
        sum=0
        while t<=n-1:
            d={}
            t1=1
            while t1<=n-1:
                m=0
                d[t1]=[]
                while m<=n-1:
                    if (m==t):
                        u=0
                    else:
                        d[t1].append(l[t1][m])
                    m+=1
                t1+=1
            l1=[d[x] for x in d]
            sum=sum+i*(l[0][t])*(det(l1))
            i=i*(-1)
            t+=1
        return sum
    else:
        return (l[0][0]*l[1][1]-l[0][1]*l[1][0])

def heron(a,b,c):
    s = (a+b+c)/2
    return sqrt(abs(s*(s-a)*(s-b)*(s-c)))

def dist(a,b): #a and b are tuples of variable length
    assert len(a) == len(b)
    return sqrt(sum((a[i]-b[i])**2 for i in range(len(a))))

class Tetrahedron:
    def __init__(self,a,b,c,d,e,f):
        self.a = a
        self.b = b
        self.c = c
        self.d = d
        self.e = e
        self.f = f

        self.W = heron(d,e,f)
        self.X = heron(b,d,c)
        self.Y = heron(a,c,e)
        self.Z = heron(a,b,f)


        self.volume = sqrt(det([[0,a**2,b**2,c**2,1],
                          [a**2,0,f**2,e**2,1],
                           [b**2,f**2,0,d**2,1],
                           [c**2,e**2,d**2,0,1],
                           [1,1,1,1,0]])/288)

        self.height = self.volume*3/self.W

class Triangle:
    def __init__(self,a,b,c):
        self.a = a
        self.b = b
        self.c = c
        self.area = heron(a,b,c)
        self.heightA = 2*self.area/a
        self.heightB = 2*self.area/b
        self.heightC = 2*self.area/c
        self.squareA = 2*self.area/(a+self.heightA)
        self.squareB = 2*self.area/(b+self.heightB)
        self.squareC = 2*self.area/(c+self.heightC)
        self.ideal = sqrt(2*self.area)

        
