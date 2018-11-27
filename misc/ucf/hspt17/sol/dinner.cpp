#include <iostream>
#include <string>

using namespace std;

#define MAX_VALUE 50

bool notprime[MAX_VALUE+10];

//Checks if a number is a perfect square. We know all the number that will be checked only go up to 50, so 7*7 is sufficiently high
bool perfect(int num){
    int i;
    for(i = 0; i < 8; i++){
        if(num==i*i)return true;
    }
    return false;
}

//Tests if a string matches the requirements
bool valid(string name){
    int ys=0;
    int vowels=0;
    int i = 0;
    //count vowels and ys
    for(i = 0; i < name.length(); i++){
        char c = tolower(name[i]);
        if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u')vowels++;
        if(c=='y')ys++;
    }
    //Only count pairs of ys, and odd numbers of ys are an immediate fail condition
    if(ys%2!=0)return false;
    vowels+=ys/2;
    //Both are perfect or the name being prime length with odd vowels are both acceptable.
    return (perfect(name.length()) && perfect(vowels)) || (!notprime[name.length()] && vowels%2!=0);
}

int main(){
    int i;
    //Seive of Eratosthenes, creates a prime table in O(N log N) time.
    notprime[0]=true;
    notprime[1]=true;
    //The general idea is that we can go through all values, and if they are prime (aren't a multiple of any previous prime), then we mark all their multiples as nonprimes.
    for(i = 2; i < MAX_VALUE+10; i++){
        if(notprime[i])continue;
        int j;
        for(j = 2*i; j < MAX_VALUE+10; j+=i){
            notprime[j]=true;
        }
    }
    //Read in input
    int testcases;
    cin >> testcases;
    int practice;
    string garbage;
    for(practice = 1; practice <= testcases; practice++){
        int count;
        cin >> count;
        //Have to be careful, there's still a newline character from reading in count, so we need to get rid of that
        getline(cin,garbage);

        string names[count];
        int numvalid = 0;
        cout<<"Practice #"<<practice<<": ";
        //Figure out how many are valid
        for(i = 0; i < count; i++){
            getline(cin,names[i]);
            if(valid(names[i])){
                numvalid++;
            }
        }
        if(numvalid==0){
            cout<<"It's hopeless!\n";
        }else{
            cout<<numvalid<<" valid options\n";
        }
        //Output all valid ones (in the case that there aren't any this won't have any effect, so that's fine)
        for(i = 0; i < count; i++){
            if(valid(names[i])){
                cout<<names[i]<<"\n";
            }
        }
        cout<<"\n";
    }
}