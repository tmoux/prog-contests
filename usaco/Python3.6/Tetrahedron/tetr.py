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

        self.H2 = 1/16*(4*a**2*d**2-((b**2+e**2)-(c**2+f**2))**2)
        self.J2 = 1/16*(4*b**2*e**2-((c**2+f**2)-(a**2+d**2))**2)
        self.K2 = 1/16*(4*c**2*f**2-((a**2+d**2)-(b**2+e**2))**2)

        self.cosBC = (self.W**2+self.X**2-self.H2)/(2*self.W*self.X)
        self.cosAB = (self.W**2+self.Z**2-self.K2)/(2*self.W*self.Z)
        self.cosAC = (self.W**2+self.Y**2-self.J2)/(2*self.W*self.Y)
        self.cosOA = (self.Y**2+self.Z**2-self.H2)/(2*self.Y*self.Z)
        self.cosOB = (self.Z**2+self.X**2-self.J2)/(2*self.Z*self.X)
        self.cosOC = (self.X**2+self.Y**2-self.K2)/(2*self.X*self.Y)

        #print(self.cosBC,self.cosAB,self.cosAC)


        self.numBaseObtuse = 0
        for i in [self.cosBC,self.cosAB,self.cosAC]:
            if i < 0:
                self.numBaseObtuse += 1
        #print(self.numBaseObtuse)

        self.volume = sqrt(det([[0,a**2,b**2,c**2,1],
                          [a**2,0,f**2,e**2,1],
                           [b**2,f**2,0,d**2,1],
                           [c**2,e**2,d**2,0,1],
                           [1,1,1,1,0]])/288)

        self.height = self.volume*3/self.W
        

        if self.numBaseObtuse == 0:
            self.oVolume = self.volume*2/9
        elif self.numBaseObtuse == 1:
            if self.cosBC < 0:
                aprime = -1*((a*(d - e - f)*(d + e - f)*(d - e + f)*(d + e + f))/(2*a**2*d**2 + (c - e)*(c + e)*(-1*d + e)*(d + e) + (-1*c**2+ d**2 + 2*e**2)*f**2 - f**4 - b**2*(d**2 + e**2 - f**2)))
                self.oVolume = self.volume*2/9*aprime/a
            else:
                self.oVolume = Tetrahedron(b,c,a,e,f,d).oVolume
        elif self.numBaseObtuse == 2:
            if self.cosBC >= 0:
                aprime = sqrt((1-self.cosBC**2)*(d+e-f)**2*(d-e+f)**2*(-1*d+e+f)**2*(d+e+f)**2)/(2*self.cosBC*d*sqrt((d+e-f)*(d-e+f)*(-1*d+e+f)*(d+e+f)))
                self.oVolume = self.volume*2/9*aprime/self.height
            else:
                self.oVolume = Tetrahedron(b,c,a,e,f,d).oVolume

                

                
    def getoVolume(self):
        return self.oVolume
    def getaVolume(self):
        self.aVolume = Tetrahedron(self.e,self.f,self.a,self.b,self.c,self.d).oVolume
        return self.aVolume
    def getbVolume(self):
        self.bVolume = Tetrahedron(self.f,self.d,self.b,self.c,self.a,self.e).oVolume
        return self.bVolume
    def getcVolume(self):
        self.cVolume = Tetrahedron(self.d,self.e,self.c,self.a,self.b,self.f).oVolume
        return self.cVolume

    def fromPoints(O,A,B,C):
        a = dist(O,A)
        b = dist(O,B)
        c = dist(O,C)
        d = dist(B,C)
        e = dist(A,C)
        f = dist(A,B)
        return Tetrahedron(a,b,c,d,e,f)
    def printAll(self):
        print(self.getoVolume())
        print(self.getaVolume())
        print(self.getbVolume())
        print(self.getcVolume())
    def findMax(self):
        return max(self.getoVolume(),self.getaVolume(),self.getbVolume(),self.getcVolume())

    
                




#main
a = Tetrahedron(1.3,2,2,sqrt(2),1,1)
b = Tetrahedron.fromPoints((-1,-1,-1),(0,0,0),(1,0,0),(0,0,1))





       
        
