//This problem is divided into two main parts, being able to generate all permutations of a number, and checking if that number is prime.

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

#define MAX_VALUE 99999999

bool notprime[MAX_VALUE+1];
string start;


//A utility function, since it's easier to permute a string than it is to permute an int (in my experience), but checking if an int is prime is substantially easier.
int stringToInt(string s){
    int ans = 0;
    int i;
    for(i = 0; i < s.length(); i++){
        //Since this is in base 10, all that needs to be done is just raising all the digits to their appropriate power of 10.
        ans+= ((int)(s[i]-'0')) * pow(10,s.length() - i - 1);
    }
    return ans;
}

//This will generate all permutations, and then check if they are prime.
int subprimes(string cur, string remaining){
    int i;
    int ans = 0;
    //If all remaining characters are used up, then this is a number we want to check for primality.
    if(remaining==""){
        //This function actually doublecounts primes (like 11, where there exist two ways to write it), but since we just care if there is another prime, as long as we find a prime that isn't our starting prime we are good to go.
        if(start!=cur && !notprime[stringToInt(cur)]){
            return 1;
        }
        return 0;
    }
    //Permute by trying every possible character from remaining getting appended to our current string.
    for(i = 0; i < remaining.length(); i++){
        if(cur==""&&remaining[i]=='0')continue;
        string newcur = cur + remaining[i];
        string newremaining = "";
        int j;
        for(j = 0; j < remaining.length(); j++){
            if(j==i)continue;
            newremaining+=remaining[j];
        }
        ans += subprimes(newcur,newremaining);
    }
    return ans;
}
int main(){
    //This is what's known as the Seive of Eratosthenes. It lets us generate a primality check table for an entire range in O(N log N) time.
    notprime[0]=true;
    notprime[1]=true;
    int i;
    //The basic idea is try every possible value, and if that value is prime (i.e. it wasn't a multiple of any previous primes), mark all of it's multiples as non-prime
    for(i = 2; i <= MAX_VALUE; i++){
        if(notprime[i])continue;
        int j;
        for(j = i*2; j <= MAX_VALUE; j+=i){
            notprime[j]=true;
        }
    }
    //Now we just have to read in the input and check it using our previously created functions
    int b;
    cin >> b;
    for(i = 1; i <= b; i++){
        string cur;
        cin >> cur;
        start = cur;
        cout<<"Battle #"<<i<<": ";
        if(!notprime[stringToInt(cur)]&&subprimes("",cur)>0){
            cout<<"Autobots, roll out!";
        }else{
            cout<<"Oh no, the autobots are doomed!";
        }
        cout<<"\n";
    }
}
