#include <stdlib.h>
#include <stdio.h>

int main(void) {
    // intitialize our variables
    long t, x, y, ans;
    
    // read in the number of test cases
    scanf("%ld", &t);
    
    // loop through each test case
    for(int i = 0; i < t; i++) {
        // read in the two numbers we want to multiply
        scanf("%ld %ld", &x, &y);
        
        // multiply these two numbers and store the result in ans
        ans = x * y;
        
        // print out our answer
        printf("%ld\n", ans);
    }
    
    return 0;
}
